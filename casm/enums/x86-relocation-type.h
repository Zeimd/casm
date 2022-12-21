
#ifndef CASM_X86_RELOCATION_TYPE
#define CASM_X86_RELOCATION_TYPE

namespace X86
{
	namespace RelocationType
	{
		enum value
		{
			// Can be used to pad relocation section
			unused = 0,

			// Full address is encoded as disp32 (int32_t)
			disp32 = 1,

			// Full address is encoded as uint32_t
			// This is used for pointers in data section,
			// and in code when more than 2GB of address space is needed
			full32 = 2,

			// Full address is encoded as uint64_t
			// Used with "mov reg64, imm64" instruction.
			full64 = 3,

			// Unused. Forces enum storage to int32.
			force_32b = 1 << 30 ,
		};
	}
}

#endif