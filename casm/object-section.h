
#ifndef CASM_OBJECT_SECTION_H
#define CASM_OBJECT_SECTION_H

#include "symbol.h"

#include <vector>

#include <ceng/datatypes/return-val.h>

namespace X86
{
	class RelocationData;
}

namespace Casm
{
	class Symbol;
	class SymbolRef;

	class ObjectSection : public Symbol
	{
	protected:

		ObjectSection();

	public:

		Ceng::UINT32 options;

		std::vector<Ceng::UINT8> codeBuffer;

	public:

		ObjectSection(const Ceng::String& name, const Ceng::UINT32 options);

		ObjectSection(const Ceng::String& name, const Ceng::UINT32 options,
			std::vector<Ceng::UINT8>&& codeBuffer);

		~ObjectSection() override;

		const Ceng::UINT32 SizeBytes() const
		{
			return codeBuffer.size();
		}

		Ceng::CRESULT Append(std::vector<Ceng::UINT8>& destBuffer) const;

		Ceng::CRESULT ToCodeBuffer(Ceng::UINT8* buffer) const;

		void Print(std::wostream& out) const;
	};
}

#endif