/*****************************************************************************
*
* parser-variable.h
*
* By Jari Korkala 5/2014
*
*****************************************************************************/

#ifndef CASM_PARSER_VARIABLE_H
#define CASM_PARSER_VARIABLE_H

#include "parser-operand.h"

namespace Casm
{
	class ParserVariable : public ParserOperand
	{
	public:

	protected:

		std::shared_ptr<X86::Symbol> variable;

	public:

		ParserVariable() : ParserOperand(ParserToken::variable,ParserBasicType::unknown,0,TokenData())
		{
		}

		virtual ~ParserVariable()
		{
		}

		ParserVariable(std::shared_ptr<X86::Symbol> variable,
						const TokenData &data) 
			: ParserOperand(ParserToken::variable,ParserBasicType::unknown,0,data),variable(variable)
		{
		}

		virtual const Ceng::BOOL RangeCheck(const Ceng::INT64 minValue,const Ceng::UINT64 maxValue) const override
		{
			return false;
		}

		virtual const Ceng::BOOL RangeCheck(const Ceng::FLOAT64 minValue,const Ceng::FLOAT64 maxValue) const override
		{
			return false;
		}

		virtual const Ceng::BOOL UnderflowCheck(const Ceng::FLOAT64 minPosValue) const override
		{
			return false;
		}

		virtual operator const Ceng::FLOAT32() const
		{
			return 0.0f;
		}

		virtual operator const Ceng::UINT64() const
		{
			return 0;
		}

		virtual operator const Ceng::INT64() const
		{
			return 0;
		}
	};
}

#endif