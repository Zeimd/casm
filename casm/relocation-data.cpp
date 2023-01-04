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
	const Ceng::INT64 negativeExtra)
	: symbol(symbol), symbolType(symbolType),
	writeSection(writeSection), writeOffset(writeOffset),
	offsetSize(offsetSize), type(type), negativeExtra(negativeExtra)
{

}

/*
Ceng::CRESULT RelocationData::Relocate(const Ceng::UINT64 dataSectionBase,
									   const Ceng::UINT64 codeSectionBase,
	Casm::ExternSymbol* externs, uint32_t externCount) const
{
	Ceng::UINT64 writeAddress = codeSectionBase;

	if (writeSection == DATA_SECTION)
	{
		writeAddress = dataSectionBase;
	}

	writeAddress += writeOffset;

	Ceng::UINT64 symbolBase = dataSectionBase;
	if (relocationSection == CODE_SECTION)
	{
		symbolBase = codeSectionBase;
	}
	else if (relocationSection == EXTERNAL)
	{
		Casm::ExternSymbol* found = nullptr;

		for (uint32_t k = 0; k < externCount; k++)
		{
			if (externName == externs[k].name)
			{
				found = &externs[k];
				break;
			}
		}

		if (found == nullptr)
		{
			return Ceng::CE_ERR_FAIL;
		}

		symbolBase = (Ceng::UINT64)found->address;
	}

	std::wcout << "write address = 0x" << std::hex << writeAddress << std::dec << std::endl;

	std::wcout << "symbol section base = 0x" << std::hex << symbolBase << std::dec << std::endl;

	if (type == Casm::REFERENCE_TYPE::ADDRESS)
	{
		if (offsetSize == OPERAND_SIZE::DWORD)
		{
			Ceng::UINT32 *ptr = (Ceng::UINT32*)writeAddress;

			std::wcout << "initial offset = " << *ptr << "(0x" << std::hex << *ptr << std::dec << ")"
				<< std::endl;

			*ptr += Ceng::UINT32(symbolBase);
		}
		else if (offsetSize == OPERAND_SIZE::QWORD)
		{
			Ceng::UINT64 *ptr = (Ceng::UINT64*)writeAddress;

			*ptr += Ceng::UINT64(symbolBase);
		}
	}
	else if (type == Casm::REFERENCE_TYPE::IP_RELATIVE)
	{
		if (offsetSize == OPERAND_SIZE::DWORD)
		{
			Ceng::INT32* ptr = (Ceng::INT32*)writeAddress;

			// The value currently at writeAddress is
			// *ptr = symbolOffset - ipBase
			// NOTE: for externs symbolOffset = 0

			std::wcout << "initial = 0x" << std::hex << *ptr << std::dec << std::endl;

			// What we want here is
			// symbolBase + symbolOffset - (writeAddress + ipBase)
			// but since symbolOffset isn't known at relocation time,
			// we encode it and ipBase into the immediate field

			*ptr = Ceng::INT32(symbolBase) - Ceng::INT32(writeAddress) + *ptr;

			std::wcout << "final = 0x" << std::hex << *ptr << std::dec << std::endl;
		}
	}		

	return Ceng::CE_OK;
}
*/