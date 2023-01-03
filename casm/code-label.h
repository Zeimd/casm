/*****************************************************************************
*
* code-label.h
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#ifndef X86_CODE_LABEL_H
#define X86_CODE_LABEL_H

#include "code-element.h"

#include "symbol.h"

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/boolean.h>
#include <ceng/datatypes/ce-string.h>
#include <ceng/datatypes/return-val.h>

namespace Casm
{
	class CodeElement;
	class Section;
	class Symbol;

	class CodeLabel : public CodeElement
	{
	protected:

		// Next code element following the label
		std::shared_ptr<CodeElement> target;

		CodeLabel() : symbol(nullptr), target(nullptr)
		{

		}
	public:

		std::shared_ptr<Symbol> symbol;


		CodeLabel(const Ceng::UINT32 position,std::shared_ptr<Symbol>& symbol);

		~CodeLabel();
		
		std::shared_ptr<CodeElement> Target() const;	

		Ceng::BOOL CompareName(const Ceng::String &test) const;

		Ceng::CRESULT SetTarget(std::shared_ptr<CodeElement>& target);

		const Ceng::String Name() const override
		{
			return symbol->name;
		}

		void Print(std::wostream& out) const override;

		void SetOffset(const Ceng::UINT64 offset) override;
	};
}

#endif