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

#include "enums/symbol-type.h"

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

		// Symbol is defined in this file
		Ceng::BOOL defined;
 
		// Symbol is visible outside of file
		Ceng::BOOL isGlobal;

		// Offset of the symbol in its section.
		Ceng::INT64 offset;

		SymbolType::value type;
		
		// NOTE: must be weak so that section can
		//       point to itself
		Section* section;

	protected:

		Symbol();

	public:

		Ceng::String name;

		Symbol(const Ceng::String& name, Section* section, 
			const SymbolType::value type,
			const Ceng::BOOL defined,const Ceng::BOOL isGlobal);
			
		virtual ~Symbol();

		const Ceng::BOOL IsDefined() const;
		const Ceng::BOOL IsExternal() const;
		const Ceng::BOOL IsGlobal() const;

		const Ceng::INT64 Offset() const;
		void SetOffset(const Ceng::INT64 offset);

		void MarkDefined(SymbolType::value type, Ceng::BOOL isGlobal);
	
		const SymbolType::value Type() const;

		void SetType(const SymbolType::value type);

		const Section* Section() const;

		void IncRefCount();
		void DecRefCount();
		
		void ResetRefCount();

		const Ceng::UINT32 RefCount() const;		
	};

	inline const Ceng::BOOL Symbol::IsDefined() const
	{
		return defined;
	}

	inline const Ceng::BOOL Symbol::IsGlobal() const
	{
		return isGlobal;
	}

	inline void Symbol::MarkDefined(SymbolType::value type, Ceng::BOOL isGlobal)
	{
		defined = true;

		this->type = type;
		this->isGlobal = isGlobal;
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

	inline const Ceng::INT64 Symbol::Offset() const
	{
		return offset;
	}

	inline void Symbol::SetOffset(const Ceng::INT64 offset)
	{
		this->offset = offset;
	}

	inline const SymbolType::value Symbol::Type() const
	{
		return type;
	}

	inline void Symbol::SetType(const SymbolType::value type)
	{
		if (this->type == SymbolType::unknown)
		{
			this->type = type;
		}
	}


	inline const Section* Symbol::Section() const
	{
		return section;
	}

}


#endif