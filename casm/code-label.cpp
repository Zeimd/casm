/*****************************************************************************
*
* code-label.cpp
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#include "code-label.h"

#include "section.h"

using namespace Casm;

Label::Label(Section* section, const Ceng::String name,const Ceng::BOOL undefined) 
	: section(section), name(name),undefined(undefined),target(nullptr)
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

void Label::Print(std::wostream& out) const
{
	out << name << ":" << std::endl;
}