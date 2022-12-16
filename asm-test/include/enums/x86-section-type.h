
#ifndef CASM_X86_SECTION_TYPE_H
#define CASM_X86_SECTION_TYPE_H

namespace X86
{
	namespace SectionType
	{
		enum value
		{
			unknown = 0,
			data = 1,
			bss = 2,
			text = 3,

			force_32b = 1 << 30,
		};
	}
}

#endif