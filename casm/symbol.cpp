/*****************************************************************************
*
* symbol.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "symbol.h"

#include "data-item.h"

#include "section.h"

using namespace Casm;

Symbol::Symbol() 
	: type(Casm::SymbolType::unknown), section(nullptr),
	offset(0), refCount(0), defined(false), isGlobal(false)
{

}

Symbol::Symbol(const Ceng::String& name, Casm::Section* section, 
	const Casm::SymbolType::value type,
	const Ceng::BOOL defined,const Ceng::BOOL isGlobal)
	: name(name), section(section), type(type), offset(0), 
	refCount(0), defined(defined),isGlobal(isGlobal)
{

}

Symbol::~Symbol()
{
}

Section* Symbol::GetSection() const
{
	return (Section*)section;
}

void Symbol::MarkDefined(Section* section, SymbolType::value type, Ceng::BOOL isGlobal)
{
	defined = true;

	this->section = section;

	this->type = type;
	this->isGlobal = isGlobal;
}

const char* Symbol::TypeToString(Casm::SymbolType::value symbolType)
{
	switch (symbolType)
	{
	case SymbolType::section:
		return "section";
		break;
	case SymbolType::function:
		return "function";
		break;
	case SymbolType::data:
		return "data";
		break;
	case SymbolType::unknown:
		return "unknown";
		break;
	default:
		return "<invalid_value>";
		break;
	}
}