/*****************************************************************************
*
* parser-register.cpp
*
* By Jari Korkala 5/2014
*
*****************************************************************************/

#include "../include/parser-register.h"

using namespace Casm;

ParserRegister::ParserRegister(const X86::RegisterOperand *reg,const TokenData &data) 
	: ParserOperand(ParserToken::registerOp,ParserBasicType::unknown,0,data),reg(reg),scale(1)
{
}

ParserRegister::ParserRegister(const X86::RegisterOperand *reg,const Ceng::UINT32 scale,const TokenData &data) 
	: ParserOperand(ParserToken::registerOp,ParserBasicType::unknown,0,data),reg(reg),scale(scale)
{
}

const Ceng::BOOL ParserRegister::IsIndexReg() const
{
	return (scale > 1);
}

const Ceng::BOOL ParserRegister::IsComposite() const
{
	return !IsPow2(scale);
}

const Ceng::UINT32 ParserRegister::Scale() const
{
	return scale;
}

const X86::RegisterOperand* ParserRegister::RegisterOp() const
{
	return reg;
}

const std::shared_ptr<ParserOperand> ParserRegister::BinaryMul(ParserState *state,
															   std::shared_ptr<ParserOperand> left_this,
															   std::shared_ptr<ParserOperand> right)
{
	if (right->Datatype() & ParserBasicType::floating)
	{
		// Invalid multiplier type

		return nullptr;
	}

	Ceng::UINT32 temp = Ceng::UINT64(*right);

	/**
		* Valid multipliers:
		*
		* Index reg only: 1,2,4,8
		*
		* Additional if base = index : 3,5,9
		*/

	if (temp > 9)
	{
		// Too large value

		return nullptr;
	}

	Ceng::BOOL test = IsPow2(temp);

	if ( IsPow2(temp) || IsPow2(temp-1))
	{
		return std::shared_ptr<ParserOperand>(new ParserRegister(reg,temp,data));
	}

	return nullptr;
}

const Ceng::BOOL ParserRegister::IsPow2(const Ceng::UINT32 x)
{
	return !(x & (x-1));
}