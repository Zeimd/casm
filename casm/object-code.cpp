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

#include "relocation-data.h"

using namespace Casm;

ObjectCode::ObjectCode(std::vector<std::shared_ptr<ObjectSection>>&& sections,
	std::vector<std::shared_ptr<Symbol>>&& symbols,
	std::vector<std::shared_ptr<RelocationData>>&& relocationData)
	: sections(sections), symbols(symbols), relocationData(relocationData)
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
			
		out << Symbol::TypeToString(x->Type());

		out << " ";

		out << x->name << " : ";

		if (x->Type() != SymbolType::section)
		{
			const Section* section = x->GetSection();
			
			if (section != nullptr)
			{
				out << x->GetSection()->name << " : ";
			}
		}

		out << x->Offset();
	
		out << std::endl;
	}

	out << "relocation data:" << std::endl;

	for (auto& x : relocationData)
	{
		out << '\t' << Symbol::TypeToString(x->symbolType);
			
		out << ' ' << x->symbol << " -> ";

		out << x->writeSection << " : ";

		out << x->writeOffset << std::endl;
	}
}


