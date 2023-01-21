/*****************************************************************************
*
* object-code.cpp
*
* By Jari Korkala 12/2022
*
*****************************************************************************/

#include "object-code.h"

#include "data-item.h"

#include "object-section.h"

#include "symbol.h"

#include "section.h"

#include "relocation-data.h"

#include "executable.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using namespace Casm;

ObjectCode::ObjectCode(const Ceng::String& name,
	std::vector<std::shared_ptr<ObjectSection>>&& sections,
	std::vector<std::shared_ptr<Symbol>>&& symbols,
	std::vector<RelocationData>&& relocationData)
	: name(name), sections(sections), symbols(symbols), relocationData(relocationData)
{
}

ObjectCode::~ObjectCode()
{

}

std::shared_ptr<Symbol> ObjectCode::FindSymbol(const Ceng::String& name) const
{
	for (auto& x : symbols)
	{
		if (x->name == name)
		{
			return x;
		}
	}

	return nullptr;
}

std::shared_ptr<Symbol> ObjectCode::FindSymbol(const Ceng::String& name,
	Casm::ExternSymbol* externs, uint32_t externCount) const
{
	std::shared_ptr<Symbol> temp = FindSymbol(name);

	if (temp != nullptr)
	{
		return temp;
	}

	Casm::ExternSymbol* found = nullptr;

	for (uint32_t k = 0; k < externCount; k++)
	{
		if (name == externs[k].name)
		{
			found = &externs[k];
			break;
		}
	}

	if (found == nullptr)
	{
		return nullptr;
	}

	temp = std::make_shared<Symbol>(found->name, nullptr, found->type, true, true);

	temp->SetOffset((Ceng::INT64)found->address);

	return temp;
}

Ceng::UINT64 ObjectCode::GetSectionBase(Symbol* section,
	std::vector<SectionInfo>& sectionInfo) const
{
	Ceng::UINT64 baseAddress = 0;

	if (section == nullptr)
	{
		std::wcout << "ERROR: GetSectionBase: nullptr" << std::endl;
		return 0;
	}

	std::wcout << "GetSectionBase : " << section->name << std::endl;

	for (auto& x : sectionInfo)
	{
		if (x.section->name == section->name)
		{
			std::wcout << "offset = " << std::hex << x.offset <<std::dec << std::endl;

			baseAddress = x.offset;

			if (x.parent != nullptr)
			{
				baseAddress += GetSectionBase(x.parent, sectionInfo);
			}
			return baseAddress;
		}
	}

	return 0;

}

