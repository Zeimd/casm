/*****************************************************************************
*
* x86-return.cpp
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#include "../include/x86-return.h"
#include "../include/build-params.h"

#include "../include/encode-data.h"

#include "../include/x86-immediate-op.h"

using namespace X86;

ReturnInstruction::ReturnInstruction(const Ceng::UINT8 opcode_bare,const Ceng::UINT8 opcode_imm16) 
	: opcode_bare(opcode_bare),opcode_imm16(opcode_imm16)
{
}

ReturnInstruction::~ReturnInstruction()
{
}

const Ceng::CRESULT ReturnInstruction::SelectOpcode(BuildParams *params,EncodeData *encodeData) const
{
	encodeData->opcode = 0xc3;

	return Ceng::CE_OK;
}

const Ceng::CRESULT ReturnInstruction::SelectOpcode(BuildParams *params,
												   EncodeData *encodeData,const Operand *operand) const
{
	if ( operand->IsImmediateOperand() == false)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (operand->Size() > OPERAND_SIZE::WORD)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->opcode = 0xc2;

	encodeData->immEncoding = OPERAND_SIZE::WORD;
	encodeData->operandPlace[0] = OPERAND_PLACE::IMM;

	return Ceng::CE_OK;
}