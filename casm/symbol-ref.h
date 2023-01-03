/*****************************************************************************
*
* symbol-ref.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_SYMBOL_REF_H
#define X86_SYMBOL_REF_H

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/boolean.h>
#include <ceng/datatypes/return-val.h>
#include <memory>

#include "enums/reference-type.h"
#include "enums/x86-operand-sizes.h"

namespace Casm
{
	class Symbol;

	class SymbolRef
	{
	public:
		std::shared_ptr<Symbol> symbol;
		Ceng::INT64 encodeOffset;
		Ceng::BOOL isUnsigned;

		Ceng::BOOL deleted;

		/**
		 * Offset of IP pointer
		 */
		Ceng::INT64 ipDelta;
		
		X86::OPERAND_SIZE::value encodeSize;
		Casm::REFERENCE_TYPE::value refType;

		SymbolRef(const std::shared_ptr<Symbol>& symbol,const Ceng::UINT64 offset,
							const X86::OPERAND_SIZE::value encodeSize,
							const Casm::REFERENCE_TYPE::value refType);

		Ceng::CRESULT WriteOffset(const Ceng::UINT64 baseAddress);

		Ceng::CRESULT ConfigIPdelta(const Ceng::UINT64 baseIP);
	};
}

#endif