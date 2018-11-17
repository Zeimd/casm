/*****************************************************************************
*
* x86-alu-shift.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_ALU_SHIFT_H
#define X86_ALU_SHIFT_H

#include "x86-two-form-alu.h"

namespace X86
{
	class ALU_Shift : public TwoForm_ALU
	{
	protected:

		static const Ceng::UINT8 opcode_r8_one = 0xd0;
		static const Ceng::UINT8 opcode_r8_CL = 0xd2;
		static const Ceng::UINT8 opcode_r8_imm8 = 0xc0;

		static const Ceng::UINT8 opcode_r32_one = 0xd1;
		static const Ceng::UINT8 opcode_r32_CL = 0xd3;
		static const Ceng::UINT8 opcode_r32_imm8 = 0xc1;
		
		const Ceng::UINT8 option;

	public:

		ALU_Shift(const Ceng::UINT8 option);

		virtual ~ALU_Shift();

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *dest,
											const Operand *source) const override;

	protected:

		const Ceng::CRESULT Select_R_R(BuildParams *params,EncodeData *encodeData,
											const RegisterOperand *dest,
											const RegisterOperand *source) const;

		const Ceng::CRESULT Select_R_I(BuildParams *params,EncodeData *encodeData,
											const RegisterOperand *dest,
											const ImmediateOperand *source) const;

		const Ceng::CRESULT Select_M_R(BuildParams *params,EncodeData *encodeData,
											const MemoryOperand *dest,
											const RegisterOperand *source) const;

		const Ceng::CRESULT Select_M_I(BuildParams *params,EncodeData *encodeData,
											const MemoryOperand *dest,
											const ImmediateOperand *source) const;
	};
}

#endif
