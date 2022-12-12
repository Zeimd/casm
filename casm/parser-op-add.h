/*****************************************************************************
*
* parser-op-add.h
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#ifndef CASM_PARSER_OP_ADD_H
#define CASM_PARSER_OP_ADD_H

#include "parser-operator.h"

namespace Casm
{
	class ParserOp_Add : public ParserOperator
	{
	public:

		ParserOp_Add(const TokenData &data);

		virtual ~ParserOp_Add();

		virtual const std::shared_ptr<ParserOperand> LocalAction(ParserState *state,
																std::shared_ptr<ParserOperand> left,
																std::shared_ptr<ParserOperand> right);
	};

	class ParserOp_Unary_Add : public ParserOperator
	{
	public:

		ParserOp_Unary_Add(const TokenData &data);

		virtual ~ParserOp_Unary_Add();

		virtual const std::shared_ptr<ParserOperand> LocalAction(ParserState *state,
																std::shared_ptr<ParserOperand> left,
																std::shared_ptr<ParserOperand> right);
	};

}

#endif