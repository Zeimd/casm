/*****************************************************************************
*
* parser-state.h
*
* By Jari Korkala 5/2014
*
*****************************************************************************/

#ifndef CASM_PARSER_STATE_H
#define CASM_PARSER_STATE_H

#include "parser-token.h"

#include "parser-context.h"

#include <lib/liblog.h>

namespace X86
{
	class ProgramBuilder;
}

namespace Casm
{
	class ParserState
	{
	public:

		X86::ProgramBuilder *program;

		Ceng::LogType *errorLog;

		ParserContext *activeContext;

		std::vector<std::shared_ptr<ParserContext>> contextStack;

	public:
		ParserState();

		virtual ~ParserState();
	};
}

#endif