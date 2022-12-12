/*****************************************************************************
*
* x86-move.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_MOVE_H
#define X86_MOVE_H

#include "x86-two-form-alu.h"

namespace X86
{
	class RegisterOperand;
	class MemoryOperand;
	class ImmediateOperand;

	class MoveInstruction : public TwoForm_ALU
	{
	protected:

		static const Ceng::UINT8 opcode_rm8_r8 = 0x88;
		static const Ceng::UINT8 opcode_rm32_r32 = 0x89;

		static const Ceng::UINT8 opcode_r8_rm8 = 0x8a;
		static const Ceng::UINT8 opcode_r32_rm32 = 0x8b;

		static const Ceng::UINT8 opcode_r8_imm8 = 0xb0;
		static const Ceng::UINT8 opcode_r32_imm32 = 0xb8;

		static const Ceng::UINT8 opcode_rm8_imm8 = 0xc6;
		static const Ceng::UINT8 opcode_rm32_imm32 = 0xc7;

	public:
		MoveInstruction();

		virtual ~MoveInstruction();

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *dest,
											const Operand *source) const override;

	protected:

		const Ceng::CRESULT Select_R_I(BuildParams *params,
											EncodeData *encodeData,const RegisterOperand *dest,
											const ImmediateOperand *source) const;

		const Ceng::CRESULT Select_M_I(BuildParams *params,
											EncodeData *encodeData,const MemoryOperand *dest,
											const ImmediateOperand *source) const;
	};

}

#endif