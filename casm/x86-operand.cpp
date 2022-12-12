/*****************************************************************************
*
* x86-operand.cpp
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#include "../include/x86-operand.h"

using namespace X86;

Operand::Operand()
{
	usesREX = false;
}

Operand::Operand(const OPERAND_TYPE::value type,const Ceng::BOOL usesREX,
				 const OPERAND_SIZE::value size) 
	: type(type),usesREX(usesREX),size(size)
{
}

Operand::~Operand()
{
}

const Ceng::CRESULT Operand::EncodeAsOperand(BuildParams *params,EncodeData *encodeData,
											 const Ceng::UINT32 operandIndex) const
{
	return Ceng::CE_ERR_INVALID_PARAM;
}

const OPERAND_SIZE::value Operand::Size() const
{
	return size;
}

const Ceng::BOOL Operand::UsesREX() const
{
	return usesREX;
}

const Ceng::BOOL Operand::IsRegisterOperand() const
{
	return (type == OPERAND_TYPE::REG);
}
		
const Ceng::BOOL Operand::IsMemoryOperand() const
{
	return (type == OPERAND_TYPE::MEM);
}

const Ceng::BOOL Operand::IsImmediateOperand() const
{
	return (type == OPERAND_TYPE::IMM);
}

const Ceng::BOOL Operand::IsMemoryRegisterOperand() const
{
	return (type == OPERAND_TYPE::REG_MEM);
}
