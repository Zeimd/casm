/*****************************************************************************
*
* parser-operator.cpp
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#include "../include/parser-operator.h"

/*

using namespace Casm;

ParserOperator::ParserOperator(const ParserOpType::value opType,
							   const ParserOpMode::value opMode,
							   const ParserOpRange::value opRange,
							   const ParserOpAssocDir::value opDir,
							   const Ceng::INT32 priority,
							   const Ceng::INT32 affects,
							   const TokenData &data) 
	: ParserToken(op,data),opType(opType),priority(priority),
						affects(affects),opRange(opRange),opDir(opDir),opMode(opMode)
{
}

ParserOperator::~ParserOperator()
{
}

const ParserOpType::value ParserOperator::OperatorType() const
{
	return opType;
}

const ParserOpRange::value ParserOperator::OperatorRange() const
{
	return opRange;
}

const Ceng::UINT32 ParserOperator::Priority() const
{
	return priority;
}

const Ceng::UINT32 ParserOperator::Affects() const
{
	return affects;
}

const std::shared_ptr<ParserOperand> ParserOperator::Action(ParserState *state,
															std::shared_ptr<ParserOperand> left,
															std::shared_ptr<ParserOperand> right)
{
	if (right == nullptr)
	{
		return nullptr;
	}

	// TODO: Separate class for this?

	if (opMode == ParserOpMode::binary)
	{
		if (left == nullptr)
		{
			return nullptr;
		}
	}

	return LocalAction(state,left,right);
}

*/
