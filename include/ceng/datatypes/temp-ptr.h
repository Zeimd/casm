/*****************************************************************************
*
* temp-ptr.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_TEMP_PTR_H
#define _CENG_TEMP_PTR_H

#include "base-ptr.h"

namespace Ceng
{
	template<class T>
	class LocalPtr;

	template<class T>
	class SharedPtr;

	template<class T>
	class TempPtr : public Ceng::BasePtr<T>
	{
	protected:
		
	public:

		TempPtr();
		TempPtr(T *other);
		TempPtr(const TempPtr &other);
		TempPtr(const LocalPtr<T> &other);
		TempPtr(const SharedPtr<T> &other);

		~TempPtr();

		TempPtr& operator = (const T* other);
		TempPtr& operator = (const TempPtr &other);
		TempPtr& operator = (const LocalPtr<T> &other);
		TempPtr& operator = (const SharedPtr<T> &other);
	};

	template<class T>
	inline TempPtr<T>::TempPtr()
	{
		pointer = NULL;
	}

	template<class T>
	inline TempPtr<T>::~TempPtr()
	{
	}

	template<class T>
	inline TempPtr<T>::TempPtr(T *other)
	{
		pointer = other;
	}

	template<class T>
	inline TempPtr<T>::TempPtr(const TempPtr<T> &other)
	{
		pointer = other.pointer;
	}

	
	template<class T>
	inline TempPtr<T>::TempPtr(const LocalPtr<T> &other)
	{
		pointer = other.pointer;
	}
	
	template<class T>
	inline TempPtr<T>::TempPtr(const SharedPtr<T> &other)
	{
		pointer = other.pointer;
	}

	template<class T>
	inline TempPtr<T>& TempPtr<T>::operator=(const T *other)
	{
		pointer = other;
		return *this;
	}

	template<class T>
	inline TempPtr<T>& TempPtr<T>::operator=(const TempPtr<T> &other)
	{
		pointer = other.pointer;
		return *this;
	}

	template<class T>
	inline TempPtr<T>& TempPtr<T>::operator=(const LocalPtr<T> &other)
	{
		pointer = other.pointer;
		return *this;
	}

	template<class T>
	inline TempPtr<T>& TempPtr<T>::operator=(const SharedPtr<T> &other)
	{
		pointer = other.pointer;
		return *this;
	}
	
};

#endif