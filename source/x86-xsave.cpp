/*****************************************************************************
*
* x86-xsave.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-xsave.h"

#include "../include/encode-data.h"

#include "../include/x86-memory-op.h"

#include "../include/build-params.h"

using namespace X86;

SaveExtState::SaveExtState(const Ceng::UINT8 option,const Ceng::BOOL x64)
	: option(option),x64(x64)
{
}

SaveExtState::~SaveExtState()
{
}

const Ceng::CRESULT SaveExtState::SelectOpcode(BuildParams *params,
											   EncodeData *encodeData,const Operand *operand) const
{
	if (operand->IsMemoryOperand())
	{
		return Select_M(params,encodeData,static_cast<const MemoryOperand*>(operand));
	}

	return Ceng::CE_ERR_INVALID_PARAM;
}

const Ceng::CRESULT SaveExtState::Select_M(BuildParams *params,EncodeData *encodeData,
										   const MemoryOperand *operand) const
{
	if (x64 == true)
	{
		if (params->mode->cpuMode != CPU_MODE::X64)
		{
			return Ceng::CE_ERR_INVALID_PARAM;
		}

		encodeData->rex.SetWideSize();
	}
	
	encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
	encodeData->opcode = opcode;

	encodeData->modRM.SetRegField(option);

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;

	return Ceng::CE_OK;
}