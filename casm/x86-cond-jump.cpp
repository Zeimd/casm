/*****************************************************************************
*
* x86-cond-jump.cpp
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#include "x86-cond-jump.h"

#include "build-params.h"
#include "encode-data.h"

#include "x86-immediate-op.h"

using namespace X86;

const Ceng::CRESULT CondJumpInstruction::SelectOpcode(BuildParams *params,EncodeData *encodeData,
													  const Operand *operand) const
{
	if (operand->IsImmediateOperand())
	{
		return Select_I(params,encodeData,(ImmediateOperand*)operand);
	}
	
	return Ceng::CE_ERR_INVALID_PARAM;
}


const Ceng::CRESULT CondJumpInstruction::Select_I(BuildParams *params,EncodeData *encodeData,
												  const ImmediateOperand *immediate) const
{

	if (immediate->Size() == X86::OPERAND_SIZE::BYTE)
	{
		encodeData->opcode = opcode_imm8;

		encodeData->operandPlace[0] = OperandPlace::imm;
		encodeData->immEncoding = X86::OPERAND_SIZE::BYTE;
	}
	else
	{
		if (opcode_imm32 == 0x00)
		{
			return Ceng::CE_ERR_INVALID_PARAM;
		}

		encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
		encodeData->opcode = opcode_imm32;

		encodeData->operandPlace[0] = OperandPlace::imm;
		encodeData->immEncoding = params->mode->defaultOpSize;
	}

	return Ceng::CE_OK;
}