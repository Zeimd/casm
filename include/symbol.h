/*****************************************************************************
*
* symbol.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_SYMBOL_H
#define X86_SYMBOL_H

#include <datatypes/basic-types.h>
#include <datatypes/boolean.h>
#include <datatypes/ce-string.h>
#include <datatypes/temp-ptr.h>

namespace X86
{
	class DataItem;
	class FunctionBuilder;
	class ObjectFunction;

	class Symbol
	{
	public:

		enum TYPE
		{
			UNKNOWN = 0 ,
			DATA = 1 ,
			FUNCTION = 2 ,
			OBJECT_FUNCTION = 4 ,

			TYPE_FORCE_32B = 1 << 30 ,
		};

	protected:
		Ceng::UINT32 refCount;
		Ceng::BOOL defined;
		Ceng::BOOL external;

		/**
		 * Offset of the symbol in its section.
		 */
		Ceng::INT64 offset;

		TYPE type;
	public:

		Ceng::String name;

		Symbol();	

		Symbol(const Ceng::String &name);
		Symbol(const Ceng::String &name,const TYPE type,const Ceng::BOOL defined,
					const Ceng::BOOL external);
			
		virtual ~Symbol();

		const Ceng::BOOL IsDefined() const;
		const Ceng::BOOL IsExternal() const;

		const Ceng::INT64 Offset() const;
		void SetOffset(const Ceng::INT64 offset);

		void MarkDefined();
	
		void IncRefCount();
		void DecRefCount();
		
		void ResetRefCount();

		const Ceng::UINT32 RefCount() const;
	
		const TYPE Type() const;

		Ceng::TempPtr<DataItem> AsData() const;
		Ceng::TempPtr<FunctionBuilder> AsFunction() const;
		Ceng::TempPtr<ObjectFunction> AsObjectFunction() const;
		
	};

	inline const Ceng::BOOL Symbol::IsDefined() const
	{
		return defined;
	}

	inline const Ceng::BOOL Symbol::IsExternal() const
	{
		return external;
	}

	inline void Symbol::MarkDefined()
	{
		defined = true;
	}

	inline void Symbol::IncRefCount()
	{
		refCount++;
	}

	inline void Symbol::DecRefCount()
	{
		refCount--;
	}

	inline void Symbol::ResetRefCount()
	{
		refCount = 0;
	}

	inline const Ceng::UINT32 Symbol::RefCount() const
	{
		return refCount;
	}

	inline const Symbol::TYPE Symbol::Type() const
	{
		return type;
	}

	inline const Ceng::INT64 Symbol::Offset() const
	{
		return offset;
	}

	inline void Symbol::SetOffset(const Ceng::INT64 offset)
	{
		this->offset = offset;
	}

}


#endif