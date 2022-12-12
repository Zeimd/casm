/*****************************************************************************
*
* parser-instruction.h
*
* By Jari Korkala 5/2014
*
*****************************************************************************/

#ifndef CASM_PARSER_INSTRUCTION_H
#define CASM_PARSER_INSTRUCTION_H

#include "parser-operand.h"

#include "code-line.h"

namespace Casm
{
	class ParserInstruction : public ParserOperand
	{
	protected:

		X86::CodeLine *line;

	public:

		ParserInstruction(X86::CodeLine *line,const TokenData &data) :
			ParserOperand(ParserToken::instruction,ParserBasicType::unknown,0,data),line(line)
		{
		}

		virtual ~ParserInstruction()
		{
		}

		X86::CodeLine* GetCodeLine()
		{
			return line;
		}

	};
}

#endif