/*****************************************************************************
*
* data-item.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_DATA_ITEM_H
#define X86_DATA_ITEM_H

#include <ceng/datatypes/basic-types.h>


#include "enums/x86-operand-sizes.h"

#include "enums/x86-data-options.h"

#include "code-line.h"
#include "initializer.h"

namespace Casm
{
	class DataItem : public CodeLine
	{
	public:
		Ceng::UINT32 options;

		X86::OPERAND_SIZE::value elementSize;

		const Casm::InitializerType *initializer;

	protected:

		DataItem() : 
			options(0), elementSize(X86::OPERAND_SIZE::OPERAND_SIZE_FORCE_32B), 
			initializer(nullptr)
		{

		}

	public:

		DataItem(Ceng::UINT32 options, X86::OPERAND_SIZE::value size, 
			Casm::Section* section, const Casm::InitializerType* initializer)
			: initializer(initializer), options(options), elementSize(size)
		{

		}

		~DataItem()
		{
			if (initializer != nullptr)
			{
				delete initializer;
				initializer = nullptr;
			}
		}

		uint32_t Size() const
		{
			if (initializer != nullptr)
			{
				return initializer->Size();
			}
			return 0;
		}

		void Print(std::wostream& out) const override;
	};
}

#endif