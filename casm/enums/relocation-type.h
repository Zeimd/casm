
#ifndef CASM_RELOCATION_TYPE
#define CASM_RELOCATION_TYPE

namespace Casm
{
	namespace RelocationType
	{
		enum value
		{
			// Can be used to pad relocation section
			unused = 0,

			// x86 : Full address is encoded as disp32
			full_int32 = 1,

			// Full address is encoded as uint32_t
			// This is used for pointers in data section,
			// and in code when more than 2GB of address space is needed
			full_uint32 = 2,

			// Full address is encoded as uint64_t
			// x86 : "mov reg64, imm64" instruction.
			full_uint64 = 3,

			// x86 : IP-relative from start of next instruction.
			//       Add value already in target location to symbol address
			rel32_add = 4,

			// x86 : IP-relative from start of next instruction.
			//       Add value already in target location to symbol address
			//       NOTE: Real mode only.
			rel16_add = 5,

			// Unused. Forces enum storage to int32.
			force_32b = 1 << 30 ,
		};
	}
}

#endif