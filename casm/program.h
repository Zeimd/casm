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

#include <ostream>

#include <ceng/datatypes/basic-types.h>

#include "relocation-data.h"

#include "executable.h"

#include "extern-symbol.h"

#include "enums/section-options.h"

namespace Casm
{
	class ProgramSection
	{
	public:
		Ceng::String name;

		Ceng::UINT32 options;

		std::vector<Ceng::UINT8> buffer;
	};

	class Program
	{
	protected:

		std::vector<Casm::RelocationData> relocationData;

		std::vector<ProgramSection> sections;

		Program();

	public:

		Program(std::vector<Casm::RelocationData>&& relocationData,
			std::vector<ProgramSection>&& sections);

		~Program();

		Ceng::CRESULT GetExecutable(Casm::ExternSymbol* externs, uint32_t externCount,
			Executable **output);

		void Print(std::wostream& out) const;

	};
}

#endif