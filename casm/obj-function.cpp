/*****************************************************************************
*
* obj-function.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "obj-function.h"

#include "symbol-ref.h"

#include "hex-dump.h"

using namespace X86;

ObjectFunction::ObjectFunction() : references(nullptr), codeBuffer(nullptr)
{
}

ObjectFunction::ObjectFunction(const Ceng::String &name,
							   std::vector<std::shared_ptr<SymbolRef>> *references,
							   std::vector<Ceng::UINT8> *codeBuffer)
	: Symbol(name,SectionType::text,SymbolType::object_function,true,false),
	references(references),codeBuffer(codeBuffer)
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
	if (SizeBytes() == 0) return;
	
	out << "function " << name << " (size=" << 
		std::dec << SizeBytes() << ")" << std::endl;
	
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
			if (temp->Type() == SymbolType::data)
			{
				dataList->push_back( (*references)[k]->symbol);
			}
			else if (temp->Type() == SymbolType::object_function)
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
		bool write = true;

		if ((*references)[k]->symbol->Type() == SymbolType::object_function)
		{
			X86::ObjectFunction* objFunc = (*references)[k]->symbol->AsObjectFunction();

			if (objFunc->SizeBytes() == 0)
			{
				write = false;
			}
		}

		if (write)
		{
			(*references)[k]->WriteOffset((Ceng::UINT64) & (*codeBuffer)[0]);
		}
	}

	return Ceng::CE_OK;
}

Ceng::CRESULT ObjectFunction::ToCodeBuffer(Ceng::UINT8 *buffer) const
{
	memcpy(buffer,&(*codeBuffer)[0],codeBuffer->size());

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

			Ceng::String externName;

			if ( (*references)[k]->symbol->Type() == SymbolType::object_function)
			{
				X86::ObjectFunction* objFunc = (*references)[k]->symbol->AsObjectFunction();

				if (objFunc->SizeBytes() > 0)
				{
					symbolSection = RelocationData::CODE_SECTION;					
				}
				else
				{
					symbolSection = RelocationData::EXTERNAL;
					externName = (*references)[k]->symbol->name;
				}				
			}

			relocationData.push_back(RelocationData(RelocationData::CODE_SECTION,
					(*references)[k]->encodeOffset + offset,symbolSection,
					(*references)[k]->encodeSize,
					refType,externName,0));
		}
	}
	
	return Ceng::CE_OK;
}