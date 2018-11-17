/*****************************************************************************
*
* relocation-data.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/relocation-data.h"

using namespace X86;

Ceng::CRESULT RelocationData::Relocate(const Ceng::UINT64 dataSectionBase,
									   const Ceng::UINT64 codeSectionBase) const
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

		if (offsetSize == OPERAND_SIZE::DWORD)
		{
			Ceng::UINT32 *ptr = (Ceng::UINT32*)writeAddress;

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