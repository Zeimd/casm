/*****************************************************************************
*
* local-ptr.h
*
* By Jari Korkala 4/2013
*
* class LocalPtr<T> : 
*
* A pointer that deletes its contents when it goes out of scope.
*
* Intended for memory allocation in sections of code that could
* throw an exception.
*
* NOTE: Assignment to an another pointer invalidates this object.
*
*****************************************************************************/

#ifndef _CENG_LOCAL_PTR_H
#define _CENG_LOCAL_PTR_H

#include "base-ptr.h"

namespace Ceng
{
	template<class T>
	class TempPtr;

	template<class T>
	class LocalPtr : public Ceng::BasePtr<T>
	{
	protected:

	public:

		LocalPtr();

		LocalPtr(const TempPtr<T> &other);

		LocalPtr(T *barePtr);
		
		virtual ~LocalPtr();

		LocalPtr& operator = (const T *source);

		//LocalPtr& operator = (const TempPtr<T> &other);
		
		/**
		 * Transfer pointer from other LocalPtr. Source pointer
		 * is cleared to prevent multiple deallocations.
		 */
		LocalPtr& operator = (LocalPtr &other);

	protected:
		void Release();
	};

	template<class T>
	inline LocalPtr<T>::LocalPtr()
	{
		pointer = NULL;
	}
	
	template<class T>
	inline LocalPtr<T>::LocalPtr(T *barePtr)
	{
		pointer = barePtr;
	}

	template<class T>
	inline LocalPtr<T>::~LocalPtr()
	{
		Release();
	}

	template<class T>
	inline void LocalPtr<T>::Release()
	{
		if (pointer != NULL)
		{
			delete pointer;
			pointer = NULL;
		}
	}

	template<class T>
	inline LocalPtr<T>& LocalPtr<T>::operator = (const T *source)
	{
		Release();
		pointer = source;
	}
	
	template<class T>
	inline LocalPtr<T>& LocalPtr<T>::operator = (LocalPtr<T> &other)
	{
		if (this == &other) return *this;

		pointer = other.pointer;
		other.pointer = NULL;
		return *this;
	}
	
};

#endif