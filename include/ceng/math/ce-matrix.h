/*****************************************************************************
*
* ce-matrix.h
*
* By Jari Korkala 9/2011
*
*
*****************************************************************************/

#ifndef _CONCEPT2_MATRIX_H
#define _CONCEPT2_MATRIX_H

#include <math.h>
#include "ce-vector.h"

namespace Ceng
{

	class Matrix4
	{
	public:
		FLOAT32 data[4][4];

	public:
		Matrix4();
		Matrix4(const Matrix4 &other);

		~Matrix4();

		Matrix4& operator = (const Matrix4 &other);
		Matrix4& operator += (const Matrix4 &other);
		Matrix4& operator -= (const Matrix4 &other);

		Matrix4& operator *= (const Matrix4 &other);
		Matrix4& operator *= (const FLOAT32 value);

		const Matrix4 operator + (const Matrix4 &other) const;
		const Matrix4 operator - (const Matrix4 &other) const;

		const Matrix4 operator * (const Matrix4 &other) const;
		const VectorF4 operator * (const VectorF4 &other) const;

		const Matrix4 operator * (const FLOAT32 value) const;

		const Matrix4 Inverse() const;

		const Ceng::FLOAT32 Determinant() const;

		void Identity();
	};

	//*************************************************************
	// Inlined methods

	inline Matrix4::Matrix4()
	{
	}

	inline Matrix4::Matrix4(const Matrix4 &other)
	{
		int k, j;

		for (k = 0; k < 4; k++)
		{
			for (j = 0; j < 4; j++)
			{
				data[k][j] = other.data[k][j];
			}
		}
	}

	inline Matrix4::~Matrix4()
	{
	}

	inline void Matrix4::Identity()
	{
		data[0][0] = 1.0;
		data[0][1] = 0;
		data[0][2] = 0;
		data[0][3] = 0;

		data[1][0] = 0;
		data[1][1] = 1.0;
		data[1][2] = 0;
		data[1][3] = 0;

		data[2][0] = 0;
		data[2][1] = 0;
		data[2][2] = 1.0;
		data[2][3] = 0;

		data[3][0] = 0;
		data[3][1] = 0;
		data[3][2] = 0;
		data[3][3] = 1.0;
	}

	inline Matrix4& Matrix4::operator = (const Matrix4 &other)
	{
		memcpy(&data[0][0], &other.data[0][0], 16 * sizeof(FLOAT32));
		return *this;
	}

	inline Matrix4& Matrix4::operator += (const Matrix4 &other)
	{
		data[0][0] += other.data[0][0];
		data[0][1] += other.data[0][1];
		data[0][2] += other.data[0][2];
		data[0][3] += other.data[0][3];

		data[1][0] += other.data[1][0];
		data[1][1] += other.data[1][1];
		data[1][2] += other.data[1][2];
		data[1][3] += other.data[1][3];

		data[2][0] += other.data[2][0];
		data[2][1] += other.data[2][1];
		data[2][2] += other.data[2][2];
		data[2][3] += other.data[2][3];

		data[3][0] += other.data[3][0];
		data[3][1] += other.data[3][1];
		data[3][2] += other.data[3][2];
		data[3][3] += other.data[3][3];

		return *this;
	}

	inline Matrix4& Matrix4::operator -= (const Matrix4 &other)
	{
		data[0][0] -= other.data[0][0];
		data[0][1] -= other.data[0][1];
		data[0][2] -= other.data[0][2];
		data[0][3] -= other.data[0][3];

		data[1][0] -= other.data[1][0];
		data[1][1] -= other.data[1][1];
		data[1][2] -= other.data[1][2];
		data[1][3] -= other.data[1][3];

		data[2][0] -= other.data[2][0];
		data[2][1] -= other.data[2][1];
		data[2][2] -= other.data[2][2];
		data[2][3] -= other.data[2][3];

		data[3][0] -= other.data[3][0];
		data[3][1] -= other.data[3][1];
		data[3][2] -= other.data[3][2];
		data[3][3] -= other.data[3][3];

		return *this;
	}

