/*****************************************************************************
*
* x86-basic-block.h
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#ifndef X86_BASIC_BLOCK_H
#define X86_BASIC_BLOCK_H

#include "code-element.h"

#include "code-line.h"

#include "relocation-data.h"

namespace Casm
{
	// A block of code that is constant in size, and doesn't
	// have any jumps from or to it.
	class BasicBlock : public CodeElement
	{
	protected:

		std::vector<std::shared_ptr<Casm::CodeLine>> lines;
		std::vector<Ceng::UINT8> codeBuffer;

		std::vector<std::shared_ptr<Casm::RelocationData>> relocationData;

		BasicBlock()
		{
		}

	public:		
		
		BasicBlock(const Ceng::UINT32 position);

		~BasicBlock() override;

		Ceng::CRESULT AddLine(std::shared_ptr<CodeLine>& newLine);

		Ceng::CRESULT PreBuild(X86::BuildParams* params) override;

		Ceng::CRESULT Build(X86::BuildParams *params,
			const std::vector<std::shared_ptr<Label>> &labels,
			const std::vector<std::shared_ptr<CodeElement>> &codeList) override;

		Ceng::UINT32 SizeBytes() const override;
	
		Ceng::CRESULT Append(std::vector<Ceng::UINT8> &destBuffer) const override;

		Ceng::CRESULT AppendRelocationData(std::vector<RelocationData>& out) const override;

		Ceng::CRESULT AddRelocationData(std::shared_ptr<RelocationData>& data) override;

		void Print(std::wostream& out) const override;
	};
}


#endif