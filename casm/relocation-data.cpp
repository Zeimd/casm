/*****************************************************************************
*
* relocation-data.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "relocation-data.h"

#include <iostream>

using namespace Casm;

RelocationData::RelocationData(const Ceng::String& symbol,
	const Casm::SymbolType::value symbolType,
	const Ceng::String& writeSection,
	const Ceng::UINT64 writeOffset,
	const X86::OPERAND_SIZE::value offsetSize,
	const Casm::RelocationType::value type,
	const Ceng::INT64 ipDelta)
	: symbol(symbol), symbolType(symbolType),
	writeSection(writeSection), writeOffset(writeOffset),
	offsetSize(offsetSize), type(type), ipDelta(ipDelta)
{

}