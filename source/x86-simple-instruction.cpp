/*****************************************************************************
*
* x86-simple-instruction.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-simple-instruction.h"

#include "../include/encode-data.h"

using namespace X86;

SimpleInstruction::SimpleInstruction(const PREFIX_BYTE::value prefixByte,const OPCODE_ESCAPE::value escapeCode,
									 const Ceng::UINT8 opcode)
	: prefixByte(prefixByte),escapeCode(escapeCode),opcode(opcode)
{
}

SimpleInstruction::SimpleInstruction(const Ceng::UINT8 opcode)
	: prefixByte(PREFIX_BYTE::NONE),escapeCode(OPCODE_ESCAPE::NONE),opcode(opcode)
{
}

SimpleInstruction::~SimpleInstruction()
{
}

const Ceng::CRESULT SimpleInstruction::SelectOpcode(BuildParams *params,EncodeData *encodeData) const
{
	encodeData->opcodePrefix = prefixByte;

	encodeData->escapeCode = escapeCode;

	encodeData->opcode = opcode;

	return Ceng::CE_OK;
}