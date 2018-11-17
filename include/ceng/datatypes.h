/*****************************************************************************
*
* datatype-main.h
*
*
*****************************************************************************/

#ifndef _CONCEPT2_DATATYPE_MAIN_H
#define _CONCEPT2_DATATYPE_MAIN_H

#include "./datatypes/basic-types.h"

#include <math.h>

#include "./datatypes/return-val.h"

//#include "./platform/win32-types.h"

// Define concept engine floating point data types

/*
namespace Ceng
{
	typedef Ceng::FLOAT_SINGLE FLOAT32;
	typedef Ceng::FLOAT_DOUBLE FLOAT64;
}
*/

//***************************************************************
// Add non-native data types

#include "./datatypes/float16.h"

namespace Ceng
{
	typedef Float16 FLOAT16;
}

#include "./datatypes/boolean.h"

#include "./datatypes/color-format.h"

#include "./datatypes/abstract-data.h"

#include "./datatypes/ce-string.h"
#include "./datatypes/string-manipulator.h"

//****************************************************************************
// Buffer descriptors

#include "./datatypes/bufferdata-2d.h"

/**
 * Provides adequate information to use about a
 * buffer to use it as a texture or render target.
 */

namespace Ceng
{
	

	/**
 * A float->int conversion  Useful when data can be
 * moved directly from FPU register to general purpose
 * register.
 *
 * Limitations:
 *
 * - Only works for values less or equal to (2^23)-1
 * - Truncation is the only rounding mode
 */
inline INT32 FastFloatToInt(FLOAT32 x)
{
	// Adding this value to a float32 places the 
	// integer portion of *x* at bits [22:0]
	//
	// NOTE: Works by changing the exponent of *x*
	//       to (exponent of the constant + 1)

	//const _FLOAT32 floatToIntMod = _FLOAT32(12582912.0f);
	const FLOAT32 floatToIntMod = FLOAT32(1.5f * 2e23f);

	x += floatToIntMod;

	// Sign extend the integer value at bits [22:0]
	return (*(INT32*)&x - *(INT32*)&floatToIntMod);
}

/**
 * The fast inverse square root trick from Quake III engine.
 */
inline FLOAT32 FastInvSqrt(FLOAT32 x)
{
	FLOAT32 result;
	INT32 temp;
	
	temp = *((INT32*)&x);
	temp = 0x5f3759df - (temp >> 1);

	result = *((FLOAT32*)&temp);

	return result * (1.5f-0.5f*x*result*result);	
}

inline FLOAT32 FastSqrt(FLOAT32 x)
{
	return x*FastInvSqrt(x);
}

/**
 * A FastInvSqrt(x) followed by an additional
 * iteration of Newton's method.
 */
inline FLOAT32 FastInvSqrt2(FLOAT32 x)
{
	FLOAT32 result;
	INT32 temp;
	
	temp = *((INT32*)&x);
	temp = 0x5f3759df - (temp >> 1);

	result = *((FLOAT32*)&temp);

	result =  result * (1.5f-0.5f*x*result*result);
	return result * (1.5f-0.5f*x*result*result);
}

/**
 * A FastInvSqrt(x) followed by two
 * iterations of Newton's method.
 */
inline FLOAT32 FastInvSqrt3(FLOAT32 x)
{
	FLOAT32 result;
	INT32 temp;
	
	temp = *((INT32*)&x);
	temp = 0x5f3759df - (temp >> 1);

	result = *((FLOAT32*)&temp);

	result =  result * (1.5f-0.5f*x*result*result);
	result =  result * (1.5f-0.5f*x*result*result);
	return result * (1.5f-0.5f*x*result*result);
}

/* FastDiv by Jari Korkala , 20/8/2010
 * Uses the underlying idea of FastInvSqrt()
 * NOTE: Faster is quite subjective, at least
 *       on Intel Core2, where this is slower than FDIV.
 *       Must be the data transfer fpu->mem->reg->mem->fpu,
 *       which is not neccesary on ARM.
 */
inline FLOAT32 FastDiv(FLOAT32 x)
{
	FLOAT32 result;
	INT32 temp;

	temp = *((INT32*)&x); // Use the floating point binary data as an integer

	/* The constant here does the following:
	 * (253 << 23) : 
	 * When *temp* is substracted from an integer with
	 * this value in bits 23-30, it multiplies the exponent of the underlying 
	 * floating point number by (-1), and substracts 1 from it,because we 
	 * assume that the floating point number is not a power
	 * of two (there are quite a few of those compared to the whole
	 * dynamic range).
	 *
	 * Remaining added bits (1 << x): 
	 * Chosen so that the worst case relative error is as small as possible.
	 * Because mantissa bits closer to bit 23 are more important, the
	 * values can be found with a greedy algorithm that first sets each
	 * mantissa bit of *guessBase*, and then, starting from bit 22, tries 
	 * one bit off at a time, and checks if the global error maxima over some
	 * suitably wide range of *x* drops.
	 */
	const INT32 guessBase = (253 << 23) + (1 << 22) + (1 << 21) 
								+ (1 << 19) + (1 << 18)
								+ (1 << 17) + (1 << 16) 
								+ (1 << 15);
		
	// If the mantissa of *x* is larger than mantissa of *guessBase*,
	// the substraction borrows 1 from the exponent so that it will be correct.
	temp = guessBase-temp;

	result = *((FLOAT32*)&temp);

	// One iteration of Newton-Raphson -method gives the result
	// that should hold up to 3 decimal places for any *x*.
	result = result*(2.0f-x*result);

	// Use more of these if extra precision is needed.
//	result = result*(2.0f-x*result);	

	return result;	
}

/*
#else

typedef FixedPoint<16> _FLOAT32;
typedef FixedPoint<16> _FLOAT64;

#endif 
*/

//*****************************************************************
// Aligned memory allocator that is used if compiler doesn't
// provide one

/*
#ifndef _CE_PLAT_AMALLOC

void* AlignedMalloc(_UINT32 size,_UINT16 alignment)
{
	return NULL;
}

void AlignedFree(void *pointer)
{
}

#endif
*/

//***************************************************************************
// Numeric constants

