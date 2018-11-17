/*****************************************************************************
*
* x86-alu-xchg.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_ALU_XCHG_H
#define X86_ALU_XCHG_H

#include "x86-two-form-alu.h"

namespace X86
{
	class Exchange : public TwoForm_ALU
	{
	protected:
		
		static const Ceng::UINT8 opcode_EAX_r32 = 0x90;

		static const Ceng::UINT8 opcode_r8_rm8 = 0x86;
		static const Ceng::UINT8 opcode_r32_rm32 = 0x87;

	public:

		Exchange();
		virtual ~Exchange();

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *dest,
											const Operand *source) const override;

	protected:
		
		const Ceng::CRESULT Select_R_R(BuildParams *params,
											EncodeData *encodeData,const RegisterOperand *dest,
											const RegisterOperand *source) const;

		const Ceng::CRESULT Select_R_M(BuildParams *params,
											EncodeData *encodeData,const RegisterOperand *dest,
											const MemoryOperand *source) const;
	};
}

#endif