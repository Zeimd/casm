/*****************************************************************************
*
* array-atomic.h
*
* Created By Jari Korkala 9/10/2014
*
*****************************************************************************/

#ifndef CENG_ARRAY_ATOMIC_H
#define CENG_ARRAY_ATOMIC_H

#include <atomic>

namespace Ceng
{
	template<class t_ElemType>
	class ArrayAtomic
	{
	protected:

		std::atomic<t_ElemType> *buffer;

		Ceng::UINT32 size;

		ArrayAtomic(const ArrayAtomic &source);
		ArrayAtomic(ArrayAtomic &&source);

		ArrayAtomic& operator = (const ArrayAtomic &source);
		ArrayAtomic& operator = (ArrayAtomic &&source);


	public:

		ArrayAtomic();
		~ArrayAtomic();

		ArrayAtomic(const Ceng::UINT32 size,const t_ElemType &value=t_ElemType());

		std::atomic<t_ElemType>& operator [] (const Ceng::UINT32 index);

		const std::atomic<t_ElemType>& operator [] (const Ceng::UINT32 index) const;

		const Ceng::UINT32 Size() const;

	};

	template<class t_ElemType>
	ArrayAtomic<t_ElemType>::ArrayAtomic()
		: size(0),buffer(nullptr)
	{
	}

	template<class t_ElemType>
	ArrayAtomic<t_ElemType>::ArrayAtomic(const Ceng::UINT32 size,const t_ElemType &value=t_ElemType())
		: size(size)
	{
		buffer = new std::atomic<t_ElemType>[size];

		for(Ceng::UINT32 k=0;k<size;k++)
		{
			new (&buffer[k]) std::atomic<t_ElemType>(value);
		}
	}

	template<class t_ElemType>
	ArrayAtomic<t_ElemType>::~ArrayAtomic()
	{
		if (buffer != nullptr)
		{
			delete[] buffer;
		}
	}

	template<class t_ElemType>
	ArrayAtomic<t_ElemType>::ArrayAtomic(const ArrayAtomic &source)
	{
	}

	template<class t_ElemType>
	ArrayAtomic<t_ElemType>::ArrayAtomic(ArrayAtomic &&source)
	{
	}

	template<class t_ElemType>
	ArrayAtomic<t_ElemType>& ArrayAtomic<t_ElemType>::operator=(const ArrayAtomic &source)
	{
		return *this;
	}

	template<class t_ElemType>
	ArrayAtomic<t_ElemType>& ArrayAtomic<t_ElemType>::operator=(ArrayAtomic &&source)
	{
		return *this;
	}

	template<class t_ElemType>
	const Ceng::UINT32 ArrayAtomic<t_ElemType>::Size() const
	{
		return size;
	}

	template<class t_ElemType>
	std::atomic<t_ElemType>& ArrayAtomic<t_ElemType>::operator[] (const Ceng::UINT32 index)
	{
		return buffer[index];
	}

	template<class t_ElemType>
	const std::atomic<t_ElemType>& ArrayAtomic<t_ElemType>::operator[] (const Ceng::UINT32 index) const
	{
		return buffer[index];
	}
}

#endif