	inline const Matrix4 Matrix4::operator + (const Matrix4 &other) const
	{
		Matrix4 temp;

		temp.data[0][0] = data[0][0] + other.data[0][0];
		temp.data[0][1] = data[0][1] + other.data[0][1];
		temp.data[0][2] = data[0][2] + other.data[0][2];
		temp.data[0][3] = data[0][3] + other.data[0][3];

		temp.data[1][0] = data[1][0] + other.data[1][0];
		temp.data[1][1] = data[1][1] + other.data[1][1];
		temp.data[1][2] = data[1][2] + other.data[1][2];
		temp.data[1][3] = data[1][3] + other.data[1][3];

		temp.data[2][0] = data[2][0] + other.data[2][0];
		temp.data[2][1] = data[2][1] + other.data[2][1];
		temp.data[2][2] = data[2][2] + other.data[2][2];
		temp.data[2][3] = data[2][3] + other.data[2][3];

		temp.data[3][0] = data[3][0] + other.data[3][0];
		temp.data[3][1] = data[3][1] + other.data[3][1];
		temp.data[3][2] = data[3][2] + other.data[3][2];
		temp.data[3][3] = data[3][3] + other.data[3][3];

		return temp;
	}

	inline const Matrix4 Matrix4::operator - (const Matrix4 &other) const
	{
		Matrix4 temp;

		temp.data[0][0] = data[0][0] - other.data[0][0];
		temp.data[0][1] = data[0][1] - other.data[0][1];
		temp.data[0][2] = data[0][2] - other.data[0][2];
		temp.data[0][3] = data[0][3] - other.data[0][3];

		temp.data[1][0] = data[1][0] - other.data[1][0];
		temp.data[1][1] = data[1][1] - other.data[1][1];
		temp.data[1][2] = data[1][2] - other.data[1][2];
		temp.data[1][3] = data[1][3] - other.data[1][3];

		temp.data[2][0] = data[2][0] - other.data[2][0];
		temp.data[2][1] = data[2][1] - other.data[2][1];
		temp.data[2][2] = data[2][2] - other.data[2][2];
		temp.data[2][3] = data[2][3] - other.data[2][3];

		temp.data[3][0] = data[3][0] - other.data[3][0];
		temp.data[3][1] = data[3][1] - other.data[3][1];
		temp.data[3][2] = data[3][2] - other.data[3][2];
		temp.data[3][3] = data[3][3] - other.data[3][3];

		return temp;
	}

	inline Matrix4& Matrix4::operator *= (const FLOAT32 value)
	{
		data[0][0] *= value;
		data[0][1] *= value;
		data[0][2] *= value;
		data[0][3] *= value;

		data[1][0] *= value;
		data[1][1] *= value;
		data[1][2] *= value;
		data[1][3] *= value;

		data[2][0] *= value;
		data[2][1] *= value;
		data[2][2] *= value;
		data[2][3] *= value;

		data[3][0] *= value;
		data[3][1] *= value;
		data[3][2] *= value;
		data[3][3] *= value;

		return *this;
	}

