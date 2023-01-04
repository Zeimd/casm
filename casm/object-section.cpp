
#include "object-section.h"
#include "symbol.h"
#include "symbol-ref.h"
#include "code-label.h"

#include "relocation-data.h"

#include "hex-dump.h"

using namespace Casm;

ObjectSection::ObjectSection()
{
}

ObjectSection::ObjectSection(const Ceng::String& name,
	const Ceng::UINT32 options,
	std::vector<Ceng::UINT8>&& codeBuffer)
	: Symbol(name, nullptr, Casm::SymbolType::section, true, false),
	options(options), codeBuffer(codeBuffer)
{
}

ObjectSection::~ObjectSection()
{
	
}

void ObjectSection::Print(std::wostream& out) const
{
	if (SizeBytes() == 0) return;

	out << "section " << name << " (size=" <<
		std::dec << SizeBytes() << ")" << std::endl;

	Casm::HexDump(out, 16, SizeBytes(), &codeBuffer[0]);

	out << "end section" << std::endl;
}

Ceng::CRESULT ObjectSection::Append(std::vector<Ceng::UINT8>& destBuffer) const
{
	std::copy(codeBuffer.begin(), codeBuffer.end(), std::back_inserter(destBuffer));

	return Ceng::CE_OK;
}


Ceng::CRESULT ObjectSection::ReferenceAll(std::vector<std::shared_ptr<Symbol>>* dataList,
	std::vector<std::shared_ptr<Symbol>>* functionList)
{
	/*
	Ceng::UINT32 k;

	std::shared_ptr<Symbol> temp;

	for (k = 0; k < references.size(); k++)
	{
		temp = references[k]->symbol;

		if (temp->RefCount() == 0)
		{
			if (temp->Type() == X86::SymbolType::data)
			{
				dataList->push_back(references[k]->symbol);
			}
			else if (temp->Type() == X86::SymbolType::object_function)
			{
				functionList->push_back(references[k]->symbol);
			}
		}

		references[k]->symbol->IncRefCount();
	}
	*/

	return Ceng::CE_OK;
}

Ceng::CRESULT ObjectSection::WriteAllOffsets()
{
	Ceng::UINT32 k;

	/*
	for (k = 0; k < references.size(); k++)
	{
		references[k]->WriteOffset((Ceng::UINT64) & codeBuffer[0]);
	}
	*/

	return Ceng::CE_OK;
}

Ceng::CRESULT ObjectSection::ToCodeBuffer(Ceng::UINT8* buffer) const
{
	memcpy(buffer, &codeBuffer[0], codeBuffer.size());

	return Ceng::CE_OK;
}

Ceng::CRESULT ObjectSection::AppendRelocationData(std::vector<X86::RelocationData>& relocationData) const
{
	Ceng::UINT32 k;

	/*
	for (k = 0; k < references.size(); k++)
	{
		if (references[k]->deleted)
		{
			continue;
		}

		X86::RelocationData::SECTION symbolSection = X86::RelocationData::CODE_SECTION;
		Ceng::String externName;

		/*
		if ((*references)[k]->symbol->Type() == X86::SymbolType::object_function)
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
		else
		{
			symbolSection = RelocationData::SECTION::DATA_SECTION;
		}
		*/

		//Ceng::INT64 encodeOffset = references[k]->encodeOffset + offset;

		/*
		if ((*references)[k]->refType == Casm::REFERENCE_TYPE::IP_RELATIVE)
		{

		}
		*/

	/*
		relocationData.push_back(X86::RelocationData(X86::RelocationData::CODE_SECTION,
			encodeOffset, symbolSection,
			references[k]->encodeSize,
			references[k]->refType, externName, 0));
			*/
	//}

	return Ceng::CE_OK;
}