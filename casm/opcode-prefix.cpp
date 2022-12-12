/*****************************************************************************
*
* opcode-prefix.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/opcode-prefix.h"

#include "../include/build-params.h"

using namespace X86;

InstructionPrefix::InstructionPrefix()
{
	flags = PREFIX_BYTE::NONE;

	byte[0] = 0;
	byte[1] = 0;
	byte[2] = 0;
	byte[3] = 0;
}

InstructionPrefix::InstructionPrefix(const PREFIX_BYTE::value group1,const PREFIX_BYTE::value group2,
									 const PREFIX_BYTE::value group3,const PREFIX_BYTE::value group4)
{
	flags = group1 | group2 | group3 | group4;

	byte[0] = 0;

	switch(group1)
	{
	case PREFIX_BYTE::LOCK:
		byte[0] = 0xf0;
		break;
	case PREFIX_BYTE::REPEAT:
		byte[0] = 0xf3;
		break;
	case PREFIX_BYTE::REPEAT_NOT_ZERO:
		byte[0] = 0xf2;
		break;
	}

	byte[1] = 0;

	switch(group2)
	{
	case PREFIX_BYTE::CS_OVERRIDE:
		byte[1] = 0x2e;
		break;
	case PREFIX_BYTE::SS_OVERRIDE:
		byte[1] = 0x36;
		break;
	case PREFIX_BYTE::DS_OVERRIDE:
		byte[1] = 0x3e;
		break;
	case PREFIX_BYTE::ES_OVERRIDE:
		byte[1] = 0x26;
		break;
	case PREFIX_BYTE::FS_OVERRIDE:
		byte[1] = 0x64;
		break;
	case PREFIX_BYTE::GS_OVERRIDE:
		byte[1] = 0x65;
		break;			
	case PREFIX_BYTE::BRANCH_NOT_TAKEN:
		byte[1] = 0x2e;
		break;
	case PREFIX_BYTE::BRANCH_TAKEN:
		byte[1] = 0x3e;
		break;
	}

	byte[2] = 0;

	if (group3 == PREFIX_BYTE::OPERAND_SIZE)
	{
		byte[2] = 0x66;
	}

	byte[3] = 0;

	if (group4 == PREFIX_BYTE::ADDRESS_SIZE)
	{
		byte[3] = 0x67;
	}
}

const Ceng::CRESULT InstructionPrefix::Encode(BuildParams *params,std::vector<Ceng::UINT8> &destBuffer) const
{
	Ceng::UINT32 k;

	for(k=0;k<4;k++)
	{
		if (byte[k] != 0)
		{
			destBuffer.push_back(byte[k]);
		}
	}

	return Ceng::CE_OK;
}