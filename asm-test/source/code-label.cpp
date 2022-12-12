/*****************************************************************************
*
* code-label.cpp
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#include "../include/code-label.h"

using namespace X86;

Label::Label(const Ceng::String name,const Ceng::BOOL undefined) 
	: name(name),undefined(undefined),target(nullptr)
{
}

Label::~Label()
{
}

CodeElement* Label::Target() const
{
	return target;
}

Ceng::BOOL Label::CompareName(const Ceng::String &test) const
{
	return (name == test);
}

Ceng::BOOL Label::Undefined() const
{
	return undefined;
}

void Label::MarkDefined()
{
	undefined = false;
}

Ceng::CRESULT Label::SetTarget(CodeElement *target)
{
	this->target = target;
	return Ceng::CE_OK;
}
