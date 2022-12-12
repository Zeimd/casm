/*****************************************************************************
*
* keyword-group.cpp
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#include "../include/keyword-group.h"

using namespace Casm;

KeywordGroup::KeywordGroup()
{
}

KeywordGroup::~KeywordGroup()
{
}

ParserToken* KeywordGroup::FindKeyword(const Ceng::String &name) const
{
	auto iter = groups.begin();

	while(iter != groups.end())
	{
		ParserToken *temp = (*iter)->FindKeyword(name);

		if (temp != nullptr)
		{
			return temp;
		}

		++iter;
	}

	return nullptr;
}

