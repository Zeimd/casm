/*****************************************************************************
*
* parser-comma.h
*
* By Jari Korkala 5/2014
*
*****************************************************************************/

#ifndef CASM_PARSER_COMMA_H
#define CASM_PARSER_COMMA_H

/*
#include "parser-operator.h"

namespace Casm
{
	class ParserComma : public ParserOperator
	{
	protected:

	public:

		ParserComma(const TokenData &data) 
			: ParserOperator(ParserOpType::separator,ParserOpMode::binary,ParserOpRange::nearest,
								ParserOpAssocDir::right,parser_priority_comma,3,data)
		{
		}

		virtual ~ParserComma()
		{
		}

		virtual const std::shared_ptr<ParserOperand> LocalAction(ParserState *state,
															std::shared_ptr<ParserOperand> left,
															std::shared_ptr<ParserOperand> right) override
		{
			return nullptr;
		}

	};
}
*/

#endif