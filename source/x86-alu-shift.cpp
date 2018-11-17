/*****************************************************************************
*
* x86-alu-shift.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-alu-shift.h"

#include "../include/enums/x86-register-types.h"

#include "../include/x86-regs-alu-cl.h"

#include "../include/build-params.h"
#include "../include/encode-data.h"

#include "../include/x86-register-op.h"
#include "../include/x86-memory-op.h"
#include "../include/x86-immediate-op.h"

using namespace X86;

ALU_Shift::ALU_Shift(const Ceng::UINT8 option) : option(option)
{
}

ALU_Shift::~ALU_Shift()
{
}


const Ceng::CRESULT ALU_Shift::SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *dest,
											const Operand *source) const
{
	if (dest->IsImmediateOperand())
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (dest->IsRegisterOperand())
	{
		if (source->IsRegisterOperand())
		{
			return Select_R_R(params,encodeData,
							static_cast<const RegisterOperand*>(dest),
							static_cast<const RegisterOperand*>(source));
		}

		if (source->IsImmediateOperand())
		{
			return Select_R_I(params,encodeData,
							static_cast<const RegisterOperand*>(dest),
							static_cast<const ImmediateOperand*>(source));
		}
	}

	if (dest->IsMemoryOperand())
	{
		if (source->IsRegisterOperand())
		{
			return Select_M_R(params,encodeData,
							static_cast<const MemoryOperand*>(dest),
							static_cast<const RegisterOperand*>(source));
		}

		if (source->IsImmediateOperand())
		{
			return Select_M_I(params,encodeData,
							static_cast<const MemoryOperand*>(dest),
							static_cast<const ImmediateOperand*>(source));
		}
	}

	return Ceng::CE_ERR_INVALID_PARAM;
}

const Ceng::CRESULT ALU_Shift::Select_R_R(BuildParams *params,EncodeData *encodeData,
										  const RegisterOperand *dest,
										  const RegisterOperand *source) const
{
	// Check that source register is CL

	if (source->Size() != OPERAND_SIZE::BYTE)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (source->index != X86::CL.index)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	// Check that destination register is an ALU register

	if ( !(dest->RegisterFiles() & REGISTER_FILE::ALU) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	EncodeOperandSize(params,encodeData,dest->Size());

	if (dest->Size() == OPERAND_SIZE::BYTE)
	{
		encodeData->opcode = opcode_r8_CL;
	}
	else
	{
		encodeData->opcode = opcode_r32_CL;
	}

	encodeData->modRM.SetRegField(option);

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::NOT_USED;

	return Ceng::CE_OK;
}

const Ceng::CRESULT ALU_Shift::Select_M_R(BuildParams *params,EncodeData *encodeData,
										  const MemoryOperand *dest,
										  const RegisterOperand *source) const
{
	// Check that source register is CL

	if (source->Size() != OPERAND_SIZE::BYTE)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (source->index != X86::CL.index)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	// Can't determine operand size if memory operand size
	// not given

	if (dest->Size() == OPERAND_SIZE::IMPLICIT)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	EncodeOperandSize(params,encodeData,dest->Size());

	if (dest->Size() == OPERAND_SIZE::BYTE)
	{
		encodeData->opcode = opcode_r8_CL;
	}
	else
	{
		encodeData->opcode = opcode_r32_CL;
	}

	encodeData->modRM.SetRegField(option);

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::NOT_USED;

	return Ceng::CE_OK;
}

const Ceng::CRESULT ALU_Shift::Select_R_I(BuildParams *params,EncodeData *encodeData,
										  const RegisterOperand *dest,
										  const ImmediateOperand *source) const
{
	if (source->Size() != OPERAND_SIZE::BYTE)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if ( !(dest->RegisterFiles() & REGISTER_FILE::ALU) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	EncodeOperandSize(params,encodeData,dest->Size());

	encodeData->modRM.SetRegField(option);

	encodeData->immEncoding = OPERAND_SIZE::BYTE;

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::IMM;

	if (dest->Size() == OPERAND_SIZE::BYTE)
	{
		encodeData->opcode = opcode_r8_imm8;

		if (source->Value8() == 1)
		{
			encodeData->opcode = opcode_r8_one;
			encodeData->operandPlace[1] = OPERAND_PLACE::NOT_USED;
		}		
	}
	else
	{
		encodeData->opcode = opcode_r32_imm8;

		if (source->Value8() == 1)
		{
			encodeData->opcode = opcode_r32_one;
			encodeData->operandPlace[1] = OPERAND_PLACE::NOT_USED;
		}
	}

	return Ceng::CE_OK;
}

const Ceng::CRESULT ALU_Shift::Select_M_I(BuildParams *params,EncodeData *encodeData,
										  const MemoryOperand *dest,
										  const ImmediateOperand *source) const
{
	if (dest->Size() == OPERAND_SIZE::IMPLICIT)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	EncodeOperandSize(params,encodeData,dest->Size());

	encodeData->modRM.SetRegField(option);

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::IMM;

	if (dest->Size() == OPERAND_SIZE::BYTE)
	{
		encodeData->opcode = opcode_r8_imm8;

		if (source->Value8() == 1)
		{
			encodeData->opcode = opcode_r8_one;
			encodeData->operandPlace[1] = OPERAND_PLACE::NOT_USED;
		}		
	}
	else
	{
		encodeData->opcode = opcode_r32_imm8;

		if (source->Value8() == 1)
		{
			encodeData->opcode = opcode_r32_one;
			encodeData->operandPlace[1] = OPERAND_PLACE::NOT_USED;
		}
	}

	return Ceng::CE_OK;
}



