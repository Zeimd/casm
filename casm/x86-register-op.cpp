/*****************************************************************************
*
* x86-register-op.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "x86-register-op.h"

#include "encode-data.h"

#include "enums/x86-operand-place.h"

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
	if (encodeData->operandPlace[operandIndex] == OperandPlace::opcode)
	{
		encodeData->opcode += index & 7;
		
		encodeData->rex.SetBaseReg(index); // to base-field
		encodeData->vex.SetBaseReg(index); 

		return Ceng::CE_OK;
	}

	if (encodeData->operandPlace[operandIndex] == OperandPlace::vex_vvvv)
	{
		encodeData->vex.Set_VVVV(index);
		return Ceng::CE_OK;
	}

	if (encodeData->operandPlace[operandIndex] == OperandPlace::imm)
	{
		encodeData->hasImmediate = true;
		encodeData->immEncoding = OPERAND_SIZE::BYTE;

		encodeData->immediate = index << 4;

		return Ceng::CE_OK;
	}

	if (encodeData->operandPlace[operandIndex] == OperandPlace::reg_field)
	{
		encodeData->modRM.SetRegField(index);		
		encodeData->rex.SetRegField(index);
		encodeData->vex.SetRegField(index);
	}
	else if (encodeData->operandPlace[operandIndex] == OperandPlace::rm_field)
	{
		encodeData->modRM.SetBaseField(index);
		encodeData->modRM.SetBasetype(ModRM_Byte::REGISTER);

		encodeData->rex.SetBaseReg(index);
		encodeData->vex.SetBaseReg(index);
	}

	return Ceng::CE_OK;
}