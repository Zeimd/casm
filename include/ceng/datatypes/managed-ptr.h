/*****************************************************************************
*
* managed-ptr.h
*
* By Jari Korkala 5/2014
*
*****************************************************************************/

#ifndef CENG_MANAGED_PTR_H
#define CENG_MANAGED_PTR_H

#include "base-ptr.h"

namespace Ceng
{
	template<class T>
	class ManagedPtr : public BasePtr<T>
	{
	public:

		ManagedPtr();
		virtual ~ManagedPtr();

		ManagedPtr(const T *source);

		ManagedPtr& operator = (const ManagedPtr &source);
	};

	template<class T>
	ManagedPtr::ManagedPtr()
	{
	}

	template<class T>
	ManagedPtr::~ManagedPtr()
	{
	}

	template<class T>
	ManagedPtr::ManagedPtr(T *source)
	{
		pointer = source;
	}

	template<class T>
	ManagedPtr& operator = (const ManagedPtr &source)
	{
		pointer = source.pointer;
	}
	
}

#endif