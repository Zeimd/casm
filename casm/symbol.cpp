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
{
	type = TYPE::UNKNOWN;
	offset = 0;
	refCount = 0;
	defined = false;
	external = false;
}

Symbol::Symbol(const Ceng::String &name) 
	: name(name),defined(true),external(false),refCount(0),offset(0)
{
}

Symbol::Symbol(const Ceng::String &name,const TYPE type,const Ceng::BOOL defined,const Ceng::BOOL external) 
	: name(name),type(type),defined(defined),external(external),refCount(0),offset(0)
{
}

Symbol::~Symbol()
{
}

Ceng::TempPtr<DataItem> Symbol::AsData() const
{
	return (DataItem*)this;
}

Ceng::TempPtr<FunctionBuilder> Symbol::AsFunction() const
{
	return (FunctionBuilder*)this;
}

Ceng::TempPtr<ObjectFunction> Symbol::AsObjectFunction() const
{
	return (ObjectFunction*)this;
}