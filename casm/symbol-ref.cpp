/*****************************************************************************
*
* symbol-ref.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "symbol-ref.h"

#include "obj-function.h"

using namespace X86;

SymbolRef::SymbolRef(std::shared_ptr<Symbol> symbol,const Ceng::UINT64 offset,
					 const OPERAND_SIZE::value encodeSize,
					 const Casm::REFERENCE_TYPE::value refType,
					 const X86::SectionType::value section)
	: symbol(symbol),encodeOffset(offset),encodeSize(encodeSize),refType(refType),
	section(section),ipDelta(0),deleted(false)
{
}

Ceng::CRESULT SymbolRef::ConfigIPdelta(const Ceng::UINT64 baseIP)
{
	ipDelta = Ceng::INT64(baseIP - encodeOffset);

	return Ceng::CE_OK;
}

Ceng::CRESULT SymbolRef::WriteOffset(const Ceng::UINT64 baseAddress)
{

	bool isExtern = false;

	if (symbol->Type() == SymbolType::object_function)
	{
		X86::ObjectFunction* objFunc = symbol->AsObjectFunction();

		if (objFunc->SizeBytes() == 0)
		{
			isExtern = true;
		}
	}

	if (refType == Casm::REFERENCE_TYPE::ADDRESS)
	{
		switch(encodeSize)
		{
		case OPERAND_SIZE::DWORD:
			{
				Ceng::UINT32 *ptr = (Ceng::UINT32*)(Ceng::UINT32(baseAddress) + Ceng::UINT32(encodeOffset));
				*ptr = Ceng::UINT32(symbol->Offset());
			}
			break;
		case OPERAND_SIZE::QWORD:
			{
				Ceng::UINT64 *ptr = (Ceng::UINT64*)(Ceng::UINT64(baseAddress) + Ceng::UINT64(encodeOffset));
				*ptr = Ceng::UINT64(symbol->Offset());
			}
			break;
		}
	}
	else
	{
		// IP RELATIVE

		switch(encodeSize)
		{
		case OPERAND_SIZE::DWORD:
			{
				Ceng::INT32 *ptr = (Ceng::INT32*)(Ceng::UINT32(baseAddress) + Ceng::UINT32(encodeOffset));

				if (isExtern)
				{
					*ptr = Ceng::INT32(ipDelta);
				}
				else if (section == symbol->Section())
				{
					*ptr = Ceng::INT32(symbol->Offset() - (encodeOffset + ipDelta));
					deleted = true;
				}
				else
				{					
					*ptr = Ceng::INT32(symbol->Offset() - ipDelta);
				}
			}
			break;
		}
	}

	return Ceng::CE_OK;
}