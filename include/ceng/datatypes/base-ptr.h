/*****************************************************************************
*
* base-ptr.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_BASE_PTR_H
#define _CENG_BASE_PTR_H

#include "basic-types.h"

namespace Ceng
{
	template<class T>
	class BasePtr
	{
	protected:
		T *pointer;

	public:
		BasePtr();
		virtual ~BasePtr();

		operator T*() const;

		T& operator [](const UINT32 index) const;

		T* operator -> () const;
		T& operator * () const;

		// Compare pointers

		const bool operator == (const BasePtr &other) const;
		const bool operator != (const BasePtr &other) const;

		const bool operator == (const T *other) const;
		const bool operator != (const T *other) const;

		/** 
		 * Compare object address.
		 */
		const bool Equals(const BasePtr &other) const;
	};

	template<class T>
	inline BasePtr<T>::BasePtr()
	{
		pointer = nullptr;
	}

	template<class T>
	inline BasePtr<T>::~BasePtr()
	{
	}

	template<class T>
	inline BasePtr<T>::operator T *() const
	{
		return pointer;
	}

	template<class T>
	inline T& BasePtr<T>::operator * () const
	{
		return *pointer;
	}

	template<class T>
	inline T* BasePtr<T>::operator -> () const
	{
		return pointer;
	}

	template<class T>
	inline T& BasePtr<T>::operator [](const UINT32 index) const
	{
		return pointer[index];
	}

	template<class T>
	inline const bool BasePtr<T>::Equals(const BasePtr<T> &other) const
	{
		return (this == &other);
	}

	template<class T>
	inline const bool BasePtr<T>::operator ==(const BasePtr<T> &other) const
	{
		return (pointer == other.pointer);
	}

	template<class T>
	inline const bool BasePtr<T>::operator !=(const BasePtr<T> &other) const
	{
		return (pointer != other.pointer);
	}

	template<class T>
	inline const bool BasePtr<T>::operator ==(const T *other) const
	{
		return (pointer == other);
	}

	template<class T>
	inline const bool BasePtr<T>::operator !=(const T *other) const
	{
		return (pointer != other);
	}
};

#endif