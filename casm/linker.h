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
	class ObjectCode;
	class ObjectSection;
	class Symbol;

	class Linker
	{
	protected:
		Ceng::UINT32 cacheLine;

		Linker();
	public:
		
		Linker(const Ceng::UINT32 cacheLine);

		virtual ~Linker();

		Ceng::CRESULT LinkProgram(const Ceng::String& name,
			std::vector<Casm::ObjectCode*> &objects,
			std::shared_ptr<ObjectCode>& output);

	protected:

		std::shared_ptr<Symbol> FindSymbol(
			const Ceng::String& name,
			Casm::ObjectCode* currentFile,
			std::vector<Casm::ObjectCode*>& files);

		std::shared_ptr<ObjectSection> FindSection(
			const Ceng::String& name,
			const std::vector<std::shared_ptr<ObjectSection>>& sections);
			
	};
}

#endif