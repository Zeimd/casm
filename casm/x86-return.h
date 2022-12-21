
/*****************************************************************************
*
* x86-return.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_RETURN_H
#define X86_RETURN_H

#include "x86-instruction.h"

namespace X86
{
	class ReturnInstruction : public Instruction
	{
		const Ceng::UINT8 opcode_bare;
		const Ceng::UINT8 opcode_imm16;

	public:

		ReturnInstruction(const Ceng::UINT8 opcode_bare,const Ceng::UINT8 opcode_imm16);

		virtual ~ReturnInstruction();

	public:

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,EncodeData *encodeData) const override;

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *operand) const override;
	};
}

#endif