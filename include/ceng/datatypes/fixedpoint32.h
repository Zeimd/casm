/*****************************************************************************
*
* fixedpoint.h
*
* By Jari Korkala 6/2011
*
* Class FixedPoint32 : Template for fixed point arithmetic with 32-bit
*                      integers.
*
* TODO: Fix radix-4 division algorithm for large numerators
*
* TODO: Correct x86 rounding behavior for machine division with 
*       negative parameters
*
* TODO: Implement round half to even for multiplication and division
*
*****************************************************************************/

#ifndef _CONCEPT_FIXEDP32_H
#define _CONCEPT_FIXEDP32_H

#include "basic-types.h"

#include <math.h>

namespace Ceng
{

template<_UINT32 F>
class FixedPoint
{
protected:
	_INT32 value;
public:
	FixedPoint() {}
	FixedPoint(const FixedPoint &other);

	template<_UINT32 T>
	FixedPoint(const FixedPoint<T> &other);

	FixedPoint(const _INT32 a); 
	/* Loads contents of internal data field, not an integer. */

	FixedPoint(const _FLOAT_SINGLE a);
	FixedPoint(const _FLOAT_DOUBLE a);

	const _INT32 Value() const;
	/* Return data field contents */

	// Assignment operators
	FixedPoint& operator = (const FixedPoint &other);

	template<_UINT32 T>
	FixedPoint& operator = (const FixedPoint<T> &other);

	FixedPoint& operator = (const _INT32 a);
	FixedPoint& operator = (const _FLOAT_SINGLE a);
	FixedPoint& operator = (const _FLOAT_DOUBLE a);

	// Addition operators
	const FixedPoint operator + (const FixedPoint &other) const;
	
	template<_UINT32 T>
	const FixedPoint operator + (const FixedPoint<T> &other) const;

	const FixedPoint operator + (const _INT32 a) const;
	const FixedPoint operator + (const _FLOAT_SINGLE a) const;
	const FixedPoint operator + (const _FLOAT_DOUBLE a) const;

	FixedPoint& operator += (const FixedPoint &other);

	template<_UINT32 T>
	FixedPoint& operator += (const FixedPoint<T> &other);

	FixedPoint& operator += (const _INT32 a);
	FixedPoint& operator += (const _FLOAT_SINGLE a);
	FixedPoint& operator += (const _FLOAT_DOUBLE a);	
	
	// Subtract operators
	const FixedPoint operator - (const FixedPoint &other) const;

	template<_UINT32 T>
	const FixedPoint operator - (const FixedPoint<T> &other) const;

	const FixedPoint operator - (const _INT32 a) const;
	const FixedPoint operator - (const _FLOAT_SINGLE a) const;
	const FixedPoint operator - (const _FLOAT_DOUBLE a) const;

	FixedPoint& operator -= (const FixedPoint &other);

	template<_UINT32 T>
	FixedPoint& operator -= (const FixedPoint<T> &a);

	FixedPoint& operator -= (const _INT32 a);
	FixedPoint& operator -= (const _FLOAT_SINGLE a);
	FixedPoint& operator -= (const _FLOAT_DOUBLE a);	

	// Multiplication
	const FixedPoint operator * (const FixedPoint &other) const;

	template<_UINT32 T>
	const FixedPoint operator * (const FixedPoint<T> &other) const;

	template<_UINT32 T>
	const FixedPoint<F> ReducedMult(const FixedPoint<T> &a,
								const FixedPoint<T> &b) const;
	/* Multiplication in another format, 
	   convert result to this format. */

	const FixedPoint operator * (const _INT32 a) const;
	const FixedPoint operator * (const _FLOAT_SINGLE a) const;
	const FixedPoint operator * (const _FLOAT_DOUBLE a) const;

	FixedPoint& operator *= (const FixedPoint &other);

	template<_UINT32 T>
	FixedPoint& operator *= (const FixedPoint<T> &other);

	FixedPoint& operator *= (const _INT32 a);
	FixedPoint& operator *= (const _FLOAT_SINGLE a);
	FixedPoint& operator *= (const _FLOAT_DOUBLE a);	

	// Division operators
	const FixedPoint operator / (const FixedPoint &other) const;

	template<_UINT32 T>
	const FixedPoint operator / (const FixedPoint<T> &other) const;

	const FixedPoint operator / (const _INT32 a) const;
	const FixedPoint operator / (const _FLOAT_SINGLE a) const;
	const FixedPoint operator / (const _FLOAT_DOUBLE a) const;

	FixedPoint& operator /= (const FixedPoint &other);

	template<_UINT32 T>
	FixedPoint& operator /= (const FixedPoint<T> &other);

	FixedPoint& operator /= (const _INT32 a);
	FixedPoint& operator /= (const _FLOAT_SINGLE a);
	FixedPoint& operator /= (const _FLOAT_DOUBLE a);	
	
	// Comparator ==
	const bool operator == (const FixedPoint &other) const;

	template<_UINT32 T>
	const bool operator == (const FixedPoint<T> &other) const;

	const bool operator == (const _INT32 a) const;
	const bool operator == (const _FLOAT_SINGLE a) const;
	const bool operator == (const _FLOAT_DOUBLE a) const;

	// Comparator !=
	const bool operator != (const FixedPoint &other) const;

	template<_UINT32 T>
	const bool operator != (const FixedPoint<T> &other) const;

	const bool operator != (const _INT32 a) const;
	const bool operator != (const _FLOAT_SINGLE a) const;
	const bool operator != (const _FLOAT_DOUBLE a) const;

	// Comparator >
	const bool operator > (const FixedPoint &other) const;

	template<_UINT32 T>
	const bool operator > (const FixedPoint<T> &other) const;

