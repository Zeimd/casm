/*****************************************************************************
*
* keyword-hash.h
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#ifndef CASM_KEYWORD_HASH_H
#define CASM_KEYWORD_HASH_H

#include "keyword-map.h"

namespace Casm
{
	class KeywordHashMap : public KeywordMap
	{
	public:

		std::unordered_map<std::string,std::shared_ptr<ParserToken>> map;
	
	public:

		KeywordHashMap()
		{
		}

		virtual ~KeywordHashMap()
		{
		}

		virtual ParserToken* FindKeyword(const Ceng::String &name) const
		{
			auto iter = map.find(std::string(name.ToCString()));

			if (iter == map.end())
			{
				return nullptr;
			}

			auto pair = *iter;

			return static_cast<ParserToken*>(pair.second.get());
		}
	};
}

#endif