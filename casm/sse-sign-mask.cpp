/*****************************************************************************
*
* sse-sign-mask.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "sse-sign-mask.h"

#include "enums/x86-register-types.h"
#include "enums/x86-opcode-escape.h"

#include "build-params.h"
#include "encode-data.h"


using namespace X86;

const Ceng::CRESULT SSE_SignMask::SelectOpcode(BuildParams *params,EncodeData *encodeData,
											   const Operand *dest,const Operand *source) const
{
	if (dest->IsRegisterOperand() && source->IsRegisterOperand())
	{
		return Select_R_R(params,encodeData,(RegisterOperand*)dest,(RegisterOperand*)source);
	}

	return Ceng::CE_OK;
}

const Ceng::CRESULT SSE_SignMask::Select_R_R(BuildParams *params,EncodeData *encodeData,
											 const RegisterOperand *dest,
											 const RegisterOperand *source) const
{
	if (source->RegisterFiles() != REGISTER_FILE::REG_XMM)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (params->mode->cpuMode == CPU_MODE::PROTECTED)
	{
		if (dest->RegisterFiles() != REGISTER_FILE::REG_32)
		{
			return Ceng::CE_ERR_INVALID_PARAM;
		}
	}
	else if (params->mode->cpuMode == CPU_MODE::X64)
	{
		if (dest->RegisterFiles() != REGISTER_FILE::REG_64)
		{
			return Ceng::CE_ERR_INVALID_PARAM;
		}
	}

	encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
	encodeData->opcode = opcode;

	encodeData->operandPlace[0] = OperandPlace::reg_field;
	encodeData->operandPlace[1] = OperandPlace::rm_field;

	return Ceng::CE_OK;
}