/*****************************************************************************
*
* x86-vex-w.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_VEX_W_H
#define X86_VEX_W_H

namespace X86
{
	namespace VEX_W_FUNCTION
	{
		enum value
		{
			ZERO = 0 ,
			ONE = 1 ,
			REX_W = 2 ,

			FORCE_32B = 1 << 30 ,
		};
	}
}

#endif