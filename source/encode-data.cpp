/*****************************************************************************
*
* encode-data.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/encode-data.h"

#include "../include/build-params.h"
#include "../include/opcode-prefix.h"

using namespace X86;

EncodeData::EncodeData() 
	: hasImmediate(false),
	hasDisplacement(false),
	optionPrefix(0),escapeCode(OPCODE_ESCAPE::NONE),useVEX(false),
	opcodePrefix(PREFIX_BYTE::NONE)
{
	modRM = ModRM_Byte();
	sib = SIB_Byte();

	rex = REX_Byte();
	vex = VEX_Prefix();

	operandPlace[0] = OPERAND_PLACE::NOT_USED;
	operandPlace[1] = OPERAND_PLACE::NOT_USED;
	operandPlace[2] = OPERAND_PLACE::NOT_USED;
	operandPlace[3] = OPERAND_PLACE::NOT_USED;
}

const Ceng::CRESULT EncodeData::EncodeInstruction(BuildParams *params,std::vector<Ceng::UINT8> &destBuffer,
												  InstructionPrefix *prefix) const
{
	// Lock & repeat prefixes

	if (optionPrefix & PREFIX_BYTE::LOCK)
	{
		destBuffer.push_back(0xf0);
	}

	if (optionPrefix & PREFIX_BYTE::REPEAT)
	{
		destBuffer.push_back(0xf3);
	}

	if (optionPrefix & PREFIX_BYTE::REPEAT_NOT_ZERO)
	{
		destBuffer.push_back(0xf2);
	}

	// Segment override or branch hint

	if (optionPrefix & PREFIX_BYTE::CS_OVERRIDE)
	{
		destBuffer.push_back(0x2e);
	}

	if (optionPrefix & PREFIX_BYTE::SS_OVERRIDE)
	{
		destBuffer.push_back(0x36);
	}

	if (optionPrefix & PREFIX_BYTE::DS_OVERRIDE)
	{
		destBuffer.push_back(0x3e);
	}

	if (optionPrefix & PREFIX_BYTE::ES_OVERRIDE)
	{
		destBuffer.push_back(0x26);
	}

	if (optionPrefix & PREFIX_BYTE::FS_OVERRIDE)
	{
		destBuffer.push_back(0x64);
	}

	if (optionPrefix & PREFIX_BYTE::GS_OVERRIDE)
	{
		destBuffer.push_back(0x65);
	}

	if (optionPrefix & PREFIX_BYTE::BRANCH_NOT_TAKEN)
	{
		destBuffer.push_back(0x2e);
	}

	if (optionPrefix & PREFIX_BYTE::BRANCH_TAKEN)
	{
		destBuffer.push_back(0x3e);
	}

	// Operand size override

	if (optionPrefix & PREFIX_BYTE::OPERAND_SIZE)
	{
		destBuffer.push_back(0x66);
	}

	// Address size override

	if (optionPrefix & PREFIX_BYTE::ADDRESS_SIZE)
	{
		destBuffer.push_back(0x67);
	}

	// Compulsory prefix

	if (useVEX == false)
	{

		switch(opcodePrefix)
		{
		case PREFIX_BYTE::BYTE_66:
			destBuffer.push_back(0x66);
			break;
		case PREFIX_BYTE::BYTE_F2:
			destBuffer.push_back(0xf2);
			break;
		case PREFIX_BYTE::BYTE_F3:
			destBuffer.push_back(0xf3);
			break;
		}

		// REX

		if (rex != 0)
		{
			destBuffer.push_back(rex | (1 << 6));
		}

		WriteEscapeBytes(params,escapeCode,destBuffer);
	}
	else
	{
		vex.Encode(params,destBuffer);
	}

	// Opcode

	destBuffer.push_back(opcode);

	// ModRM

	modRM.Encode(params,destBuffer);

	// sib-byte
	
	sib.Encode(params,destBuffer);

	// Displacement

	if (hasDisplacement)
	{
		params->out_dispOffset = destBuffer.size();

		EncodeDisplacement(params,destBuffer,dispEncoding,displacement);
	}

	// immediate

	if (hasImmediate)
	{
		params->out_immOffset = destBuffer.size();

		EncodeImmediate(params,destBuffer,immEncoding,immediate);
	}

	return Ceng::CE_OK;
}

const Ceng::CRESULT EncodeData::EncodeDisplacement(BuildParams *params,std::vector<Ceng::UINT8> &destBuffer,
												   const OPERAND_SIZE::value encodeSize,
												   const Ceng::INT64 displacement) const
{
	params->out_dispSize = encodeSize;

	if (encodeSize == OPERAND_SIZE::BYTE)
	{
		destBuffer.push_back(Ceng::INT8(displacement));
	}
	else if (encodeSize == OPERAND_SIZE::WORD)
	{
		Ceng::INT8 *byte = (Ceng::INT8*)&displacement;

		destBuffer.push_back(byte[0]);
		destBuffer.push_back(byte[1]);
	}
	else if (encodeSize == OPERAND_SIZE::DWORD)
	{
		Ceng::INT8 *byte = (Ceng::INT8*)&displacement;

		destBuffer.push_back(byte[0]);
		destBuffer.push_back(byte[1]);
		destBuffer.push_back(byte[2]);
		destBuffer.push_back(byte[3]);
	}

	return Ceng::CE_OK;
}

const Ceng::CRESULT EncodeData::EncodeImmediate(BuildParams *params,std::vector<Ceng::UINT8> &destBuffer,
												const OPERAND_SIZE::value encodeSize,
												const Ceng::INT64 immediate) const
{
	Ceng::INT8 *byte;

	params->out_immSize = encodeSize;

	switch(encodeSize)
	{
	case X86::OPERAND_SIZE::BYTE:
	
		destBuffer.push_back(Ceng::INT8(immediate));
		break;
	case X86::OPERAND_SIZE::WORD:

		{
			Ceng::INT16 temp = Ceng::INT16(immediate);

			byte = (Ceng::INT8*)&temp;

			destBuffer.push_back(byte[0]);
			destBuffer.push_back(byte[1]);
		}

		break;
	case X86::OPERAND_SIZE::DWORD:

		{
			Ceng::INT32 temp = Ceng::INT32(immediate);

			byte = (Ceng::INT8*)&temp;

			destBuffer.push_back(byte[0]);
			destBuffer.push_back(byte[1]);
			destBuffer.push_back(byte[2]);
			destBuffer.push_back(byte[3]);
		}

		break;
	case X86::OPERAND_SIZE::QWORD:

		{
			byte = (Ceng::INT8*)&immediate;

			Ceng::INT32 k;

			for(k=0;k<8;k++)
			{
				destBuffer.push_back(byte[k]);
			}
		}
		break;
	}

	/*
	if (immediate->Symbol() != NULL)
	{
		SymbolRef *temp;

		temp = new SymbolRef(immediate->Symbol(),params->out_immOffset,
			encodeSize,
			params->imm_symbolRefType);

		params->codeElement->references.push_back(temp);

		params->immRef = temp;
	}
	*/

	return Ceng::CE_OK;
}

const Ceng::CRESULT EncodeData::WriteEscapeBytes(BuildParams *params,const OPCODE_ESCAPE::value escapeBytes,
												 std::vector<Ceng::UINT8> &destBuffer) const
{
	switch(escapeBytes)
	{
	case OPCODE_ESCAPE::BYTE_0F:
		destBuffer.push_back(0x0f);
		break;
	case OPCODE_ESCAPE::BYTES_0F_01:
		destBuffer.push_back(0x0f);
		destBuffer.push_back(0x01);
		break;
	case OPCODE_ESCAPE::BYTES_0F_3A:
		destBuffer.push_back(0x0f);
		destBuffer.push_back(0x3a);
		break;
	case OPCODE_ESCAPE::BYTES_0F_38:
		destBuffer.push_back(0x0f);
		destBuffer.push_back(0x38);
		break;
	}

	return Ceng::CE_OK;
}