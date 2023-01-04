/*****************************************************************************
*
* code-label.cpp
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#include "code-label.h"

#include "section.h"

#include "symbol.h"

using namespace Casm;

CodeLabel::CodeLabel(const Ceng::UINT32 position,
	std::shared_ptr<Symbol>& symbol) 
	: CodeElement(LABEL, position), symbol(symbol),	target(nullptr)
{
}

CodeLabel::~CodeLabel()
{
}

CodeElement* CodeLabel::Target() const
{
	return target;
}

Ceng::BOOL CodeLabel::CompareName(const Ceng::String &test) const
{
	return (symbol->name == test);
}

Ceng::CRESULT CodeLabel::SetTarget(CodeElement* target)
{
	this->target = target;
	return Ceng::CE_OK;
}

void CodeLabel::Print(std::wostream& out) const
{
	out << symbol->name << ":" << std::endl;
}

void CodeLabel::SetOffset(const Ceng::UINT64 offset)
{
	this->offset = offset;
	symbol->SetOffset(offset);
}