	inline Matrix4& Matrix4::operator *= (const Matrix4 &other)
	{
		// First row
		data[0][0] = data[0][0] * other.data[0][0] +
			data[0][1] * other.data[1][0] +
			data[0][2] * other.data[2][0] +
			data[0][3] * other.data[3][0];

		data[0][1] = data[0][0] * other.data[0][1] +
			data[0][1] * other.data[1][1] +
			data[0][2] * other.data[2][1] +
			data[0][3] * other.data[3][1];

		data[0][2] = data[0][0] * other.data[0][2] +
			data[0][1] * other.data[1][2] +
			data[0][2] * other.data[2][2] +
			data[0][3] * other.data[3][2];

		data[0][3] = data[0][0] * other.data[0][3] +
			data[0][1] * other.data[1][3] +
			data[0][2] * other.data[2][3] +
			data[0][3] * other.data[3][3];

		// Second row
		data[1][0] = data[1][0] * other.data[0][0] +
			data[1][1] * other.data[1][0] +
			data[1][2] * other.data[2][0] +
			data[1][3] * other.data[3][0];

		data[1][1] = data[1][0] * other.data[0][1] +
			data[1][1] * other.data[1][1] +
			data[1][2] * other.data[2][1] +
			data[1][3] * other.data[3][1];

		data[1][2] = data[1][0] * other.data[0][2] +
			data[1][1] * other.data[1][2] +
			data[1][2] * other.data[2][2] +
			data[1][3] * other.data[3][2];

		data[1][3] = data[1][0] * other.data[0][3] +
			data[1][1] * other.data[1][3] +
			data[1][2] * other.data[2][3] +
			data[1][3] * other.data[3][3];

		// Third row

		data[2][0] = data[2][0] * other.data[0][0] +
			data[2][1] * other.data[1][0] +
			data[2][2] * other.data[2][0] +
			data[2][3] * other.data[3][0];

		data[2][1] = data[2][0] * other.data[0][1] +
			data[2][1] * other.data[1][1] +
			data[2][2] * other.data[2][1] +
			data[2][3] * other.data[3][1];

		data[2][2] = data[2][0] * other.data[0][2] +
			data[2][1] * other.data[1][2] +
			data[2][2] * other.data[2][2] +
			data[2][3] * other.data[3][2];

		data[2][3] = data[2][0] * other.data[0][3] +
			data[2][1] * other.data[1][3] +
			data[2][2] * other.data[2][3] +
			data[2][3] * other.data[3][3];

		// Fourth row

		data[3][0] = data[3][0] * other.data[0][0] +
			data[3][1] * other.data[1][0] +
			data[3][2] * other.data[2][0] +
			data[3][3] * other.data[3][0];

		data[3][1] = data[3][0] * other.data[0][1] +
			data[3][1] * other.data[1][1] +
			data[3][2] * other.data[2][1] +
			data[3][3] * other.data[3][1];

		data[3][2] = data[3][0] * other.data[0][2] +
			data[3][1] * other.data[1][2] +
			data[3][2] * other.data[2][2] +
			data[3][3] * other.data[3][2];

		data[3][3] = data[3][0] * other.data[0][3] +
			data[3][1] * other.data[1][3] +
			data[3][2] * other.data[2][3] +
			data[3][3] * other.data[3][3];

		return *this;
	}

