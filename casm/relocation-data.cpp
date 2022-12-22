/*****************************************************************************
*
* relocation-data.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "relocation-data.h"

#include <iostream>

using namespace X86;

Ceng::CRESULT RelocationData::Relocate(const Ceng::UINT64 dataSectionBase,
									   const Ceng::UINT64 codeSectionBase,
	Casm::ExternSymbol* externs, uint32_t externCount) const
{
	if (type == Casm::REFERENCE_TYPE::ADDRESS)
	{
		Ceng::UINT64 writeAddress = codeSectionBase;

		if (writeSection == DATA_SECTION)
		{
			writeAddress = dataSectionBase;
		}
				
		writeAddress += writeOffset;

		Ceng::UINT64 value = dataSectionBase;
		if (relocationSection == CODE_SECTION)
		{
			value = codeSectionBase;
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

			value = (Ceng::UINT64)found->address;
		}

		std::wcout << "write address = 0x" << std::hex << writeAddress << std::dec << std::endl;

		std::wcout << "symbol section base = 0x" << std::hex << value << std::dec << std::endl;


		if (offsetSize == OPERAND_SIZE::DWORD)
		{
			Ceng::UINT32 *ptr = (Ceng::UINT32*)writeAddress;

			std::wcout << "initial offset = " << *ptr << "(0x" << std::hex << *ptr << std::dec << ")"
				<< std::endl;

			*ptr += Ceng::UINT32(value);
		}
		else if (offsetSize == OPERAND_SIZE::QWORD)
		{
			Ceng::UINT64 *ptr = (Ceng::UINT64*)writeAddress;

			*ptr += Ceng::UINT64(value);
		}
	}
	else if (type == Casm::REFERENCE_TYPE::IP_RELATIVE)
	{
		//Ceng::INT64 delta = Ceng::INT64(
	}

			

	return Ceng::CE_OK;
}