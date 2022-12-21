/*****************************************************************************
*
* x86-operand-sizes.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_OPERAND_SIZES_H
#define X86_OPERAND_SIZES_H

namespace X86
{
	namespace OPERAND_SIZE
	{
		enum value
		{
			IMPLICIT = -1 ,

			// 8 bits
			BYTE = 1 ,

			// 2 bytes, 16 bits
			WORD = 2 ,

			// 4 bytes, 32 bits
			DWORD = 4 ,

			// 8 bytes, 64 bits
			QWORD = 8 ,

			// 16 bytes, 128 bits
			XMMWORD = 16 ,

			// 32 bytes, 256 bits
			YMMWORD = 32 ,

			// 64 bytes, 512 bits
			ZMMWORD = 64 ,

			// Processor mode specific
			SEGMENT = 1 << 29,

			// Unused. Forces enumeration storage format to int32
			OPERAND_SIZE_FORCE_32B = 1 << 30 ,
		};
	}
}

#endif
