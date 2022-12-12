/*****************************************************************************
*
* sse-sign-mask.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_SSE_SIGN_MASK_H
#define X86_SSE_SIGN_MASK_H

#include "x86-instruction.h"
#include "x86-register-op.h"

namespace X86
{
	class SSE_SignMask : public Instruction
	{
	protected:
		const Ceng::UINT8 prefixByte;
		const Ceng::UINT8 opcode;

	public:
		SSE_SignMask(const Ceng::UINT8 prefixByte,const Ceng::UINT8 opcode)
			: prefixByte(prefixByte),opcode(opcode)
		{
		}

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *dest,
											const Operand *source) const;
	
	protected:

		const Ceng::CRESULT Select_R_R(BuildParams *params,EncodeData *encodeData,
									const RegisterOperand *dest,
									const RegisterOperand *source) const;
	};
}

#endif