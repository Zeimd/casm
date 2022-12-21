/*****************************************************************************
*
* object-code.cpp
*
* By Jari Korkala 12/2022
*
*****************************************************************************/

#include "object-code.h"

#include "data-item.h"

using namespace X86;

ObjectCode::ObjectCode(std::vector<std::shared_ptr<Symbol>>* dataSection,
	std::vector<std::shared_ptr<Symbol>>* bssSection,
	std::vector<std::shared_ptr<ObjectFunction>>* functions)
	: dataSection(dataSection), bssSection(bssSection),functions(functions)
{
}

ObjectCode::~ObjectCode()
{
	if (dataSection != nullptr)
	{
		delete dataSection;
	}

	if (bssSection != nullptr)
	{
		delete bssSection;
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

		out << x->Offset() << " : " << x->name << " (size=" << 
			std::dec << data->initializer->Size() << ") : ";

		std::vector<uint8_t> values(data->initializer->Size());

		data->initializer->WriteValues(&values[0]);

		for (size_t k = 0; k < values.size(); k++)
		{
			out << "0x" << std::hex << values[k] << " ";
		}

		out << std::endl;

		out << std::dec;
	}

	out << std::endl;

	out << "section bss" << std::endl << std::endl;

	for (auto& x : *bssSection)
	{
		DataItem* data = x->AsData();

		out << x->Offset() << " : " << x->name << " (size=" <<
			std::dec << data->initializer->Size() << ") : ";

		std::vector<uint8_t> values(data->initializer->Size());

		data->initializer->WriteValues(&values[0]);

		for (size_t k = 0; k < values.size(); k++)
		{
			out << "0x" << std::hex << values[k] << " ";
		}

		out << std::endl;

		out << std::dec;
	}

	out << std::endl;

	out << "section code" << std::endl << std::endl;

	for (auto& x : *functions)
	{
		x->Print(out);
	}
}


