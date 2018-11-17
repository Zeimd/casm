/*****************************************************************************
*
* ce-quaternion.h
*
* By Jari Korkala 2009-2011
*
* Quaternion class with simple arithmetics and functions required to perform
* rotation of a 3D point around a 3D vector.
*
* Update 10/2011 : Rotation quaternions can be converted to 4x4 matrices.
*                  Row-major form (optimal for matrix*vector) is assumed.
*
*****************************************************************************/

#ifndef _CONCEPT2_QUATERNION_H
#define _CONCEPT2_QUATERNION_H

#include <math.h>

#include "ce-vector.h"
#include "ce-matrix.h"

namespace Ceng
{

class Quaternion
{
protected:
	FLOAT32 w,x,y,z;
	FLOAT32 wMod,wMul2;
public:
	Quaternion();

	Quaternion(const FLOAT32 w0,const FLOAT32 x0,
				const FLOAT32 y0,const FLOAT32 z0);

	Quaternion(const VectorF4 &vector,const FLOAT32 angle);

	Quaternion(const Quaternion &a);

	Quaternion& operator=(const Quaternion &a);

	const Quaternion operator + (const Quaternion &a) const;
	const Quaternion operator - (const Quaternion &a) const;
	const Quaternion operator * (const Quaternion &a) const;
	const Quaternion operator / (const Quaternion &a) const;

	/**
	 * Returns the reciprocal.
	 */
	const Quaternion operator~() const; 

	/**
	 * Returns the complex conjugate.
	 */
	const Quaternion operator!() const;

	/**
	 * Changes the sign of x,y,z
	 */
	void Conjugate();

	/**
	 * Sets w=1 , x=y=z=0
	 */
	void Identity();

	/**
	 * Scales the quaternion by the reciprocal of its current length.
	 *
	 * @return 0 if the quaternion has length=0. Returns 1 otherwise.
	 */
	INT32 Normalize(); 
	
	/**
	 * Convert to reciprocal value.
	 *
	 * @return 0 if the quaternion has length=0. Returns 1 otherwise.
	 */
	INT32 Reciprocal(); 

	FLOAT32 Length();

	/**
	 * Returns the square of Length().
	 */
	FLOAT32 Square();
	
	// Spatial rotation methods

	/**
	 * Create a quaternion that represents rotation around the given vector
	 * and given angle. The rotation appears clockwise if line of sight has
	 * the direction of *vector.
	 */
	void CreateRotation(const VectorF4 &vector,const FLOAT32 angle);

	/**
	 * Creates a rotation from one vector to another.
	 */
	void CreateRotation(const VectorF4 &start,const VectorF4 &end);

	/**
	 * Rotate a group of points with this quaternion.
	 */
	void RotatePoint(const VectorF4 *source,VectorF4 *dest,const INT32 n) const;

	/**
	 * Accumulates the given rotation to the quaternion.
	 */
	void AddRotation(const Quaternion &rotation);

