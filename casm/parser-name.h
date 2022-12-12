/*****************************************************************************
*
* parser-name.h
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#ifndef CASM_PARSER_NAME_H
#define CASM_PARSER_NAME_H

#include "parser-token.h"

namespace Casm
{
	class ParserName : public ParserToken
	{
	public:

		Ceng::String name;

	public:

		ParserName(const Ceng::String &name,const TokenData &data);

		virtual ~ParserName();

		const Ceng::String& Name() const;

	};
}

#endif