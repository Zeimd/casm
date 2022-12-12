/*****************************************************************************
*
* x86-add-variant.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_ADD_VARIANT_H
#define X86_ADD_VARIANT_H

#include "x86-two-form-alu.h"

namespace X86
{
	class AddTypeInstruction : public TwoForm_ALU
	{
	public:		
		static const Ceng::UINT8 opcode_rm8_imm8 = 0x80;
		
		static const Ceng::UINT8 opcode_rm32_imm32 = 0x81;
		static const Ceng::UINT8 opcode_rm32_imm8 = 0x83;
		
		const Ceng::UINT8 opcode_rm8_r8; // dest = reg/mem
		const Ceng::UINT8 opcode_r8_rm8; // source = reg/mem

		const Ceng::UINT8 opcode_rm32_r32; // dest = reg/mem
		const Ceng::UINT8 opcode_r32_rm32; // source = reg/mem
		
		const Ceng::UINT8 opcode_AL_imm8; // dest = AL
		const Ceng::UINT8 opcode_EAX_imm32; // dest = EAX

		const Ceng::UINT8 immediateSwitch;

		/**
		 * Must be defined in the header.
		 */
		AddTypeInstruction(const Ceng::UINT8 opcode_rm32_r32,const Ceng::UINT8 opcode_r32_rm32,
						const Ceng::UINT8 opcode_rm8_r8,const Ceng::UINT8 opcode_r8_rm8,
						const Ceng::UINT8 opcode_AL_imm8,const Ceng::UINT8 opcode_EAX_imm32,
						const Ceng::UINT8 immediateSwitch);

		virtual ~AddTypeInstruction();

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