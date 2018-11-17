/*****************************************************************************
*
* x86-instruction.cpp
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#include "../include/x86-instruction.h"

#include "../include/x86-operand.h"

#include "../include/build-params.h"
#include "../include/encode-data.h"

#include "../include/opcode-prefix.h"

#include "../include/symbol-ref.h"
#include "../include/code-element.h"

using namespace X86;

Instruction::Instruction()
{
}

Instruction::~Instruction()
{
}

const Ceng::CRESULT Instruction::ValidatePrefixes(const Ceng::UINT32 prefixes) const
{
	return Ceng::CE_OK;
}

const Ceng::CRESULT Instruction::SelectOpcode(BuildParams *params,EncodeData *encodeData) const
{
	return Ceng::CE_OK;
}

const Ceng::CRESULT Instruction::SelectOpcode(BuildParams *params,
											 EncodeData *encodeData,const Operand *operand) const
{
	return Ceng::CE_OK;
}

const Ceng::CRESULT Instruction::SelectOpcode(BuildParams *params,
											 EncodeData *encodeData,const Operand *dest,
											 const Operand *source) const
{
	return Ceng::CE_OK;
}

const Ceng::CRESULT Instruction::SelectOpcode(BuildParams *params,
											  EncodeData *encodeData,const Operand *dest,
											  const Operand *source1,
											  const Operand *source2) const
{
	return Ceng::CE_OK;
}

const Ceng::CRESULT Instruction::EncodeBare(BuildParams *params,
											std::vector<Ceng::UINT8> &destBuffer) const
{
	EncodeData encodeData;
	InstructionPrefix optionPrefix;

	Ceng::CRESULT cresult;

	cresult = ValidatePrefixes(optionPrefix.flags);
	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	cresult = SelectOpcode(params,&encodeData);
	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	return encodeData.EncodeInstruction(params,destBuffer,&optionPrefix);
}

const Ceng::CRESULT Instruction::EncodeOneForm(BuildParams *params,
											   std::vector<Ceng::UINT8> &destBuffer,
											   const Operand *operand) const
{
	EncodeData encodeData;
	InstructionPrefix optionPrefix;

	Ceng::CRESULT cresult;

	cresult = ValidatePrefixes(optionPrefix.flags);
	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	cresult = SelectOpcode(params,&encodeData,operand);
	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	cresult = operand->EncodeAsOperand(params,&encodeData,0);
	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	return encodeData.EncodeInstruction(params,destBuffer,&optionPrefix);
}

const Ceng::CRESULT Instruction::EncodeTwoForm(BuildParams *params,std::vector<Ceng::UINT8> &destBuffer,
											   const Operand *dest,const Operand *source) const
{
	EncodeData encodeData;

	InstructionPrefix optionPrefix;

	// Validate operands

	Ceng::CRESULT cresult;

	cresult = ValidatePrefixes(optionPrefix.flags);
	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	cresult = SelectOpcode(params,&encodeData,dest,source);
	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	cresult = dest->EncodeAsOperand(params,&encodeData,0);
	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	cresult = source->EncodeAsOperand(params,&encodeData,1);
	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	return encodeData.EncodeInstruction(params,destBuffer,&optionPrefix);
}

const Ceng::CRESULT Instruction::EncodeThreeForm(BuildParams *params,std::vector<Ceng::UINT8> &destBuffer,
												 const Operand *dest,const Operand *source1,
												 const Operand *source2) const
{
	EncodeData encodeData;

	InstructionPrefix optionPrefix;

	// Validate operands

	Ceng::CRESULT cresult;

	cresult = ValidatePrefixes(optionPrefix.flags);
	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	cresult = SelectOpcode(params,&encodeData,dest,source1,source2);
	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	cresult = dest->EncodeAsOperand(params,&encodeData,0);
	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	cresult = source1->EncodeAsOperand(params,&encodeData,1);
	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	cresult = source2->EncodeAsOperand(params,&encodeData,2);
	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	return encodeData.EncodeInstruction(params,destBuffer,&optionPrefix);
}

