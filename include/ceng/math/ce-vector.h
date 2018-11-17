/*****************************************************************************
*
* ce-vector.h
*
* By Jari Korkala 9/2011
*
*****************************************************************************/

#ifndef _CONCEPT2_VECTOR_H
#define _CONCEPT2_VECTOR_H

#include <sstream>

#include "../datatypes/basic-types.h"
#include "../datatypes/boolean.h"

namespace Ceng
{

#define XDIR 0
#define YDIR 1
#define ZDIR 2
#define WDIR 3

//********************************************************************
// Two component vector template

template<class T>
class MathVector2
{
public:
	T x;
	T y;

	MathVector2();
	~MathVector2();

	MathVector2(const MathVector2 &other);
	MathVector2(const T nx,const T ny);

	MathVector2& operator = (const MathVector2 &other);

	// Arithmetic
	MathVector2& operator += (const MathVector2 &other);
	const MathVector2 operator + (const MathVector2 &other) const;

	MathVector2& operator -= (const MathVector2 &other);
	const MathVector2 operator - (const MathVector2 &other) const;

	MathVector2& operator *= (const MathVector2 &other);
	const MathVector2 operator * (const MathVector2 &other) const;

	MathVector2& operator *= (const T &scalar);
	const MathVector2 operator * (const T &scalar) const;

	MathVector2& operator /= (const MathVector2 &other);
	const MathVector2 operator / (const MathVector2 &other) const;

	MathVector2& operator /= (const T &scalar);
	const MathVector2 operator / (const T &scalar) const;

	// Bitwise logic
	MathVector2& operator &= (const MathVector2 &other);
	MathVector2& operator |= (const MathVector2 &other);
	MathVector2& operator ^= (const MathVector2 &other);

	const MathVector2 operator & (const MathVector2 &other) const;
	const MathVector2 operator | (const MathVector2 &other) const;
	const MathVector2 operator ^ (const MathVector2 &other) const;

	// Common vector operations
	void Normalize();
	const FLOAT32 Length() const;
	const FLOAT32 Square() const;

	const FLOAT32 DotProduct(const MathVector2 &other) const;

	// Other
	const UINT32 SignMask();
};

//********************************************************************
// Four component vector template

template<class T>
class MathVector4
{
public:
	T x;
	T y;
	T z;
	T w;
public:
	MathVector4();
	~MathVector4();

	MathVector4(const MathVector4 &other);

	MathVector4(const T nx,const T ny,const T nz);
	MathVector4(const T nx,const T ny,const T nz,const T nw);
	
	MathVector4& operator = (const MathVector4 &other);

	// Arithmetic
	MathVector4& operator += (const MathVector4 &other);
	const MathVector4 operator + (const MathVector4 &other) const;

	MathVector4& operator -= (const MathVector4 &other);
	const MathVector4 operator - (const MathVector4 &other) const;

	MathVector4& operator *= (const MathVector4 &other);
	const MathVector4 operator * (const MathVector4 &other) const;

	MathVector4& operator *= (const T &scalar);
	const MathVector4 operator * (const T &scalar) const;

	MathVector4& operator /= (const MathVector4 &other);
	const MathVector4 operator / (const MathVector4 &other) const;

	MathVector4& operator /= (const T &scalar);
	const MathVector4 operator / (const T &scalar) const;

	// Bitwise logic
	MathVector4& operator &= (const MathVector4 &other);
	MathVector4& operator |= (const MathVector4 &other);
	MathVector4& operator ^= (const MathVector4 &other);

	const MathVector4 operator & (const MathVector4 &other) const;
	const MathVector4 operator | (const MathVector4 &other) const;
	const MathVector4 operator ^ (const MathVector4 &other) const;

	// Unary -
	const MathVector4 operator -() const;

	// Common vector operations
	void Normalize();
	void HomogenNormalize();
	
	const FLOAT32 Length() const;
	const FLOAT32 HomogenLength() const;

	const FLOAT32 Square() const;
	const FLOAT32 HomogenSquare() const;
	
	const FLOAT32 DotProduct(const MathVector4 &other) const;
	const FLOAT32 HomogenDotProduct(const MathVector4 &other) const;

	// Cross product = this x other
	const MathVector4 CrossProduct(const MathVector4 &other) const;

	// Other

