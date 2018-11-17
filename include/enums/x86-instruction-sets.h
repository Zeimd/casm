/*****************************************************************************
*
* x86-instruction-sets.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_INSTRUCTION_SETS_H
#define X86_INSTRUCTION_SETS_H

namespace X86
{
	namespace INSTRUCTION_SET
	{
		enum value
		{
			SSE = 1 << 1 ,
			SSE_2 = 1 << 2 ,
			SSE_3 = 1 << 3 ,

			SSSE_3 = 1 << 4 ,
			
			SSE_41 = 1 << 5 ,
			SSE_42 = 1 << 6 ,

			AVX = 1 << 7 ,

			MMX = 1 << 8 ,

			CMOV = 1 << 9 ,

			BMI = 1 << 10 ,
			BMI_2 = 1 << 11 ,

			AVX_2 = 1 << 12 ,

			FORCE_32B = 1 << 30 ,
		};
	}
}

#endif