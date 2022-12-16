/*****************************************************************************
*
* object-code.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_OBJECT_CODE_H
#define X86_OBJECT_CODE_H

#include "obj-function.h"
#include "symbol.h"

#include <ceng/datatypes/basic-types.h>
#include <memory>

#include <ostream>


namespace X86
{
	class ObjectCode
	{
	public:

		std::vector<std::shared_ptr<Symbol>> *dataSection;

		std::vector<std::shared_ptr<Symbol>>* bssSection;

		std::vector<std::shared_ptr<ObjectFunction>> *functions;

		ObjectCode(std::vector<std::shared_ptr<Symbol>>* dataSection,
			std::vector<std::shared_ptr<Symbol>>* bssSection,
			std::vector<std::shared_ptr<ObjectFunction>>* functions);

		~ObjectCode();

		void Print(std::wostream& out) const;
	};
}

#endif