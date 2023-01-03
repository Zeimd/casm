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

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/boolean.h>
#include <ceng/datatypes/ce-string.h>
#include <ceng/datatypes/return-val.h>

namespace Casm
{
	class CodeElement;
	class Section;

	class Label : public CodeElement
	{
	protected:

		Ceng::BOOL undefined;
		Ceng::String name;

		// Visible outside the object file?
		bool isGlobal;

		// Section where the label is
		Section* section;

		// Next code element following the label
		std::shared_ptr<CodeElement> target;

		Label() : section(nullptr), target(nullptr), undefined(true), isGlobal(false)
		{

		}
	public:
		

		Label(const Ceng::UINT32 position,
			Section* section, const Ceng::String name,const Ceng::BOOL undefined,
			bool isGlobal);

		~Label();
		
		std::shared_ptr<CodeElement> Target() const;	

		Ceng::BOOL CompareName(const Ceng::String &test) const;

		Ceng::BOOL Undefined() const;

		bool IsGlobal() const;

		void MarkDefined();

		Ceng::CRESULT SetTarget(std::shared_ptr<CodeElement>& target);

		const Ceng::String Name() const override
		{
			return name;
		}

		void Print(std::wostream& out) const override;
	};
}

#endif