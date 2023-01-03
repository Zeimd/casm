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

CodeLabel::CodeLabel(const Ceng::UINT32 position,
	Section* section, const Ceng::String name,const Ceng::BOOL undefined,
	bool isGlobal) 
	: CodeElement(LABEL, position),	
	section(section), name(name),undefined(undefined), isGlobal(isGlobal),
	target(nullptr)
{
}

CodeLabel::~CodeLabel()
{
}

std::shared_ptr<CodeElement> CodeLabel::Target() const
{
	return target;
}

Ceng::BOOL CodeLabel::CompareName(const Ceng::String &test) const
{
	return (name == test);
}

Ceng::BOOL CodeLabel::Undefined() const
{
	return undefined;
}

void CodeLabel::MarkDefined()
{
	undefined = false;
}

Ceng::CRESULT CodeLabel::SetTarget(std::shared_ptr<CodeElement> &target)
{
	this->target = target;
	return Ceng::CE_OK;
}

void CodeLabel::Print(std::wostream& out) const
{
	out << name << ":" << std::endl;
}

bool CodeLabel::IsGlobal() const
{
	return isGlobal;
}