
#include "data-descriptor.h"

using namespace Casm;

DataDescriptor::DataDescriptor()
	: options(0), size(X86::OPERAND_SIZE::IMPLICIT)
{

}

DataDescriptor::DataDescriptor(const Ceng::UINT32 options)
	: options(options), size(X86::OPERAND_SIZE::IMPLICIT)
{

}

DataDescriptor::DataDescriptor(const Ceng::UINT32 options, const X86::OPERAND_SIZE::value size)
	: options(options), size(size)
{
}

