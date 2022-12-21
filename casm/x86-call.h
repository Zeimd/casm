/*****************************************************************************
*
* x86-call.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_CALL_H
#define X86_CALL_H

#include "x86-instruction.h"

namespace X86
{
	class RegisterOperand;
	class MemoryOperand;
	class ImmediateOperand;

	class CallInstruction : public Instruction
	{
		static const Ceng::UINT8 opcode_relative = 0xe8;
		static const Ceng::UINT8 opcode_absolute = 0xff;

	public:

		CallInstruction();

		virtual ~CallInstruction();
	
		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *operand) const;

	protected:

		const Ceng::CRESULT Encode_AbsoluteNear_R(BuildParams *params,EncodeData *encodeData,
												const RegisterOperand *registerOp) const;

		const Ceng::CRESULT Encode_AbsoluteNear_M(BuildParams *params,EncodeData *encodeData,
												const MemoryOperand *memoryOp) const;

		const Ceng::CRESULT Encode_Relative(BuildParams *params,EncodeData *encodeData,
											const ImmediateOperand *immediate) const;
	};
}

#endif