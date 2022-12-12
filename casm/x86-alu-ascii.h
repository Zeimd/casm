/*****************************************************************************
*
* x86-alu-ascii.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_ALU_ASCII_H
#define X86_ALU_ASCII_H

#include "x86-instruction.h"

namespace X86
{
	class ImmediateOperand;

	class ALU_Ascii : public Instruction
	{
	protected:
		const Ceng::UINT8 opcode;

	public:

		ALU_Ascii(const Ceng::UINT8 opcode);

		virtual ~ALU_Ascii();

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,EncodeData *encodeData) const override;

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *operand) const override;

	protected:

		const Ceng::CRESULT Select_I(BuildParams *params,EncodeData *encodeData,
											const ImmediateOperand *operand) const;
	};
}

#endif