/*****************************************************************************
*
* code-element.h
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#ifndef X86_CODE_ELEMENT_H
#define X86_CODE_ELEMENT_H

#include <ceng/datatypes/basic-types.h>

#include "symbol-ref.h"

#include <ostream>

namespace X86
{
	class BuildParams;
}

namespace Casm
{
	class Label;
	class ProgramBuilder;

	class CodeElement
	{
	public:
		enum TYPE
		{
			BASIC_BLOCK = 1 ,
			CONDITION_JUMP = 2 ,
			LABEL = 3,

			FORCE_32B = 1 << 30 ,
		};

	protected:
		Ceng::UINT32 position;
		TYPE type;

		CodeElement() : offset(0),position(0),type(BASIC_BLOCK)
		{
		}

	public:

		Ceng::INT64 offset;

		CodeElement(const Ceng::UINT32 position);

		virtual ~CodeElement();	

		// Build everything that's possible without accessing other code elements.
		virtual Ceng::CRESULT PreBuild(X86::BuildParams* params);

		virtual Ceng::CRESULT Build(X86::BuildParams *params,
									 const std::vector<std::shared_ptr<Label>> &labels,
									 const std::vector<std::shared_ptr<CodeElement>> &codeList);
	
		virtual Ceng::CRESULT Append(std::vector<Ceng::UINT8> &destBuffer) const;

		Ceng::UINT32 Position() const;

		TYPE Type() const;

		virtual Ceng::UINT32 SizeBytes() const;

		virtual void Print(std::wostream& out) const;

		virtual const Ceng::String Name() const;
	};

	inline Ceng::UINT32 CodeElement::Position() const
	{
		return position;
	}

	inline CodeElement::TYPE CodeElement::Type() const
	{
		return type;
	}
}

#endif