	constexpr float pi = 3.141592653589793f;
	constexpr float degree_to_radians = pi / 180.0f;
	constexpr float radians_to_degree = 180.0f / pi;

	constexpr float sq2 = 1.1414213562f;
	constexpr float invert_sq2 = 0.70710678f;

	constexpr float sq3 = 1.732050808f;
	constexpr float invert_sq3 = 0.577350269f;

	constexpr UINT32 mask_blue = 255;
	constexpr UINT32 mask_green = 255 << 8;
	constexpr UINT32 mask_red = 255 << 16;
	constexpr UINT32 mask_red_blue = mask_blue | mask_red;
	constexpr UINT32 mask_alpha = UINT32(255) << 24;

	constexpr UINT32 mask_clip = 4294967292;

#define PI FLOAT32(3.141592653589793)
#define	DEGREE_TO_RADIANS (PI / FLOAT32(180.0)) // Degrees to radians
#define SQ2 FLOAT32(1.1414213562) // Square root of 2
#define OVERSQ2 FLOAT32(0.70710678) // Inverse of SQ2

#define SQ3 FLOAT32(1.732050808) // Square root of 3
#define OVERSQ3 FLOAT32(0.577350269) // Inverse of SQ3

// 32-bit color format (alpha,red,green,blue) masks

#define MASK_BLUE 255
#define MASK_GREEN (255 << 8) //65280
#define MASK_RED (255 << 16) //16711680
#define MASK_RED_BLUE (MASK_BLUE+MASK_RED)
#define MASK_ALPHA (255 << 24) //4278190080

#define MASK_CLIP 4294967292

} // Namespace Ceng

#endif