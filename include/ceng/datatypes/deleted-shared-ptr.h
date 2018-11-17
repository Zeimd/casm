/*****************************************************************************
*
* ce-shared-ptr.h
*
* By Jari Korkala 6/2012
*
* NOTE: Do not include this file directly. Include "ce-data.h" instead!
*
* SharedPtr : a pointer class that keeps count of other shared pointers
*             to the same data. Assumes non-array new-operator was used.
*
* NOTE: Use only for those internal objects that can be referenced by
*       an unknown number of user interfaces.
*
*****************************************************************************/

#ifndef _CONCEPT2_SHARED_PTR_CR_H
#define _CONCEPT2_SHARED_PTR_CR_H

#include <exception>

#include "base-ptr.h"

namespace Ceng
{
	
	template<class T>
	class TempPtr;

	template<class T>
	class LocalPtr;

	template<class T>
	class SharedPtr : public Ceng::BasePtr<T>
	{
	protected:
		
		//TODO: Figure out why changing order of variables causes memory leaks
		
		INT32 *referenceCounter;

		INT32* GetCounter() const;

	public:

		/*
		 * Needed for casting from derived to base class ptr.
		 */
		template<class Y> friend class SharedPtr;

		SharedPtr();

		SharedPtr(T *source);
		SharedPtr(const SharedPtr &source);

		template<class Y>
		SharedPtr<T>(const SharedPtr<Y> &source);	

		virtual ~SharedPtr();
		void Release();

		INT32 ReferenceCount() const;

		/**
		 * Link to a new object.
		 */
		SharedPtr& operator = (T *newPtr);

		/**
		 * Link to an existing object.
		 */
		SharedPtr& operator = (const SharedPtr &source);

		SharedPtr& operator = (const TempPtr<T> &source);

		template<class Y>
		SharedPtr& operator = (const SharedPtr<Y> &source);

	protected:
		void NewPointer(T *source);
		void NewPointer(T *source,INT32 *counter);

	};

	template<class T>
	inline INT32* SharedPtr<T>::GetCounter() const
	{
		return referenceCounter;
	}

	template<class T>
	inline SharedPtr<T>::SharedPtr()
	{
		referenceCounter = nullptr;
		pointer = nullptr;
	}

	template<class T>
	inline void SharedPtr<T>::NewPointer(T *source)
	{
		pointer = source;
		referenceCounter = nullptr;

		if (pointer != nullptr)
		{
			try
			{
				referenceCounter = new INT32(1);
			}
			catch(std::bad_alloc &ba)
			{
				pointer = nullptr;
				referenceCounter = nullptr;
				throw ba;
			}
		}
	}

	template<class T>
	inline void SharedPtr<T>::NewPointer(T *source,INT32 *counter)
	{
		referenceCounter = counter;
		pointer = nullptr;

		if (referenceCounter != nullptr)
		{
			*referenceCounter = *referenceCounter + 1;
			pointer = source;
		}
	}

	template<class T>
	inline SharedPtr<T>::SharedPtr(T *source)
	{
		NewPointer(source);
	}

	template<class T>
	inline SharedPtr<T>::SharedPtr(const SharedPtr<T> &source)
	{
		NewPointer(source.pointer,source.referenceCounter);
	}

	template<class T>
	template<class Y>
	inline SharedPtr<T>::SharedPtr(const SharedPtr<Y> &source)
	{
		NewPointer(static_cast<T*>((Y*)(source)),source.GetCounter());
	}

	template<class T>
	inline SharedPtr<T>::~SharedPtr()
	{
		Release();
	}

	template<class T>
	inline void SharedPtr<T>::Release()
	{
		if (referenceCounter != nullptr)
		{
			*referenceCounter = *referenceCounter - 1;

			if (*referenceCounter == 0)
			{
				delete referenceCounter;
				delete pointer;
			}			

			pointer = nullptr;
			referenceCounter = nullptr;
		}
	}

	template<class T>
	inline INT32 SharedPtr<T>::ReferenceCount() const
	{
		return referenceCount;
	}

	template<class T>
	inline SharedPtr<T>& SharedPtr<T>::operator =(T *newPtr)
	{
		// If the pointer is currently pointing somewhere,
		// reduce reference counter on that object

		Release();

		NewPointer(newPtr);

		return *this;

	}

	template<class T>
	inline SharedPtr<T>& SharedPtr<T>::operator= (const TempPtr<T> &source)
	{
		NewPointer(source.pointer);
		return *this;
	}

	template<class T>
	inline SharedPtr<T>& SharedPtr<T>::operator = (const SharedPtr<T> &source)
	{
		if (&source != this)
		{
			Release();

			NewPointer(source.pointer,source.referenceCounter);
		}

		return *this;
	}

	template<class T>
	template<class Y>
	inline SharedPtr<T>& SharedPtr<T>::operator = (const SharedPtr<Y> &source)
	{
		Release();

		NewPointer(static_cast<T*>((Y*)(source)),source.GetCounter());

		return *this;
	}
};

#endif