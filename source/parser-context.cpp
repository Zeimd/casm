/*****************************************************************************
*
* parser-context.cpp
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#include "../include/parser-context.h"

using namespace Casm;

ParserContext::ParserContext()
{
}

ParserContext::~ParserContext()
{
}

const Ceng::BOOL ParserContext::IsExitToken(ParserToken *token) const
{
	return nullptr;
}

ParserToken* ParserContext::FindKeyword(const Ceng::String &name) const
{
	ParserToken *temp;

	if (overrideKeywords != nullptr)
	{
		temp = overrideKeywords->FindKeyword(name);

		if (temp != nullptr)
		{
			return temp;
		}
	}

	if (keywords != nullptr)
	{
		return keywords->FindKeyword(name);
	}

	return nullptr;
}