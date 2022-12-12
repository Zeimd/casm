/*****************************************************************************
*
* x86-alu-setcc.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-alu-setcc.h"

#include "../include/encode-data.h"

#include "../include/x86-register-op.h"
#include "../include/x86-memory-op.h"

using namespace X86;

SetCC::SetCC(const Ceng::UINT8 opcode) : opcode(opcode)
{
}

SetCC::~SetCC()
{
}

const Ceng::CRESULT SetCC::SelectOpcode(BuildParams *params,
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

const Ceng::CRESULT SetCC::Select_R(BuildParams *params,EncodeData *encodeData,
									const RegisterOperand *operand) const
{
	if (operand->Size() != OPERAND_SIZE::BYTE)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
	encodeData->opcode = opcode;

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;

	return Ceng::CE_OK;
}

const Ceng::CRESULT SetCC::Select_M(BuildParams *params,EncodeData *encodeData,
									const MemoryOperand *operand) const
{
	if (operand->Size() != OPERAND_SIZE::BYTE)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
	encodeData->opcode = opcode;

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;

	return Ceng::CE_OK;
}