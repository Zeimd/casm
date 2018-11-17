/*****************************************************************************
*
* x86-register-op.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-register-op.h"

#include "../include/encode-data.h"

#include "../include/enums/x86-operand-place.h"

using namespace X86;

RegisterOperand::RegisterOperand()
{
}

RegisterOperand::~RegisterOperand()
{
}

RegisterOperand::RegisterOperand(const Ceng::UINT32 cpuModes,const Ceng::BOOL usesREX, const Ceng::UINT32 registerFiles,
								 const OPERAND_SIZE::value size,const Ceng::INT32 index) 
	: Operand(OPERAND_TYPE::REG,usesREX,size),cpuModes(cpuModes),registerFiles(registerFiles),index(index)	
{
}

const Ceng::UINT32 RegisterOperand::RegisterFiles() const
{
	return registerFiles;
}

const Ceng::CRESULT RegisterOperand::EncodeAsOperand(BuildParams *params,EncodeData *encodeData,
													 const Ceng::UINT32 operandIndex) const
{
	if (encodeData->operandPlace[operandIndex] == OPERAND_PLACE::OPCODE)
	{
		encodeData->opcode += index & 7;
		
		encodeData->rex.SetBaseReg(index); // to base-field
		encodeData->vex.SetBaseReg(index); 

		return Ceng::CE_OK;
	}

	if (encodeData->operandPlace[operandIndex] == OPERAND_PLACE::VEX_VVVV)
	{
		encodeData->vex.Set_VVVV(index);
		return Ceng::CE_OK;
	}

	if (encodeData->operandPlace[operandIndex] == OPERAND_PLACE::IMM)
	{
		encodeData->hasImmediate = true;
		encodeData->immEncoding = OPERAND_SIZE::BYTE;

		encodeData->immediate = index << 4;

		return Ceng::CE_OK;
	}

	if (encodeData->operandPlace[operandIndex] == OPERAND_PLACE::REG_FIELD)
	{
		encodeData->modRM.SetRegField(index);		
		encodeData->rex.SetRegField(index);
		encodeData->vex.SetRegField(index);
	}
	else if (encodeData->operandPlace[operandIndex] == OPERAND_PLACE::RM_FIELD)
	{
		encodeData->modRM.SetBaseField(index);
		encodeData->modRM.SetBasetype(ModRM_Byte::REGISTER);

		encodeData->rex.SetBaseReg(index);
		encodeData->vex.SetBaseReg(index);
	}

	return Ceng::CE_OK;
}