/*****************************************************************************
*
* x86-alu-bswap.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_ALU_BSWAP_H
#define X86_ALU_BSWAP_H

#include "x86-two-form-alu.h"

namespace X86
{
	class ALU_ByteSwap : public TwoForm_ALU
	{
	protected:
		static const Ceng::UINT8 opcode = 0xc8;

	public:
		ALU_ByteSwap();

		virtual ~ALU_ByteSwap();

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *operand) const override;

	protected:

		const Ceng::CRESULT Select_R(BuildParams *params,EncodeData *encodeData,
											const RegisterOperand *operand) const;
	};
}

#endif