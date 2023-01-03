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
	offset(0), refCount(0), defined(false), external(false)
{

}

Symbol::Symbol(const Ceng::String& name, Casm::Section* section, 
	const Casm::SymbolType::value type,
	const Ceng::BOOL defined,const Ceng::BOOL external)
	: name(name), section(section), type(type), offset(0), 
	refCount(0), defined(defined),external(external)
{

}

Symbol::~Symbol()
{
}