	const UINT32 SignMask();
	void Homogenize();
	void EuclidianRestore();

};

//**************************************************************
// MathVector2 methods

template<class T>
inline MathVector2<T>::MathVector2()
{
}

template<class T>
inline MathVector2<T>::~MathVector2()
{
}

template<class T>
inline MathVector2<T>::MathVector2(const MathVector2 &other)
{
	x = other.x;
	y = other.y;
}

template<class T>
inline MathVector2<T>::MathVector2(const T nx,const T ny)
{
	x = nx;
	y = ny;
}

template<class T>
inline const UINT32 MathVector2<T>::SignMask()
{
	UINT32 temp = 0;

	if (x < T(-0.0f)) temp += 1;
	if (y < T(-0.0f)) temp += 2;

	return temp;
}

template<class T>
inline MathVector2<T>& MathVector2<T>::operator =(const MathVector2 &other)
{
	x = other.x;
	y = other.y;

	return *this;
}

template<class T>
inline MathVector2<T>& MathVector2<T>::operator += (const MathVector2 &other)
{
	x += other.x;
	y += other.y;

	return *this;
}

template<class T>
inline MathVector2<T>& MathVector2<T>::operator -= (const MathVector2 &other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}

template<class T>
inline MathVector2<T>& MathVector2<T>::operator *= (const MathVector2 &other)
{
	x *= other.x;
	y *= other.y;

	return *this;
}

template<class T>
inline MathVector2<T>& MathVector2<T>::operator *= (const T &scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

template<class T>
inline MathVector2<T>& MathVector2<T>::operator /= (const MathVector2 &other)
{
	x /= other.x;
	y /= other.y;

	return *this;
}

template<class T>
inline MathVector2<T>& MathVector2<T>::operator /= (const T &scalar)
{
	x /= scalar;
	y /= scalar;

	return *this;
}

template<class T>
inline MathVector2<T>& MathVector2<T>::operator &= (const MathVector2 &other)
{
	// Force the compiler to interpret data as 
	// an unsigned integer of same size, then operate bitwise logic
	if (sizeof(T) == 4)
	{
		UINT32 temp;

		temp = (*(UINT32*)&x) & (*(UINT32*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT32*)&y) & (*(UINT32*)&other.y);
		y = *(T*)&temp;
	}
	else if (sizeof(T) == 8)
	{
		UINT64 temp;

		temp = (*(UINT64*)&x) & (*(UINT64*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT64*)&y) & (*(UINT64*)&other.y);
		y = *(T*)&temp;
	}
	else if (sizeof(T) == 2)
	{
		UINT16 temp;

		temp = (*(UINT16*)&x) & (*(UINT16*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT16*)&y) & (*(UINT16*)&other.y);
		y = *(T*)&temp;
	}
	else if (sizeof(T) == 1)
	{
		UINT8 temp;

		temp = (*(UINT8*)&x) & (*(UINT8*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT8*)&y) & (*(UINT8*)&other.y);
		y = *(T*)&temp;
	}

	return *this;
}

template<class T>
inline MathVector2<T>& MathVector2<T>::operator |= (const MathVector2 &other)
{
// Force the compiler to interpret data as 
	// an unsigned integer of same size, then operate bitwise logic
	if (sizeof(T) == 4)
	{
		UINT32 temp;

		temp = (*(UINT32*)&x) | (*(UINT32*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT32*)&y) | (*(UINT32*)&other.y);
		y = *(T*)&temp;
	}
	else if (sizeof(T) == 8)
	{
		UINT64 temp;

		temp = (*(UINT64*)&x) | (*(UINT64*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT64*)&y) | (*(UINT64*)&other.y);
		y = *(T*)&temp;
	}
	else if (sizeof(T) == 2)
	{
		UINT16 temp;

		temp = (*(UINT16*)&x) | (*(UINT16*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT16*)&y) | (*(UINT16*)&other.y);
		y = *(T*)&temp;
	}
	else if (sizeof(T) == 1)
	{
		UINT8 temp;

		temp = (*(UINT8*)&x) | (*(UINT8*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT8*)&y) | (*(UINT8*)&other.y);
		y = *(T*)&temp;
	}

	return *this;
}

template<class T>
inline MathVector2<T>& MathVector2<T>::operator ^= (const MathVector2 &other)
{
// Force the compiler to interpret data as 
	// an unsigned integer of same size, then operate bitwise logic
	if (sizeof(T) == 4)
	{
		UINT32 temp;

		temp = (*(UINT32*)&x) ^ (*(UINT32*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT32*)&y) ^ (*(UINT32*)&other.y);
		y = *(T*)&temp;
	}
	else if (sizeof(T) == 8)
	{
		UINT64 temp;

		temp = (*(UINT64*)&x) ^ (*(UINT64*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT64*)&y) ^ (*(UINT64*)&other.y);
		y = *(T*)&temp;
	}
	else if (sizeof(T) == 2)
	{
		UINT16 temp;

		temp = (*(UINT16*)&x) ^ (*(UINT16*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT16*)&y) ^ (*(UINT16*)&other.y);
		y = *(T*)&temp;
	}
	else if (sizeof(T) == 1)
	{
		UINT8 temp;

		temp = (*(UINT8*)&x) ^ (*(UINT8*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT8*)&y) ^ (*(UINT8*)&other.y);
		y = *(T*)&temp;
	}

	return *this;
}

template<class T>
inline const MathVector2<T> MathVector2<T>::
				operator & (const MathVector2 &other) const
{
	MathVector2 temp = *this;

	temp &= other;
	return temp;
}

template<class T>
inline const MathVector2<T> MathVector2<T>::
				operator | (const MathVector2 &other) const
{
	MathVector2 temp = *this;

	temp |= other;
	return temp;
}

template<class T>
inline const MathVector2<T> MathVector2<T>::
				operator ^ (const MathVector2 &other) const
{
	MathVector4 temp = *this;

	temp ^= other;
	return temp;
}

template<class T>
inline const MathVector2<T> MathVector2<T>::
				operator + (const MathVector2 &other) const
{
	MathVector2 temp = *this;
	temp += other;
	return temp;
}

template<class T>
inline const MathVector2<T> MathVector2<T>::
				operator - (const MathVector2 &other) const
{
	MathVector2 temp = *this;
	temp -= other;
	return temp;
}

template<class T>
inline const MathVector2<T> MathVector2<T>::
				operator * (const MathVector2 &other) const
{
	MathVector2 temp = *this;
	temp *= other;
	return temp;
}

template<class T>
inline const MathVector2<T> MathVector2<T>::
				operator * (const T &scalar) const
{
	MathVector2 temp = *this;
	temp *= scalar;
	return temp;
}

template<class T>
inline const MathVector2<T> MathVector2<T>::
				operator / (const MathVector2 &other) const
{
	MathVector2 temp = *this;
	temp /= other;
	return temp;
}

template<class T>
inline const MathVector2<T> MathVector2<T>::
				operator / (const T &scalar) const
{
	MathVector2 temp = *this;
	temp /= scalar;
	return temp;
}

template<class T>
inline const FLOAT32 MathVector2<T>::Length() const
{
	return sqrt(x*x+y*y);
}

template<class T>
inline const FLOAT32 MathVector2<T>::Square() const
{
	return x*x+y*y;
}

template<class T>
inline void MathVector2<T>::Normalize()
{
	FLOAT32 div;
	div = FLOAT32(1.0) / Length();
	
	x *= div;
	y *= div;
}

template<class T>
inline const FLOAT32 MathVector2<T>::
			DotProduct(const MathVector2 &other) const
{
	return x*other.x+y*other.y;
}

//**************************************************************
// MathVector4 methods

template<class T>
inline MathVector4<T>::MathVector4()
{
}

template<class T>
inline MathVector4<T>::~MathVector4()
{
}

template<class T>
inline MathVector4<T>::MathVector4(const MathVector4 &other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}

template<class T>
inline MathVector4<T>::MathVector4(T nx, T ny, T nz)
{
	x = nx;
	y = ny;
	z = nz;
	w = 0;
}

template<class T>
inline MathVector4<T>::MathVector4(T nx, T ny, T nz, T nw)
{
	x = nx;
	y = ny;
	z = nz;
	w = nw;
}

template<class T>
inline void MathVector4<T>::Homogenize()
{
	w = 1.0;
}

template<class T>
inline void MathVector4<T>::EuclidianRestore()
{
	FLOAT32 temp;

	temp = T(1.0f) / w;

	x *= temp;
	y *= temp;
	z *= temp;
	w = temp;
}

template<class T>
inline const UINT32 MathVector4<T>::SignMask()
{
	UINT32 temp = 0;

	if (x < T(0.0f)) temp += 1;
	if (y < T(0.0f)) temp += 2;
	if (z < T(0.0f)) temp += 4;
	if (w < T(0.0f)) temp += 8;

	/*
	if (x < T(-0.0f)) temp += 1;
	if (y < T(-0.0f)) temp += 2;
	if (z < T(-0.0f)) temp += 4;
	if (w < T(-0.0f)) temp += 8;
	*/

	return temp;
}

template<class T>
inline const MathVector4<T> MathVector4<T>::operator -() const
{
	return MathVector4<T>(-x, -y, -z, -w);
}


template<class T>
inline MathVector4<T>& MathVector4<T>::operator =(const MathVector4 &other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;

	return *this;
}

template<class T>
inline MathVector4<T>& MathVector4<T>::operator += (const MathVector4 &other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;

	return *this;
}

template<class T>
inline MathVector4<T>& MathVector4<T>::operator -= (const MathVector4 &other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;

	return *this;
}

template<class T>
inline MathVector4<T>& MathVector4<T>::operator *= (const MathVector4 &other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	w *= other.w;

	return *this;
}

template<class T>
inline MathVector4<T>& MathVector4<T>::operator *= (const T &scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;

	return *this;
}

template<class T>
inline MathVector4<T>& MathVector4<T>::operator /= (const MathVector4 &other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	w /= other.w;

	return *this;
}

template<class T>
inline MathVector4<T>& MathVector4<T>::operator /= (const T &scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;

	return *this;
}

//****************************************************
// Vector4 bitwise logic

template<class T>
inline MathVector4<T>& MathVector4<T>::operator &= (const MathVector4 &other)
{
	// Force the compiler to interpret data as 
	// an unsigned integer of same size, then operate bitwise logic
	if (sizeof(T) == 4)
	{
		UINT32 temp;

		temp = (*(UINT32*)&x) & (*(UINT32*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT32*)&y) & (*(UINT32*)&other.y);
		y = *(T*)&temp;

		temp = (*(UINT32*)&z) & (*(UINT32*)&other.z);
		z = *(T*)&temp;

		temp = (*(UINT32*)&w) & (*(UINT32*)&other.w);
		w = *(T*)&temp;
	}
	else if (sizeof(T) == 8)
	{
		UINT64 temp;

		temp = (*(UINT64*)&x) & (*(UINT64*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT64*)&y) & (*(UINT64*)&other.y);
		y = *(T*)&temp;

		temp = (*(UINT64*)&z) & (*(UINT64*)&other.z);
		z = *(T*)&temp;

		temp = (*(UINT64*)&w) & (*(UINT64*)&other.w);
		w = *(T*)&temp;
	}
	else if (sizeof(T) == 2)
	{
		UINT16 temp;

		temp = (*(UINT16*)&x) & (*(UINT16*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT16*)&y) & (*(UINT16*)&other.y);
		y = *(T*)&temp;

		temp = (*(UINT16*)&z) & (*(UINT16*)&other.z);
		z = *(T*)&temp;

		temp = (*(UINT16*)&w) & (*(UINT16*)&other.w);
		w = *(T*)&temp;
	}
	else if (sizeof(T) == 1)
	{
		UINT8 temp;

		temp = (*(UINT8*)&x) & (*(UINT8*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT8*)&y) & (*(UINT8*)&other.y);
		y = *(T*)&temp;

		temp = (*(UINT8*)&z) & (*(UINT8*)&other.z);
		z = *(T*)&temp;

		temp = (*(UINT8*)&w) & (*(UINT8*)&other.w);
		w = *(T*)&temp;
	}

	return *this;
}

template<class T>
inline MathVector4<T>& MathVector4<T>::operator |= (const MathVector4 &other)
{
// Force the compiler to interpret data as 
	// an unsigned integer of same size, then operate bitwise logic
	if (sizeof(T) == 4)
	{
		UINT32 temp;

		temp = (*(UINT32*)&x) | (*(UINT32*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT32*)&y) | (*(UINT32*)&other.y);
		y = *(T*)&temp;

		temp = (*(UINT32*)&z) | (*(UINT32*)&other.z);
		z = *(T*)&temp;

		temp = (*(UINT32*)&w) | (*(UINT32*)&other.w);
		w = *(T*)&temp;
	}
	else if (sizeof(T) == 8)
	{
		UINT64 temp;

		temp = (*(UINT64*)&x) | (*(UINT64*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT64*)&y) | (*(UINT64*)&other.y);
		y = *(T*)&temp;

		temp = (*(UINT64*)&z) | (*(UINT64*)&other.z);
		z = *(T*)&temp;

		temp = (*(UINT64*)&w) | (*(UINT64*)&other.w);
		w = *(T*)&temp;
	}
	else if (sizeof(T) == 2)
	{
		UINT16 temp;

		temp = (*(UINT16*)&x) | (*(UINT16*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT16*)&y) | (*(UINT16*)&other.y);
		y = *(T*)&temp;

		temp = (*(UINT16*)&z) | (*(UINT16*)&other.z);
		z = *(T*)&temp;

		temp = (*(UINT16*)&w) | (*(UINT16*)&other.w);
		w = *(T*)&temp;
	}
	else if (sizeof(T) == 1)
	{
		UINT8 temp;

		temp = (*(UINT8*)&x) | (*(UINT8*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT8*)&y) | (*(UINT8*)&other.y);
		y = *(T*)&temp;

		temp = (*(UINT8*)&z) | (*(UINT8*)&other.z);
		z = *(T*)&temp;

		temp = (*(UINT8*)&w) | (*(UINT8*)&other.w);
		w = *(T*)&temp;
	}

	return *this;
}

template<class T>
inline MathVector4<T>& MathVector4<T>::operator ^= (const MathVector4 &other)
{
// Force the compiler to interpret data as 
	// an unsigned integer of same size, then operate bitwise logic
	if (sizeof(T) == 4)
	{
		UINT32 temp;

		temp = (*(UINT32*)&x) ^ (*(UINT32*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT32*)&y) ^ (*(UINT32*)&other.y);
		y = *(T*)&temp;

		temp = (*(UINT32*)&z) ^ (*(UINT32*)&other.z);
		z = *(T*)&temp;

		temp = (*(UINT32*)&w) ^ (*(UINT32*)&other.w);
		w = *(T*)&temp;
	}
	else if (sizeof(T) == 8)
	{
		UINT64 temp;

		temp = (*(UINT64*)&x) ^ (*(UINT64*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT64*)&y) ^ (*(UINT64*)&other.y);
		y = *(T*)&temp;

		temp = (*(UINT64*)&z) ^ (*(UINT64*)&other.z);
		z = *(T*)&temp;

		temp = (*(UINT64*)&w) ^ (*(UINT64*)&other.w);
		w = *(T*)&temp;
	}
	else if (sizeof(T) == 2)
	{
		UINT16 temp;

		temp = (*(UINT16*)&x) ^ (*(UINT16*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT16*)&y) ^ (*(UINT16*)&other.y);
		y = *(T*)&temp;

		temp = (*(UINT16*)&z) ^ (*(UINT16*)&other.z);
		z = *(T*)&temp;

		temp = (*(UINT16*)&w) ^ (*(UINT16*)&other.w);
		w = *(T*)&temp;
	}
	else if (sizeof(T) == 1)
	{
		UINT8 temp;

		temp = (*(UINT8*)&x) ^ (*(UINT8*)&other.x);
		x = *(T*)&temp;

		temp = (*(UINT8*)&y) ^ (*(UINT8*)&other.y);
		y = *(T*)&temp;

		temp = (*(UINT8*)&z) ^ (*(UINT8*)&other.z);
		z = *(T*)&temp;

		temp = (*(UINT8*)&w) ^ (*(UINT8*)&other.w);
		w = *(T*)&temp;
	}

	return *this;
}

template<class T>
inline const MathVector4<T> MathVector4<T>::
			operator & (const MathVector4 &other) const
{
	MathVector4 temp = MathVector4(*this);

	temp &= other;
	return temp;
}

template<class T>
inline const MathVector4<T> MathVector4<T>::
			operator | (const MathVector4 &other) const
{
	MathVector4 temp = MathVector4(*this);

	temp |= other;
	return temp;
}

template<class T>
inline const MathVector4<T> MathVector4<T>::
			operator ^ (const MathVector4 &other) const
{
	MathVector4 temp = MathVector4(*this);

	temp ^= other;
	return temp;
}

//*************************************************************
// Vector4 two parameter arithmetic

template<class T>
__forceinline const MathVector4<T> MathVector4<T>::
				operator + (const MathVector4 &other) const
{
	MathVector4 temp = MathVector4(*this);
	temp += other;
	return temp;
	
}

template<class T>
inline const MathVector4<T> MathVector4<T>::
			operator - (const MathVector4 &other) const
{
	MathVector4 temp = MathVector4(*this);
	temp -= other;
	return temp;
}

template<class T>
inline const MathVector4<T> MathVector4<T>::
			operator * (const MathVector4 &other) const
{
	MathVector4 temp = MathVector4(*this);
	temp *= other;
	return temp;
}

template<class T>
inline const MathVector4<T> MathVector4<T>::
			operator * (const T &scalar) const
{
	MathVector4 temp = MathVector4(*this);
	temp *= scalar;
	return temp;
}

template<class T>
inline const MathVector4<T> MathVector4<T>::
			operator / (const MathVector4 &other) const
{
	MathVector4 temp = MathVector4(*this);
	temp /= other;
	return temp;
}

template<class T>
inline const MathVector4<T> MathVector4<T>::
			operator / (const T &scalar) const
{
	MathVector4 temp = MathVector4(*this);
	temp /= scalar;
	return temp;
}

//**********************************************************************
// Vector4 common operations

template<class T>
inline const FLOAT32 MathVector4<T>::Length() const
{
	return sqrt(x*x+y*y+z*z);
}

template<class T>
inline const FLOAT32 MathVector4<T>::HomogenLength() const
{
	return sqrt(x*x+y*y+z*z+w*w);
}

template<class T>
inline const FLOAT32 MathVector4<T>::Square() const
{
	return x*x+y*y+z*z;
}

template<class T>
inline const FLOAT32 MathVector4<T>::HomogenSquare() const
{
	return x*x+y*y+z*z+w*w;
}

template<class T>
inline void MathVector4<T>::Normalize()
{
	FLOAT32 div;
	div = FLOAT32(1.0) / Length();
	
	x *= div;
	y *= div;
	z *= div;
	w = 0.0f;
}

template<class T>
inline void MathVector4<T>::HomogenNormalize()
{
	FLOAT32 div;
	div = FLOAT32(1.0) / Length();
	
	x *= div;
	y *= div;
	z *= div;
	w *= div;
}

template<class T>
inline const FLOAT32 MathVector4<T>::
			DotProduct(const MathVector4 &other) const
{
	return x*other.x+y*other.y+z*other.z;
}

template<class T>
inline const FLOAT32 MathVector4<T>::
			HomogenDotProduct(const MathVector4 &other) const
{
	return x*other.x+y*other.y+z*other.z+w*other.w;
}

template<class T>
inline const MathVector4<T> MathVector4<T>::
			CrossProduct(const MathVector4 &other) const
{
	MathVector4 temp;
	temp.x = y*other.z-z*other.y;
	temp.y = z*other.x-x*other.z;
	temp.z = x*other.y-y*other.x;
	temp.w = 0;
	return temp;
}

typedef MathVector2<FLOAT32> VectorF2;
typedef MathVector4<FLOAT32> VectorF4;

typedef MathVector2<FLOAT64> VectorD2;
typedef MathVector4<FLOAT64> VectorD4;

typedef MathVector2<UINT32> VectorU2;
typedef MathVector4<UINT32> VectorU4;

typedef MathVector2<INT32> VectorI2;
typedef MathVector4<INT32> VectorI4;

typedef MathVector2<Ceng::BOOL> VectorB2;
typedef MathVector4<Ceng::BOOL> VectorB4;

// Euclidian (Cartesian) basis vectors
const VectorF4 euclidianBasis4[3] = 
{
	VectorF4(FLOAT32(1.0f),FLOAT32(0.0f),FLOAT32(0.0f)),
	VectorF4(FLOAT32(0.0f),FLOAT32(1.0f),FLOAT32(0.0f)),
	VectorF4(FLOAT32(0.0f),FLOAT32(0.0f),FLOAT32(1.0f))
};

const VectorF2 euclidianBasis2[2] =
{
	VectorF2(FLOAT32(1.0f),FLOAT32(0.0f)),
	VectorF2(FLOAT32(0.0f),FLOAT32(1.0f))
};

}

#endif // Include guard