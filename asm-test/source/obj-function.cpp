/*****************************************************************************
*
* obj-function.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/obj-function.h"

#include "../include/symbol-ref.h"

#include "../include/hex-dump.h"

using namespace X86;

ObjectFunction::ObjectFunction() : references(nullptr), codeBuffer(nullptr)
{
}

ObjectFunction::ObjectFunction(const Ceng::String &name,
							   std::vector<std::shared_ptr<SymbolRef>> *references,
							   std::vector<Ceng::UINT8> *codeBuffer)
	: Symbol(name,Symbol::OBJECT_FUNCTION,true,false),references(references),codeBuffer(codeBuffer)
{
}

ObjectFunction::~ObjectFunction()
{
	if (references != nullptr)
	{
		delete references;
	}

	if (codeBuffer != nullptr)
	{
		delete codeBuffer;
	}
}

void ObjectFunction::Print(std::wostream& out) const
{
	out << "function " << name << " (size=" << SizeBytes() << ")" << std::endl;
	
	Casm::HexDump(out, 16, SizeBytes(), &(*codeBuffer)[0]);


	out << "end function" << std::endl;
	
}

Ceng::CRESULT ObjectFunction::Append(std::vector<Ceng::UINT8> &destBuffer) const
{
	std::copy(codeBuffer->begin(),codeBuffer->end(),std::back_inserter(destBuffer));

	return Ceng::CE_OK;
}


Ceng::CRESULT ObjectFunction::ReferenceAll(std::vector<std::shared_ptr<Symbol>> *dataList,
											std::vector<std::shared_ptr<Symbol>> *functionList)
{
	Ceng::UINT32 k;

	std::shared_ptr<Symbol> temp;

	for(k=0;k<references->size();k++)
	{
		temp = (*references)[k]->symbol;

		if ( temp->RefCount() == 0)
		{
			if (temp->Type() == Symbol::DATA)
			{
				dataList->push_back( (*references)[k]->symbol);
			}
			else if (temp->Type() == Symbol::OBJECT_FUNCTION)
			{
				functionList->push_back( (*references)[k]->symbol);
			}
		}
		
		(*references)[k]->symbol->IncRefCount();
	}

	return Ceng::CE_OK;
}

Ceng::CRESULT ObjectFunction::WriteAllOffsets()
{
	Ceng::UINT32 k;

	for(k=0;k<references->size();k++)
	{
		(*references)[k]->WriteOffset((Ceng::UINT64)&(*codeBuffer)[0]);
	}

	return Ceng::CE_OK;
}

Ceng::CRESULT ObjectFunction::ToCodeBuffer(Ceng::UINT8 *buffer) const
{
	memcpy(&buffer[offset],&(*codeBuffer)[0],codeBuffer->size());

	return Ceng::CE_OK;
}

Ceng::CRESULT ObjectFunction::AppendRelocationData(std::vector<RelocationData> &relocationData) const
{
	Ceng::UINT32 k;

	for(k=0;k<references->size();k++)
	{
		if ( (*references)[k]->refType != Casm::REFERENCE_TYPE::IP_RELATIVE)
		{
			RelocationData::SECTION symbolSection = RelocationData::DATA_SECTION;

			Casm::REFERENCE_TYPE::value refType = Casm::REFERENCE_TYPE::ADDRESS;

			if ( (*references)[k]->symbol->Type() == Symbol::OBJECT_FUNCTION)
			{
				symbolSection = RelocationData::CODE_SECTION;
			}

			relocationData.push_back(RelocationData(RelocationData::CODE_SECTION,
					(*references)[k]->encodeOffset + offset,symbolSection,
					(*references)[k]->encodeSize,
					refType,0));
		}
	}
	
	return Ceng::CE_OK;
}