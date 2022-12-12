/*****************************************************************************
*
* x86-bit-test.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_BIT_TEST_H
#define X86_BIT_TEST_H

#include "x86-two-form-alu.h"

namespace X86
{
	class ALU_BitTest : public TwoForm_ALU
	{
	protected:

		static const Ceng::UINT8 opcode_imm = 0xba;
		const Ceng::UINT8 immediateSwitch;

		const Ceng::UINT8 opcode_reg;
	public:

		ALU_BitTest(const Ceng::UINT8 opcode_reg,const Ceng::UINT8 immediateSwitch);

		virtual ~ALU_BitTest();

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