/*****************************************************************************
*
* x86-simple-instruction.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_SIMPLE_INSTRUCTION_H
#define X86_SIMPLE_INSTRUCTION_H

#include "x86-instruction.h"

#include "enums/x86-opcode-escape.h"
#include "enums/x86-prefix-bytes.h"

namespace X86
{
	class SimpleInstruction : public Instruction
	{
	protected:
		const PREFIX_BYTE::value prefixByte;

		const OPCODE_ESCAPE::value escapeCode;
		const Ceng::UINT8 opcode;

	public:
		SimpleInstruction(const PREFIX_BYTE::value prefixByte,const OPCODE_ESCAPE::value escapeCode,
							const Ceng::UINT8 opcode);

		SimpleInstruction(const Ceng::UINT8 opcode);

		virtual ~SimpleInstruction();

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,EncodeData *encodeData) const;

	};
}

#endif