/*****************************************************************************
*
* parser-op-size.cpp
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#include "../include/parser-op-size.h"

using namespace Casm;

ParserOp_SizeCast::ParserOp_SizeCast(const Ceng::UINT32 newSize,const TokenData &data) 
	: ParserOperator(ParserOpType::size_cast,ParserOpMode::unary_prefix,
		ParserOpRange::nearest,ParserOpAssocDir::right,parser_priority_mul,2,data),
		newSize(newSize)
{
}

ParserOp_SizeCast::~ParserOp_SizeCast()
{
}

const std::shared_ptr<ParserOperand> ParserOp_SizeCast::LocalAction(ParserState *state,
														std::shared_ptr<ParserOperand> left,
														std::shared_ptr<ParserOperand> right)
{
	return right->SizeCast(state,right,newSize);
}