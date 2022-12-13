/*****************************************************************************
*
* parser-op-sub.cpp
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#include "../include/parser-op-sub.h"

/*

using namespace Casm;

ParserOp_Sub::ParserOp_Sub(const TokenData &data) 
	: ParserOperator(ParserOpType::sub,ParserOpMode::binary,
		ParserOpRange::nearest,ParserOpAssocDir::right,parser_priority_add,3,data)
{
}

ParserOp_Sub::~ParserOp_Sub()
{
}

const std::shared_ptr<ParserOperand> ParserOp_Sub::LocalAction(ParserState *state,
														std::shared_ptr<ParserOperand> left,
														std::shared_ptr<ParserOperand> right)
{
	return left->BinarySub(state,left,right);
}

//**************************************************************************************
// Unary sub

ParserOp_Unary_Sub::ParserOp_Unary_Sub(const TokenData &data) 
	: ParserOperator(ParserOpType::unary_sub,ParserOpMode::unary_prefix,
		ParserOpRange::nearest,ParserOpAssocDir::left,parser_priority_unary_add,2,data)
{
}

ParserOp_Unary_Sub::~ParserOp_Unary_Sub()
{
}

const std::shared_ptr<ParserOperand> ParserOp_Unary_Sub::LocalAction(ParserState *state,
														std::shared_ptr<ParserOperand> left,
														std::shared_ptr<ParserOperand> right)
{
	return *right *= -1;
}

*/