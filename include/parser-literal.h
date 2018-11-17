/*****************************************************************************
*
* parser-literal.h
*
* By Jari Korkala 5/2014
*
*****************************************************************************/

#ifndef CASM_PARSER_LITERAL_H
#define CASM_PARSER_LITERAL_H

#include "parser-operand.h"

#include "enums/x86-operand-sizes.h"

namespace Casm
{
	class ParserLiteral : public ParserOperand
	{
	protected:

		ParserLiteral() : ParserOperand(),opSize(X86::OPERAND_SIZE::IMPLICIT)
		{
		}

		const X86::OPERAND_SIZE::value opSize;

	public:

		virtual ~ParserLiteral()
		{
		}

		ParserLiteral(const Ceng::INT32 sizeBytes,const ParserBasicType::value datatype,
						const TokenData &data) : 
			ParserOperand(ParserToken::literal_value,datatype,sizeBytes,data),
				opSize(X86::OPERAND_SIZE::IMPLICIT)
		{
		}

		ParserLiteral(const Ceng::INT32 sizeBytes,const ParserBasicType::value datatype,
						const X86::OPERAND_SIZE::value opSize,
						const TokenData &data) : 
			ParserOperand(ParserToken::literal_value,datatype,sizeBytes,data),
				opSize(opSize)
		{
		}

		const X86::OPERAND_SIZE::value OpSize() const
		{
			return opSize;
		}

		virtual void ToBuffer(void *destBuffer) const=0;
	};

	
}

#endif