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
#include "program.h"

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

Ceng::CRESULT Linker::LinkProgram(std::vector<Casm::ObjectCode*> &objects, 
	std::shared_ptr<Program>& output)
{
	output = nullptr;

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

	std::vector<ProgramSection> progSections;

	// Calculate offsets that sections will have after
	// merging

	Ceng::UINT64 offset = 0;

	for (auto& info : sectionInfo)
	{
		progSections.emplace_back(*info.name, info.options);

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

			if (symbol == nullptr)
			{
				// We are dealing with genuinely extern linkage symbol.
				// These won't be available until executable relocationing.

				switch (relocation.type)
				{
				case RelocationType::rel32_add:
					{
						Ceng::INT32* ptr = 
							(Ceng::INT32*)&relocationSection->codeBuffer[relocation.writeOffset];

						*ptr = -Ceng::INT32(relocation.ipDelta);

						relocationData.emplace_back(
							relocation.symbol,
							relocation.symbolType,
							relocationSection->name,
							relocation.writeOffset + relocationSection->Offset(),
							relocation.offsetSize,
							Casm::RelocationType::rel32_add,
							0);
					}
					break;
				case RelocationType::full_int32:

					relocationData.push_back(relocation);

					break;
				default:
					std::wcout << "WARNING: Linker: unhandled relocation type" << std::endl;
					break;
				};	

				continue;
			}

			switch (relocation.type)
			{
			case RelocationType::rel32_add:
				break;
			case RelocationType::full_int32:
				{
					Ceng::INT32* ptr =
					(Ceng::INT32*)&relocationSection->codeBuffer[relocation.writeOffset];

					*ptr += symbol->GetSection()->Offset();

					relocationData.push_back(relocation);
				}
				break;
			default:
				std::wcout << "WARNING: Linker: unhandled relocation type" << std::endl;
				break;
			}
			
		}			
	}
	

	size_t k;

	for (k=0; k < sectionInfo.size();++k)
	{
		for (auto& file : objects)
		{
			for (auto& sect : file->sections)
			{
				if (sect->name == *sectionInfo[k].name)
				{
					sect->Append(progSections[k].buffer);
				}
			}
		}
	}

	output = std::make_shared<Program>(std::move(relocationData), std::move(progSections));




	// Find entry point function

	/*

	std::shared_ptr<X86::ObjectFunction> entryPoint = nullptr;

	Ceng::UINT32 k,j;

	for(k=0;k<objects.size();k++)
	{
		for(j=0;j<objects[k]->functions->size();j++)
		{
			std::vector<std::shared_ptr<X86::ObjectFunction>> *temp = objects[k]->functions;

			if ( (*temp)[k]->name == entryFunction)
			{
				entryPoint = (*temp)[k];
			}
		}
	}

	entryPoint->IncRefCount();

	std::vector<std::shared_ptr<X86::SymbolRef>> *linkDisplacements;
	std::vector<std::shared_ptr<X86::Symbol>> *linkData;
		
	std::vector<std::shared_ptr<X86::Symbol>> *linkFunctions;

	linkData = new std::vector<std::shared_ptr<X86::Symbol>>();
	linkFunctions = new std::vector<std::shared_ptr<X86::Symbol>>();
	linkDisplacements = new std::vector<std::shared_ptr<X86::SymbolRef>>();

	// Gather symbols that will be present in the final executable

	linkFunctions->push_back(entryPoint);

	k = 0;
	do
	{
		// NOTE: ReferenceAll adds all functions called to linkFunctions
		//       if they are currently unreferenced

		X86::ObjectFunction *objFunc = (*linkFunctions)[k]->AsObjectFunction();

		objFunc->ReferenceAll(linkData,linkFunctions);

		k++;
	} while (k < linkFunctions->size());

	// Allocate variables to data segment

	Ceng::UINT32 dataSegmentSize = 0;

	for(k=0;k<linkData->size();k++)
	{
		(*linkData)[k]->SetOffset(dataSegmentSize);
		
		X86::DataItem *item = (*linkData)[k]->AsData();

		dataSegmentSize += item->Size();
	}

	// Build code section

	Ceng::UINT32 codeSegSize = 0;
	
	for(k=0;k<linkFunctions->size();k++)
	{
		// TODO: Pad function offset to start at cache line if necessary

		(*linkFunctions)[k]->SetOffset(codeSegSize);

		X86::ObjectFunction *objFunc = (*linkFunctions)[k]->AsObjectFunction();

		if (objFunc->SizeBytes() > 0)
		{
			codeSegSize += objFunc->SizeBytes();
		}
	}

	Ceng::AlignedBuffer<Ceng::UINT8> dataSegment; 
	
	dataSegment = Ceng::AlignedBuffer<Ceng::UINT8>::AlignedBuffer(dataSegmentSize,cacheLine);

	// Write initial values of data items

	for(k=0;k< linkData->size();k++)
	{
		X86::DataItem *item = (*linkData)[k]->AsData(); 

		item->initializer->WriteValues(&dataSegment[(Ceng::UINT32)(*linkData)[k]->Offset()]);
	}

	// Build linked program

	X86::Program *program = new X86::Program();

	Ceng::AlignedBuffer<Ceng::UINT8> codeBuffer;

	codeBuffer = Ceng::AlignedBuffer<Ceng::UINT8>::AlignedBuffer(codeSegSize,cacheLine);

	memset(&codeBuffer[0], 0, codeBuffer.GetSize());

	program->entryPoint = 0;

	for(k=0;k<linkFunctions->size();k++)
	{
		X86::ObjectFunction *objFunc = (*linkFunctions)[k]->AsObjectFunction();

		if (objFunc->SizeBytes() == 0) continue;
		
		objFunc->WriteAllOffsets();

		uint32_t offset = uint32_t(objFunc->Offset());

		objFunc->ToCodeBuffer(&codeBuffer[offset]);
		objFunc->AppendRelocationData(program->relocationData);
	}

	program->codeBuffer = std::move(codeBuffer);
	program->dataSection = std::move(dataSegment);

	delete linkData;
	delete linkDisplacements;
	delete linkFunctions;

	*output = program;
	*/

	return Ceng::CE_OK;
}