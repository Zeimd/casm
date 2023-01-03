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
#include "symbol-ref.h"

#include "section.h"

using namespace Casm;

ObjectCode::ObjectCode(std::vector<std::shared_ptr<ObjectSection>>&& sections,
	std::vector<std::shared_ptr<Symbol>>&& symbols,
	std::vector<std::shared_ptr<SymbolRef>>&& references)
	: sections(sections), symbols(symbols), references(references)
{
}

ObjectCode::~ObjectCode()
{

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
			
		switch (x->Type())
		{
		case SymbolType::section:
			out << "section";
			break;
		case SymbolType::function:
			out << "function";
			break;
		case SymbolType::data:
			out << "data";
			break;
		case SymbolType::unknown:
			out << "unknown";
			break;
		default:
			out << "<invalid_value>";
			break;
		}

		out << " ";

		if (x->Type() != SymbolType::section)
		{
			const Section* section = x->Section();
			
			if (section != nullptr)
			{
				out << " : " << x->Section()->name << " : ";
			}
		}

		out << x->name << " : ";

		if (x->Type() != SymbolType::section)
		{
			out << x->Offset();
		}

		out << std::endl;
	}

	out << "references:" << std::endl;

	for (auto& x : references)
	{
		out << '\t' << x->symbol->name << " : " << x->encodeOffset << std::endl;
	}
}


