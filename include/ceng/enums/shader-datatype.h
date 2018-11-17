/*****************************************************************************
*
* shader-datatype.h
*
* By Jari Korkala 5/2013
*
*****************************************************************************/

#ifndef _CENG_SHADER_DATATYPE_H
#define _CENG_SHADER_DATATYPE_H

namespace Ceng
{
	/**
	 * Possible shader variable data types.
	 *
	 * NOTE: All integral data types are 32 bits per element.
	 */
	namespace SHADER_DATATYPE
	{
		enum value
		{
			UNKNOWN = 0 ,

			FLOAT = 1 ,
			FLOAT2 = 2 ,
			FLOAT3 = 3 ,
			FLOAT4 = 4 ,

			DOUBLE = 5 ,
			DOUBLE2 = 6 ,
			DOUBLE3 = 7 ,
			DOUBLE4 = 8 ,

			UINT = 9 ,
			UINT2 = 10 ,
			UINT3 = 11 ,
			UINT4 = 12 ,

			INT = 13 ,
			INT2 = 14 ,
			INT3 = 15 ,
			INT4 = 16 ,

			BOOL = 17 ,
			BOOL2 = 18 ,
			BOOL3 = 19 ,
			BOOL4 = 20 ,

			// Matrix types

			FLOAT4x4 = 21 ,
			FLOAT3x3 = 22 ,
			FLOAT2x2 = 23 ,

			DOUBLE4x4 = 24 ,
			DOUBLE3x3 = 25 ,
			DOUBLE2x2 = 26 ,

			UINT4x4 = 27 ,
			UINT3x3 = 28 ,
			UINT2x2 = 29 ,

			INT4x4 = 30 ,
			INT3x3 = 31 ,
			INT2x2 = 32 ,

			BOOL4x4 = 33 ,
			BOOL3x3 = 34 ,
			BOOL2x2 = 35 ,
	
			FORCE_32B = 1 << 30 ,
		};
	};
};

#endif
