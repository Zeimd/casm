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
#include <memory>
#include <vector>

#include <ostream>

namespace Casm
{
	class ObjectSection;
	class Symbol;
	class SymbolRef;

	class ObjectCode
	{
	public:

		std::vector<std::shared_ptr<ObjectSection>> sections;

		std::vector<std::shared_ptr<Symbol>> symbols;
		std::vector<std::shared_ptr<SymbolRef>> references;

		ObjectCode(std::vector<std::shared_ptr<ObjectSection>>&& sections,
			std::vector<std::shared_ptr<Symbol>>&& symbols,
			std::vector<std::shared_ptr<SymbolRef>>&& references);

		~ObjectCode();

		void Print(std::wostream& out) const;
	};
}

#endif