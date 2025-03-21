/*****************************************************************************
*
* code-element.cpp
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#include "code-element.h"

#include "code-label.h"

#include "build-params.h"

using namespace Casm;

CodeElement::CodeElement(CodeElement::TYPE type, const Ceng::INT32 position) 
	: type(type), position(position), offset(0)
{
}

CodeElement::~CodeElement()
{
}

void CodeElement::Print(std::wostream& out) const
{
	out << "CodeElement" << std::endl;
}

const Ceng::String CodeElement::Name() const
{
	return "CodeElement";
}


Ceng::CRESULT CodeElement::PreBuild(X86::BuildParams* params)
{
	return Ceng::CE_OK;
}

Ceng::CRESULT CodeElement::Build(X86::BuildParams *params,
								 const std::vector<std::shared_ptr<Label>> &labels,
								 const std::vector<std::shared_ptr<CodeElement>> &codeList)
{
	return Ceng::CE_OK;
}

Ceng::CRESULT CodeElement::Append(std::vector<Ceng::UINT8> &destBuffer) const
{
	return Ceng::CE_OK;
}

Ceng::UINT32 CodeElement::SizeBytes() const
{
	return 0;
}

void CodeElement::SetOffset(const Ceng::UINT64 offset)
{
	this->offset = offset;
}

Ceng::CRESULT CodeElement::AppendRelocationData(std::vector<RelocationData>& out) const
{
	return Ceng::CE_OK;
}

Ceng::CRESULT CodeElement::AddRelocationData(std::shared_ptr<RelocationData>& data)
{
	return Ceng::CE_OK;
}
