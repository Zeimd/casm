/*****************************************************************************
*
* dynamic-library.h
*
* Created By Jari Korkala 28/2/2015
*
*****************************************************************************/

#ifndef CENG_DYNAMIC_LIBRARY_H
#define CENG_DYNAMIC_LIBRARY_H

#include "base-interface.h"
#include "../datatypes/ce-string.h"

namespace Ceng
{
	

	class DynamicLibrary : public BASE_INTERFACE
	{
	protected:

		virtual ~DynamicLibrary()
		{
		}

	public:

		DynamicLibrary()
		{
		}

		virtual void Release() = 0;

		virtual DynamicCallback GetFunction(const Ceng::String &name) = 0;
		virtual DynamicCallback GetFunction(const char *name) = 0;
		virtual DynamicCallback GetFunction(const wchar_t *name) = 0;
	};
}

#endif