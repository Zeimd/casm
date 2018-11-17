/*****************************************************************************
*
* parser-op-sub.h
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#ifndef CASM_PARSER_OP_SUB_H
#define CASM_PARSER_OP_SUB_H

#include "parser-operator.h"

namespace Casm
{
	class ParserOp_Sub : public ParserOperator
	{
	public:

		ParserOp_Sub(const TokenData &data);

		virtual ~ParserOp_Sub();

		virtual const std::shared_ptr<ParserOperand> LocalAction(ParserState *state,
																std::shared_ptr<ParserOperand> left,
																std::shared_ptr<ParserOperand> right);
	};

	class ParserOp_Unary_Sub : public ParserOperator
	{
	public:

		ParserOp_Unary_Sub(const TokenData &data);

		virtual ~ParserOp_Unary_Sub();

		virtual const std::shared_ptr<ParserOperand> LocalAction(ParserState *state,
																std::shared_ptr<ParserOperand> left,
																std::shared_ptr<ParserOperand> right);	
	};

}

#endif