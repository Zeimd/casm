/*****************************************************************************
*
* x86-bit-scan.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_BIT_SCAN_H
#define X86_BIT_SCAN_H

#include "x86-two-form-alu.h"

namespace X86
{
	class ALU_BitScan : public TwoForm_ALU
	{
	protected:

		const Ceng::UINT8 opcode;

	public:
		ALU_BitScan(const Ceng::UINT8 opcode);

		virtual ~ALU_BitScan();

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *dest,
											const Operand *source) const override;

	protected:

		const Ceng::CRESULT Select_R_R(BuildParams *params,EncodeData *encodeData,
											const RegisterOperand *dest,
											const RegisterOperand *source) const;

		const Ceng::CRESULT Select_R_M(BuildParams *params,EncodeData *encodeData,
											const RegisterOperand *dest,
											const MemoryOperand *source) const;
	};
}

#endif