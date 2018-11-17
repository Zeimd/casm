/*****************************************************************************
*
* x86-wide-shift.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_WIDE_SHIFT_H
#define X86_WIDE_SHIFT_H

#include "x86-two-form-alu.h"

namespace X86
{
	class ALU_WideShift : public TwoForm_ALU
	{
	protected:

		const Ceng::UINT8 opcode_imm8;
		const Ceng::UINT8 opcode_CL;

	public:

		ALU_WideShift(const Ceng::UINT8 opcode_imm8,const Ceng::UINT8 opcode_CL);

		virtual ~ALU_WideShift();

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *dest,
											const Operand *source1,
											const Operand *source2) const override;

	protected:

		const Ceng::CRESULT Select_R_R_R(BuildParams *params,EncodeData *encodeData,
											const RegisterOperand *dest,
											const RegisterOperand *source1,
											const RegisterOperand *source2) const;

		const Ceng::CRESULT Select_M_R_R(BuildParams *params,EncodeData *encodeData,
											const MemoryOperand *dest,
											const RegisterOperand *source1,
											const RegisterOperand *source2) const;

		const Ceng::CRESULT Select_R_R_I(BuildParams *params,EncodeData *encodeData,
											const RegisterOperand *dest,
											const RegisterOperand *source1,
											const ImmediateOperand *source2) const;

		const Ceng::CRESULT Select_M_R_I(BuildParams *params,EncodeData *encodeData,
											const MemoryOperand *dest,
											const RegisterOperand *source1,
											const ImmediateOperand *source2) const;


	};
}

#endif