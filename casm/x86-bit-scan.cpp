/*****************************************************************************
*
* x86-bit-scan.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "x86-bit-scan.h"

#include "encode-data.h"

#include "x86-register-op.h"
#include "x86-memory-op.h"
#include "enums/x86-register-types.h"

using namespace X86;

ALU_BitScan::ALU_BitScan(const Ceng::UINT8 opcode) : opcode(opcode)
{
}

ALU_BitScan::~ALU_BitScan()
{
}

const Ceng::CRESULT ALU_BitScan::SelectOpcode(BuildParams *params,
											  EncodeData *encodeData,const Operand *dest,
											  const Operand *source) const
{
	if (dest->IsRegisterOperand() == false)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (source->IsRegisterOperand())
	{
		return Select_R_R(params,encodeData,
							static_cast<const RegisterOperand*>(dest),
							static_cast<const RegisterOperand*>(source));
	}

	if (dest->IsMemoryOperand())
	{
		return Select_R_M(params,encodeData,
							static_cast<const RegisterOperand*>(dest),
							static_cast<const MemoryOperand*>(source));
	}


	return Ceng::CE_ERR_INVALID_PARAM;
}

const Ceng::CRESULT ALU_BitScan::Select_R_R(BuildParams *params,EncodeData *encodeData,
											const RegisterOperand *dest,
											const RegisterOperand *source) const
{
	if ( !(dest->RegisterFiles() & source->RegisterFiles()) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if ( !(dest->RegisterFiles() & REGISTER_FILE::ALU) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
	encodeData->opcode = opcode;

	EncodeOperandSize(params,encodeData,dest->Size());

	encodeData->operandPlace[0] = OperandPlace::reg_field;
	encodeData->operandPlace[1] = OperandPlace::rm_field;

	return Ceng::CE_OK;
}

const Ceng::CRESULT ALU_BitScan::Select_R_M(BuildParams *params,EncodeData *encodeData,
											const RegisterOperand *dest,
											const MemoryOperand *source) const
{
	if ( !(dest->RegisterFiles() & REGISTER_FILE::ALU) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
	encodeData->opcode = opcode;

	EncodeOperandSize(params,encodeData,dest->Size());

	encodeData->operandPlace[0] = OperandPlace::reg_field;
	encodeData->operandPlace[1] = OperandPlace::rm_field;

	return Ceng::CE_OK;
}