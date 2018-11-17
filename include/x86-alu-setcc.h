/*****************************************************************************
*
* x86-alu-setcc.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_ALU_SETCC_H
#define X86_ALU_SETCC_H

#include "x86-instruction.h"

namespace X86
{
	class RegisterOperand;
	class MemoryOperand;

	class SetCC : public Instruction
	{
	protected:

		const Ceng::UINT8 opcode;

	public:

		SetCC(const Ceng::UINT8 opcode);

		virtual ~SetCC();

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