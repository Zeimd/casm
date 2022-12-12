/*****************************************************************************
*
* program.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_PROGRAM_H
#define X86_PROGRAM_H

#include <vector>

#include <ceng/datatypes/basic-types.h>

#include "relocation-data.h"

#include "executable.h"

namespace X86
{
	class Program
	{
	public:

		Ceng::UINT64 entryPoint;

		std::vector<RelocationData> relocationData;

		Ceng::AlignedBuffer<Ceng::UINT8> codeBuffer;

		Ceng::AlignedBuffer<Ceng::UINT8> dataSection;

		Program();
		~Program();

		Ceng::CRESULT GetExecutable(Executable **output);

	};
}

#endif