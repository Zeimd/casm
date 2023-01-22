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

std::shared_ptr<ObjectSection> Linker::FindSection(
	const Ceng::String& name,
	const std::vector<std::shared_ptr<ObjectSection>>&	sections)
{
	for (auto& x : sections)
	{
		if (x->name == name)
		{
			return x;
		}
	}

	return nullptr;
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

static Ceng::CRESULT SetSectionOffset(ObjectCode* file, Symbol* section, Ceng::UINT64 offset, std::vector<FileInfo>& sectionInfo)
{
	for (auto& info : sectionInfo)
	{
		if (info.file->name == file->name)
		{
			for (auto& sec : info.sections)
			{
				if (sec.section->name == section->name)
				{
					sec.offset = offset;
					return Ceng::CE_OK;
				}
			}
		}
	}

	return Ceng::CE_ERR_INVALID_PARAM;
}

static Ceng::UINT64 GetSectionOffset(ObjectCode* file, Symbol* section, std::vector<FileInfo>& sectionInfo)
{
	for (auto& info : sectionInfo)
	{
		if (info.file->name == file->name)
		{
			for (auto& sec : info.sections)
			{
				if (sec.section->name == section->name)
				{
					return sec.offset;
				}
			}
		}
	}

	return 0;
}

static std::shared_ptr<ObjectSection> FindSection(const Ceng::String& name, std::vector<std::shared_ptr<ObjectSection>>& sections)
{
	for (auto& sect : sections)
	{
		if (sect->name == name)
		{
			return sect;
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

	// TODO: initialize section offset table


	std::vector<FileInfo> sectionInfo;

	for (auto& file : objects)
	{
		FileInfo temp;

		temp.file = file;

		for (auto& section : file->sections)
		{
			temp.sections.emplace_back(section.get(), nullptr, section->options, 0);
		}

		sectionInfo.push_back(temp);
	}


	// Gather unique section names

	std::vector<SectionInfo> uniqueSections;

	for (auto& file : objects)
	{
		for (auto& sect : file->sections)
		{
			size_t k;
			bool found = false;

			for (k = 0; k < uniqueSections.size(); ++k)
			{
				if (uniqueSections[k].section->name == sect->name)
				{
					found = true;
					break;
				}
			}

			if (found == false)
			{
				uniqueSections.push_back({sect.get(),nullptr,sect->options,0});
			}			
			else
			{
				// Sections with same name need to have same options
				// for merging
				if (uniqueSections[k].options != sect->options)
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

	for (auto& info : uniqueSections)
	{
		outSections.emplace_back(std::make_shared<ObjectSection>(info.section->name, info.options));

		outSymbols.push_back(outSections.back());

		offset = 0;

		for (auto& file : objects)
		{
			for (auto& sect : file->sections)
			{
				if (sect->name == info.section->name)
				{
					Ceng::CRESULT cresult;

					cresult = SetSectionOffset(file, sect.get(), offset, sectionInfo);

					if (cresult != Ceng::CE_OK)
					{
						std::wcout << "ERROR: Linker: failed to set section offset: "
							<< file->name << " : " << sect->name << std::endl;
					}

					offset += sect->SizeBytes();
				}
			}
		}
	}

	for (size_t k = 0; k < uniqueSections.size(); ++k)
	{
		for (auto& file : objects)
		{
			for (auto& sect : file->sections)
			{
				if (sect->name == uniqueSections[k].section->name)
				{
					sect->Append(outSections[k]->codeBuffer);
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

			Ceng::UINT64 symbolOffsetChange = 0;
			
			if (symbol != nullptr)
			{
				symbolOffsetChange = GetSectionOffset(file, symbol->GetSection(), sectionInfo);
			}

			Ceng::UINT64 newWriteOffset = relocation.writeOffset +
				GetSectionOffset(file, relocationSection.get(), sectionInfo);

			relocationSection = FindSection(relocationSection->name, outSections);

			bool deleted = false;

			switch (relocation.type)
			{
			case RelocationType::rel32_add:
				{
					Ceng::INT32* ptr =
						(Ceng::INT32*)&relocationSection->codeBuffer[newWriteOffset];

					if (symbol == nullptr)
					{
						*ptr = -Ceng::INT32(relocation.ipDelta);
					}
					else if (symbol->GetSection()->name == relocationSection->name)
					{
						Ceng::UINT64 newSymbolOffset = symbol->Offset() +
							symbolOffsetChange;

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
						(Ceng::INT32*)&relocationSection->codeBuffer[newWriteOffset];

					*ptr += Ceng::INT32(symbolOffsetChange);
				}

				break;

			case RelocationType::full_uint32:

				if (symbol != nullptr)
				{
					Ceng::UINT32* ptr =
						(Ceng::UINT32*)&relocationSection->codeBuffer[newWriteOffset];

					*ptr += Ceng::UINT32(symbolOffsetChange);
				}

				break;
			case RelocationType::full_uint64:

				if (symbol != nullptr)
				{
					Ceng::UINT64* ptr =
						(Ceng::UINT64*)&relocationSection->codeBuffer[newWriteOffset];

					*ptr += Ceng::UINT64(symbolOffsetChange);
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
				relocation.refType,
				relocation.type,
				0);
			
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
				std::shared_ptr<ObjectSection> newSect =
					FindSection(x->GetSection()->name, outSections);

				outSymbols.emplace_back(

					std::make_shared<Symbol>(x->name, newSect.get(),
						x->Type(), x->IsDefined(), x->IsGlobal())
				);

				outSymbols.back()->SetOffset(x->Offset() +
					GetSectionOffset(file, x->GetSection(), sectionInfo));
			}
		}
	}

	output = std::make_shared<ObjectCode>(
		name, std::move(outSections), std::move(outSymbols),
		std::move(relocationData) );

	return Ceng::CE_OK;
}