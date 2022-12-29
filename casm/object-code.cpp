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

using namespace Casm;

ObjectCode::ObjectCode(std::vector<std::shared_ptr<ObjectSection>>&& sections)
	: sections(sections)
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
}


