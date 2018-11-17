/*****************************************************************************
*
* parser-opcode.h
*
* By Jari Korkala 5/2014
*
*****************************************************************************/

#ifndef CASM_PARSER_OPCODE_H
#define CASM_PARSER_OPCODE_H

#include "parser-operator.h"

#include "x86-instruction.h"

namespace Casm
{
	class ParserOpcode : public ParserOperator
	{
	protected:

		const X86::Instruction *instruction;
	
	public:

		ParserOpcode(const X86::Instruction *instruction,const TokenData &data);

		virtual ~ParserOpcode();

		virtual const std::shared_ptr<ParserOperand> Action(ParserState *state,
														std::shared_ptr<ParserOperand> left,
														std::shared_ptr<ParserOperand> right) override;

		virtual const std::shared_ptr<ParserOperand> LocalAction(ParserState *state,
															std::shared_ptr<ParserOperand> left,
															std::shared_ptr<ParserOperand> right) override;
	};
}

#endif