	const bool operator > (const _INT32 a) const;
	const bool operator > (const _FLOAT_SINGLE a) const;
	const bool operator > (const _FLOAT_DOUBLE a) const;

	// Comparator <
	const bool operator < (const FixedPoint &other) const;

	template<_UINT32 T>
	const bool operator < (const FixedPoint<T> &other) const;

	const bool operator < (const _INT32 a) const;
	const bool operator < (const _FLOAT_SINGLE a) const;
	const bool operator < (const _FLOAT_DOUBLE a) const;

	// Comparator >=
	const bool operator >= (const FixedPoint &other) const;

	template<_UINT32 T>
	const bool operator >= (const FixedPoint<T> &other) const;

	const bool operator >= (const _INT32 a) const;
	const bool operator >= (const _FLOAT_SINGLE a) const;
	const bool operator >= (const _FLOAT_DOUBLE a) const;

	// Comparator <=
	const bool operator <= (const FixedPoint &other) const;

	template<_UINT32 T>
	const bool operator <= (const FixedPoint<T> &other) const;

	const bool operator <= (const _INT32 a) const;
	const bool operator <= (const _FLOAT_SINGLE a) const;
	const bool operator <= (const _FLOAT_DOUBLE a) const;

	
	// Conversions
	operator int() const;

	operator _FLOAT_SINGLE() const;
	operator _FLOAT_DOUBLE() const;

	// These use either FPU or do an emulated conversion
	// with integer arithmetic.
	// NOTE :  Whenever input or output parameter is a float, these
	//         should be used for conversion.
	const _INT32 ReadFloat(const _FLOAT_SINGLE a) const;
	const _INT32 ReadDouble(const _FLOAT_DOUBLE a) const;

	const _FLOAT_SINGLE WriteFloat() const;
	const _FLOAT_DOUBLE WriteDouble() const;

	// Division for those platforms that lack the machine code
	// instruction
	const FixedPoint AlgorithmDivide(const FixedPoint &other) const;

