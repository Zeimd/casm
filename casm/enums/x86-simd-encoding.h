/*****************************************************************************
*
* x86-simd-encoding.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_SIMD_ENCODING_H
#define X86_SIMD_ENCODING_H

namespace X86
{
	namespace SIMD_ENCODING
	{
		enum value
		{
			LEGACY = 0 ,
			VEX = 1 ,

			FORCE_32B = 1 << 30 ,
		};
	}
}

#endif