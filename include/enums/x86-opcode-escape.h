/*****************************************************************************
*
* x86-opcode-escape.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_OPCODE_ESCAPE_H
#define X86_OPCODE_ESCAPE_H

namespace X86
{
	namespace OPCODE_ESCAPE
	{
		enum value
		{
			NONE = 0 ,
			BYTE_0F = 1 ,
			BYTES_0F_3A = 2 ,
			BYTES_0F_38 = 3 ,

			BYTES_0F_01 = 4 ,

			FORCE_32B = 1 << 30 ,
		};
	}
}

#endif