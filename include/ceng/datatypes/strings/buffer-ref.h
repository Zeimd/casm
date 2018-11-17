/*****************************************************************************
*
* buffer-ref.h
*
* By Jari Korkala 3/2014
*
*****************************************************************************/

#ifndef CENG_STRING_BUFFER_REF_H
#define CENG_STRING_BUFFER_REF_H

#include "../basic-types.h"
#include "../boolean.h"

#include <vector>

namespace Ceng
{
	template<class DATA_ELEMENT>
	class PointerRef
	{
	protected:

		DATA_ELEMENT *buffer;

	public:

		PointerRef();
		~PointerRef();

		PointerRef(DATA_ELEMENT *buffer);
	
		PointerRef(const PointerRef &source);

		PointerRef& operator = (const PointerRef &source);

		const Ceng::INT32 MaxIndex() const;

		DATA_ELEMENT* GetPointer(const Ceng::INT32 offset) const;

		const Ceng::BOOL operator == (const PointerRef &other) const;

		const Ceng::BOOL operator != (const PointerRef &other) const;
	};

	template<class DATA_ELEMENT>
	PointerRef<DATA_ELEMENT>::PointerRef()
	{
		buffer = nullptr;
	}

	template<class DATA_ELEMENT>
	PointerRef<DATA_ELEMENT>::~PointerRef()
	{
	}

	template<class DATA_ELEMENT>
	PointerRef<DATA_ELEMENT>::PointerRef(DATA_ELEMENT *buffer) : buffer(buffer)
	{
	}

	template<class DATA_ELEMENT>
	PointerRef<DATA_ELEMENT>::PointerRef(const PointerRef &source) : buffer(source.buffer)
	{
	}

	template<class DATA_ELEMENT>
	PointerRef<DATA_ELEMENT>& PointerRef<DATA_ELEMENT>::operator = (const PointerRef &source)
	{
		buffer = source.buffer;
		return *this;
	}

	template<class DATA_ELEMENT>
	const Ceng::INT32 PointerRef<DATA_ELEMENT>::MaxIndex() const
	{
		return 0;
	}

	template<class DATA_ELEMENT>
	DATA_ELEMENT* PointerRef<DATA_ELEMENT>::GetPointer(const Ceng::INT32 offset) const
	{
		return &buffer[offset];
	}

	template<class DATA_ELEMENT>
	const Ceng::BOOL PointerRef<DATA_ELEMENT>::operator == (const PointerRef &other) const
	{
		return buffer == other.buffer;
	}

	template<class DATA_ELEMENT>
	const Ceng::BOOL PointerRef<DATA_ELEMENT>::operator != (const PointerRef &other) const
	{
		return !(*this == other);
	}

	//**********************************************************************************
	// class VectorRef

	template<class DATA_ELEMENT>
	class VectorRef 
	{
	protected:

		std::vector<DATA_ELEMENT> *buffer;

	public:

		VectorRef();
		~VectorRef();

		VectorRef(std::vector<DATA_ELEMENT> *buffer);

		VectorRef& operator = (const VectorRef &other);

		const Ceng::INT32 MaxIndex() const;

		const Ceng::BOOL operator == (const VectorRef &other) const;

		const Ceng::BOOL operator != (const VectorRef &other) const;

		const Ceng::BOOL operator == (const std::vector<DATA_ELEMENT> *other) const;

		const Ceng::BOOL operator != (const std::vector<DATA_ELEMENT> *other) const;

		DATA_ELEMENT* GetPointer(const Ceng::INT32 offset) const;

		void Insert(const Ceng::INT32 startPos,const Ceng::INT32 amount,const Ceng::UINT8 value);

		void Erase(const Ceng::INT32 startPos,const Ceng::INT32 endPos);
	};

	template<class DATA_ELEMENT>
	VectorRef<DATA_ELEMENT>::VectorRef()
	{
		buffer = nullptr;
	}

	template<class DATA_ELEMENT>
	VectorRef<DATA_ELEMENT>::~VectorRef()
	{
	}

	template<class DATA_ELEMENT>
	VectorRef<DATA_ELEMENT>::VectorRef(std::vector<DATA_ELEMENT> *buffer) : buffer(buffer)
	{
	}

	template<class DATA_ELEMENT>
	VectorRef<DATA_ELEMENT>& VectorRef<DATA_ELEMENT>::operator = (const VectorRef &other)
	{
		buffer = other.buffer;

		return *this;
	}

