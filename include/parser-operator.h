/*****************************************************************************
*
* parser-operator.h
*
* By Jari Korkala 5/2014
*
*****************************************************************************/

#ifndef CASM_PARSER_OPERATOR_H
#define CASM_PARSER_OPERATOR_H

#include "parser-operand.h"

#include "parser-group.h"

#include "parser-state.h"

namespace Casm
{
	namespace ParserOpType
	{
		enum value
		{
			unknown = 0 ,

			add = 1 ,
			sub = 2 ,

			mul = 3 ,
			div = 4 ,

			unary_add = 5 ,
			unary_sub = 6 ,

			unary_parenthesis = 7 ,

			/**
			 * Type cast according to target type size.
			 */
			size_cast = 8 ,

			/**
			 * Create a memory operand.
			 */
			memory = 9 ,

			opcode = 10 ,

			separator = 11 ,		

			func_decl = 12 ,

			force_32b = 1 << 30 ,
		};
	}

	namespace ParserOpAssocDir
	{
		enum value
		{
			/**
			 * Operators of same priority are processed left to right.
			 */
			left = 1 ,

			/**
			 * Operators of same priority are processed right to left.
			 */
			right = 2 ,

			force_32b = 1 << 30 ,
		};
	}

	namespace ParserOpMode
	{
		enum value
		{
			unary_prefix = 1 ,
			unary_postfix = 1 << 1 ,

			binary = 1 << 2 ,

			force32_b = 1 << 30 ,
		};
	}

	namespace ParserOpRange
	{
		enum value
		{
			/**
			 * Operator takes nearest token from the left / right as argument.
			 */
			nearest = 1 ,

			/**
			 * Operator takes everything from left/right as argument.
			 */
			all = 2 ,

			force_32b = 1 << 30 ,
		};
	}

	class ParserOperator : public ParserToken
	{
	protected:

		const ParserOpType::value opType;
		
		const ParserOpAssocDir::value opDir;

		const ParserOpRange::value opRange;

		const ParserOpMode::value opMode;

		const Ceng::UINT32 priority;

		const Ceng::INT32 affects;

	public:

		ParserOperator(const ParserOpType::value opType,
						const ParserOpMode::value opMode,
						const ParserOpRange::value opRange,
						const ParserOpAssocDir::value opDir,
							const Ceng::INT32 priority,
							const Ceng::INT32 affects,
							const TokenData &data);

		const ParserOpType::value OperatorType() const;

		const ParserOpRange::value OperatorRange() const;

		const Ceng::UINT32 Priority() const;

		const Ceng::UINT32 Affects() const;

		virtual ~ParserOperator();

		virtual const std::shared_ptr<ParserOperand> Action(ParserState *state,
														std::shared_ptr<ParserOperand> left,
														std::shared_ptr<ParserOperand> right);

		virtual const std::shared_ptr<ParserOperand> LocalAction(ParserState *state,
															std::shared_ptr<ParserOperand> left,
															std::shared_ptr<ParserOperand> right)=0;
	};

	const Ceng::UINT32 parser_priority_block_decl = 0;

	const Ceng::UINT32 parser_priority_parenthesis = 1;

	const Ceng::UINT32 parser_priority_member_select = 2;

	const Ceng::UINT32 parser_priority_unary_add = 3;

	const Ceng::UINT32 parser_priority_mul = 4;
	const Ceng::UINT32 parser_priority_add = 5;

	const Ceng::UINT32 parser_priority_comma = 6;

	const Ceng::UINT32 parser_priority_opcode = 7;
	
	
}

#endif