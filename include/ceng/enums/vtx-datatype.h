/*****************************************************************************
*
* vtx-datatype.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_VTX_DATATYPE_H
#define _CENG_VTX_DATATYPE_H

namespace Ceng
{
	namespace VTX_DATATYPE 
	{
		enum value
		{
			UNKNOWN = 0 ,

			// **** Single-precision floats
			FLOAT = 1 ,
			FLOAT2 = 2 ,
			FLOAT3 = 3 ,
			FLOAT4 = 4 ,

			// **** Double-precision floats
		
			DOUBLE = 5 ,
			DOUBLE2 = 6 ,
			DOUBLE3 = 7 ,
			DOUBLE4 = 8 ,

			// **** Half-precision floats
		
			FP16_2 = 9 , // 2 x 16-bit floating point
			FP16_4 = 10 , // 4 x 16-bit floating point
		
			// **** Values are taken as signed integer
		
			DWORD = 11 , // 32-bit integer
			DWORD2 = 12 ,
			DWORD3 = 13 ,
			DWORD4 = 14 , // Packed 4 signed integers
		
			WORD2 = 15 , // Packed 2 signed words
			WORD4 = 16 , // Packed 4 signed words	
			BYTE4 = 17 , // Packed 4 bytes
		
			// **** Values are taken as unsigned integer
		
			UWORD2 = 18 ,
			UWORD4 = 19 ,
			UBYTE4 = 20 , // Packed 4 unsigned bytes
		
			// Values are normalized between [-1,1] for signed,
			// and [0,1] for unsigned
		
			UNWORD2 = 21 , // Converted to (x / 65535.0 , y / 65535.0)
			UNWORD4 = 22 ,
			UNBYTE4 = 23 ,
			
			NWORD2 = 24 , // Converted to (x / 32767.0 , y / 32767.0)
			NWORD4 = 25 ,
			NBYTE4 = 26 ,			
		
			// **** Color formats
		
			COLOR_R5_G6_B5 = 27 , // 16-bit R5_G6_B5 (Direct3D)
			COLOR_B5_G6_R5 = 28 , // 16-bit B5_G6_B5 (OpenGL)

			COLOR_A1_R5_G5_B5 = 29 , // 16-bit A1_R5_G5_B5 (Direct3D)
			COLOR_A1_B5_G5_R5 = 30 , // 16-bit A1_B5_G5_R5 (OpenGL)

			COLOR_R5_G5_B5 = 31 , // 16-bit R5_G5_B5 (Direct3D)
			COLOR_B5_G5_R5 = 32 , // 16-bit B5_G5_R5 (OpenGL)

			COLOR_A4_R4_G4_B4 = 33 , // 16-bit A4_R4_G4_B4 (Direct3D)
			COLOR_A4_B4_G4_R4 = 34 , // 16-bit A4_B4_G4_R4 (OpenGL)

			COLOR_A8_R8_G8_B8 = 35 , // Blue in least significant byte (Direct3D)
			COLOR_A8_B8_G8_R8 = 36 , // Red in least significant byte (OpenGL)
			
			COLOR_X8_R8_G8_B8 = 37 , // 24-bit color
			COLOR_X8_B8_G8_R8 = 38 ,

			COLOR_A6_R6_G6_B6 = 39 , // 18-bit color with alpha (stored in 32 bits)
			COLOR_A6_B6_G6_R6 = 40 ,

			COLOR_X6_R6_G6_B6 = 41 , // 18-bit color (stored in 32 bits)
			COLOR_X6_B6_G6_R7 = 42 , 

			COLOR_A16_R16_G16_B16 = 43 , // 48-bit color with alpha (Direct3D)
			COLOR_A16_B16_G16_R16 = 44 , // (OpenGL)

			COLOR_X16_R16_G16_B16 = 45 , // 48-bit color (Direct3D)
			COLOR_X16_B16_G16_R16 = 46 , // (OpenGL)
		
			UDEC3 = 47 , // Three 10-bit unsigned integers
			NDEC3 = 48 , // Three 10-bit signed integers , normalized
		
			
		
			FORMAT_END = 1 << 30,
		};
	};
	
};

#endif