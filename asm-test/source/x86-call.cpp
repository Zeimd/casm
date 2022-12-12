/*****************************************************************************
*
* x86-call.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-call.h"
#include "../include/symbol-ref.h"

#include "../include/build-params.h"
#include "../include/encode-data.h"

#include "../include/x86-register-op.h"
#include "../include/x86-memory-op.h"
#include "../include/x86-immediate-op.h"

using namespace X86;

CallInstruction::CallInstruction()
{
}

CallInstruction::~CallInstruction()
{
}

const Ceng::CRESULT CallInstruction::SelectOpcode(BuildParams *params,EncodeData *encodeData,
												  const Operand *operand) const
{
	if (operand->IsRegisterOperand())
	{
		return Encode_AbsoluteNear_R(params,encodeData,(RegisterOperand*)operand);
	}

	if (operand->IsMemoryOperand())
	{
		return Encode_AbsoluteNear_M(params,encodeData,(MemoryOperand*)operand);
	}

	if (operand->IsImmediateOperand())
	{
		return Encode_Relative(params,encodeData,(ImmediateOperand*)operand);
	}

	return Ceng::CE_ERR_INVALID_PARAM;
}

const Ceng::CRESULT CallInstruction::Encode_AbsoluteNear_R(BuildParams *params,EncodeData *encodeData,
														   const RegisterOperand *registerOp) const
{
	encodeData->opcode = opcode_absolute;

	encodeData->modRM.SetRegField(2);

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;

	return Ceng::CE_OK;
}

const Ceng::CRESULT CallInstruction::Encode_AbsoluteNear_M(BuildParams *params,EncodeData *encodeData,
														   const MemoryOperand *memoryOp) const
{
	encodeData->opcode = opcode_absolute;

	encodeData->modRM.SetRegField(2);

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;

	return Ceng::CE_OK;
}

const Ceng::CRESULT CallInstruction::Encode_Relative(BuildParams *params,EncodeData *encodeData,
													 const ImmediateOperand *immediate) const
{
	encodeData->opcode = opcode_relative;

	encodeData->immEncoding = params->mode->defaultOpSize;

	encodeData->operandPlace[0] = OPERAND_PLACE::IMM;

	//params->imm_symbolRefType = REFERENCE_TYPE::IP_RELATIVE;

	return Ceng::CE_OK;
}