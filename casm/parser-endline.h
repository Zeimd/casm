/*****************************************************************************
*
* parser-endline.h
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#ifndef CASM_PARSER_ENDLINE_H
#define CASM_PARSER_ENDLINE_H

#include "parser-token.h"

namespace Casm
{
	class Marker : public ParserToken
	{
	public:

		Marker() : ParserToken(ParserToken::unknown,TokenData())
		{
		}

		virtual ~Marker()
		{
		}
	};

	class Endline : public Marker
	{
	public:

		Endline() 
		{
		}

		virtual ~Endline()
		{
		}

		virtual const char* TypeString() const
		{
			return "end of line";
		}

		virtual void LexographAction(ParserState *state)
		{

		}
	};
}

#endif