/*****************************************************************************
*
* x86-two-form-alu.cpp
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#include "../include/enums/x86-register-types.h"

#include "../include/x86-two-form-alu.h"

#include "../include/build-params.h"
#include "../include/encode-data.h"

#include "../include/x86-register-op.h"
#include "../include/x86-memory-op.h"
#include "../include/x86-immediate-op.h"

using namespace X86;

TwoForm_ALU::TwoForm_ALU()
{
}

TwoForm_ALU::~TwoForm_ALU()
{
}

void TwoForm_ALU::EncodeOperandSize(BuildParams *params,
									EncodeData *encodeData,const OPERAND_SIZE::value opSize) const
{
	if (opSize == OPERAND_SIZE::QWORD)
	{
		encodeData->rex.SetWideSize();
	}
	else if (opSize != params->mode->defaultOpSize)
	{
		encodeData->optionPrefix |= PREFIX_BYTE::OPERAND_SIZE;
	}
}

void TwoForm_ALU::Opcode_RM_R(BuildParams *params,EncodeData *encodeData,
							  const OPERAND_SIZE::value opSize,
							  const Ceng::UINT8 opcode_rm8_r8,
							  const Ceng::UINT8 opcode_rm32_r32) const
{
	if (opSize == OPERAND_SIZE::BYTE)
	{
		encodeData->opcode = opcode_rm8_r8;
	}
	else
	{
		encodeData->opcode = opcode_rm32_r32;
	}
}

const Ceng::CRESULT TwoForm_ALU::ValidateOperands_R_R(BuildParams *params,const RegisterOperand *dest,
													  const RegisterOperand *source) const
{
	if (ValidateRegisterOp(params,dest) == false)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (ValidateRegisterOp(params,source) == false)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (dest->Size() != source->Size())
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if ( !(dest->RegisterFiles() & source->RegisterFiles()) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	return Ceng::CE_OK;
}

const Ceng::BOOL TwoForm_ALU::ValidateRegisterOp(BuildParams *params,const RegisterOperand *registerOp) const
{
	if (registerOp->index < 0) return false;

	Ceng::INT32 maxIndex = 7;

	if (params->mode->cpuMode == CPU_MODE::X64)
	{
		maxIndex = 15;
	}
	else
	{
		if (registerOp->registerFiles & X86::REGISTER_FILE::REG_64)
		{
			return false;
		}

		if (registerOp->registerFiles & X86::REGISTER_FILE::REG_8_X64)
		{
			if ( !(registerOp->registerFiles & X86::REGISTER_FILE::REG_8_X86) )
			{
				return false;
			}
		}
	}

	if (registerOp->Size() > maxIndex) return false;

	if (registerOp->RegisterFiles() & X86::REGISTER_FILE::REG_MM)
	{
		return false;
	}

	if (registerOp->RegisterFiles() & X86::REGISTER_FILE::REG_XMM)
	{
		return false;
	}

	return true;
}

const Ceng::CRESULT TwoForm_ALU::Standard_R_R(BuildParams *params,EncodeData *encodeData,
											  const Ceng::UINT8 opcode_rm8_r8,
											  const Ceng::UINT8 opcode_rm32_r32,
											  const RegisterOperand *dest,
											  const RegisterOperand *source) const
{
	Ceng::CRESULT cresult;

	cresult = ValidateOperands_R_R(params,dest,source);
	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::REG_FIELD;

	OPERAND_SIZE::value opSize = dest->Size();

	EncodeOperandSize(params,encodeData,opSize);
	
	Opcode_RM_R(params,encodeData,opSize,opcode_rm8_r8,opcode_rm32_r32);

	return Ceng::CE_OK;
}

const Ceng::CRESULT TwoForm_ALU::Standard_M_R(BuildParams *params,EncodeData *encodeData,
											  const Ceng::UINT8 opcode_rm8_r8,
											  const Ceng::UINT8 opcode_rm32_r32,
											  const MemoryOperand *dest,
											  const RegisterOperand *source) const
{
	if (ValidateRegisterOp(params,source) == false)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::REG_FIELD;

	OPERAND_SIZE::value opSize = source->Size();

	EncodeOperandSize(params,encodeData,opSize);
	
	Opcode_RM_R(params,encodeData,opSize,opcode_rm8_r8,opcode_rm32_r32);

	return Ceng::CE_OK;
}

const Ceng::CRESULT TwoForm_ALU::Standard_R_M(BuildParams *params,EncodeData *encodeData,
											  const Ceng::UINT8 opcode_r8_rm8,
											  const Ceng::UINT8 opcode_r32_rm32,
											  const RegisterOperand *dest,
											  const MemoryOperand *source) const
{
	if (ValidateRegisterOp(params,dest) == false)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->operandPlace[0] = OPERAND_PLACE::REG_FIELD;
	encodeData->operandPlace[1] = OPERAND_PLACE::RM_FIELD;

	OPERAND_SIZE::value opSize = dest->Size();

	EncodeOperandSize(params,encodeData,opSize);

	if (opSize == OPERAND_SIZE::BYTE)
	{
		encodeData->opcode = opcode_r8_rm8;
	}
	else
	{
		encodeData->opcode = opcode_r32_rm32;
	}

	return Ceng::CE_OK;
}