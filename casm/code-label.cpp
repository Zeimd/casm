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

Label::Label(const Ceng::UINT32 position,
	Section* section, const Ceng::String name,const Ceng::BOOL undefined,
	bool isGlobal) 
	: CodeElement(LABEL, position),	
	section(section), name(name),undefined(undefined), isGlobal(isGlobal),
	target(nullptr)
{
}

Label::~Label()
{
}

std::shared_ptr<CodeElement> Label::Target() const
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

Ceng::CRESULT Label::SetTarget(std::shared_ptr<CodeElement> &target)
{
	this->target = target;
	return Ceng::CE_OK;
}

void Label::Print(std::wostream& out) const
{
	out << name << ":" << std::endl;
}

bool Label::IsGlobal() const
{
	return isGlobal;
}