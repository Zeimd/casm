#ifndef CASM_DATA_DESCRIPTOR_H
#define CASM_DATA_DESCRIPTOR_H

#include <ceng/datatypes/basic-types.h>
#include "enums/x86-operand-sizes.h"

namespace Casm
{
	class DataDescriptor
	{
	public:
		Ceng::UINT32 options;
		X86::OPERAND_SIZE::value size;

		DataDescriptor();

		DataDescriptor(const Ceng::UINT32 options, const X86::OPERAND_SIZE::value size);

		DataDescriptor(const Ceng::UINT32 options);
	};
}

#endif