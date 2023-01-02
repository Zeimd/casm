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

CodeElement::CodeElement(const Ceng::UINT32 position) : position(position)
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