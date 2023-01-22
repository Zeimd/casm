/*****************************************************************************
*
* object-code.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_OBJECT_CODE_H
#define X86_OBJECT_CODE_H

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/ce-string.h>
#include <ceng/datatypes/return-val.h>

#include <memory>
#include <vector>

#include <ostream>

namespace Casm
{
	class ObjectSection;
	class Symbol;

	class RelocationData;

	struct ExternSymbol;

	class Executable;

	class SectionInfo
	{
	public:
		Symbol* section;
		Symbol* parent;
		Ceng::UINT32 options;
		Ceng::UINT64 offset;

		SectionInfo(Symbol* section,
			Symbol* parent,
			Ceng::UINT32 options,
			Ceng::UINT64 offset)
			: section(section), parent(parent), options(options),offset(offset)
		{

		}
	};


	class ObjectCode
	{
	public:
		Ceng::String name;

		std::vector<std::shared_ptr<ObjectSection>> sections;

		std::vector<std::shared_ptr<Symbol>> symbols;
		std::vector<RelocationData> relocationData;

		ObjectCode(const Ceng::String& name, std::vector<std::shared_ptr<ObjectSection>>&& sections,
			std::vector<std::shared_ptr<Symbol>>&& symbols,
			std::vector<RelocationData>&& relocationData);

		~ObjectCode();

		void Print(std::wostream& out) const;

		std::shared_ptr<Symbol> FindSymbol(const Ceng::String& name) const;

		std::shared_ptr<Symbol> FindSymbol(const Ceng::String& name,
			Casm::ExternSymbol* externs, uint32_t externCount) const;

		Ceng::CRESULT GetJitExecutable(const Ceng::String& entryPoint,
			Casm::ExternSymbol* externs, uint32_t externCount,
			Executable** output) const;

	protected:

		Ceng::UINT64 GetSectionBase(Symbol* section,
			std::vector<SectionInfo>& sectionInfo) const;
	};
}

#endif