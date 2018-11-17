/*****************************************************************************
*
* code-label.h
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#ifndef X86_CODE_LABEL_H
#define X86_CODE_LABEL_H

#include <datatypes/basic-types.h>
#include <datatypes/boolean.h>
#include <datatypes/ce-string.h>
#include <datatypes/return-val.h>

namespace X86
{
	class CodeElement;

	class Label
	{
	protected:
		Ceng::BOOL undefined;
		Ceng::String name;
		CodeElement *target;

		Label()
		{
		}
	public:
		

		Label(const Ceng::String name,const Ceng::BOOL undefined);

		~Label();
		
		CodeElement* Target() const;	

		Ceng::BOOL CompareName(const Ceng::String &test) const;

		Ceng::BOOL Undefined() const;

		void MarkDefined();

		Ceng::CRESULT SetTarget(CodeElement *target);
	};
}

#endif