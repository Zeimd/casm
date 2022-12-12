/*****************************************************************************
*
* parser-c-function.h
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#ifndef CASM_PARSER_C_FUNCTION_H
#define CASM_PARSER_C_FUNCTION_H

#include "parser-context.h"

namespace Casm
{
	class FunctionContext : public ParserContext
	{
	public:

		FunctionContext();

		~FunctionContext();

		virtual const Ceng::BOOL IsExitToken(ParserToken *token) const;
	};
}

#endif