	inline const Matrix4 Matrix4::operator * (const Matrix4 &other) const
	{
		Matrix4 temp;

		// First row
		temp.data[0][0] = data[0][0] * other.data[0][0] +
			data[0][1] * other.data[1][0] +
			data[0][2] * other.data[2][0] +
			data[0][3] * other.data[3][0];

		temp.data[0][1] = data[0][0] * other.data[0][1] +
			data[0][1] * other.data[1][1] +
			data[0][2] * other.data[2][1] +
			data[0][3] * other.data[3][1];

		temp.data[0][2] = data[0][0] * other.data[0][2] +
			data[0][1] * other.data[1][2] +
			data[0][2] * other.data[2][2] +
			data[0][3] * other.data[3][2];

		temp.data[0][3] = data[0][0] * other.data[0][3] +
			data[0][1] * other.data[1][3] +
			data[0][2] * other.data[2][3] +
			data[0][3] * other.data[3][3];

		// Second row
		temp.data[1][0] = data[1][0] * other.data[0][0] +
			data[1][1] * other.data[1][0] +
			data[1][2] * other.data[2][0] +
			data[1][3] * other.data[3][0];

		temp.data[1][1] = data[1][0] * other.data[0][1] +
			data[1][1] * other.data[1][1] +
			data[1][2] * other.data[2][1] +
			data[1][3] * other.data[3][1];

		temp.data[1][2] = data[1][0] * other.data[0][2] +
			data[1][1] * other.data[1][2] +
			data[1][2] * other.data[2][2] +
			data[1][3] * other.data[3][2];

		temp.data[1][3] = data[1][0] * other.data[0][3] +
			data[1][1] * other.data[1][3] +
			data[1][2] * other.data[2][3] +
			data[1][3] * other.data[3][3];

		// Third row

		temp.data[2][0] = data[2][0] * other.data[0][0] +
			data[2][1] * other.data[1][0] +
			data[2][2] * other.data[2][0] +
			data[2][3] * other.data[3][0];

		temp.data[2][1] = data[2][0] * other.data[0][1] +
			data[2][1] * other.data[1][1] +
			data[2][2] * other.data[2][1] +
			data[2][3] * other.data[3][1];

		temp.data[2][2] = data[2][0] * other.data[0][2] +
			data[2][1] * other.data[1][2] +
			data[2][2] * other.data[2][2] +
			data[2][3] * other.data[3][2];

		temp.data[2][3] = data[2][0] * other.data[0][3] +
			data[2][1] * other.data[1][3] +
			data[2][2] * other.data[2][3] +
			data[2][3] * other.data[3][3];

		// Fourth row

		temp.data[3][0] = data[3][0] * other.data[0][0] +
			data[3][1] * other.data[1][0] +
			data[3][2] * other.data[2][0] +
			data[3][3] * other.data[3][0];

		temp.data[3][1] = data[3][0] * other.data[0][1] +
			data[3][1] * other.data[1][1] +
			data[3][2] * other.data[2][1] +
			data[3][3] * other.data[3][1];

		temp.data[3][2] = data[3][0] * other.data[0][2] +
			data[3][1] * other.data[1][2] +
			data[3][2] * other.data[2][2] +
			data[3][3] * other.data[3][2];

		temp.data[3][3] = data[3][0] * other.data[0][3] +
			data[3][1] * other.data[1][3] +
			data[3][2] * other.data[2][3] +
			data[3][3] * other.data[3][3];

		return temp;
	}

	inline const VectorF4 Matrix4::operator *(const VectorF4 &other) const
	{
		VectorF4 temp;

		temp.x = data[0][0] * other.x + data[0][1] * other.y +
			data[0][2] * other.z + data[0][3] * other.w;

		temp.y = data[1][0] * other.x + data[1][1] * other.y +
			data[1][2] * other.z + data[1][3] * other.w;

		temp.z = data[2][0] * other.x + data[2][1] * other.y +
			data[2][2] * other.z + data[2][3] * other.w;

		temp.w = data[3][0] * other.x + data[3][1] * other.y +
			data[3][2] * other.z + data[3][3] * other.w;

		return temp;
	}