	// Newton-Rhapson method for 1/x
	const FixedPoint FixedPoint::FastDiv(const FixedPoint &other) const;
};

//***************************************************************************
// Float <==> fixed point conversions

#ifdef _CE_HAS_FPU

template<_UINT32 F>
inline const _INT32 FixedPoint<F>::ReadFloat(const _FLOAT_SINGLE a) const
{
	return _INT32(_FLOAT_SINGLE(1 << F)*a);
}

template<_UINT32 F>
inline const _INT32 FixedPoint<F>::ReadDouble(const _FLOAT_DOUBLE a) const
{
	return _INT32(_FLOAT_DOUBLE(1 << F)*a);
}

template<_UINT32 F>
inline const _FLOAT_SINGLE FixedPoint<F>::WriteFloat() const
{
	const _FLOAT_SINGLE scale = _FLOAT_SINGLE(1.0) / _FLOAT_SINGLE(1 << F);

	return _FLOAT_SINGLE(value)*scale;
}

template<_UINT32 F>
inline const _FLOAT_DOUBLE FixedPoint<F>::WriteDouble() const
{
	const _FLOAT_DOUBLE scale = _FLOAT_DOUBLE(1.0) / _FLOAT_DOUBLE(1 << F);

	return _FLOAT_DOUBLE(value)*scale;
}

#else // No FPU available => use integer arithmetic

template<_UINT32 F>
inline const _INT32 FixedPoint<F>::ReadFloat(const _FLOAT_SINGLE a) const
{
	_INT32 floatBits;
	_INT32 mantissa;
	_INT32 exponent;
	_INT32 sign;

	floatBits = *(_INT32*)&a;

	mantissa = floatBits & ((_INT32(1) << 23)-_INT32(1));
	mantissa += _INT32(1) << 23; // Add implicit bit

	exponent = (floatBits >> 23) & _INT32(255);
	exponent -= 127;

	exponent -= 23-F;

	sign = (floatBits >> 31) & 1;

	if (exponent >= 0)
	{
		mantissa = mantissa << exponent;
	}
	else
	{
		mantissa = mantissa >> (-exponent);
	}

	if (sign) mantissa = -mantissa;

	return mantissa;
}

template<_UINT32 F>
inline const _INT32 FixedPoint<F>::ReadDouble(const _FLOAT_DOUBLE a) const
{
	_INT32 result;
	_INT64 floatBits;
	_INT64 mantissa;
	_INT64 exponent;
	_INT64 sign;

	floatBits = *(_INT64*)&a;

	mantissa = floatBits & ((_INT64(1) << 52)-_INT64(1));
	mantissa += _INT64(1) << 52; // Add implicit bit

	exponent = (floatBits >> 52) & _INT64(2047);
	exponent -= 1023;

	exponent -= 52-F;

	sign = (floatBits >> 63) & 1;

	if (exponent >= 0)
	{
		mantissa = mantissa << exponent;
	}
	else
	{
		mantissa = mantissa >> (-exponent);
	}

	result = _INT32(mantissa);

	if (sign) result = -result;

	return result;
}

#include <stdio.h>

template<_UINT32 F>
inline const _FLOAT_SINGLE FixedPoint<F>::WriteFloat() const
{
	
	_UINT32 k;
	_UINT32 mask;

	_INT32 temp;

	_UINT32 sign;
	_UINT32 mantissa;
	_UINT32 exponent;

	mask = _UINT32(1) << 31;
	sign = (value & mask);

	temp = value;
	if (sign)
	{
		temp = -temp;
	}

	// Find exponent = most significant set bit
	for(k=30;k>=0;k--)
	{
		if (temp & mask) break;
		mask = mask >> 1;
	}

	exponent = k-F+1;

	// Move most significant bit to implicit position
	if (k < 23)
	{
		mantissa = temp << (22-k);
	}
	else
	{
		mantissa = temp >> (k-22);
	}

	// Erase implicit bit
	mantissa = mantissa & ((1 << 23)-1);

	// Store adjusted exponent
	exponent += 127;
	mantissa += exponent << 23;

	// Store sign
	mantissa += sign;

	return *(_FLOAT_SINGLE*)&mantissa;
}

template<_UINT32 F>
inline const _FLOAT_DOUBLE FixedPoint<F>::WriteDouble() const
{
	
	_UINT32 k;
	_UINT32 mask;

	_INT32 temp;

	_UINT64 sign;
	_UINT64 mantissa;
	_UINT64 exponent;

	mask = _UINT32(1) << 31;
	sign = _UINT64(value & mask) << 32;

	temp = value;
	if (sign)
	{
		temp = -temp;
	}

	// Find exponent = most significant set bit
	for(k=30;k>=0;k--)
	{
		if (temp & mask) break;
		mask = mask >> 1;
	}

	exponent = k-F+1;

	// Move most significant bit to implicit position
	if (k < 52)
	{
		mantissa = _UINT64(temp) << (51-k);
	}
	else
	{
		mantissa = _UINT64(temp) >> (k-51);
	}

	// Erase implicit bit
	mantissa = mantissa & ((_UINT64(1) << 52)-_UINT64(1));

	// Store adjusted exponent
	exponent += _UINT64(1023);
	mantissa += exponent << 52;

	// Store sign
	mantissa += sign;

	return *(_FLOAT_DOUBLE*)&mantissa;
}

#endif

//***************************************************************************
// Class FixedPoint methods

template<_UINT32 F>
inline const _INT32 FixedPoint<F>::Value() const
{
	return value;
}

// *******************************
// Constructors

template<_UINT32 F>
inline FixedPoint<F>::FixedPoint(const FixedPoint &other)
{
	value = other.value;
}


template<_UINT32 F>
template<_UINT32 T>
inline FixedPoint<F>::FixedPoint(const FixedPoint<T> &other)
{
	_INT32 temp;

	if (F > T)
	{
		value = other.Value() << (F-T);
	}
	else
	{
		value = other.Value() >> (T-F);
	}
}

template<_UINT32 F>
inline FixedPoint<F>::FixedPoint(const _INT32 a)
{
	value = a; // Must do this to allow explicit construction
}

template<_UINT32 F>
inline FixedPoint<F>::FixedPoint(const _FLOAT_SINGLE a)
{
	value = ReadFloat(a);
}

template<_UINT32 F>
inline FixedPoint<F>::FixedPoint(const _FLOAT_DOUBLE a)
{
	value = ReadDouble(a);
}

// *************************
// Assignment operators
template<_UINT32 F>
inline FixedPoint<F>& FixedPoint<F>::operator = (const FixedPoint &other)
{
	value = other.value;
	return *this;
}

template<_UINT32 F>
template<_UINT32 T>
inline FixedPoint<F>& FixedPoint<F>::operator = (const FixedPoint<T> &other)
{
	if (F > T)
	{
		value = other.Value() << (F-T);
	}
	else
	{
		value = other.Value() >> (T-F);
	}
	return *this;
}

template<_UINT32 F>
inline FixedPoint<F>& FixedPoint<F>::operator = (const _INT32 a)
{
	value = a;
	return *this;
}

template<_UINT32 F>
inline FixedPoint<F>& FixedPoint<F>::operator = (const _FLOAT_SINGLE a)
{
	value = ReadFloat(a);
	return *this;
}

template<_UINT32 F>
inline FixedPoint<F>& FixedPoint<F>::operator = (const _FLOAT_DOUBLE a)
{
	value = ReadDouble(a);
	return *this;
}

//***************************
// Conversions

template<_UINT32 F>
inline FixedPoint<F>::operator int() const
{
	return value >> F;
}

template<_UINT32 F>
inline FixedPoint<F>::operator _FLOAT_SINGLE() const
{
	return WriteFloat();
}

template<_UINT32 F>
inline FixedPoint<F>::operator _FLOAT_DOUBLE() const
{
	return WriteDouble();
}

//***************************
// Addition

template<_UINT32 F>
inline const FixedPoint<F> FixedPoint<F>::operator+(const FixedPoint<F> &other) const
{
	return FixedPoint(value + other.value);
}

template<_UINT32 F>
inline FixedPoint<F>& FixedPoint<F>::operator += (const FixedPoint<F> &other)
{
	value += other.value;
	return *this;
}

template<_UINT32 F>
template<_UINT32 T>
inline const FixedPoint<F> FixedPoint<F>::operator+(const FixedPoint<T> &other) const
{
	_INT32 temp;
	if (F > T)
	{
		temp = other.Value() << (F-T);
	}
	else
	{
		temp = other.Value() >> (T-F);
	}
	return FixedPoint(value + temp);
}

template<_UINT32 F>
template<_UINT32 T>
inline FixedPoint<F>& FixedPoint<F>::operator += (const FixedPoint<T> &other)
{
	_INT32 temp;
	if (F > T)
	{
		temp = other.Value() << (F-T);
	}
	else
	{
		temp = other.Value() >> (T-F);
	}
	value += temp;
	return *this;
}

template<_UINT32 F>
inline const FixedPoint<F> FixedPoint<F>::operator+(const _INT32 a) const
{
	return FixedPoint(value + (a << F));
}

template<_UINT32 F>
inline FixedPoint<F>& FixedPoint<F>::operator += (const _INT32 a)
{
	value += a << F;
	return *this;
}

template<_UINT32 F>
inline const FixedPoint<F> FixedPoint<F>::operator+(const _FLOAT_SINGLE a) const
{
	_INT32 temp;

	temp = ReadFloat(a);
	return FixedPoint(value + temp);
}

template<_UINT32 F>
inline FixedPoint<F>& FixedPoint<F>::operator += (const _FLOAT_SINGLE a)
{
	value += ReadFloat(a);
	return *this;
}

template<_UINT32 F>
inline const FixedPoint<F> FixedPoint<F>::operator+(const _FLOAT_DOUBLE a) const
{
	_INT32 temp;

	temp = ReadDouble(a);
	return FixedPoint(value + temp);
}

template<_UINT32 F>
inline FixedPoint<F>& FixedPoint<F>::operator += (const _FLOAT_DOUBLE a)
{
	value += ReadDouble(a);
	return *this;
}

//***************************
// Subtraction

template<_UINT32 F>
inline FixedPoint<F>& FixedPoint<F>::operator -= (const FixedPoint<F> &other)
{
	value -= other.value;
	return *this;
}

template<_UINT32 F>
template<_UINT32 T>
inline FixedPoint<F>& FixedPoint<F>::operator -= (const FixedPoint<T> &other)
{
	_INT32 temp;
	if (F > T)
	{
		temp = other.Value() << (F-T);
	}
	else
	{
		temp = other.Value() >> (T-F);
	}
	value -= temp;
	return *this;
}

template<_UINT32 F>
inline const FixedPoint<F> FixedPoint<F>::operator-(const FixedPoint<F> &other) const
{
	return FixedPoint(value - other.value);
}

template<_UINT32 F>
template<_UINT32 T>
inline const FixedPoint<F> FixedPoint<F>::operator-(const FixedPoint<T> &other) const
{
	FixedPoint<F> temp;

	temp = *this;

	return (*this -= other);	
}



template<_UINT32 F>
inline const FixedPoint<F> FixedPoint<F>::operator-(const _INT32 a) const
{
	return FixedPoint(value - (a << F));
}

template<_UINT32 F>
inline FixedPoint<F>& FixedPoint<F>::operator -= (const _INT32 a)
{
	value -= a << F;
	return *this;
}

template<_UINT32 F>
inline const FixedPoint<F> FixedPoint<F>::operator-(const _FLOAT_SINGLE a) const
{
	_INT32 temp;

	temp = ReadFloat(a);
	return FixedPoint(value - temp);
}

template<_UINT32 F>
inline FixedPoint<F>& FixedPoint<F>::operator -= (const _FLOAT_SINGLE a)
{
	value -= ReadFloat(a);
	return *this;
}

template<_UINT32 F>
inline const FixedPoint<F> FixedPoint<F>::operator-(const _FLOAT_DOUBLE a) const
{
	_INT32 temp;

	temp = ReadDouble(a);
	return FixedPoint(value - temp);
}

template<_UINT32 F>
inline FixedPoint<F>& FixedPoint<F>::operator -= (const _FLOAT_DOUBLE a)
{
	value -= ReadDouble(a);
	return *this;
}

//***************************
// Multiplication

template<_UINT32 F>
inline FixedPoint<F>& FixedPoint<F>::operator *= (const FixedPoint<F> &a)
{
	_INT64 temp;
	_INT64 adjust;
	
	temp = _INT64(value)*a.value;

	// Round half to even
	
	value = _INT32(temp >> F);

	return *this;
}

template<_UINT32 F>
template<_UINT32 T>
inline FixedPoint<F>& FixedPoint<F>::operator *= (const FixedPoint<T> &other)
{
	_INT64 temp;
	_INT64 adjust;

	temp = _INT64(value)*other.Value();

	// Round half to even

	value = _INT32(temp >> T);

	return *this;
}

template<_UINT32 F>
inline const FixedPoint<F> FixedPoint<F>::operator * (const FixedPoint<F> &other) const
{
	FixedPoint temp;

	temp = *this;

	return (temp *= other);
}

template<_UINT32 F>
template<_UINT32 T>
inline const FixedPoint<F> FixedPoint<F>::operator * (const FixedPoint<T> &other) const
{
	FixedPoint<F> temp;

	temp = *this;
	return (temp *= other);
}

template<_UINT32 F>
inline const FixedPoint<F> FixedPoint<F>::operator * (const _INT32 a) const
{
	return FixedPoint(value*a);
}

template<_UINT32 F>
inline FixedPoint<F>& FixedPoint<F>::operator *= (const _INT32 a)
{
	value *= a;
	return *this;
}

template<_UINT32 F>
inline const FixedPoint<F> FixedPoint<F>::operator * (const _FLOAT_SINGLE a) const
{
	_INT32 temp;

	temp = ReadFloat(a);
	return (*this * FixedPoint(temp));
}

template<_UINT32 F>
inline FixedPoint<F>& FixedPoint<F>::operator *= (const _FLOAT_SINGLE a)
{
	_INT32 temp;

	temp = ReadFloat(a);

	*this *= FixedPoint(temp);

	return *this;
}

template<_UINT32 F>
inline const FixedPoint<F> FixedPoint<F>::operator * (const _FLOAT_DOUBLE a) const
{
	_INT32 temp;

	temp = ReadDouble(a);
	return (*this * FixedPoint(temp));
}

template<_UINT32 F>
inline FixedPoint<F>& FixedPoint<F>::operator *= (const _FLOAT_DOUBLE a)
{
	_INT32 temp;

	temp = ReadDouble(a);

	*this *= FixedPoint(temp);

	return *this;
}

//**********************************
// Division

template<_UINT32 F>
inline FixedPoint<F>& FixedPoint<F>::operator /= (const FixedPoint<F> &other)
{
	_INT64 temp;
	_INT64 adjust;
	
	if (other.value == 0)
	{
		if ( value < 0)
		{
			value = _UINT32(1) << 31;
		}
		else
		{
			value = -1 ^(_UINT32(1) << 31);
		}
		return *this;
	}
	else
	{
		temp = (_INT64(value) << (F+1)) / other.value;

		// Round half to even

		value = _INT32(temp >> 1);
		
		return *this;
	}
}

template<_UINT32 F>
template<_UINT32 T>
inline FixedPoint<F>& FixedPoint<F>::operator /= (const FixedPoint<T> &other)
{
	_INT64 temp;
	_INT64 adjust;
	
	if (other.Value() == 0)
	{
		// Saturate infinities
		if ( value < 0)
		{
			value = _UINT32(1) << 31;
		}
		else
		{
			value = -1 ^(_UINT32(1) << 31);
		}
		return *this;
	}
	else
	{
		temp = (_INT64(value) << (T+1)) / other.Value();

		// Round half to even

		value = _INT32(temp >> 1);
		
		return *this;
	}
}

template<_UINT32 F>
inline FixedPoint<F>& FixedPoint<F>::operator /= (const _INT32 a)
{
	_INT64 temp;
	_INT64 adjust;
	
	if (a == 0)
	{
		if ( value < 0)
		{
			value = _UINT32(1) << 31;
		}
		else
		{
			value = -1 ^(_UINT32(1) << 31);
		}
		return *this;
	}
	else
	{
		temp = (_INT64(value) << 1) / a;

		// Round half to even

		value = _INT32(temp >> 1);
		
		return *this;
	}
}

template<_UINT32 F>
inline const FixedPoint<F> FixedPoint<F>::operator / (const FixedPoint<F> &other) const
{
	FixedPoint temp;
	
	temp = *this;
	return (temp /= other);
}

template<_UINT32 F>
template<_UINT32 T>
inline const FixedPoint<F> FixedPoint<F>::operator / (const FixedPoint<T> &other) const
{
	FixedPoint<F> temp;
	temp = *this;
	return (temp /= other);
}

template<_UINT32 F>
inline const FixedPoint<F> FixedPoint<F>::operator / (const _INT32 a) const
{
	FixedPoint temp;
	temp = *this;
	return (temp /= a);
}

template<_UINT32 F>
inline const FixedPoint<F> FixedPoint<F>::operator / (const _FLOAT_SINGLE a) const
{
	_INT32 divisor;

	divisor = ReadFloat(a);
	return (*this / FixedPoint(divisor));
}

template<_UINT32 F>
inline FixedPoint<F>& FixedPoint<F>::operator /= (const _FLOAT_SINGLE a)
{
	_INT32 divisor;

	divisor = ReadFloat(a);

	*this /= FixedPoint(divisor);

	return *this;
}

template<_UINT32 F>
inline const FixedPoint<F> FixedPoint<F>::operator / (const _FLOAT_DOUBLE a) const
{
	_INT32 divisor;

	divisor = ReadDouble(a);
	return (*this / FixedPoint(divisor));
}

template<_UINT32 F>
inline FixedPoint<F>& FixedPoint<F>::operator /= (const _FLOAT_DOUBLE a)
{
	_INT32 divisor;

	divisor = ReadDouble(a);

	*this /= FixedPoint(divisor);

	return *this;
}

//********************************
// Compare ==

template<_UINT32 F>
inline const bool FixedPoint<F>::operator == (const FixedPoint &a) const
{
	return (value == a.value);
}

template<_UINT32 F>
template<_UINT32 T>
inline const bool FixedPoint<F>::operator == (const FixedPoint<T> &a) const
{
	_INT32 temp;

	if (F > T)
	{
		temp = a.Value() << (F-T);
	}
	else
	{
		temp = a.Value() >> (T-F);
	}

	return (value == temp);
}

template<_UINT32 F>
inline const bool FixedPoint<F>::operator == (const _INT32 a) const
{
	return (value == (a << F));
}

template<_UINT32 F>
inline const bool FixedPoint<F>::operator == (const _FLOAT_SINGLE a) const
{
	return (value == ReadFloat(a));
}

template<_UINT32 F>
inline const bool FixedPoint<F>::operator == (const _FLOAT_DOUBLE a) const
{
	return (value == ReadDouble(a));
}

//***********************************
// Compare !=

template<_UINT32 F>
inline const bool FixedPoint<F>::operator != (const FixedPoint &a) const
{
	return !(value == a.value);
}

template<_UINT32 F>
template<_UINT32 T>
inline const bool FixedPoint<F>::operator != (const FixedPoint<T> &a) const
{
	_INT32 temp;

	if (F > T)
	{
		temp = a.Value() << (F-T);
	}
	else
	{
		temp = a.Value() >> (T-F);
	}

	return !(value == temp);
}

template<_UINT32 F>
inline const bool FixedPoint<F>::operator != (const _INT32 a) const
{
	return !(value == (a << F));
}

template<_UINT32 F>
inline const bool FixedPoint<F>::operator != (const _FLOAT_SINGLE a) const
{
	return !(value == ReadFloat(a));
}

template<_UINT32 F>
inline const bool FixedPoint<F>::operator != (const _FLOAT_DOUBLE a) const
{
	return (value != ReadDouble(a));
}

//*******************************
// Compare >

template<_UINT32 F>
inline const bool FixedPoint<F>::operator > (const FixedPoint &a) const
{
	return (value > a.value);
}

template<_UINT32 F>
template<_UINT32 T>
inline const bool FixedPoint<F>::operator > (const FixedPoint<T> &a) const
{
	_INT32 temp;

	if (F > T)
	{
		temp = a.Value() << (F-T);
	}
	else
	{
		temp = a.Value() >> (T-F);
	}

	return (value > temp);
}

template<_UINT32 F>
inline const bool FixedPoint<F>::operator > (const _INT32 a) const
{
	return (value > (a << F));
}

template<_UINT32 F>
inline const bool FixedPoint<F>::operator > (const _FLOAT_SINGLE a) const
{
	return (value > ReadFloat(a));
}

template<_UINT32 F>
inline const bool FixedPoint<F>::operator > (const _FLOAT_DOUBLE a) const
{
	return (value > ReadDouble(a));
}

//*******************************
// Compare >=

template<_UINT32 F>
inline const bool FixedPoint<F>::operator >= (const FixedPoint &a) const
{
	return (value >= a.value);
}

template<_UINT32 F>
template<_UINT32 T>
inline const bool FixedPoint<F>::operator >= (const FixedPoint<T> &a) const
{
	_INT32 temp;

	if (F > T)
	{
		temp = a.Value() << (F-T);
	}
	else
	{
		temp = a.Value() >> (T-F);
	}

	return (value >= temp);
}

template<_UINT32 F>
inline const bool FixedPoint<F>::operator >= (const _INT32 a) const
{
	return (value >= (a << F));
}

template<_UINT32 F>
inline const bool FixedPoint<F>::operator >= (const _FLOAT_SINGLE a) const
{
	return (value >= ReadFloat(a));
}

template<_UINT32 F>
inline const bool FixedPoint<F>::operator >= (const _FLOAT_DOUBLE a) const
{
	return (value >= ReadDouble(a));
}

//*******************************
// Compare <

template<_UINT32 F>
inline const bool FixedPoint<F>::operator < (const FixedPoint &a) const
{
	return (value < a.value);
}

template<_UINT32 F>
template<_UINT32 T>
inline const bool FixedPoint<F>::operator < (const FixedPoint<T> &a) const
{
	_INT32 temp;

	if (F > T)
	{
		temp = a.Value() << (F-T);
	}
	else
	{
		temp = a.Value() >> (T-F);
	}

	return (value < temp);
}

template<_UINT32 F>
inline const bool FixedPoint<F>::operator < (const _INT32 a) const
{
	return (value < (a << F));
}

template<_UINT32 F>
inline const bool FixedPoint<F>::operator < (const _FLOAT_SINGLE a) const
{
	return (value < ReadFloat(a));
}

template<_UINT32 F>
inline const bool FixedPoint<F>::operator < (const _FLOAT_DOUBLE a) const
{
	return (value < ReadDouble(a));
}

//*******************************
// Compare <=

template<_UINT32 F>
inline const bool FixedPoint<F>::operator <= (const FixedPoint &a) const
{
	return (value <= a.value);
}

template<_UINT32 F>
template<_UINT32 T>
inline const bool FixedPoint<F>::operator <= (const FixedPoint<T> &a) const
{
	_INT32 temp;

	if (F > T)
	{
		temp = a.Value() << (F-T);
	}
	else
	{
		temp = a.Value() >> (T-F);
	}

	return (value <= temp);
}

template<_UINT32 F>
inline const bool FixedPoint<F>::operator <= (const _INT32 a) const
{
	return (value <= (a << F));
}

template<_UINT32 F>
inline const bool FixedPoint<F>::operator <= (const _FLOAT_SINGLE a) const
{
	return (value <= ReadFloat(a));
}

template<_UINT32 F>
inline const bool FixedPoint<F>::operator <= (const _FLOAT_DOUBLE a) const
{
	return (value <= ReadDouble(a));
}


//************************************************************************
// C math library method overloads

template<_UINT32 F>
inline const FixedPoint<F> fmod(const FixedPoint<F> &numerator, const FixedPoint<F> &denominator)
{
	FixedPoint<F> div;
	FixedPoint<F> temp;
	_INT32 d,frac;

	div = numerator / denominator;

	d = div;
	frac = div & ((1 << F)-1);
	if (d < 0 && frac) d++; // Truncate towards zero

	div = d;
	div = div*denominator;

	temp = numerator-div;
	return temp;
}

template <_UINT32 F>
inline const FixedPoint<F> ceil(const FixedPoint<F> &other)
{
	_INT32 temp;
	const _INT32 mod=(1 << F)-1;
	
	temp = other.Value();
	return FixedPoint<F>((temp+mod) & (~mod));
	
}

template <_UINT32 F>
inline const FixedPoint<F> floor(const FixedPoint<F> &other)
{
	_INT32 temp;
	const _INT32 mod=(1 << F)-1;
	const _UINT32 fracNull = -1 ^ mod;

	temp = other.Value();

	return FixedPoint<F>(temp & (fracNull));
}

template <_UINT32 F>
inline const FixedPoint<F> modf(FixedPoint<F> x,FixedPoint<F> *y)
{
	const _INT32 fracSign = (1 << 31) + (1 << F) - 1;
	const _INT32 intSign = -1 ^ ((1 << F) -1);

	if (x.Value() < 0)
	{
		_INT32 temp;
		temp = -x.Value();
		*y = FixedPoint<F>(-_INT32(temp & intSign));
		return FixedPoint<F>(-(temp & fracSign));
	}
	else
	{
		*y = FixedPoint<F>(_INT32(x.Value() & intSign));
		return FixedPoint<F>(x.Value() & fracSign);
	}
}

/* const FixedPoint<F> sqrt(const FixedPoint<F> &other)
 *
 * Uses a per-bit algorithm to compute the square root
 * of a positive fixed point number. The result is
 * undefined if source is negative.
 */
template<_UINT32 F>
inline const FixedPoint<F> sqrt(const FixedPoint<F> &other)
{
	_UINT64 temp;
	_UINT64 result;
	_UINT64 one;
	_UINT64 bitLevel;
	
	temp = other.Value();
	temp = temp << F;
	
	one = _INT64(1) << 48;
	result = 0;
	
	while (one > temp)
	{
		one = one >> 2;
	};
	
	while (one != 0)
	{
		if (temp >= result+one)
		{
			temp -= result+one;
			result = (result >> 1) + one;
		}			
		else
		{
			result = result >> 1;
		}
		one = one >> 2;
	}
	return FixedPoint<F>(_INT32(result));
}

//****************************************************************************
// Unoptimized experimental methods

#include <stdio.h>

template<_UINT32 F>
inline const FixedPoint<F> FixedPoint<F>::AlgorithmDivide(const FixedPoint &other) const
{
	_INT32 result;
	_INT32 sign;

	_INT64 numerator;
	_INT64 divisor;
	_UINT64 quotient;

	quotient = 0;
	sign = 0;
	
	if (value < 0)
	{
		sign = 1;
		numerator = -value;
	}
	else
	{
		numerator = value;
	}

	if (other.value < 0)
	{
		sign = sign ^ 1;
		divisor = _INT64(-other.value) << 32;
	}
	else
	{
		divisor = _INT64(other.value) << 32;
	}

	
	_INT32 k;

	// Find the most significant bit of divisor
	_UINT64 mask = _UINT64(1) << 63;
	for(k=63;k>=0;k--)
	{
		if (mask & divisor) break;
		mask = mask >> 1;
	}
	_INT32 comparePos = k;
	_INT64 compareMask = _INT64(3) << k;
	_INT64 quotientBits;
	_INT64 compare;

	_INT64 divisorMul[4];

	divisorMul[0] = 0;
	divisorMul[1] = divisor;
	divisorMul[2] = divisor << 1;
	divisorMul[3] = divisor + (divisor << 1);

	FILE *debug;
	
	debug = fopen("debug.txt","w+");

	fprintf(debug,"initial numerator = %lli\n",numerator);
	fprintf(debug,"initial divisor = %lli\n",divisor);

	fprintf(debug,"leading divisor bit pos = %i\n",comparePos);

	// Radix 4 restorative division (ie. 0 < numerator < divisor) at
	// end of each iteration

	k = 0;
	for(k=0;k<=62;k += 2)
	{
		fprintf(debug,"iteration %i:\n",k >> 1);

		numerator = numerator << 2;
		compare = numerator & compareMask;

		fprintf(debug,"numerator = %lli\n",numerator);
		fprintf(debug,"numerator float = %f\n",float(FixedPoint(_INT32(numerator >> 2+k))));

		quotientBits = compare >> comparePos;

		fprintf(debug,"compare float = %f\n",float(FixedPoint(_INT32(compare >> (comparePos-F)))));

		fprintf(debug,"quotient pos = %i\n",62-k);	
		fprintf(debug,"quotient bits (trial / final) = %lli /",quotientBits);

		numerator -= divisorMul[quotientBits];

		// TODO: Convert to non-restorative division to avoid this
		if (numerator < 0)
		{
			quotientBits--;
			numerator += divisor;
		}
		fprintf(debug," %lli\n",quotientBits);

		quotient += quotientBits << (62-k);
		
		result = _INT32(quotient >> F);
		fprintf(debug,"current quotient float = %f\n",float(FixedPoint(result)));
	}

	/*
	// Round half to even
	_INT64 adjust;
	adjust = (quotient & (2 << (F-1))) >> 1;
	quotient += adjust;
	*/

	result = _INT32(quotient >> F);
	if (sign)
	{
		result = -result;
	}

	fclose(debug);

	return FixedPoint(result);
}

static const _INT32 bitMirror[16] = {0 , 8 , 4 , 12 , 2 , 10 , 6 , 14 , 1 , 9 , 5 , 13 , 3 , 11 , 7 , 15};

#include <stdio.h>

template<_UINT32 F>
inline const FixedPoint<F> FixedPoint<F>::FastDiv(const FixedPoint &other) const
{
	_INT32 result;
	_INT32 x;
	_INT32 k;
	_INT64 mul;

	_INT32 field;

	_INT32 min,max;

	result = 0;
	x = other.value;

	// Use bit mirroring about bit F as initial guess

	FILE *debug;

	debug = fopen("debug.txt","w");

	if ( x >= 1)
	{
		field = x & (15 << (F+1));
		field = field >> (F+1);

		result += bitMirror[field] << (F-4);

		field = x & (15 << (F+5));
		field = field >> (F+5);

		result += bitMirror[field] << (F-8);		

		field = x & (15 << (F+9));
		field = field >> (F+9);

		result += bitMirror[field] << (F-12);		

		field = x & (15 << (F+13));
		field = field >> (F+13);

		result += bitMirror[field] << (F-16);		
	}

	// Shift right by (most significant bit pos - least significant bit pos over F) + 1
	min = F+1;
	for(k=F+1;k<32;k++)
	{
		if (x & (1 << k))
		{
			min = k;
			break;
		}
	}

	max = F+1;
	for(k=31;k>F;k--)
	{
		if (x & (_UINT32(1) << k))
		{
			max = k;
			break;
		}
	}

	result = result >> (max-min+1);

	fprintf(debug,"x            = ");
	BinaryPrint(*(_UINT32*)&x,debug);
	fprintf(debug,"\n");

	fprintf(debug,"most significant bit = %i , least = %i\n",max,min);

	fprintf(debug,"mirror guess = ");
	BinaryPrint(*(_UINT32*)&result,debug);
	fprintf(debug,"\n");

	float z;

	z = 1 / float(other);

	FixedPoint convert;
	
	convert = z;

	fprintf(debug,"exact 1/x = %f\n",z);
	fprintf(debug,"exact 1/x (b)= ");
	BinaryPrint(convert.Value(),debug);
	fprintf(debug,"\n");

	z = float(FixedPoint(result));
	fprintf(debug,"mirror guess (float) = %f\n",z);

	// First iteration of Newton's method
	
	mul = (_INT64(x)*result) >> F;

	mul = (2 << F) - mul;

	mul = (mul*result) >> F;

	result = _INT32(mul);

	z = float(FixedPoint(result));
	fprintf(debug,"newton 1 = %f\n",z);

	// Second iteration of Newton's method

	mul = (_INT64(x)*result) >> F;

	mul = (2 << F) - mul;

	mul = (mul*result) >> F;

	result = _INT32(mul);

	z = float(FixedPoint(result));
	fprintf(debug,"newton 2 = %f\n",z);

	mul = (_INT64(x)*result) >> F;

	mul = (2 << F) - mul;

	mul = (mul*result) >> F;

	result = _INT32(mul);

	z = float(FixedPoint(result));
	fprintf(debug,"newton 3 = %f\n",z);

	mul = (_INT64(x)*result) >> F;

	mul = (2 << F) - mul;

	mul = (mul*result) >> F;

	result = _INT32(mul);

	z = float(FixedPoint(result));
	fprintf(debug,"newton 4 = %f\n",z);

	fclose(debug);

	return FixedPoint(result);
}

template<unsigned int F>
inline FixedPoint<F> InvSqrt(FixedPoint<F> a)
{
	int k;
	FixedPoint<F> alpha,beta,gamma;
	FixedPoint<F> x,old,t;
	FixedPoint<F> oneHalf,half;
	FixedPoint<F> square,temp;

	oneHalf = 1.5;
	half = 0.5;			

//	printf("1.0/sqrt(%.16lf)\n",double(a));

	if (a.Value() < (1 << F)+1)
	{
		// Use two-term partial fraction approximation
		// to calculate initial guess
		// x = alpha + beta/(x+gamma)	

		alpha = 0.89116318569477548;
		beta = 0.014794971552932100;
		gamma = 5.3643790280784702e-05;

		/*
		printf("alpha = %.16lf\n",double(alpha));
		printf("beta = %.16lf\n",double(beta));
		printf("gamma = %.16lf\n",double(gamma));
		*/

		x = a+gamma;
		x = beta / x;
		x = x + alpha;
		
		printf("initial guess = %.16lf\n",double(x));

		if (F < 16)
		{
			FixedPoint<F> product;

			/*
			k = 0;
			do
			{
				printf("iteration %i:\n",k+1);
				product = x;
				product = product * x;
				printf("square = %.16lf , exact = %.16lf\n",double(product),double(x)*double(x));
				square = a * product;;
				square = square * half;
				printf("square*a = %.16lf , exact = %.16lf\n",double(square),double(product)*double(a)*0.5);
				temp = oneHalf - square;
				coef = x;
				old = x;
				x = x * temp;
				printf("x*temp = %.16lf , exact = %.16lf\n",double(x),double(coef)*double(temp));
				t = x-old;
				t = fabs(t);
				printf("eps = %.16lf\n",double(t));
				k++;
			} while (t.Value() > 1);
			printf("iterations: %u\n",k);
			*/
		}
		else
		{			
			
			FixedPoint<30-F> product;

			k = 0;
			do
			{
				printf("iteration %i:\n",k+1);
				printf("a = %.16lf\n",double(a));
				//product = x;
				//product = product * x; // Minimize precision loss
				product.ReducedMult(x,x);
				printf("square = %.16lf , exact = %.16lf\n",double(product),double(x)*double(x));
				square = a * product;
				square = square * half;
				printf("square*a = %.16lf , exact = %.16lf\n",double(square),double(product)*double(a)*0.5);
				temp = oneHalf - square;
				old = x;
				x = x * temp;
				printf("x*temp = %.16lf , exact = %.16lf\n",double(x),double(old)*double(temp));
				t = x-old;
				t = fabs(t);
				printf("eps = %.16lf\n",double(t));
				printf("cap = %.16lf\n",double(1.0 / (1 << (F-2*F-2+32))));
				k++;
				if (k > 16)
				{
					printf("safety abort!\n");
					printf("a = %.16lf\n",double(a));
					printf("eps = %.16lf\n",double(t));
					break;
				}
			} while (t.Value() > (1 << (2*F-30)));
			printf("iterations: %u\n",k);

			return x;
		}	
	}
	else
	{
		FixedPoint<F> product;
	}
}

inline void BinaryPrint(_UINT32 value,FILE *output)
{
	int k;
	unsigned int bit;
	unsigned int mask;
	unsigned char shift;
	
	mask = 1 << 31;
	shift = 31;
	
	for(k=0;k<8;k++)
	{
		bit = (value & mask) >> shift;
		fprintf(output,"%i",bit);
		mask = mask >> 1;
		shift--;
	}
	fprintf(output," ");
	for(k=0;k<8;k++)
	{
		bit = (value & mask) >> shift;
		fprintf(output,"%i",bit);
		mask = mask >> 1;
		shift--;
	}
	fprintf(output," ");
	for(k=0;k<8;k++)
	{
		bit = (value & mask) >> shift;
		fprintf(output,"%i",bit);
		mask = mask >> 1;
		shift--;
	}
	fprintf(output," ");
	for(k=0;k<8;k++)
	{
		bit = (value & mask) >> shift;
		fprintf(output,"%i",bit);
		mask = mask >> 1;
		shift--;
	}
}

}

#endif