	operator Matrix4() const;
};

//***************************************************************
// Methods

inline Quaternion::Quaternion()
{
	// Identity quaternion
	w = FLOAT32(1.0f);
	x = 0;
	y = 0;
	z = 0;

	// Precalculate quaternion-vector multiplication
	// constants
	wMod = w*w-(x*x)-(y*y)-(z*z);	
	wMul2 = FLOAT32(2.0f)*w;
}

inline Quaternion::Quaternion(const Quaternion &a)
{
	w = a.w;
	x = a.x;
	y = a.y;
	z = a.z;

	wMod = w*w-(x*x)-(y*y)-(z*z);	
	wMul2 = FLOAT32(2.0f)*w;
}

inline Quaternion::Quaternion(const FLOAT32 w0,const FLOAT32 x0,
							  const FLOAT32 y0,const FLOAT32 z0)
{
	w = w0;
	x = x0;
	y = y0;
	z = z0;

	wMod = w*w-(x*x)-(y*y)-(z*z);	
	wMul2 = FLOAT32(2.0f)*w;
}

inline Quaternion::Quaternion(const VectorF4 &vector,const FLOAT32 angle)
{
	FLOAT32 cosv,sinv;
	FLOAT32 half;

	half = FLOAT32(0.5f)*angle;
	cosv = cos(DEGREE_TO_RADIANS*half);
	sinv = sin(DEGREE_TO_RADIANS*half);

	w = cosv;
	x = sinv*vector.x;
	y = sinv*vector.y;
	z = sinv*vector.z;

	wMod = w*w-(x*x)-(y*y)-(z*z);	
	wMul2 = FLOAT32(2.0f)*w;
}

inline Quaternion& Quaternion::operator=(const Quaternion &a)
{
	if (&a == this) return *this;

	w = a.w;
	x = a.x;
	y = a.y;
	z = a.z;

	wMod = w*w-(x*x)-(y*y)-(z*z);	
	wMul2 = FLOAT32(2.0f)*w;
	return *this;
}

inline void Quaternion::Identity()
{
	w = FLOAT32(1.0f);
	x = 0;
	y = 0;
	z = 0;
}

inline void Quaternion::Conjugate()
{
	x = -x;
	y = -y;
	z = -z;
}

inline INT32 Quaternion::Normalize()
{
	FLOAT32 length;
	FLOAT32 divisor;
	
	length = Length();
	if (length == FLOAT32(0.0f)) return 0;
	
	divisor = FLOAT32(1.0f)/length;

	w = w*divisor;
	x = x*divisor;
	y = y*divisor;
	z = z*divisor;

	return 1;
}

inline FLOAT32 Quaternion::Length()
{
	FLOAT32 length;

	length = w*w + x*x + y*y + z*z;
	return sqrt(length);
}

inline FLOAT32 Quaternion::Square()
{
	return (w*w+x*x+y*y+z*z);
}

inline INT32 Quaternion::Reciprocal()
{
	FLOAT32 length;
	FLOAT32 divisor;

	length = w*w+x*x+y*y+z*z;
	if (length == FLOAT32(0.0f)) return 0;

	divisor = FLOAT32(1.0f)/length;

	w = divisor*w;	
	x = -divisor*x;
	y = -divisor*y;
	z = -divisor*z;

	return 1;
}

inline const Quaternion Quaternion::operator+(const Quaternion &a) const
{
	return Quaternion(w+a.w,x+a.x,y+a.y,z+a.z);
}

inline const Quaternion Quaternion::operator-(const Quaternion &a) const
{
	return Quaternion(w-a.w,x-a.x,y-a.y,z-a.z);
}

inline const Quaternion Quaternion::operator*(const Quaternion &a) const
{
	return Quaternion(
		(w*a.w)-(x*a.x)-(y*a.y)-(z*a.z),
		(w*a.x)+(a.w*x)+(y*a.z)-(z*a.y),
		(w*a.y)+(a.w*y)+(z*a.x)-(x*a.z),
		(w*a.z)+(a.w*z)+(x*a.y)-(y*a.x));
}

inline const Quaternion Quaternion::operator/(const Quaternion &a) const
{
	Quaternion temp;
	FLOAT32 divisor;
	FLOAT32 length;

	length = a.w*a.w+a.x*a.x+a.y*a.y+a.z*a.z;
	if (length == FLOAT32(0.0)) return Quaternion();

	divisor = FLOAT32(1.0)/length;

	return Quaternion(
		divisor*(w*a.w+x*a.x+y*a.y+z*a.z),
		divisor*(a.w*x-w*a.x+z*a.y-y*a.z),
		divisor*(a.w*y-w*a.y+x*a.z-z*a.x),
		divisor*(a.w*z-w*a.z+y*a.x-x*a.y));
}

inline void Quaternion::CreateRotation(const VectorF4 &vector,
									   const FLOAT32 angle)
{
	FLOAT32 cosv,sinv;
	FLOAT32 half;

	half = FLOAT32(0.5f)*angle;
	cosv = cos(DEGREE_TO_RADIANS*half);
	sinv = sin(DEGREE_TO_RADIANS*half);

	w = cosv;
	x = sinv*vector.x;
	y = sinv*vector.y;
	z = sinv*vector.z;

	wMod = w*w-(x*x)-(y*y)-(z*z);	
	wMul2 = FLOAT32(2.0f)*w;
}

inline void Quaternion::CreateRotation(const VectorF4 &start,
									   const VectorF4 &end)
{
	FLOAT32 angle,half;
	FLOAT32 cosv,sinv;
	FLOAT32 dot;

	VectorF4 cross;

	dot = start.DotProduct(end);

	cross.x = 0.0;
	cross.y = 0.0;
	cross.z = 1.0;
	
	if (fabs(1-dot) < 1.0e-5)
	{
		angle = 0.0;
	}
	else if (fabs(1+dot) < 1.0e-5)
	{
		angle = PI;
	}
	else
	{
		cross = start.CrossProduct(end);
		angle = acos(dot);
		cross.Normalize();
	}	
	
	half = FLOAT32(0.5)*angle;

	//cosv = cos(DEGREE_TO_RADIANS*half);
	//sinv = sin(DEGREE_TO_RADIANS*half);

	cosv = cos(half);
	sinv = sin(half);

	w = cosv;
	x = sinv*cross.x;
	y = sinv*cross.y;
	z = sinv*cross.z;

	wMod = w*w-(x*x)-(y*y)-(z*z);	
	wMul2 = FLOAT32(2.0f)*w;	
}


inline void Quaternion::RotatePoint(const VectorF4 *source,
									VectorF4 *dest,const INT32 points) const
{
	INT32 k;
	FLOAT32 dotMod;

	VectorF4 temp;

	for(k=0;k<points;k++)
	{
		dotMod = FLOAT32(2.0f) * 
			((source[k].x * x) + (source[k].y * y) + (source[k].z * z));
		
		temp.x = (wMod * source[k].x) + (dotMod * x) - 
			wMul2 * ((source[k].y * z) - (source[k].z * y));

		temp.y = (wMod * source[k].y) + (dotMod * y) + 
			wMul2 * ((source[k].x * z) - (source[k].z * x));

		temp.z = (wMod * source[k].z) + (dotMod * z) - 
			wMul2 * ((source[k].x * y)-(source[k].y * x));			

		dest[k] = temp;
	}
}

inline Quaternion::operator Matrix4() const
{
	Matrix4 temp;

	// Construct a matrix so that matrix*vector has the
	// same effect as RotatePoint(vector)

	temp.data[0][0] = FLOAT32(2.0f)*x*x + wMod;
	temp.data[0][1] = FLOAT32(2.0f)*x*y - wMul2 * z;
	temp.data[0][2] = FLOAT32(2.0f)*x*z + wMul2 * y;
	temp.data[0][3] = FLOAT32(0.0f);

	temp.data[1][0] = FLOAT32(2.0f)*x*y + wMul2 * z;
	temp.data[1][1] = FLOAT32(2.0f)*y*y + wMod;
	temp.data[1][2] = FLOAT32(2.0f)*z*y - wMul2 * x;
	temp.data[1][3] = FLOAT32(0.0f);

	temp.data[2][0] = FLOAT32(2.0f)*x*z - wMul2 * y;
	temp.data[2][1] = FLOAT32(2.0f)*y*z + wMul2 * x;
	temp.data[2][2] = FLOAT32(2.0f)*z*z + wMod;
	temp.data[2][3] = FLOAT32(0.0f);

	temp.data[3][0] = FLOAT32(0.0f);
	temp.data[3][1] = FLOAT32(0.0f);
	temp.data[3][2] = FLOAT32(0.0f);
	temp.data[3][3] = FLOAT32(1.0f);

	return temp;
}

inline void Quaternion::AddRotation(const Quaternion &rotation)
{
	*this = rotation * (*this);
}

}

#endif