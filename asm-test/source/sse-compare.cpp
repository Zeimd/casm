/*****************************************************************************
*
* sse-compare.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/sse-compare.h"

#include "../include/x86-register-op.h"
#include "../include/x86-memory-op.h"

#include "../include/build-params.h"
#include "../include/encode-data.h"

using namespace X86;

const Ceng::CRESULT SSE_Compare::SelectOpcode(BuildParams *params,EncodeData *encodeData,
											  const Operand *dest,const Operand *source) const
{
	if (dest->IsRegisterOperand() && source->IsRegisterOperand())
	{
		return Select_R_R(params,encodeData,(RegisterOperand*)dest,(RegisterOperand*)source);
	}

	if (dest->IsRegisterOperand() && source->IsMemoryOperand())
	{
		return Select_R_M(params,encodeData,(RegisterOperand*)dest,(MemoryOperand*)source);
	}

	return Ceng::CE_ERR_INVALID_PARAM;
}

const Ceng::CRESULT SSE_Compare::Select_R_R(BuildParams *params,EncodeData *encodeData,
											const RegisterOperand *dest,
											const RegisterOperand *source) const
{
	if ( !ValidateRegister(params,dest))
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if ( !ValidateRegister(params,source))
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
	encodeData->opcode = opcode;
	
	encodeData->operandPlace[0] = OPERAND_PLACE::REG_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::RM_FIELD;

	// Comparison type to immediate operand

	encodeData->hasImmediate = true;
	encodeData->immEncoding = OPERAND_SIZE::BYTE;
	
	encodeData->immediate = comparisonType;
	
	return Ceng::CE_OK;
}

const Ceng::CRESULT SSE_Compare::Select_R_M(BuildParams *params,EncodeData *encodeData,
											const RegisterOperand *dest,
											const MemoryOperand *source) const
{
	if ( !ValidateRegister(params,dest))
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
	encodeData->opcode = opcode;
	
	encodeData->operandPlace[0] = OPERAND_PLACE::REG_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::RM_FIELD;

	// Comparison type to immediate operand

	encodeData->hasImmediate = true;
	encodeData->immEncoding = OPERAND_SIZE::BYTE;
	
	encodeData->immediate = comparisonType;

	return Ceng::CE_OK;
}