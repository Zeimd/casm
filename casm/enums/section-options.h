
#ifndef CASM_SECTION_OPTIONS_H
#define CASM_SECTION_OPTIONS_H

namespace Casm
{
	namespace SectionOptions
	{
		enum value
		{
			writable = 1,

			// Executable code
			executable = 1 << 1,

			// Occupies memory during execution
			alloc_mem = 1 << 2,

			// Unused. Forces enum storage to int32
			force_32b = 1 << 30,
		};
	}
}

#endif