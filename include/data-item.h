/*****************************************************************************
*
* data-item.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_DATA_ITEM_H
#define X86_DATA_ITEM_H

#include <datatypes/basic-types.h>


#include "enums/x86-operand-sizes.h"

#include "symbol.h"
#include "initializer.h"

namespace X86
{
	namespace DATA_OPTION
	{
		enum value
		{
			CONSTANT = 1 ,
			STATIC = 1 << 1 ,

			FORCE_32B = 1 << 30 ,
		};
	}

	class DataItem : public Symbol
	{
	public:
		Ceng::UINT32 options;

		OPERAND_SIZE::value elementSize;

		const InitializerType *initializer;

		DataItem()
		{
			initializer = nullptr;
		}

		~DataItem()
		{
			if (initializer != nullptr)
			{
				delete initializer;
				initializer = nullptr;
			}
		}
	};
}

#endif