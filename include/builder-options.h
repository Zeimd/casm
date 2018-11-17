/*****************************************************************************
*
* builder-options.h
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#ifndef CASM_BUILDER_OPTIONS_H
#define CASM_BUILDER_OPTIONS_H

#include <datatypes/boolean.h>

namespace Casm
{
	class BuilderOptions
	{
	public:
		Ceng::BOOL outputAssembly;

		BuilderOptions()
			: outputAssembly(false)
		{
		}

		BuilderOptions(const Ceng::BOOL outputAssembly)
			: outputAssembly(outputAssembly)
		{
		}
	};
}

#endif