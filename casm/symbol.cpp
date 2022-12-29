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
	: type(X86::SymbolType::unknown), section(nullptr),
	offset(0), refCount(0), defined(false), external(false)
{

}

Symbol::Symbol(const Ceng::String& name, Casm::Section* section, 
	const X86::SymbolType::value type,
	const Ceng::BOOL defined,const Ceng::BOOL external)
	: name(name), section(section), type(type), offset(0), 
	refCount(0), defined(defined),external(external)
{

}

Symbol::~Symbol()
{
}

DataItem* Symbol::AsData() const
{
	return (DataItem*)this;
}

FunctionBuilder* Symbol::AsFunction() const
{
	return (FunctionBuilder*)this;
}

ObjectFunction* Symbol::AsObjectFunction() const
{
	return (ObjectFunction*)this;
}