/*****************************************************************************
*
* parser-context.h
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#ifndef CASM_PARSER_CONTEXT_H
#define CASM_PARSER_CONTEXT_H

#include "keyword-map.h"

#include <memory>

namespace Casm
{
	class ParserContext
	{
	public:
		std::shared_ptr<KeywordMap> overrideKeywords;
		std::shared_ptr<KeywordMap> keywords;

	public:

		ParserContext();
		~ParserContext();

		ParserToken* FindKeyword(const Ceng::String &name) const;

		virtual const Ceng::BOOL IsExitToken(ParserToken *token) const;
	};

}

#endif