/*****************************************************************************
*
* aligned-buffer.h
*
* Created By Jari Korkala 27/8/2014
*
*****************************************************************************/

#ifndef CENG_ALIGNED_BUFFER_H
#define CENG_ALIGNED_BUFFER_H

#include "basic-types.h"

namespace Ceng
{
	template<class T>
	class AlignedBuffer
	{
	protected:
		T *buffer;

		Ceng::UINT32 elements;
		Ceng::UINT32 sizeBytes;
		Ceng::UINT32 alignment;

	public:

		AlignedBuffer();
		AlignedBuffer(const Ceng::UINT32 elements,const Ceng::UINT32 alignment);

		AlignedBuffer(const AlignedBuffer &source);

		AlignedBuffer(AlignedBuffer &&source);

		~AlignedBuffer();

		AlignedBuffer& operator = (const AlignedBuffer &source);

		AlignedBuffer& operator = (AlignedBuffer &&source);

		/**
		 * Returns the number of elements of type T.
		 */
		const Ceng::UINT32 GetElements() const;

		/**
		 * Returns the size of allocated buffer in bytes.
		 */
		const Ceng::UINT32 GetSize() const;

		/**
		 * Returns memory alignment of the buffer in bytes.
		 */
		const Ceng::UINT32 GetAlignment() const;

		operator T*() const;

		T& operator [] (const Ceng::UINT32 index) const;
		T& operator [] (const Ceng::INT32 index) const;

		const bool operator == (const T *other) const;
		const bool operator != (const T *other) const;

	};

	template<class T>
	inline AlignedBuffer<T>::AlignedBuffer()
	{
		buffer = nullptr;

		elements = 0;
		sizeBytes = 0;
		alignment = 0;
	}

	template<class T>
	AlignedBuffer<T>::AlignedBuffer(const Ceng::UINT32 elements,const Ceng::UINT32 alignment)
	{
		this->elements = elements;

		buffer = (T*)AlignedMalloc(elements*sizeof(T),alignment);
		this->alignment = alignment;

		sizeBytes = elements*sizeof(T);
	}

	template<class T>
	inline AlignedBuffer<T>::~AlignedBuffer()
	{
		if (buffer != nullptr)
		{
			AlignedFree(buffer);
			buffer = nullptr;
		}
	}

	template<class T>
	inline AlignedBuffer<T>::AlignedBuffer(const AlignedBuffer &source)
	{
		alignment = source.alignment;
		elements = source.elements;
		sizeBytes = source.sizeBytes;

		buffer = nullptr;

		if (source.buffer != nullptr)
		{
			buffer = (T*)AlignedMalloc(elements*sizeof(T),alignment);
			
			memcpy(buffer,source.buffer,elements*sizeof(T));
		}
	}

	template<class T>
	inline AlignedBuffer<T>::AlignedBuffer(AlignedBuffer &&source)
	{
		alignment = source.alignment;
		elements = source.elements;
		sizeBytes = source.sizeBytes;
		buffer = source.buffer;

		source.elements = 0;
		source.sizeBytes = 0;
		source.alignment = 0;		

		source.buffer = nullptr;
	}

	template<class T>
	inline AlignedBuffer<T>& AlignedBuffer<T>::operator=(const AlignedBuffer<T> &source)
	{
		if (&source == this)
		{
			return *this;
		}

		if (buffer != nullptr && sizeBytes != source.sizeBytes)
		{
			AlignedFree(buffer);
			buffer = nullptr;
		}

		alignment = source.alignment;
		elements = source.elements;
		sizeBytes = source.sizeBytes;

		if (source.buffer != nullptr)
		{
			if (buffer == nullptr)
			{
				buffer = (T*)AlignedMalloc(elements*sizeof(T),alignment);
			}

			memcpy(buffer,source.buffer,elements*sizeof(T));
		}
	
		return *this;
	}

	template<class T>
	inline AlignedBuffer<T>& AlignedBuffer<T>::operator=(AlignedBuffer<T> &&source)
	{
		if (&source == this)
		{
			return *this;
		}

		alignment = source.alignment;
		elements = source.elements;
		sizeBytes = source.sizeBytes;
		buffer = source.buffer;

		source.elements = 0;
		source.sizeBytes = 0;
		source.alignment = 0;
		source.buffer = nullptr;
	
		return *this;
	}

	template<class T>
	inline const UINT32 AlignedBuffer<T>::GetSize() const
	{
		return sizeBytes;
	}

	template<class T>
	inline const UINT32 AlignedBuffer<T>::GetElements() const
	{
		return elements;
	}

	template<class T>
	inline const UINT32 AlignedBuffer<T>::GetAlignment() const
	{
		return alignment;
	}

	template<class T>
	inline T& AlignedBuffer<T>::operator[] (const UINT32 index) const
	{
		return buffer[index];
	}

	template<class T>
	inline T& AlignedBuffer<T>::operator[] (const INT32 index) const
	{
		return buffer[index];
	}

	
	template<class T>
	inline AlignedBuffer<T>::operator T*() const
	{
		return buffer;
	}
	
	template<class T>
	inline const bool AlignedBuffer<T>::operator==(const T *other) const
	{
		return (buffer == other);
	}

	template<class T>
	inline const bool AlignedBuffer<T>::operator!=(const T *other) const
	{
		return (buffer != other);
	}
}

#endif