	/**
	 * Uses Gauss-Jordan elimination method from Intel's 
	 * "Streaming SIMD Extensions - Inverse of 4x4 Matrix".
	 */
	inline const Matrix4 Matrix4::Inverse() const
	{
		Matrix4 out(*this);

		INT32 indxc[4], indxr[4], ipiv[4];

		INT32 i, icol, irow, j, ir, ic;

		FLOAT32	big, dum, pivinv, temp, bb;

		ipiv[0] = -1;
		ipiv[1] = -1;
		ipiv[2] = -1;
		ipiv[3] = -1;

		/*
		out.data[0][0] = data[0][0];
		a[1][0] = b[1][0];
		a[2][0] = b[2][0];
		a[3][0] = b[3][0];
		a[0][1] = b[0][1];
		a[1][1] = b[1][1];
		a[2][1] = b[2][1];
		a[3][1] = b[3][1];
		a[0][2] = b[0][2];
		a[1][2] = b[1][2];
		a[2][2] = b[2][2];
		a[3][2] = b[3][2];
		a[0][3] = b[0][3];
		a[1][3] = b[1][3];
		a[2][3] = b[2][3];
		a[3][3] = b[3][3];
		*/

		for (i = 0; i < 4; ++i)
		{
			big = 0.0f;

			for (j = 0; j < 4; ++j)
			{
				if (ipiv[j] != 0)
				{
					if (ipiv[0] == -1)
					{
						if ((bb = (FLOAT32)fabs(out.data[j][0])) > big)
						{
							big = bb;
							irow = j;
							icol = 0;
						}
					}
					else if (ipiv[0] > 0)
					{
						return out;
					}

					if (ipiv[1] == -1)
					{
						if ((bb = (FLOAT32)fabs(out.data[j][1])) > big)
						{
							big = bb;
							irow = j;
							icol = 1;
						}
					}
					else if (ipiv[1] > 0)
					{
						return out;
					}

					if (ipiv[2] == -1)
					{
						if ((bb = (float)fabs(out.data[j][2])) > big)
						{
							big = bb;
							irow = j;
							icol = 2;
						}
					}
					else if (ipiv[2] > 0)
					{
						return out;
					}

					if (ipiv[3] == -1)
					{
						if ((bb = (FLOAT32)fabs(out.data[j][3])) > big)
						{
							big = bb;
							irow = j;
							icol = 3;
						}
					}
					else if (ipiv[3] > 0)
					{
						return out;
					}
				}
			}

			++(ipiv[icol]);

			if (irow != icol)
			{
				temp = out.data[irow][0];

				out.data[irow][0] = out.data[icol][0];
				out.data[icol][0] = temp;

				temp = out.data[irow][1];
				out.data[irow][1] = out.data[icol][1];
				out.data[icol][1] = temp;

				temp = out.data[irow][2];
				out.data[irow][2] = out.data[icol][2];
				out.data[icol][2] = temp;

				temp = out.data[irow][3];
				out.data[irow][3] = out.data[icol][3];
				out.data[icol][3] = temp;
			}

			indxr[i] = irow;
			indxc[i] = icol;

			if (out.data[icol][icol] == 0.0f)
			{
				return out;
			}

			pivinv = 1.0f / out.data[icol][icol];
			out.data[icol][icol] = 1.0f;
			out.data[icol][0] *= pivinv;
			out.data[icol][1] *= pivinv;
			out.data[icol][2] *= pivinv;
			out.data[icol][3] *= pivinv;

			if (icol != 0)
			{
				dum = out.data[0][icol];
				out.data[0][icol] = 0.0f;
				out.data[0][0] -= out.data[icol][0] * dum;
				out.data[0][1] -= out.data[icol][1] * dum;
				out.data[0][2] -= out.data[icol][2] * dum;
				out.data[0][3] -= out.data[icol][3] * dum;
			}

			if (icol != 1)
			{
				dum = out.data[1][icol];
				out.data[1][icol] = 0.0f;
				out.data[1][0] -= out.data[icol][0] * dum;
				out.data[1][1] -= out.data[icol][1] * dum;
				out.data[1][2] -= out.data[icol][2] * dum;
				out.data[1][3] -= out.data[icol][3] * dum;
			}

			if (icol != 2)
			{
				dum = out.data[2][icol];

				out.data[2][icol] = 0.0f;
				out.data[2][0] -= out.data[icol][0] * dum;
				out.data[2][1] -= out.data[icol][1] * dum;
				out.data[2][2] -= out.data[icol][2] * dum;
				out.data[2][3] -= out.data[icol][3] * dum;
			}

			if (icol != 3)
			{
				dum = out.data[3][icol];

				out.data[3][icol] = 0.0f;
				out.data[3][0] -= out.data[icol][0] * dum;
				out.data[3][1] -= out.data[icol][1] * dum;
				out.data[3][2] -= out.data[icol][2] * dum;
				out.data[3][3] -= out.data[icol][3] * dum;
			}
		}

		if (indxr[3] != indxc[3])
		{
			ir = indxr[3];
			ic = indxc[3];

			temp = out.data[0][ir];

			out.data[0][ir] = out.data[0][ic];
			out.data[0][ic] = temp;

			temp = out.data[1][ir];

			out.data[1][ir] = out.data[1][ic];
			out.data[1][ic] = temp;

			temp = out.data[2][ir];
			out.data[2][ir] = out.data[2][ic];
			out.data[2][ic] = temp;

			temp = out.data[3][ir];

			out.data[3][ir] = out.data[3][ic];
			out.data[3][ic] = temp;
		}

		if (indxr[2] != indxc[2])
		{
			ir = indxr[2];
			ic = indxc[2];

			temp = out.data[0][ir];
			out.data[0][ir] = out.data[0][ic];
			out.data[0][ic] = temp;

			temp = out.data[1][ir];
			out.data[1][ir] = out.data[1][ic];
			out.data[1][ic] = temp;

			temp = out.data[2][ir];
			out.data[2][ir] = out.data[2][ic];
			out.data[2][ic] = temp;

			temp = out.data[3][ir];
			out.data[3][ir] = out.data[3][ic];
			out.data[3][ic] = temp;
		}

		if (indxr[1] != indxc[1])
		{
			ir = indxr[1];
			ic = indxc[1];

			temp = out.data[0][ir];
			out.data[0][ir] = out.data[0][ic];
			out.data[0][ic] = temp;

			temp = out.data[1][ir];
			out.data[1][ir] = out.data[1][ic];
			out.data[1][ic] = temp;

			temp = out.data[2][ir];
			out.data[2][ir] = out.data[2][ic];
			out.data[2][ic] = temp;

			temp = out.data[3][ir];
			out.data[3][ir] = out.data[3][ic];
			out.data[3][ic] = temp;
		}

		if (indxr[0] != indxc[0])
		{
			ir = indxr[0];
			ic = indxc[0];

			temp = out.data[0][ir];
			out.data[0][ir] = out.data[0][ic];
			out.data[0][ic] = temp;

			temp = out.data[1][ir];
			out.data[1][ir] = out.data[1][ic];
			out.data[1][ic] = temp;

			temp = out.data[2][ir];
			out.data[2][ir] = out.data[2][ic];
			out.data[2][ic] = temp;

			temp = out.data[3][ir];
			out.data[3][ir] = out.data[3][ic];
			out.data[3][ic] = temp;
		}

		return out;
	}

