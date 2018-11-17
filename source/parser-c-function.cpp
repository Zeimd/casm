/*****************************************************************************
*
* parser-c-function.cpp
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#include "../include/parser-c-function.h"

using namespace Casm;

FunctionContext::FunctionContext()
{
}

FunctionContext::~FunctionContext()
{
}

const Ceng::BOOL FunctionContext::IsExitToken(ParserToken *token) const
{
	/*
	if (dynamic_cast<FunctionEndToken>(token))
	{
		return true;
	}
	*/
	return false;
}