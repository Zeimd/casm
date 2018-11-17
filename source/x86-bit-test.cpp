/*****************************************************************************
*
* x86-bit-test.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-bit-test.h"

#include "../include/enums/x86-register-types.h"

#include "../include/build-params.h"
#include "../include/encode-data.h"

#include "../include/x86-register-op.h"
#include "../include/x86-memory-op.h"
#include "../include/x86-immediate-op.h"

using namespace X86;

ALU_BitTest::ALU_BitTest(const Ceng::UINT8 opcode_reg,const Ceng::UINT8 immediateSwitch)
	: opcode_reg(opcode_reg),immediateSwitch(immediateSwitch)
{
}

ALU_BitTest::~ALU_BitTest()
{
}


const Ceng::CRESULT ALU_BitTest::SelectOpcode(BuildParams *params,
											  EncodeData *encodeData,const Operand *dest,
											  const Operand *source) const
{
	if (dest->IsImmediateOperand())
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (dest->IsRegisterOperand())
	{
		if (source->IsRegisterOperand())
		{
			return Select_R_R(params,encodeData,
							static_cast<const RegisterOperand*>(dest),
							static_cast<const RegisterOperand*>(source));
		}

		if (source->IsImmediateOperand())
		{
			return Select_R_I(params,encodeData,
							static_cast<const RegisterOperand*>(dest),
							static_cast<const ImmediateOperand*>(source));
		}
	}

	if (dest->IsMemoryOperand())
	{
		if (source->IsRegisterOperand())
		{
			return Select_M_R(params,encodeData,
							static_cast<const MemoryOperand*>(dest),
							static_cast<const RegisterOperand*>(source));
		}

		if (source->IsImmediateOperand())
		{
			return Select_M_I(params,encodeData,
							static_cast<const MemoryOperand*>(dest),
							static_cast<const ImmediateOperand*>(source));
		}
	}

	return Ceng::CE_ERR_INVALID_PARAM;
}

const Ceng::CRESULT ALU_BitTest::Select_R_R(BuildParams *params,EncodeData *encodeData,
											const RegisterOperand *dest,
											const RegisterOperand *source) const
{
	if ( !(dest->RegisterFiles() & source->RegisterFiles() ) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if ( !(dest->RegisterFiles() & REGISTER_FILE::ALU) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
	encodeData->opcode = opcode_reg;

	EncodeOperandSize(params,encodeData,dest->Size());

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::REG_FIELD;

	return Ceng::CE_OK;
}

const Ceng::CRESULT ALU_BitTest::Select_M_R(BuildParams *params,EncodeData *encodeData,
											const MemoryOperand *dest,
											const RegisterOperand *source) const
{
	if ( !(source->RegisterFiles() & REGISTER_FILE::ALU) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (dest->Size() == OPERAND_SIZE::IMPLICIT)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
	encodeData->opcode = opcode_reg;

	EncodeOperandSize(params,encodeData,dest->Size());

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::REG_FIELD;

	return Ceng::CE_OK;
}

const Ceng::CRESULT ALU_BitTest::Select_R_I(BuildParams *params,EncodeData *encodeData,
											const RegisterOperand *dest,
											const ImmediateOperand *source) const
{
	if ( !(dest->RegisterFiles() & REGISTER_FILE::ALU) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (source->Size() != OPERAND_SIZE::BYTE)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (source->Value8() < 0)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	switch(dest->Size())
	{
	case OPERAND_SIZE::WORD:
		if (source->Value8() > 15) return Ceng::CE_ERR_INVALID_PARAM;
	case OPERAND_SIZE::DWORD:
		if (source->Value8() > 31) return Ceng::CE_ERR_INVALID_PARAM;
	case OPERAND_SIZE::QWORD:
		if (source->Value8() > 63) return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
	encodeData->opcode = opcode_imm;

	encodeData->modRM.SetRegField(immediateSwitch);

	EncodeOperandSize(params,encodeData,dest->Size());

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::IMM;

	return Ceng::CE_OK;
}



const Ceng::CRESULT ALU_BitTest::Select_M_I(BuildParams *params,EncodeData *encodeData,
											const MemoryOperand *dest,
											const ImmediateOperand *source) const
{
	if (source->Size() != OPERAND_SIZE::BYTE)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (source->Value8() < 0)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (dest->Size() == OPERAND_SIZE::IMPLICIT)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	switch(dest->Size())
	{
	case OPERAND_SIZE::WORD:
		if (source->Value8() > 15) return Ceng::CE_ERR_INVALID_PARAM;
	case OPERAND_SIZE::DWORD:
		if (source->Value8() > 31) return Ceng::CE_ERR_INVALID_PARAM;
	case OPERAND_SIZE::QWORD:
		if (source->Value8() > 63) return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
	encodeData->opcode = opcode_imm;

	encodeData->modRM.SetRegField(immediateSwitch);

	EncodeOperandSize(params,encodeData,dest->Size());

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::IMM;

	return Ceng::CE_OK;
}