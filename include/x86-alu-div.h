/*****************************************************************************
*
* x86-alu-div.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_ALU_DIV_H
#define X86_ALU_DIV_H

#include "x86-two-form-alu.h"

namespace X86
{
	class ALU_Div : public TwoForm_ALU
	{
	protected:

		static const Ceng::UINT8 opcode_rm8 = 0xf6;
		static const Ceng::UINT8 opcode_rm32 = 0xf7;

		const Ceng::UINT8 option;

	public:
		ALU_Div(const Ceng::UINT8 option);

		virtual ~ALU_Div();

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *operand) const;

	protected:

		const Ceng::CRESULT Select_R(BuildParams *params,EncodeData *encodeData,
											const RegisterOperand *operand) const;

		const Ceng::CRESULT Select_M(BuildParams *params,EncodeData *encodeData,
											const MemoryOperand *operand) const;
	};
}

#endif