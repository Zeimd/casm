/*****************************************************************************
*
* x86-two-form.cpp
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#include "../include/x86-add-variant.h"

#include "../include/x86-regs-alu.h"

#include "../include/build-params.h"
#include "../include/encode-data.h"

#include "../include/x86-register-op.h"
#include "../include/x86-memory-op.h"
#include "../include/x86-immediate-op.h"

using namespace X86;

AddTypeInstruction::AddTypeInstruction(const Ceng::UINT8 opcode_rm32_r32,const Ceng::UINT8 opcode_r32_rm32,
									   const Ceng::UINT8 opcode_rm8_r8,const Ceng::UINT8 opcode_r8_rm8,
									   const Ceng::UINT8 opcode_AL_imm8,const Ceng::UINT8 opcode_EAX_imm32,
									   const Ceng::UINT8 immediateSwitch)
	: opcode_rm32_r32(opcode_rm32_r32),opcode_r32_rm32(opcode_r32_rm32),
	opcode_rm8_r8(opcode_rm8_r8),opcode_r8_rm8(opcode_r8_rm8),
	opcode_AL_imm8(opcode_AL_imm8),opcode_EAX_imm32(opcode_EAX_imm32),
	immediateSwitch(immediateSwitch)
{
}

AddTypeInstruction::~AddTypeInstruction()
{
}

const Ceng::CRESULT AddTypeInstruction::SelectOpcode(BuildParams *params,
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


const Ceng::CRESULT AddTypeInstruction::Select_R_I(BuildParams *params,
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

	// Store extra opcode in regField (selects from ADD,SUB,AND,OR, etc...)
	
	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::IMM;

	OPERAND_SIZE::value opSize = dest->Size();

	EncodeOperandSize(params,encodeData,opSize);

	encodeData->immEncoding = opSize;

	if (opSize == OPERAND_SIZE::BYTE)
	{
		if (dest->index == X86::EAX.index)
		{
			encodeData->operandPlace[0] = OPERAND_PLACE::NOT_USED;
			encodeData->opcode = opcode_AL_imm8;
		}
		else
		{
			encodeData->opcode = opcode_rm8_imm8;
			encodeData->modRM.SetRegField(immediateSwitch);
		}
		
	}
	else
	{
		if (source->Size() == OPERAND_SIZE::BYTE)
		{
			encodeData->immEncoding = OPERAND_SIZE::BYTE;
			encodeData->opcode = opcode_rm32_imm8;
			
			encodeData->modRM.SetRegField(immediateSwitch);
		}
		else
		{
			if (dest->index == X86::EAX.index)
			{
				encodeData->operandPlace[0] = OPERAND_PLACE::NOT_USED;
				encodeData->opcode = opcode_EAX_imm32;
			}			
			else
			{
				encodeData->opcode = opcode_rm32_imm32;
				encodeData->modRM.SetRegField(immediateSwitch);
			}
		}
	}

	return Ceng::CE_OK;
}

const Ceng::CRESULT AddTypeInstruction::Select_M_I(BuildParams *params,
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

	if (opSize < source->Size())
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::IMM;

	EncodeOperandSize(params,encodeData,opSize);

	encodeData->immEncoding = opSize;

	if (opSize == OPERAND_SIZE::BYTE)
	{
		encodeData->opcode = opcode_rm8_imm8;
	}
	else
	{
		if (source->Size() == OPERAND_SIZE::BYTE)
		{
			encodeData->immEncoding = OPERAND_SIZE::BYTE;
			encodeData->opcode = opcode_rm32_imm8;
		}
		else
		{
			encodeData->opcode = opcode_rm32_imm32;	
		}
	}

	return Ceng::CE_OK;
}