/*****************************************************************************
*
* linker.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_LINKER_H
#define X86_LINKER_H

#include <datatypes/basic-types.h>
#include <datatypes/return-val.h>
#include <datatypes/ce-string.h>

namespace X86
{
	class Program;
	class ObjectCode;
}

namespace Casm
{
	class Linker
	{
	protected:
		Ceng::UINT32 cacheLine;

		Linker();
	public:
		
		Linker(const Ceng::UINT32 cacheLine);

		virtual ~Linker();

		Ceng::CRESULT LinkProgram(const Ceng::String &entryFunction,
			std::vector<X86::ObjectCode*> &objects,X86::Program **output);
			
	};
}

#endif