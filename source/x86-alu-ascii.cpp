/*****************************************************************************
*
* x86-alu-ascii.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-alu-ascii.h"

#include "../include/build-params.h"
#include "../include/encode-data.h"

#include "../include/x86-immediate-op.h"

using namespace X86;

ALU_Ascii::ALU_Ascii(const Ceng::UINT8 opcode) : opcode(opcode)
{
}

ALU_Ascii::~ALU_Ascii()
{
}

const Ceng::CRESULT ALU_Ascii::SelectOpcode(BuildParams *params,EncodeData *encodeData) const
{
	if (params->mode->cpuMode == CPU_MODE::X64)
	{
		return Ceng::CE_ERR_NOT_SUPPORTED;
	}

	encodeData->opcode = opcode;

	encodeData->hasImmediate = true;

	encodeData->immediate = 10;
	encodeData->immEncoding = OPERAND_SIZE::BYTE;	

	return Ceng::CE_OK;
}

const Ceng::CRESULT ALU_Ascii::SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *operand) const
{
	if (params->mode->cpuMode == CPU_MODE::X64)
	{
		return Ceng::CE_ERR_NOT_SUPPORTED;
	}

	if (operand->IsImmediateOperand())
	{
		return Select_I(params,encodeData,static_cast<const ImmediateOperand*>(operand));
	}

	return Ceng::CE_ERR_INVALID_PARAM;
}

const Ceng::CRESULT ALU_Ascii::Select_I(BuildParams *params,EncodeData *encodeData,
										const ImmediateOperand *operand) const
{
	if (operand->Size() != OPERAND_SIZE::BYTE)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->opcode = opcode;

	encodeData->immEncoding = OPERAND_SIZE::BYTE;

	encodeData->operandPlace[0] = OPERAND_PLACE::IMM;

	return Ceng::CE_OK;
}