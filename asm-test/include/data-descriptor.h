#ifndef CASM_DATA_DESCRIPTOR_H
#define CASM_DATA_DESCRIPTOR_H

#include <ceng/datatypes/basic-types.h>
#include "enums/x86-operand-sizes.h"

namespace X86
{
	class DataDescriptor
	{
	public:
		Ceng::UINT32 options;
		OPERAND_SIZE::value size;

		DataDescriptor(const Ceng::UINT32 options, const OPERAND_SIZE::value size);
	};
}

#endif