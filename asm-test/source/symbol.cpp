/*****************************************************************************
*
* symbol.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/symbol.h"

#include "../include/data-item.h"
#include "../include/function-builder.h"
#include "../include/obj-function.h"

using namespace X86;

Symbol::Symbol() 
	: type(SymbolType::unknown), section(SectionType::unknown),
	offset(0), refCount(0), defined(false), external(false)
{

}

Symbol::Symbol(const Ceng::String& name, const SectionType::value section, 
	const SymbolType::value type,
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