/*****************************************************************************
*
* x86-alu-incr.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_ALU_INCR_H
#define X86_ALU_INCR_H

#include "x86-two-form-alu.h"

namespace X86
{
	class ALU_Incr : public TwoForm_ALU
	{
	protected:
		static const Ceng::UINT8 opcode_rm8 = 0xfe;
		static const Ceng::UINT8 opcode_rm32 = 0xff;

		const Ceng::UINT8 opcode_r32;

		const Ceng::UINT8 option;

	public:
		ALU_Incr(const Ceng::UINT8 opcode_r32,const Ceng::UINT8 option);

		virtual ~ALU_Incr();

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *operand) const override;

	protected:

		const Ceng::CRESULT Select_R(BuildParams *params,EncodeData *encodeData,
											const RegisterOperand *operand) const;

		const Ceng::CRESULT Select_M(BuildParams *params,EncodeData *encodeData,
											const MemoryOperand *operand) const;
	};
}

#endif