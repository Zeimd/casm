
#include "data-descriptor.h"

using namespace X86;

DataDescriptor::DataDescriptor(const Ceng::UINT32 options, const OPERAND_SIZE::value size)
	: options(options), size(size)
{
}

