/*****************************************************************************
*
* x86-cbw-variant.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-cbw-variant.h"

#include "../include/build-params.h"
#include "../include/encode-data.h"

using namespace X86;

CBW_Variant::CBW_Variant(const Ceng::UINT8 opcode,const OPERAND_SIZE::value opSize)
	: opcode(opcode),opSize(opSize)
{
}

CBW_Variant::~CBW_Variant()
{
}

const Ceng::CRESULT CBW_Variant::SelectOpcode(BuildParams *params,EncodeData *encodeData) const
{
	if (opSize == OPERAND_SIZE::QWORD)
	{
		if (params->mode->cpuMode != CPU_MODE::X64)
		{
			return Ceng::CE_ERR_NOT_SUPPORTED;
		}
	}

	encodeData->opcode = opcode;

	EncodeOperandSize(params,encodeData,opSize);

	return Ceng::CE_OK;
}