	template<class DATA_ELEMENT>
	const Ceng::INT32 VectorRef<DATA_ELEMENT>::MaxIndex() const
	{
		return buffer->size()-1;
	}

	template<class DATA_ELEMENT>
	const Ceng::BOOL VectorRef<DATA_ELEMENT>::operator == (const VectorRef &other) const
	{
		return buffer == other.buffer;
	}

	template<class DATA_ELEMENT>
	const Ceng::BOOL VectorRef<DATA_ELEMENT>::operator != (const VectorRef &other) const
	{
		return !(*this == other);
	}

	template<class DATA_ELEMENT>
	const Ceng::BOOL VectorRef<DATA_ELEMENT>::operator == (const std::vector<DATA_ELEMENT> *other) const
	{
		return buffer == other;
	}

	template<class DATA_ELEMENT>
	const Ceng::BOOL VectorRef<DATA_ELEMENT>::operator != (const std::vector<DATA_ELEMENT> *other) const
	{
		return !(*this == other);
	}

	template<class DATA_ELEMENT>
	DATA_ELEMENT* VectorRef<DATA_ELEMENT>::GetPointer(const Ceng::INT32 offset) const
	{
		return &(*buffer)[offset];
	}

	template<class DATA_ELEMENT>
	void VectorRef<DATA_ELEMENT>::Insert(const Ceng::INT32 startPos,const Ceng::INT32 amount,const Ceng::UINT8 value)
	{
		buffer->insert(buffer->begin()+startPos,amount,value);
	}

	template<class DATA_ELEMENT>
	void VectorRef<DATA_ELEMENT>::Erase(const Ceng::INT32 startPos,const Ceng::INT32 endPos)
	{
		buffer->erase(buffer->begin()+startPos,buffer->begin()+endPos);
	}

	//*****************************************************************************************
	// Class ConstVectorRef

	template<class DATA_ELEMENT>
	class ConstVectorRef 
	{
	protected:

		const std::vector<DATA_ELEMENT> *buffer;

	public:

		ConstVectorRef();
		~ConstVectorRef();

		ConstVectorRef(const std::vector<DATA_ELEMENT> *buffer);

		const Ceng::INT32 MaxIndex() const;

		const Ceng::BOOL operator == (const ConstVectorRef &other) const;

		const Ceng::BOOL operator != (const ConstVectorRef &other) const;

		const Ceng::BOOL operator == (const std::vector<DATA_ELEMENT> *other) const;

		const Ceng::BOOL operator != (const std::vector<DATA_ELEMENT> *other) const;

		const DATA_ELEMENT* GetPointer(const Ceng::INT32 offset) const;
	};

	template<class DATA_ELEMENT>
	ConstVectorRef<DATA_ELEMENT>::ConstVectorRef()
	{
		buffer = nullptr;
	}

	template<class DATA_ELEMENT>
	ConstVectorRef<DATA_ELEMENT>::~ConstVectorRef()
	{
	}

	template<class DATA_ELEMENT>
	ConstVectorRef<DATA_ELEMENT>::ConstVectorRef(const std::vector<DATA_ELEMENT> *buffer) : buffer(buffer)
	{
	}

	template<class DATA_ELEMENT>
	const Ceng::INT32 ConstVectorRef<DATA_ELEMENT>::MaxIndex() const
	{
		return buffer->size()-1;
	}

	template<class DATA_ELEMENT>
	const Ceng::BOOL ConstVectorRef<DATA_ELEMENT>::operator == (const ConstVectorRef &other) const
	{
		return buffer == other.buffer;
	}

	template<class DATA_ELEMENT>
	const Ceng::BOOL ConstVectorRef<DATA_ELEMENT>::operator != (const ConstVectorRef &other) const
	{
		return !(*this == other);
	}

	template<class DATA_ELEMENT>
	const Ceng::BOOL ConstVectorRef<DATA_ELEMENT>::operator == (const std::vector<DATA_ELEMENT> *other) const
	{
		return buffer == other;
	}

	template<class DATA_ELEMENT>
	const Ceng::BOOL ConstVectorRef<DATA_ELEMENT>::operator != (const std::vector<DATA_ELEMENT> *other) const
	{
		return !(*this == other);
	}

	template<class DATA_ELEMENT>
	const DATA_ELEMENT* ConstVectorRef<DATA_ELEMENT>::GetPointer(const Ceng::INT32 offset) const
	{
		if (offset < 0)
		{
			return nullptr;
		}

		return &(*buffer)[offset];
	}
}

#endif