/*****************************************************************************
*
* parser-memory.h
*
* By Jari Korkala 5/2014
*
*****************************************************************************/

#ifndef CASM_PARSER_MEMORY_H
#define CASM_PARSER_MEMORY_H

#include "parser-operator.h"

#include "parser-register.h"
#include "parser-literal.h"

namespace Casm
{
	class ParserMemory : public ParserOperand
	{
	protected:

		const X86::RegisterOperand *baseReg;
		const X86::RegisterOperand *indexReg;

		const Ceng::UINT32 indexScale;
		const Ceng::INT32 offset;

		const X86::OPERAND_SIZE::value opSize;

		TokenData data;

	public:

		ParserMemory(const X86::RegisterOperand *baseReg,const X86::RegisterOperand *indexReg,
						const Ceng::UINT32 indexScale,const Ceng::INT32 offset,
						const X86::OPERAND_SIZE::value opSize,
						const TokenData &data);

		virtual ~ParserMemory();

		const X86::RegisterOperand* BaseReg() const;
	
		const X86::RegisterOperand* IndexReg() const;

		const Ceng::UINT32 IndexScale() const;

		const Ceng::INT32 Offset() const;

		const X86::OPERAND_SIZE::value OpSize() const;

		virtual const std::shared_ptr<ParserOperand> SizeCast(ParserState *state,
																std::shared_ptr<ParserOperand> right_this,
																const Ceng::UINT32 newSize) override;
	};

	class ParserOp_Memory : public ParserOperator
	{
	protected:

	public:

		ParserOp_Memory(const TokenData data);

		virtual ~ParserOp_Memory();

		virtual const std::shared_ptr<ParserOperand> LocalAction(ParserState *state,
																std::shared_ptr<ParserOperand> left,
																std::shared_ptr<ParserOperand> right) override;
	};
}

#endif