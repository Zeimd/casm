/*****************************************************************************
*
* linker.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "linker.h"
#include "object-code.h"
#include "data-item.h"

#include "object-section.h"

#include "relocation-data.h"
#include "section.h"

using namespace Casm;

Linker::Linker() : cacheLine(64)
{
}

Linker::Linker(const Ceng::UINT32 cacheLine) : cacheLine(cacheLine)
{
}

Linker::~Linker()
{

}

std::shared_ptr<Symbol> Linker::FindSymbol(
	const Ceng::String& name,
	Casm::ObjectCode* currentFile,
	std::vector<Casm::ObjectCode*>& files)
{
	std::shared_ptr<Symbol> temp;

	temp = currentFile->FindSymbol(name);

	if (temp != nullptr)
	{
		return temp;
	}

	for (auto& file : files)
	{
		if (file == currentFile)
		{
			continue;
		}

		temp = file->FindSymbol(name);

		if (temp != nullptr)
		{
			return temp;
		}
	}

	return nullptr;
}

Ceng::CRESULT Linker::LinkProgram(
	const Ceng::String& name,
	std::vector<Casm::ObjectCode*> &objects, 
	std::shared_ptr<ObjectCode>& output)
{
	output = nullptr;

	// TODO: check for duplicate symbols (other than section names)

	// TODO: Set reference counts so that only sections
	//       that need to be present get included

	// Gather unique section names

	struct SectionInfo
	{
		Ceng::String* name;
		Ceng::UINT32 options;
	};

	std::vector<SectionInfo> sectionInfo;

	for (auto& file : objects)
	{
		for (auto& sect : file->sections)
		{
			size_t k;
			bool found = false;

			for (k = 0; k < sectionInfo.size(); ++k)
			{
				if (*sectionInfo[k].name == sect->name)
				{
					found = true;
					break;
				}
			}

			if (found == false)
			{
				sectionInfo.push_back({&sect->name,sect->options});
			}			
			else
			{
				// Sections with same name need to have same options
				// for merging
				if (sectionInfo[k].options != sect->options)
				{
					return Ceng::CE_ERR_INCOMPATIBLE_FORMAT;
				}
			}
		}
	}

	/*
	std::wcout << "unique names:" << std::endl;

	for (auto& name : sectionNames)
	{
		std::wcout << '\t' << (*name) << std::endl;
	}
	*/

	std::vector<std::shared_ptr<ObjectSection>> outSections;

	std::vector<std::shared_ptr<Symbol>> outSymbols;

	// Calculate offsets that sections will have after
	// merging.
	//
	// NOTE: Don't copy sections yet so that following
	//       relocation step has a bit easier math

	Ceng::UINT64 offset = 0;

	for (auto& info : sectionInfo)
	{
		outSections.emplace_back(std::make_shared<ObjectSection>(*info.name, info.options));

		outSymbols.push_back(outSections.back());

		for (auto& file : objects)
		{
			for (auto& sect : file->sections)
			{
				if (sect->name == *info.name)
				{
					sect->SetOffset(offset);
				}
			}
		}
	}

	std::vector<Casm::RelocationData> relocationData;

	for (auto& file : objects)
	{
		for (auto& relocation : file->relocationData)
		{
			std::shared_ptr<ObjectSection> relocationSection =
				std::static_pointer_cast<ObjectSection>(
					FindSymbol(relocation.writeSection,
						file, objects)
					);

			std::shared_ptr<Symbol> symbol = FindSymbol(relocation.symbol,
				file, objects);

			Ceng::UINT64 newWriteOffset = relocation.writeOffset +
				relocationSection->Offset();

			bool deleted = false;

			switch (relocation.type)
			{
			case RelocationType::rel32_add:
				{
					Ceng::INT32* ptr =
						(Ceng::INT32*)&relocationSection->codeBuffer[relocation.writeOffset];

					if (symbol == nullptr)
					{
						*ptr = -Ceng::INT32(relocation.ipDelta);
					}
					else if (symbol->GetSection()->name == relocationSection->name)
					{
						Ceng::UINT64 newSymbolOffset = symbol->Offset() +
							symbol->GetSection()->Offset();

						*ptr = Ceng::INT32(newSymbolOffset - (newWriteOffset + relocation.ipDelta));

						deleted = true;
					}
					else
					{

					}
				}
				break;
			case RelocationType::full_int32:

				if (symbol != nullptr)
				{
					Ceng::INT32* ptr =
						(Ceng::INT32*)&relocationSection->codeBuffer[relocation.writeOffset];

					*ptr += Ceng::INT32(symbol->GetSection()->Offset());
				}

				break;
			default:
				std::wcout << "WARNING: Linker: unhandled relocation type" << std::endl;
				deleted = true;
				break;
			};

			if (deleted)
			{
				continue;
			}

			relocationData.emplace_back(
				relocation.symbol,
				relocation.symbolType,
				relocationSection->name,
				newWriteOffset,
				relocation.offsetSize,
				relocation.type,
				0);
			
		}			
	}

	// Copy sections to new buffer according to offsets
	// calculated earlier

	for (size_t k = 0; k < sectionInfo.size(); ++k)
	{
		for (auto& file : objects)
		{
			for (auto& sect : file->sections)
			{
				if (sect->name == *sectionInfo[k].name)
				{
					sect->Append(outSections[k]->codeBuffer);
				}
			}
		}
	}

	for (auto& file : objects)
	{
		for (auto& x : file->symbols)
		{
			if (x->Type() == SymbolType::section)
			{
				continue;
			}

			if (x->IsDefined() == true && x->IsGlobal())
			{
				outSymbols.emplace_back(

					std::make_shared<Symbol>(x->name, x->GetSection(),
						x->Type(), x->IsDefined(), x->IsGlobal())
				);

				outSymbols.back()->SetOffset(x->Offset() +
					x->GetSection()->Offset());
			}
		}
	}

	output = std::make_shared<ObjectCode>(
		name, std::move(outSections), std::move(outSymbols),
		std::move(relocationData) );

	return Ceng::CE_OK;
}