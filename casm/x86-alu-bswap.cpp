/*****************************************************************************
*
* x86-alu-bswap.cpp
*
* By Jari Korkala 2/2014
*
******************************************************************************/

#include "x86-alu-bswap.h"

#include "enums/x86-register-types.h"

#include "encode-data.h"

#include "x86-register-op.h"

using namespace X86;

ALU_ByteSwap::ALU_ByteSwap()
{
}

ALU_ByteSwap::~ALU_ByteSwap()
{
}

const Ceng::CRESULT ALU_ByteSwap::SelectOpcode(BuildParams *params,
											   EncodeData *encodeData,const Operand *operand) const
{
	if (operand->IsRegisterOperand())
	{
		return Select_R(params,encodeData,static_cast<const RegisterOperand*>(operand));
	}

	return Ceng::CE_ERR_INVALID_PARAM;
}

const Ceng::CRESULT ALU_ByteSwap::Select_R(BuildParams *params,EncodeData *encodeData,
										   const RegisterOperand *operand) const
{
	if ( !(operand->RegisterFiles() & REGISTER_FILE::ALU) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (operand->Size() < OPERAND_SIZE::DWORD)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	EncodeOperandSize(params,encodeData,operand->Size());

	encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
	encodeData->opcode = opcode;

	encodeData->operandPlace[0] = OperandPlace::opcode;

	return Ceng::CE_OK;
}