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
#include <ceng/datatypes/ce-string.h>

#include <ceng/datatypes/return-val.h>

#include <vector>
#include <ostream>

namespace X86
{
	class BuildParams;
}

namespace Casm
{
	class Label;
	class ProgramBuilder;
	class RelocationData;

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
		Ceng::INT32 position;

		TYPE type;

		Ceng::INT64 offset;


		CodeElement() : offset(0),position(0),type(BASIC_BLOCK)
		{
		}

	public:


		CodeElement(TYPE type, const Ceng::INT32 position);

		virtual ~CodeElement();	

		// Build everything that's possible without accessing other code elements.
		virtual Ceng::CRESULT PreBuild(X86::BuildParams* params);

		virtual Ceng::CRESULT Build(X86::BuildParams *params,
									 const std::vector<std::shared_ptr<Label>> &labels,
									 const std::vector<std::shared_ptr<CodeElement>> &codeList);
	
		virtual Ceng::CRESULT Append(std::vector<Ceng::UINT8> &destBuffer) const;

		virtual Ceng::CRESULT AppendRelocationData(std::vector<RelocationData>& out) const;

		virtual Ceng::CRESULT AddRelocationData(std::shared_ptr<RelocationData>& data);

		Ceng::INT32 Position() const;

		TYPE Type() const;

		Ceng::UINT64 Offset() const;

		virtual void SetOffset(const Ceng::UINT64 offset);

		virtual Ceng::UINT32 SizeBytes() const;

		virtual void Print(std::wostream& out) const;

		virtual const Ceng::String Name() const;
	};

	inline Ceng::INT32 CodeElement::Position() const
	{
		return position;
	}

	inline CodeElement::TYPE CodeElement::Type() const
	{
		return type;
	}

	inline Ceng::UINT64 CodeElement::Offset() const
	{
		return offset;
	}



}

#endif