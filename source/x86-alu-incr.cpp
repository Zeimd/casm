/*****************************************************************************
*
* x86-alu-incr.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-alu-incr.h"

#include "../include/enums/x86-register-types.h"

#include "../include/build-params.h"
#include "../include/encode-data.h"

#include "../include/x86-register-op.h"
#include "../include/x86-memory-op.h"

using namespace X86;

ALU_Incr::ALU_Incr(const Ceng::UINT8 opcode_r32,const Ceng::UINT8 option)
	: opcode_r32(opcode_r32),option(option)
{
}

ALU_Incr::~ALU_Incr()
{
}

const Ceng::CRESULT ALU_Incr::SelectOpcode(BuildParams *params,
										   EncodeData *encodeData,const Operand *operand) const
{
	if (operand->IsRegisterOperand())
	{
		return Select_R(params,encodeData,static_cast<const RegisterOperand*>(operand));
	}

	if (operand->IsMemoryOperand())
	{
		return Select_M(params,encodeData,static_cast<const MemoryOperand*>(operand));
	}

	return Ceng::CE_ERR_INVALID_PARAM;
}

const Ceng::CRESULT ALU_Incr::Select_R(BuildParams *params,EncodeData *encodeData,
									   const RegisterOperand *operand) const
{
	if ( !(operand->RegisterFiles() & REGISTER_FILE::ALU) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	EncodeOperandSize(params,encodeData,operand->Size());

	if (params->mode->cpuMode == CPU_MODE::X64)
	{
		encodeData->opcode = opcode_rm32;

		if (operand->Size() == OPERAND_SIZE::BYTE)
		{
			encodeData->opcode = opcode_rm8;
		}

		encodeData->modRM.SetRegField(option);

		encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;
	}
	else
	{
		encodeData->opcode = opcode_r32;

		if (operand->Size() == OPERAND_SIZE::BYTE)
		{
			encodeData->opcode = opcode_rm8;
				 
			encodeData->modRM.SetRegField(option);
			
			encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;
		}
		else
		{
			encodeData->operandPlace[0] = OPERAND_PLACE::OPCODE;
		}
	}

	return Ceng::CE_OK;
}

const Ceng::CRESULT ALU_Incr::Select_M(BuildParams *params,EncodeData *encodeData,
									   const MemoryOperand *operand) const
{
	if (operand->Size() == OPERAND_SIZE::IMPLICIT)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	EncodeOperandSize(params,encodeData,operand->Size());

	encodeData->opcode = opcode_rm32;

	if (operand->Size() == OPERAND_SIZE::BYTE)
	{
		encodeData->opcode = opcode_rm8;
	}

	encodeData->modRM.SetRegField(option);

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;

	return Ceng::CE_OK;
}