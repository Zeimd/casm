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
#include <memory>
#include <vector>

#include <ostream>

namespace Casm
{
	class ObjectSection;
	class Symbol;
	class SymbolRef;

	class RelocationData;

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

		std::shared_ptr<Symbol> FindSymbol(const Ceng::String& name);
	};
}

#endif