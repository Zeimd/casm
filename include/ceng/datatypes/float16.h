/*****************************************************************************
*
* ce-float16.h
*
* By Jari Korkala 1/2012
*
* 16-bit floating point class for those platforms that can't handle
* it internally
*
* WARNING: Do not include this file directly. Include "../../include/datatypes/datatype-main.h" instead.
*
*****************************************************************************/

#ifndef _CONCEPT2FLOAT16_H
#define _CONCEPT2FLOAT16_H

#include "basic-types.h"

namespace Ceng
{
	const UINT16 FP32_TO_FP16(const FLOAT32 input);
	const FLOAT32 FP16_TO_FP32(const UINT16 input);
	
	const UINT16 FP64_TO_FP16(const FLOAT64 input);
	const FLOAT64 FP16_TO_FP64(const UINT16 input);
	
	const UINT16 UINT32_TO_FP16(const UINT32 input);
	const UINT32 FP16_TO_UINT32(const UINT16 input);

class Float16
{
protected:
	UINT16 value;

public:
	Float16();
	~Float16();

	Float16(const Float16 &other);

	Float16(const FLOAT32 &source);
	Float16(const FLOAT64 &source);

	Float16& operator = (const Float16 &other);
	Float16& operator = (const FLOAT32 &source);
	Float16& operator = (const FLOAT64 &source);

	const bool operator == (const Float16 &other) const;

	const bool operator != (const Float16 &other) const;
	const bool operator != (const FLOAT32 &other) const;
	const bool operator != (const FLOAT64 &other) const;
	const bool operator != (const INT32 &other) const;

	operator INT32() const;
	operator UINT32() const;

	operator FLOAT32() const;
	operator FLOAT64() const;
};

inline Float16::Float16()
{
}

inline Float16::~Float16()
{
}

inline Float16::Float16(const Float16 &other)
{
	value = other.value;
}

inline Float16& Float16::operator =(const Float16 &other)
{
	value = other.value;
	return *this;
}

inline Float16& Float16::operator =(const FLOAT32 &source)
{
	value = FP32_TO_FP16(source);
	return *this;
}

inline Float16& Float16::operator =(const FLOAT64 &source)
{
	value = FP64_TO_FP16(source);
	return *this;
}

inline const bool Float16::operator ==(const Float16 &other) const
{
	return (value == other.value);
}

inline const bool Float16::operator !=(const Float16 &other) const
{
	return (value != other.value);
}

inline const bool Float16::operator !=(const INT32 &other) const
{
	UINT16 temp;

	temp = FP32_TO_FP16(FLOAT32(other));
	if (temp != value)
	{
		return false;
	}
	return true;
}

inline Float16::operator INT32() const
{
	FLOAT32 temp;

	temp = FP16_TO_FP32(value);
	return INT32(temp);
}

inline Float16::operator UINT32() const
{
	FLOAT32 temp;

	temp = FP16_TO_FP32(value);
	return UINT32(temp);
}

inline Float16::operator FLOAT32() const
{
	return FP16_TO_FP32(value);
}

inline Float16::operator FLOAT64() const
{
	return FP16_TO_FP64(value);
}

const UINT32 exponentMap[] =
{
	0,
	(-14+127) << 23,
	(-13+127) << 23,
	(-12+127) << 23,
	(-11+127) << 23,
	(-10+127) << 23,
	(-9+127) << 23,
	(-8+127) << 23,
	(-7+127) << 23,
	(-6+127) << 23,
	(-5+127) << 23,
	(-4+127) << 23,
	(-3+127) << 23,
	(-2+127) << 23,
	(-1+127) << 23,
	127 << 23,
	(1+127) << 23,
	(2+127) << 23,
	(3+127) << 23,
	(4+127) << 23,
	(5+127) << 23,
	(6+127) << 23,
	(7+127) << 23,
	(8+127) << 23,
	(9+127) << 23,
	(10+127) << 23,
	(11+127) << 23,
	(12+127) << 23,
	(13+127) << 23,
	(14+127) << 23,
	(15+127) << 23,
	255 << 23
};

inline const FLOAT32 FP16_TO_FP32(const UINT16 input)
{
	UINT32 mantissa;
	INT32 exponent;
	UINT32 sign;

	mantissa = input;

	sign = mantissa >> 15;

	exponent = (mantissa >> 10) & 31;

	mantissa = mantissa & ((1 << 10) - 1);

	mantissa = mantissa << 12;

	// Map exponents from -14 to 15 correct fp32 value,
	// but -15 (zero/subnormal)  becomes 0, 
	// and 16 (infinity/NaN) becomes 255.

	// NOTE: Look-up table has the exponent in the
	//       correct bit position

	mantissa += exponentMap[exponent];
	mantissa += sign << 31;

	return *(FLOAT32*)&mantissa;
}

inline const UINT16 FP32_TO_FP16(const FLOAT32 input)
{
	INT32 floatBits;
	INT32 mantissa;
	INT32 exponent;
	INT32 sign;

	floatBits = *(INT32*)&input;

	mantissa = floatBits & ((INT32(1) << 23)-INT32(1));

	exponent = (floatBits >> 23) & INT32(255);
	exponent -= 127;

	sign = (floatBits >> 31) & 1;

	if (exponent == 128)
	{
		// NaN or infinity

		if (mantissa > 0)
		{
			// Retain quiet Nan flag from original
			// mantissa, and set an additional
			// bit to ensure a NaN in any case

			mantissa = (mantissa >> 12) | (1 << 8);
		}

		exponent = 31; 
	}
	else if (exponent == -127)
	{
		// Source is zero or subnormal

		mantissa = mantissa >> 12;
		exponent = 0;
	}
	else 
	{
		mantissa += INT32(1) << 23; // Add implicit bit

		// TODO: Round half to even at bit position 11?

		// Shift mantissa down to 10 bits
		mantissa = mantissa >> 12;

		if (exponent < -14)
		{
			// Subnormal number

			mantissa = mantissa >> (-14-exponent);
			exponent = -15;
		}
		else if (exponent > 15)
		{
			// Overflow => set to infinity

			mantissa = 0;
			exponent = 16;
		}

		exponent += 15;
	}

	// Remove implicit most significant bit if present
	mantissa = mantissa & ((1 << 10) - 1);

	mantissa += exponent << 10;
	mantissa += sign << 15;

	return *(UINT16*)&mantissa;
}

inline const FLOAT64 FP16_TO_FP64(const UINT16 input)
{
	FLOAT64 temp = 0.0;

	return temp;
}

inline const UINT16 FP64_TO_FP16(const FLOAT64 input)
{
	UINT16 temp = 0;
	return temp;
}

} // Namespace Ceng

#endif // Include Guard