/*****************************************************************************
*
* x86-alu-xchg.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-alu-xchg.h"

#include "../include/enums/x86-register-types.h"

#include "../include/x86-regs-alu.h"

#include "../include/encode-data.h"

#include "../include/x86-register-op.h"
#include "../include/x86-memory-op.h"


using namespace X86;

Exchange::Exchange()
{
}

Exchange::~Exchange()
{
}

const Ceng::CRESULT Exchange::SelectOpcode(BuildParams *params,
										   EncodeData *encodeData,const Operand *dest,
										   const Operand *source) const
{
	if (dest->IsImmediateOperand())
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (source->IsImmediateOperand())
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

		if (source->IsMemoryOperand())
		{
			return Select_R_M(params,encodeData,
									static_cast<const RegisterOperand*>(dest),
									static_cast<const MemoryOperand*>(source));
		}
	}

	if (dest->IsMemoryOperand())
	{
		if (source->IsRegisterOperand())
		{
			return Select_R_M(params,encodeData,
									static_cast<const RegisterOperand*>(source),
									static_cast<const MemoryOperand*>(dest));
		}
	}

	return Ceng::CE_ERR_INVALID_PARAM;
}

const Ceng::CRESULT Exchange::Select_R_R(BuildParams *params,
										 EncodeData *encodeData,const RegisterOperand *dest,
										 const RegisterOperand *source) const
{
	if ( !(dest->RegisterFiles() & source->RegisterFiles() ) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if ( !(dest->RegisterFiles() & REGISTER_FILE::ALU) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (dest->Size() == OPERAND_SIZE::BYTE)
	{
		encodeData->opcode = opcode_r8_rm8;

		encodeData->operandPlace[0] = OPERAND_PLACE::REG_FIELD;
		encodeData->operandPlace[1] = OPERAND_PLACE::RM_FIELD;
	}
	else
	{
		EncodeOperandSize(params,encodeData,dest->Size());

		if (dest->index == X86::EAX.index)
		{
			encodeData->opcode = opcode_EAX_r32;

			encodeData->operandPlace[1] = OPERAND_PLACE::OPCODE;
		}
		else if (source->index == X86::EAX.index)
		{
			encodeData->opcode = opcode_EAX_r32;

			encodeData->operandPlace[0] = OPERAND_PLACE::OPCODE;
		}
		else
		{
			encodeData->opcode = opcode_r32_rm32;

			encodeData->operandPlace[0] = OPERAND_PLACE::REG_FIELD;
			encodeData->operandPlace[1] = OPERAND_PLACE::RM_FIELD;
		}
	}

	return Ceng::CE_OK;
}

const Ceng::CRESULT Exchange::Select_R_M(BuildParams *params,
										 EncodeData *encodeData,const RegisterOperand *dest,
										 const MemoryOperand *source) const
{
	if ( !(dest->RegisterFiles() & REGISTER_FILE::ALU) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	EncodeOperandSize(params,encodeData,dest->Size());

	encodeData->opcode = opcode_r32_rm32;

	if (dest->Size() == OPERAND_SIZE::BYTE)
	{
		encodeData->opcode = opcode_r8_rm8;	
	}

	encodeData->operandPlace[0] = OPERAND_PLACE::REG_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::RM_FIELD;

	return Ceng::CE_OK;
}