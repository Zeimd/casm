/*****************************************************************************
*
* x86-move.cpp
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#include "../include/x86-move.h"
#include "../include/build-params.h"

#include "../include/encode-data.h"

#include "../include/x86-register-op.h"
#include "../include/x86-memory-op.h"
#include "../include/x86-immediate-op.h"

using namespace X86;

MoveInstruction::MoveInstruction()
{
}

MoveInstruction::~MoveInstruction()
{
}

const Ceng::CRESULT MoveInstruction::SelectOpcode(BuildParams *params,
												  EncodeData *encodeData,const Operand *dest,
												  const Operand *source) const
{
	if (dest->IsRegisterOperand() && source->IsRegisterOperand())
	{
		return Standard_R_R(params,encodeData,
							opcode_rm8_r8,opcode_rm32_r32,
							static_cast<const RegisterOperand*>(dest),
							static_cast<const RegisterOperand*>(source));
	}

	if (dest->IsMemoryOperand() && source->IsRegisterOperand())
	{
		return Standard_M_R(params,encodeData,
							opcode_rm8_r8,opcode_rm32_r32,
							static_cast<const MemoryOperand*>(dest),
							static_cast<const RegisterOperand*>(source));
	}

	if (dest->IsRegisterOperand() && source->IsMemoryOperand())
	{
		return Standard_R_M(params,encodeData,
							opcode_r8_rm8,opcode_r32_rm32,
							static_cast<const RegisterOperand*>(dest),
							static_cast<const MemoryOperand*>(source));
	}

	if (dest->IsRegisterOperand() && source->IsImmediateOperand())
	{
		return Select_R_I(params,encodeData,
							static_cast<const RegisterOperand*>(dest),
							static_cast<const ImmediateOperand*>(source));
	}

	if (dest->IsMemoryOperand() && source->IsImmediateOperand())
	{
		return Select_M_I(params,encodeData,
							static_cast<const MemoryOperand*>(dest),
							static_cast<const ImmediateOperand*>(source));
	}

	return Ceng::CE_ERR_INVALID_PARAM;
}

const Ceng::CRESULT MoveInstruction::Select_R_I(BuildParams *params,
												EncodeData *encodeData,const RegisterOperand *dest,
												const ImmediateOperand *source) const
{
	if (ValidateRegisterOp(params,dest) == false)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (dest->Size() < source->Size())
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->operandPlace[0] = OPERAND_PLACE::OPCODE;
	encodeData->operandPlace[1] = OPERAND_PLACE::IMM;

	OPERAND_SIZE::value opSize = dest->Size();

	EncodeOperandSize(params,encodeData,opSize);

	if (opSize == OPERAND_SIZE::BYTE)
	{
		encodeData->opcode = opcode_r8_imm8;
	}
	else
	{
		encodeData->opcode = opcode_r32_imm32;
	}

	encodeData->immEncoding = opSize;

	return Ceng::CE_OK;
}

const Ceng::CRESULT MoveInstruction::Select_M_I(BuildParams *params,
												EncodeData *encodeData,const MemoryOperand *dest,
												const ImmediateOperand *source) const
{
	OPERAND_SIZE::value opSize = dest->Size();

	if (dest->Size() == OPERAND_SIZE::IMPLICIT)
	{
		if (source->Size() == OPERAND_SIZE::IMPLICIT)
		{
			return Ceng::CE_ERR_INVALID_PARAM;
		}

		opSize = source->Size();
	}

	if (dest->Size() != OPERAND_SIZE::IMPLICIT && source->Size() != OPERAND_SIZE::IMPLICIT)
	{
		if (dest->Size() < source->Size())
		{
			return Ceng::CE_ERR_INVALID_PARAM;
		}
	}

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::IMM;

	EncodeOperandSize(params,encodeData,opSize);

	if (opSize == OPERAND_SIZE::BYTE)
	{
		encodeData->opcode = opcode_rm8_imm8;
	}
	else
	{
		encodeData->opcode = opcode_rm32_imm32;
	}

	encodeData->immEncoding = opSize;

	return Ceng::CE_OK;
}