	inline const Ceng::FLOAT32 Matrix4::Determinant() const
	{
		return data[0][0] * data[1][1] * data[2][2] * data[3][3] +
			data[0][0] * data[1][2] * data[2][3] * data[3][1] +
			data[0][0] * data[1][3] * data[2][1] * data[3][2] +

			data[0][1] * data[1][0] * data[2][3] * data[3][2] +
			data[0][1] * data[1][2] * data[2][0] * data[3][3] +
			data[0][1] * data[1][3] * data[2][2] * data[3][0] +

			data[0][2] * data[1][0] * data[2][1] * data[3][3] +
			data[0][2] * data[1][1] * data[2][3] * data[3][0] +
			data[0][2] * data[1][3] * data[2][0] * data[3][1] +

			data[0][3] * data[1][0] * data[2][2] * data[3][1] +
			data[0][3] * data[1][1] * data[2][0] * data[3][2] +
			data[0][3] * data[1][2] * data[2][1] * data[3][0] -

			data[0][0] * data[1][1] * data[2][3] * data[3][2] -
			data[0][0] * data[1][2] * data[2][1] * data[3][3] -
			data[0][0] * data[1][3] * data[2][2] * data[3][1] -

			data[0][1] * data[1][0] * data[2][2] * data[3][3] -
			data[0][1] * data[1][2] * data[2][3] * data[3][0] -
			data[0][1] * data[1][3] * data[2][0] * data[3][2] -

			data[0][2] * data[1][0] * data[2][3] * data[3][1] -
			data[0][2] * data[1][1] * data[2][0] * data[3][3] -
			data[0][2] * data[1][3] * data[2][1] * data[3][0] -

			data[0][3] * data[1][0] * data[2][1] * data[3][2] -
			data[0][3] * data[1][1] * data[2][2] * data[3][0] -
			data[0][3] * data[1][2] * data[2][0] * data[3][1];
	}

}

#endif