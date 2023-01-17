/*****************************************************************************
*
* x86-call.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "x86-call.h"

#include "build-params.h"
#include "encode-data.h"

#include "x86-register-op.h"
#include "x86-memory-op.h"
#include "x86-immediate-op.h"

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

	encodeData->operandPlace[0] = OperandPlace::rm_field;

	return Ceng::CE_OK;
}

const Ceng::CRESULT CallInstruction::Encode_AbsoluteNear_M(BuildParams *params,EncodeData *encodeData,
														   const MemoryOperand *memoryOp) const
{
	encodeData->opcode = opcode_absolute;

	encodeData->modRM.SetRegField(2);

	encodeData->operandPlace[0] = OperandPlace::rm_field;

	return Ceng::CE_OK;
}

const Ceng::CRESULT CallInstruction::Encode_Relative(BuildParams *params,EncodeData *encodeData,
													 const ImmediateOperand *immediate) const
{
	encodeData->opcode = opcode_relative;

	encodeData->immEncoding = params->mode->defaultOpSize;

	encodeData->operandPlace[0] = OperandPlace::imm;

	params->imm_symbolRefType = Casm::REFERENCE_TYPE::IP_RELATIVE;

	return Ceng::CE_OK;
}