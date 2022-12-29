/*****************************************************************************
*
* symbol.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_SYMBOL_H
#define X86_SYMBOL_H

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/boolean.h>
#include <ceng/datatypes/ce-string.h>

#include "enums/x86-section-type.h"
#include "enums/x86-symbol-type.h"

namespace Casm
{
	class DataItem;
	class FunctionBuilder;
	class ObjectFunction;

	class Section;

	class Symbol
	{
	protected:
		Ceng::UINT32 refCount;
		Ceng::BOOL defined;
		Ceng::BOOL external;

		// Offset of the symbol in its section.
		Ceng::INT64 offset;

		X86::SymbolType::value type;
		
		Section* section;

	protected:

		Symbol();

	public:

		Ceng::String name;


		Symbol(const Ceng::String& name, Section* section, 
			const X86::SymbolType::value type,
			const Ceng::BOOL defined, const Ceng::BOOL external);
			
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
	
		const X86::SymbolType::value Type() const;

		DataItem* AsData() const;
		FunctionBuilder* AsFunction() const;
		ObjectFunction* AsObjectFunction() const;
		
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

	inline const X86::SymbolType::value Symbol::Type() const
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