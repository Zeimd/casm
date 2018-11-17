/*****************************************************************************
*
* vstudio-win32.h
*
* By Jari Korkala 5/2014
*
*****************************************************************************/

#ifndef CENG_VSTUDIO_WIN32_H
#define CENG_VSTUDIO_WIN32_H

//**********************************************************
// Microsoft Visual Studio
// Data types and platform-specific methods

#ifdef _MSC_VER
	
namespace Ceng
{
	//*******************************
	// Data types

	typedef char INT8;
	typedef unsigned char UINT8;
	
	typedef short INT16;
	typedef unsigned short UINT16;
	
	typedef int INT32;
	typedef unsigned int UINT32;
	
	typedef __int64 INT64;
	typedef unsigned __int64 UINT64;

	typedef int(__stdcall *DynamicCallback)();
}

#define PLATFORM_HAS_FPU

#ifdef _M_IX86

namespace Ceng
{
	typedef unsigned int POINTER;
}

#define PLATFORM_CPU_X86
#endif

#ifdef _M_X64

namespace Ceng
{
	typedef unsigned __int64 POINTER;
}

#define PLATFORM_CPU_X86_64

#endif // _M_X64

namespace Ceng
{
	typedef char CHAR;
}

//************************************
// Placeholder typedefs for floating
// point formats

namespace Ceng
{
	typedef float FLOAT32;
	typedef double FLOAT64;
}

//*************************************************************
// Aligned memory allocator

#include <malloc.h>

#define PLATFORM_ALIGNED_MALLOC // Flag the presence of allocator

namespace Ceng
{
	inline void* AlignedMalloc(UINT32 size,UINT32 alignment)
	{
		void *out = _aligned_malloc(size, alignment);

		return out;
	}
	
	inline void AlignedFree(void* pointer)
	{
		_aligned_free(pointer);
	}
}

//***************************************************************

/**
 * x86-specific float to int conversion that
 * doesn't change rounding mode to C-language's
 * standard truncation (which is slow).
 */

namespace Ceng
{
	inline const INT32 CE_FloatToInt(const FLOAT32 x)
	{
		INT32 temp;
		__asm
		{
			fld DWORD PTR x;
			fistp DWORD PTR temp;
		}
		return temp;
	}
	
	inline const INT64 CE_DoubleToInt(const FLOAT64 x)
	{
		INT64 temp;
		__asm
		{
			fld QWORD PTR x;
			fistp QWORD PTR temp;
		}
		return temp;
	}

} // Namespace Ceng

#if (_MSC_VER >= 11)

#define PLATFORM_EXTERN_TEMPLATE

#endif

#endif // _MSC_VER

#endif