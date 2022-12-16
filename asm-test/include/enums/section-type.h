
#ifndef CASM_SECTION_TYPE_H
#define CASM_SECTION_TYPE_H

namespace X86
{
	namespace SectionType
	{
		enum value
		{
			undefined = 0,
			data = 1,
			bss = 2,
			code = 3,

			// Unused. Forces enum storage type to int32
			force_32b = 1 << 30,
		};
	}
}

#endif