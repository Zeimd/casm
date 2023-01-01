/*****************************************************************************
*
* x86-xsave.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "x86-xsave.h"

#include "encode-data.h"

#include "x86-memory-op.h"

#include "build-params.h"

using namespace X86;

SaveExtState::SaveExtState(const char* name, const Ceng::UINT8 option,const Ceng::BOOL x64)
	: name(name), option(option),x64(x64)
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

	encodeData->operandPlace[0] = OperandPlace::rm_field;

	return Ceng::CE_OK;
}