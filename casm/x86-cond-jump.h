/*****************************************************************************
*
* x86-cond-jump.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_COND_JUMP_H
#define X86_COND_JUMP_H

#include "x86-instruction.h"

namespace X86
{
	class ImmediateOperand;

	class CondJumpInstruction : public Instruction
	{
	protected:
		const Ceng::UINT8 opcode_imm8;
		const Ceng::UINT8 opcode_imm32;
	public:

		/**
		 * Must be in the header.
		 */
		CondJumpInstruction(const Ceng::UINT8 opcode_imm8,const Ceng::UINT8 opcode_imm32)
			: opcode_imm8(opcode_imm8),opcode_imm32(opcode_imm32)
		{
		}

		virtual ~CondJumpInstruction()
		{
		}

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *operand) const;

	protected:

		const Ceng::CRESULT Select_I(BuildParams *params,EncodeData *encodeData,
										const ImmediateOperand *immediate) const;
	};
}

#endif