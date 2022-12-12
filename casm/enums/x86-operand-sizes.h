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

			BYTE = 1 ,
			WORD = 2 ,
			DWORD = 4 ,
			QWORD = 8 ,
			XMMWORD = 16 ,
			YMMWORD = 32 ,

			OPERAND_SIZE_FORCE_32B = 1 << 30 ,
		};
	}
}

#endif
