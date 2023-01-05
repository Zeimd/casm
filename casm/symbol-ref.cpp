/*****************************************************************************
*
* symbol-ref.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "symbol-ref.h"

#include "symbol.h"

using namespace Casm;

SymbolRef::SymbolRef(const std::shared_ptr<Symbol> &symbol,
	Symbol* section, const Ceng::UINT64 offset,
	const X86::OPERAND_SIZE::value encodeSize,
	const Casm::REFERENCE_TYPE::value refType)
	: symbol(symbol), section(section), encodeOffset(offset),encodeSize(encodeSize),
	refType(refType),ipDelta(0),deleted(false)
{
}

Ceng::CRESULT SymbolRef::ConfigIPdelta(const Ceng::UINT64 baseIP)
{
	ipDelta = Ceng::INT64(baseIP - encodeOffset);

	return Ceng::CE_OK;
}

