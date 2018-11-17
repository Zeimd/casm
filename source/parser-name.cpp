/*****************************************************************************
*
* parser-name.cpp
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#include "../include/parser-name.h"

using namespace Casm;

ParserName::ParserName(const Ceng::String &name,const TokenData &data)
	: ParserToken(ParserToken::name,data),name(name)
{
}

ParserName::~ParserName()
{
}

const Ceng::String& ParserName::Name() const
{
	return name;
}