Ceng::CRESULT ObjectCode::GetJitExecutable(const Ceng::String& entryPoint,
	Casm::ExternSymbol* externs, 
	uint32_t externCount, Executable** output) const
{
	std::wcout << "JIT: start" << std::endl;

	*output = nullptr;

	std::vector<SectionInfo> sectionInfo;

	Symbol virtualCode("::out_code::", nullptr, SymbolType::section, true, true);

	Symbol virtualData("::out_data::", nullptr, SymbolType::section, true, true);

	sectionInfo.emplace_back(&virtualCode, nullptr, 0);
	sectionInfo.emplace_back(&virtualData, nullptr, 0);

	Ceng::UINT64 codeSize = 0;
	Ceng::UINT64 dataSize = 0;

	for (auto& x : sections)
	{
		if (x->options & SectionOptions::executable)
		{
			sectionInfo.emplace_back(x.get(), &virtualCode, codeSize);

			codeSize += x->SizeBytes();
		}
		else 
		{
			sectionInfo.emplace_back(x.get(), &virtualData, dataSize);

			dataSize += x->SizeBytes();
		}
	}

	Ceng::UINT64 allocSize = codeSize;

	if (allocSize & 4095)
	{
		allocSize = (allocSize + 4095) & ~4095;
	}

	Ceng::UINT8* execPage = nullptr;

	execPage = (Ceng::UINT8*)VirtualAlloc(nullptr, SIZE_T(allocSize), 
		MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	if (execPage == nullptr)
	{
		std::wcout << "ERROR: JIT: Failed to allocate executable memory" << std::endl;
		return Ceng::CE_ERR_OUT_OF_MEMORY;
	}

	sectionInfo[0].offset = (Ceng::UINT64)execPage;

	Ceng::AlignedBuffer<Ceng::UINT8> data;

	data = Ceng::AlignedBuffer<Ceng::UINT8>::AlignedBuffer(dataSize, 4096);

	sectionInfo[1].offset = (Ceng::UINT64)&data[0];

	std::wcout << "section info dump:" << std::endl;

	for (auto& x : sectionInfo)
	{
		std::wcout << x.section->name << " : " << x.offset;
		if (x.parent != nullptr)
		{
			std::wcout << ", parent = " << x.parent->name;
		}
		std::wcout << std::endl;
	}


	// Copy buffers to final locations

	Ceng::UINT32 offset = 0;

	for (auto& x : sections)
	{
		if (x->options & SectionOptions::executable)
		{
			x->ToCodeBuffer(&execPage[offset]);
			offset += x->SizeBytes();
		}
	}

	offset = 0;

	for (auto& x : sections)
	{
		if ((x->options & SectionOptions::executable) == 0)
		{
			x->ToCodeBuffer(&data[offset]);
			offset += x->SizeBytes();
		}
	}



	std::wcout << "GetExecutable:" << std::endl;

	std::wcout << "data section base = 0x" << std::hex << &data[0] << std::dec << std::endl;

	std::wcout << "code section base = 0x" << std::hex << &execPage[0] << std::dec << std::endl;

	std::wcout << "data section size = " << data.GetElements() << std::endl;

	std::wcout << "code section size = " << codeSize << std::endl;

	// Relocationing

	//std::wcout << "relocationing:" << std::endl;

	for (auto& relocation : relocationData)
	{
		std::wcout << "symbol : " << relocation.symbol << std::endl;

		std::shared_ptr<ObjectSection> relocationSection =
			std::static_pointer_cast<ObjectSection>(
				FindSymbol(relocation.writeSection)
				);

		std::wcout << "relocation section : " << relocationSection->name << std::endl;

		Ceng::UINT64 fullWriteAddress =
			relocation.writeOffset + GetSectionBase(relocationSection.get(), sectionInfo);

		std::wcout << "full write address = " << std::hex << fullWriteAddress << std::dec
			<< std::endl;

		std::shared_ptr<Symbol> symbol = FindSymbol(relocation.symbol,
			externs, externCount);

		if (symbol == nullptr)
		{
			std::wcout << "ERROR: JIT: Undefined symbol: " << relocation.symbol << std::endl;
			return Ceng::CE_ERR_UNDEFINED_UNIFORM;
		}

		Ceng::UINT64 symbolAddress = 0;

		if (symbol->GetSection() == nullptr)
		{
			// External symbol

			// Value in target field is zero

			symbolAddress = symbol->Offset();
		}
		else
		{
			// Local symbol

			// Value in target field = symbol's offset within section

			symbolAddress = GetSectionBase(symbol->GetSection(), sectionInfo);
		}

		std::wcout << "symbol address = " << std::hex << symbolAddress << std::dec << std::endl;

		switch (relocation.type)
		{
		case RelocationType::rel32_add:
		{
			Ceng::INT32* ptr =
				(Ceng::INT32*)fullWriteAddress;

			*ptr += Ceng::INT32(symbolAddress - fullWriteAddress);
		}
		break;
		case RelocationType::full_int32:

		{
			Ceng::INT32* ptr = (Ceng::INT32*)fullWriteAddress;

			*ptr += Ceng::INT32(symbolAddress);
		}

		break;
		case RelocationType::full_uint32:

			{
				Ceng::UINT32* ptr =	(Ceng::UINT32*)fullWriteAddress;


				*ptr += Ceng::UINT32(symbolAddress);
			}

			break;
		case RelocationType::full_uint64:

		{
			Ceng::UINT64* ptr = (Ceng::UINT64*)fullWriteAddress;

			*ptr += Ceng::UINT64(symbolAddress);
		}

		break;
		default:
			std::wcout << "WARNING: JIT: unhandled relocation type" << std::endl;
			return Ceng::CE_ERR_NOT_SUPPORTED;
			break;
		};
	}


	std::shared_ptr<Symbol> entry = FindSymbol(entryPoint);

	if (entry == nullptr)
	{
		std::wcout << "Failed to find entry point: " << entryPoint << std::endl;
		return Ceng::CE_ERR_FAIL;
	}

	Ceng::UINT64 entryAddress = entry->Offset() + 
		GetSectionBase(entry->GetSection(),sectionInfo);

	std::wcout << "entry point address = " << std::hex << entryAddress << std::dec
		<< std::endl;

	Executable *temp = Executable::Create((void*)entryAddress, execPage,codeSize,std::move(data));

	*output = temp;

	return Ceng::CE_OK;
}


void ObjectCode::Print(std::wostream& out) const
{
	for (auto& x : sections)
	{
		x->Print(out);
	}

	out << "symbols:" << std::endl;

	for (auto& x : symbols)
	{
		out << '\t';
			
		out << Symbol::TypeToString(x->Type());

		out << " ";

		out << x->name << " : ";

		if (x->Type() != SymbolType::section)
		{
			const Section* section = x->GetSection();
			
			if (section != nullptr)
			{
				out << x->GetSection()->name << " : ";
			}
		}

		out << x->Offset();
	
		out << std::endl;
	}

	out << "relocation data:" << std::endl;

	for (auto& x : relocationData)
	{
		out << '\t' << Symbol::TypeToString(x.symbolType);
			
		out << ' ' << x.symbol << " : ";
		
		out << x.type;

		out << " -> ";

		out << x.writeSection << " : ";

		out << x.writeOffset << std::endl;
	}
}


