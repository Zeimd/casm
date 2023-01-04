/*****************************************************************************
*
* relocation-data.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_RELOCATION_DATA_H
#define X86_RELOCATION_DATA_H

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/return-val.h>
#include <ceng/datatypes/ce-string.h>

#include "enums/reference-type.h"
#include "enums/x86-operand-sizes.h"

#include "enums/symbol-type.h"

#include "enums/relocation-type.h"

#include "extern-symbol.h"

namespace Casm
{
	class RelocationData
	{
	public:

		Ceng::String symbol;

		Casm::SymbolType::value symbolType;

		Casm::RelocationType::value type;

		// Section that needs to be modified for the relocation
		Ceng::String writeSection;

		// Which offset the relocation value is written to.
		Ceng::UINT64 writeOffset;

		X86::OPERAND_SIZE::value offsetSize;

		Ceng::INT64 ipDelta;

		RelocationData(const Ceng::String& symbol,
			const Casm::SymbolType::value symbolType,
			const Ceng::String& writeSection,
			const Ceng::UINT64 writeOffset,
			const X86::OPERAND_SIZE::value offsetSize,
			const Casm::RelocationType::value type,
			const Ceng::INT64 ipDelta);

		/*
		Ceng::CRESULT Relocate(const Ceng::UINT64 dataSectionBase,
								const Ceng::UINT64 codeSectionBase,
			Casm::ExternSymbol* externs, uint32_t externCount) const;
			*/
	};
}

#endif