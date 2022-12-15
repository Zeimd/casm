/*****************************************************************************
*
* object-code.cpp
*
* By Jari Korkala 12/2022
*
*****************************************************************************/

#include "../include/object-code.h"

#include "../include/data-item.h"

using namespace X86;

ObjectCode::ObjectCode(std::vector<std::shared_ptr<Symbol>>* dataSection,
	std::vector<std::shared_ptr<ObjectFunction>>* functions)
	: dataSection(dataSection), functions(functions)
{
}

ObjectCode::~ObjectCode()
{
	if (dataSection != nullptr)
	{
		delete dataSection;
	}

	if (functions != nullptr)
	{
		delete functions;
	}
}

void ObjectCode::Print(std::wostream& out) const
{
	out << "section data" << std::endl << std::endl;

	for (auto& x : *dataSection)
	{
		DataItem* data = x->AsData();

		out << x->Offset() << " : " << x->name << " (size=" << data->initializer->Size() << ") : ";

		std::vector<uint8_t> values(data->initializer->Size());

		data->initializer->WriteValues(&values[0]);

		for (size_t k = 0; k < values.size(); k++)
		{
			out << "0x" << std::hex << values[k] << " ";
		}

		out << std::endl;
	}

	out << std::endl;

	out << "section code" << std::endl << std::endl;

	for (auto& x : *functions)
	{
		x->Print(out);
	}
}


