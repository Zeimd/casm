/*****************************************************************************
*
* x86-cpu-modes.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_CPU_MODES_H
#define X86_CPU_MODES_H

namespace X86
{
	namespace CPU_MODE
	{
		enum value
		{
			REAL = 1 ,
			PROTECTED = 2 ,
			X64 = 4 ,

			FORCE_32B = 1 << 30 ,
		};
	}
}

#endif