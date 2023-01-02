/*****************************************************************************
*
* basic-block.cpp
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#include "basic-block.h"

using namespace Casm;

BasicBlock::BasicBlock(const Ceng::UINT32 position) : CodeElement(position)
{
	type = BASIC_BLOCK;
}

BasicBlock::~BasicBlock()
{
}

Ceng::CRESULT BasicBlock::AddLine(std::shared_ptr<CodeLine>& newLine)
{
	lines.push_back(newLine);

	return Ceng::CE_OK;
}

Ceng::CRESULT BasicBlock::Build(X86::BuildParams *params,
								const std::vector<std::shared_ptr<Label>> &labels,
								const std::vector<std::shared_ptr<CodeElement>> &codeList)
{
	Ceng::CRESULT cresult;

	params->codeElement = this;

	for(size_t k=0;k<lines.size();k++)
	{
		cresult = lines[k]->Encode(params,codeBuffer);
		if (cresult != Ceng::CE_OK)
		{
			//codeBuffer.clear();
			return cresult;
		}

		// Store base offset for IP-relative addressing
	
		if (params->immRef != nullptr)
		{
			params->immRef->encodeOffset = params->out_immOffset;
			params->immRef->encodeSize = params->out_immSize;

			params->immRef->ConfigIPdelta(codeBuffer.size());
		}

		if (params->memRef != nullptr)
		{
			params->memRef->encodeOffset = params->out_dispOffset;
			params->memRef->encodeSize = params->out_dispSize;
		}

		params->Clean();

	}

	return Ceng::CE_OK;
}

Ceng::UINT32 BasicBlock::SizeBytes() const
{
	return codeBuffer.size();
}

Ceng::CRESULT BasicBlock::Append(std::vector<Ceng::UINT8> &destBuffer) const
{
	std::copy(codeBuffer.begin(),codeBuffer.end(),std::back_inserter(destBuffer));

	return Ceng::CE_OK;
}

void BasicBlock::Print(std::wostream& out) const 
{
	//out << "BasicBlock : size = " << lines.size() << std::endl;

	for (auto& x : lines)
	{
		x->Print(out);
	}
}