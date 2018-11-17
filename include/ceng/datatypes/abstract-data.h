/*****************************************************************************
*
* abstract-data.h
*
* By Jari Korkala 10/2012
*
* A class that contains 64 bits which are interpreted as the desired
* data type. The class doesn't know what it contains and cannot be used
* for comparisons or arithmetic.
*
* WARNING: Only store objects if they don't allocate memory
*
* NOTE: Do not include this file directly. Include "datatypes.h" instead.
*
*****************************************************************************/

#ifndef _CONCEPT2_ABSTRACT_64_H
#define _CONCEPT2_ABSTRACT_64_H

#include "basic-types.h"

namespace Ceng
{
	template<UINT32 tBytes>
	class Abstract
	{
	protected:

		UINT8 data[tBytes];

	public:
		Abstract();	
		Abstract(const Abstract &other);

		template<class T>
		Abstract(const T &source);

		template<UINT32 otherBytes>
		Abstract(const Abstract<otherBytes> &other);

		~Abstract();

		Abstract& operator = (const Abstract &other);

		template<UINT32 otherBytes>
		Abstract& operator = (const Abstract<otherBytes> &other);
	
		template<class T>
		Abstract& operator = (const T &value);
		
		template<class T>
		operator T() const;

		
	};

	//****************************************************
	// Constructors 

	template<UINT32 tBytes>
	inline Abstract<tBytes>::Abstract()
	{
		memset(data,0,tBytes);
	}

	template<UINT32 tBytes>
	inline Abstract<tBytes>::~Abstract()
	{
	}

	template<UINT32 tBytes>
	template<class T>
	inline Abstract<tBytes>::Abstract(const T &source)
	{
		T *ptr = (T*)data;

		*ptr = source;
	}

	template<UINT32 tBytes>
	inline Abstract<tBytes>::Abstract(const Abstract<tBytes> &other)
	{
		memcpy(data,other.data,tBytes);
	}

	template<UINT32 tBytes>
	template<UINT32 otherBytes>
	inline Abstract<tBytes>::Abstract(const Abstract<otherBytes> &other)
	{
		UINT32 min = tBytes;
		
		if (otherBytes < min)
		{
			min = otherBytes;
		}

		memcpy(data,other.data,min);
	}

	//******************************************************
	// Assignment operators

	template<UINT32 tBytes>
	inline Abstract<tBytes>& Abstract<tBytes>::
							operator=(const Abstract<tBytes> &other)
	{
		memcpy(data,other.data,tBytes);
		return *this;
	}

	template<UINT32 tBytes>
	template<UINT32 otherBytes>
	inline Abstract<tBytes>& Abstract<tBytes>::
							operator=(const Abstract<otherBytes> &other)
	{
		UINT32 min = tBytes;
		
		if (otherBytes < min)
		{
			min = otherBytes;
		}

		memcpy(data,other.data,min);
		return *this;
	}

	template<UINT32 tBytes>
	template<class T>
	inline Abstract<tBytes>& Abstract<tBytes>::
							operator=(const T &value)
	{
		if (sizeof(T) > tBytes)
		{
			memset(data,0,tBytes);
			return *this;
		}


		T *dataPtr = reinterpret_cast<T*>(data);
		
		*dataPtr = value;
		return *this;
	}

	//************************************************************
	// Conversion operator

	template<UINT32 tBytes>
	template<class T>
	inline Abstract<tBytes>::operator T() const
	{
		if (sizeof(T) > tBytes)
		{
			return T();
		}
		
		T *dataPtr = reinterpret_cast<T*>(data);
		return *dataPtr;
	}

} // Namespace Ceng

#endif // Include guard