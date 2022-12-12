/*****************************************************************************
*
* x86-wide-shift.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-wide-shift.h"

#include "../include/enums/x86-register-types.h"

#include "../include/x86-regs-alu-cl.h"

#include "../include/build-params.h"
#include "../include/encode-data.h"

#include "../include/x86-register-op.h"
#include "../include/x86-memory-op.h"
#include "../include/x86-immediate-op.h"

using namespace X86;

ALU_WideShift::ALU_WideShift(const Ceng::UINT8 opcode_imm8,const Ceng::UINT8 opcode_CL)
	: opcode_imm8(opcode_imm8),opcode_CL(opcode_CL)
{
}

ALU_WideShift::~ALU_WideShift()
{
}

const Ceng::CRESULT ALU_WideShift::SelectOpcode(BuildParams *params,
												EncodeData *encodeData,const Operand *dest,
												const Operand *source1,
												const Operand *source2) const
{
	if (dest->IsImmediateOperand())
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (source1->IsRegisterOperand() == false)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (dest->IsRegisterOperand())
	{
		if (source2->IsRegisterOperand())
		{
			return Select_R_R_R(params,encodeData,
								static_cast<const RegisterOperand*>(dest),
								static_cast<const RegisterOperand*>(source1),
								static_cast<const RegisterOperand*>(source2));
		}

		if (source2->IsImmediateOperand())
		{
			return Select_R_R_I(params,encodeData,
								static_cast<const RegisterOperand*>(dest),
								static_cast<const RegisterOperand*>(source1),
								static_cast<const ImmediateOperand*>(source2));
		}
	}

	if (dest->IsMemoryOperand())
	{
		if (source2->IsRegisterOperand())
		{
			return Select_M_R_R(params,encodeData,
								static_cast<const MemoryOperand*>(dest),
								static_cast<const RegisterOperand*>(source1),
								static_cast<const RegisterOperand*>(source2));
		}

		if (source2->IsImmediateOperand())
		{
			return Select_M_R_I(params,encodeData,
								static_cast<const MemoryOperand*>(dest),
								static_cast<const RegisterOperand*>(source1),
								static_cast<const ImmediateOperand*>(source2));
		}
	}


	return Ceng::CE_ERR_INVALID_PARAM;
}

const Ceng::CRESULT ALU_WideShift::Select_R_R_R(BuildParams *params,EncodeData *encodeData,
												const RegisterOperand *dest,
												const RegisterOperand *source1,
												const RegisterOperand *source2) const
{
	if (source2->Size() != OPERAND_SIZE::BYTE)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (source2->index != X86::CL.index)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if ( !(dest->RegisterFiles() & source1->RegisterFiles()) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if ( !(dest->RegisterFiles() & REGISTER_FILE::ALU) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
	encodeData->opcode = opcode_CL;

	EncodeOperandSize(params,encodeData,dest->Size());

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::REG_FIELD;
	encodeData->operandPlace[2] = OPERAND_PLACE::NOT_USED;

	return Ceng::CE_OK;
}

const Ceng::CRESULT ALU_WideShift::Select_M_R_R(BuildParams *params,EncodeData *encodeData,
												const MemoryOperand *dest,
												const RegisterOperand *source1,
												const RegisterOperand *source2) const
{
	if (source2->Size() != OPERAND_SIZE::BYTE)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (source2->index != X86::CL.index)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if ( !(source1->RegisterFiles() & REGISTER_FILE::ALU) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
	encodeData->opcode = opcode_CL;

	EncodeOperandSize(params,encodeData,source1->Size());

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::REG_FIELD;
	encodeData->operandPlace[2] = OPERAND_PLACE::NOT_USED;

	return Ceng::CE_OK;
}

const Ceng::CRESULT ALU_WideShift::Select_R_R_I(BuildParams *params,EncodeData *encodeData,
												const RegisterOperand *dest,
												const RegisterOperand *source1,
												const ImmediateOperand *source2) const
{
	if ( !(dest->RegisterFiles() & source1->RegisterFiles()) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if ( !(dest->RegisterFiles() & REGISTER_FILE::ALU) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
	encodeData->opcode = opcode_imm8;

	EncodeOperandSize(params,encodeData,dest->Size());

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::REG_FIELD;
	encodeData->operandPlace[2] = OPERAND_PLACE::IMM;

	encodeData->immEncoding = OPERAND_SIZE::BYTE;

	return Ceng::CE_OK;
}

const Ceng::CRESULT ALU_WideShift::Select_M_R_I(BuildParams *params,EncodeData *encodeData,
												const MemoryOperand *dest,
												const RegisterOperand *source1,
												const ImmediateOperand *source2) const
{
	if ( !(source1->RegisterFiles() & REGISTER_FILE::ALU) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
	encodeData->opcode = opcode_imm8;

	EncodeOperandSize(params,encodeData,source1->Size());

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::REG_FIELD;
	encodeData->operandPlace[2] = OPERAND_PLACE::IMM;

	encodeData->immEncoding = OPERAND_SIZE::BYTE;

	return Ceng::CE_OK;
}