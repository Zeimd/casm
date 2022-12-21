/*****************************************************************************
*
* parser-reg.h
*
* By Jari Korkala 4/2014
*
*****************************************************************************/

#ifndef CASM_PARSER_REG_H
#define CASM_PARSER_REG_H

/*
#include "parser-operand.h"

#include "x86-register-op.h"

namespace Casm
{
	class ParserRegister : public ParserOperand
	{
	protected:

		const X86::RegisterOperand *reg;

		const Ceng::UINT32 scale;

	public:

		ParserRegister(const X86::RegisterOperand *reg,const TokenData &data);

		ParserRegister(const X86::RegisterOperand *reg,const Ceng::UINT32 scale,const TokenData &data);

		const Ceng::BOOL IsIndexReg() const;
	
		const Ceng::BOOL IsComposite() const;

		const Ceng::UINT32 Scale() const;

		const X86::RegisterOperand* RegisterOp() const;
	
		virtual const std::shared_ptr<ParserOperand> BinaryMul(ParserState *state,
																std::shared_ptr<ParserOperand> left_this,
																std::shared_ptr<ParserOperand> right) override;

		static const Ceng::BOOL IsPow2(const Ceng::UINT32 x);
	};
}
*/

#endif