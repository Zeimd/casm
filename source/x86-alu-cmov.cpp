/*****************************************************************************
*
* x86-alu-cmov.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-alu-cmov.h"

#include "../include/encode-data.h"

#include "../include/enums/x86-register-types.h"

#include "../include/x86-register-op.h"
#include "../include/x86-memory-op.h"

using namespace X86;

ConditionalMove::ConditionalMove(const Ceng::UINT8 opcode) : opcode(opcode)
{
}

ConditionalMove::~ConditionalMove()
{
}

const Ceng::CRESULT ConditionalMove::SelectOpcode(BuildParams *params,
												  EncodeData *encodeData,const Operand *dest,
												  const Operand *source) const
{
	if (dest->IsRegisterOperand() == false)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (source->IsRegisterOperand())
	{
		return Select_R_R(params,encodeData,
								static_cast<const RegisterOperand*>(dest),
								static_cast<const RegisterOperand*>(source));
	}

	if (source->IsRegisterOperand())
	{
		return Select_R_M(params,encodeData,
								static_cast<const RegisterOperand*>(dest),
								static_cast<const MemoryOperand*>(source));
	}

	return Ceng::CE_ERR_INVALID_PARAM;
}

const Ceng::CRESULT ConditionalMove::Select_R_R(BuildParams *params,
												EncodeData *encodeData,const RegisterOperand *dest,
												const RegisterOperand *source) const
{
	if ( !(dest->RegisterFiles() & source->RegisterFiles()) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	return Config(params,encodeData,dest);
}

const Ceng::CRESULT ConditionalMove::Select_R_M(BuildParams *params,
												EncodeData *encodeData,const RegisterOperand *dest,
												const MemoryOperand *source) const
{
	return Config(params,encodeData,dest);
}

const Ceng::CRESULT ConditionalMove::Config(BuildParams *params,EncodeData *encodeData,
											const RegisterOperand *dest) const
{
	if ( !(dest->RegisterFiles() & REGISTER_FILE::ALU) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (dest->Size() == OPERAND_SIZE::BYTE)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
	encodeData->opcode = opcode;

	EncodeOperandSize(params,encodeData,dest->Size());

	encodeData->operandPlace[0] = OPERAND_PLACE::REG_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::RM_FIELD;

	return Ceng::CE_OK;
}