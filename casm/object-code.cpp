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

std::shared_ptr<Symbol> ObjectCode::FindSymbol(const Ceng::String& name)
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
	Casm::ExternSymbol* externs, uint32_t externCount)
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


Ceng::CRESULT ObjectCode::GetJitExecutable(const Ceng::String& entryPoint,
	Casm::ExternSymbol* externs, 
	uint32_t externCount, Executable** output)
{
	std::wcout << "JIT: start" << std::endl;

	*output = nullptr;

	std::shared_ptr<Symbol> virtualCode =
		std::make_shared<Symbol>(".text", nullptr, SymbolType::section, true, true);

	std::shared_ptr<Symbol> virtualData =
		std::make_shared<Symbol>(".data", nullptr, SymbolType::section, true, true);

	Ceng::UINT64 codeSize = 0;
	Ceng::UINT64 dataSize = 0;

	for (auto& x : sections)
	{
		if (x->options & SectionOptions::executable)
		{
			x->MarkDefined(virtualCode.get(), SymbolType::section, true);

			x->SetOffset(codeSize);
			codeSize += x->SizeBytes();
		}
		else 
		{
			x->MarkDefined(virtualData.get(), SymbolType::section, true);

			x->SetOffset(dataSize);
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

	virtualCode->SetOffset((Ceng::INT64)execPage);

	Ceng::AlignedBuffer<Ceng::UINT8> data;

	data = Ceng::AlignedBuffer<Ceng::UINT8>::AlignedBuffer(dataSize, 4096);

	virtualData->SetOffset((Ceng::INT64)&data[0]);

	std::wcout << "GetExecutable:" << std::endl;

	std::wcout << "data section base = 0x" << std::hex << &data[0] << std::dec << std::endl;

	std::wcout << "code section base = 0x" << std::hex << &execPage[0] << std::dec << std::endl;

	std::wcout << "data section size = " << data.GetElements() << std::endl;

	// Relocationing

	//std::wcout << "relocationing:" << std::endl;

	for (auto& relocation : relocationData)
	{
		//std::wcout << "symbol : " << relocation.symbol << std::endl;

		std::shared_ptr<ObjectSection> relocationSection =
			std::static_pointer_cast<ObjectSection>(
				FindSymbol(relocation.writeSection)
				);

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

			// Offset of section in allocation
			symbolAddress = symbol->GetSection()->Offset();

			if (symbol->Type() != SymbolType::section)
			{
				// Start of allocation (virtual symbol)
				symbolAddress += symbol->GetSection()->GetSection()->Offset(); 
			}
		}

		//std::wcout << "symbol address = " << std::hex << symbolAddress << std::dec << std::endl;

		switch (relocation.type)
		{
		case RelocationType::rel32_add:
		{
			//std::wcout << "rel32_add:" << std::endl;

			Ceng::UINT64 fullWriteAddress =
				relocation.writeOffset +
				relocationSection->Offset() +              // Offset of section in allocation 
				relocationSection->GetSection()->Offset(); // Start of allocation (virtual symbol)

			//std::wcout << "full write address = " << std::hex << fullWriteAddress << std::dec
			//	<< std::endl;

			//std::wcout << "ipDelta = " << relocation.ipDelta << std::endl;

			Ceng::INT32* ptr =
				(Ceng::INT32*)&relocationSection->codeBuffer[relocation.writeOffset];

			*ptr += Ceng::INT32(symbolAddress - fullWriteAddress);
		}
		break;
		case RelocationType::full_int32:

			{
				Ceng::INT32* ptr =
					(Ceng::INT32*)&relocationSection->codeBuffer[relocation.writeOffset];

				*ptr += Ceng::INT32(symbolAddress);
			}

			break;
		default:
			std::wcout << "WARNING: JIT: unhandled relocation type" << std::endl;
			return Ceng::CE_ERR_NOT_SUPPORTED;
			break;
		};
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

	Ceng::UINT64 entryAddress = 0;

	std::shared_ptr<Symbol> entry = FindSymbol(entryPoint);

	if (entry == nullptr)
	{
		std::wcout << "Failed to find entry point: " << entryPoint << std::endl;
		return Ceng::CE_ERR_FAIL;
	}

	entryAddress = entry->Offset() +
		entry->GetSection()->Offset() +
		entry->GetSection()->GetSection()->Offset();

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
			
		out << ' ' << x.symbol << " -> ";

		out << x.writeSection << " : ";

		out << x.writeOffset << std::endl;
	}
}


