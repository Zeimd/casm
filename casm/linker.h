/*****************************************************************************
*
* linker.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_LINKER_H
#define X86_LINKER_H

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/return-val.h>
#include <ceng/datatypes/ce-string.h>

namespace Casm
{
	class Program;
	class ObjectCode;

	class Linker
	{
	protected:
		Ceng::UINT32 cacheLine;

		Linker();
	public:
		
		Linker(const Ceng::UINT32 cacheLine);

		virtual ~Linker();

		Ceng::CRESULT LinkProgram(const Ceng::String &entryFunction,
			std::vector<Casm::ObjectCode*> &objects,Casm::Program **output);
			
	};
}

#endif