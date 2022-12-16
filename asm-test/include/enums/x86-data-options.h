#ifndef CASM_X86_DATA_OPTIONS_H
#define CASM_X86_DATA_OPTIONS_H

namespace X86
{
	namespace DataOptions
	{
		enum value
		{
			// Data is not visible outside of compilation unit
			no_export = 1,

			constant = 1 << 1,

			// Unused. Forces enum storage to int32
			force_32b = 1 << 30 ,
		};
	}
}

#endif