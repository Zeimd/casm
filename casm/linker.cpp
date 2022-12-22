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

#include "obj-function.h"

using namespace Casm;

Linker::Linker()
{
}

Linker::Linker(const Ceng::UINT32 cacheLine) : cacheLine(cacheLine)
{
}

Linker::~Linker()
{

}

Ceng::CRESULT Linker::LinkProgram(const Ceng::String &entryFunction,
	std::vector<X86::ObjectCode*> &objects,
	ExternSymbol* externs, uint32_t externCount, X86::Program **output)
{
	// Find entry point function

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

		dataSegmentSize += item->elementSize;
	}

	// Build code section

	Ceng::UINT32 codeSegSize = 0;
	
	for(k=0;k<linkFunctions->size();k++)
	{
		// TODO: Pad function offset to start at cache line if necessary

		(*linkFunctions)[k]->SetOffset(codeSegSize);

		X86::ObjectFunction *objFunc = (*linkFunctions)[k]->AsObjectFunction();

		codeSegSize += objFunc->SizeBytes();
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

	return Ceng::CE_OK;
}