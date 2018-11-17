/*****************************************************************************
*
* x86-alu-div.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-alu-div.h"

#include "../include/x86-register-op.h"
#include "../include/x86-memory-op.h"

#include "../include/enums/x86-register-types.h"

#include "../include/encode-data.h"

using namespace X86;

ALU_Div::ALU_Div(const Ceng::UINT8 option) : option(option)
{
}

ALU_Div::~ALU_Div()
{
}

const Ceng::CRESULT ALU_Div::SelectOpcode(BuildParams *params,
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

const Ceng::CRESULT ALU_Div::Select_R(BuildParams *params,EncodeData *encodeData,
									  const RegisterOperand *operand) const
{
	if ( !(operand->RegisterFiles() & REGISTER_FILE::ALU) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->opcode = opcode_rm32;

	if (operand->Size() == OPERAND_SIZE::BYTE)
	{
		encodeData->opcode = opcode_rm8;
	}

	encodeData->modRM.SetRegField(option);

	EncodeOperandSize(params,encodeData,operand->Size());

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;

	return Ceng::CE_OK;
}

const Ceng::CRESULT ALU_Div::Select_M(BuildParams *params,EncodeData *encodeData,
									  const MemoryOperand *operand) const
{
	if (operand->Size() == OPERAND_SIZE::IMPLICIT)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->opcode = opcode_rm32;

	if (operand->Size() == OPERAND_SIZE::BYTE)
	{
		encodeData->opcode = opcode_rm8;
	}

	encodeData->modRM.SetRegField(option);

	EncodeOperandSize(params,encodeData,operand->Size());

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;

	return Ceng::CE_OK;
}