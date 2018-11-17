/*****************************************************************************
*
* boolean.h
*
* By Jari Korkala 10/2012
*
* NOTE: Do not include this file directly. Include "datatype-main.h".
*
*****************************************************************************/

#ifndef _CONCEPT2_BOOLEAN_H
#define _CONCEPT2_BOOLEAN_H

#include "basic-types.h"

//*************************************************************
// class BOOL 

/**
 *  A boolean data type stored in a 32-bit integer,
 *  with truth values stored as
 *
 *  true = all bits set ( = -1)
 *  false = 0
 *
 *  Converting BOOL to other primitive types yields
 *
 *  1 = true
 *  0 = false
 * 
 */

namespace Ceng
{
	class BOOL
	{
	
	protected:
		INT32 boolean;
	
	public:
		inline BOOL()
		{
			boolean = 0;
		}
		
		inline BOOL(const INT32 contents)
		{
			boolean = contents;
		}
		
		inline BOOL(const BOOL &other)
		{
			boolean = other.boolean;
		}
		
		template<class T>
		inline BOOL(const T &value)
		{
			boolean = 0;
			if (value != 0)
			{
				boolean = -1;
			}
		}
		
		inline BOOL& operator = (const BOOL &other)
		{
			boolean = other.boolean;
			return *this;
		}
		
		inline BOOL& operator = (const bool value)
		{
			boolean = -1;
			if (value == false)
			{
				boolean = 0;
			}
			return *this;
		}
		
		template<class T>
		inline BOOL& operator = (const T &value)
		{
			boolean = 0;
			if (value != 0)
			{
				boolean = -1;
			}
			return *this;
		}
		
		inline BOOL& operator &= (const BOOL &other)
		{
			boolean &= other.boolean;
			return *this;
		}
		
		inline BOOL& operator |= (const BOOL &other)
		{
			boolean |= other.boolean;
			return *this;
		}
		
		inline BOOL& operator ^= (const BOOL &other)
		{
			boolean ^= other.boolean;
			return *this;
		}
		
		inline const BOOL operator & (const BOOL &other) const
		{
			return BOOL(boolean & other.boolean);
		}
		
		inline const BOOL operator | (const BOOL &other) const
		{
			return BOOL(boolean | other.boolean);
		}
		
		inline const BOOL operator ^ (const BOOL &other) const
		{
			return BOOL(boolean ^ other.boolean);
		}
		
		inline const BOOL operator ~ () const
		{
			return BOOL(boolean ^ -1);
		}

		inline const bool operator ==  (const BOOL &other) const
		{
			return (boolean == other.boolean);
		}

		inline const bool operator != (const BOOL &other) const
		{
			return (boolean != other.boolean);
		}

		template<class T>
		inline const bool operator == (const T &other) const
		{
			return (*this == BOOL(other));
		}

		template<class T>
		inline const bool operator != (const T &other) const
		{
			return (*this != BOOL(other));
		}
		
		inline operator bool() const
		{
			return (boolean != 0);

			/*
			if (boolean == 0)
			{
				return false;
			}
			return true;
			*/
		}

		template<class T>
		inline operator T() const
		{
			return static_cast<T>(boolean & 1);
		}
		
		inline operator FLOAT32() const
		{
			if (boolean == -1)
			{
				return FLOAT32(1.0f);
			}
			return FLOAT32(0.0f);
		}
		
		inline operator FLOAT64() const
		{
			if (boolean == -1)
			{
				return FLOAT32(1.0f);
			}
			return FLOAT32(0.0);
		}
	};

} // Namespace Ceng

#endif // Include guard