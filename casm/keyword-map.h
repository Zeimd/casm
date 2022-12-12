/*****************************************************************************
*
* keyword-map.h
*
* By Jari Korkala 5/2014
*
*****************************************************************************/

#ifndef CASM_KEYWORD_MAP_H
#define CASM_KEYWORD_MAP_H

#include "parser-token.h"

#include <string>
#include <unordered_map>

namespace Casm
{
	class KeywordMap
	{
	public:

		virtual ~KeywordMap()
		{
		}

		virtual ParserToken* FindKeyword(const Ceng::String &name) const =0;
	};
}

#endif