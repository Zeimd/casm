/*****************************************************************************
*
* x86-two-form-alu.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_TWO_FORM_ALU_H
#define X86_TWO_FORM_ALU_H

#include "x86-instruction.h"

#include "enums/x86-operand-sizes.h"

#include <datatypes/boolean.h>

namespace X86
{
	class RegisterOperand;
	class MemoryOperand;
	class ImmediateOperand;

	class TwoForm_ALU : public Instruction
	{
	protected:
		TwoForm_ALU();
	public:

		virtual ~TwoForm_ALU();
		
	protected:
		const Ceng::CRESULT ValidateOperands_R_R(BuildParams *params,const RegisterOperand *dest,
										const RegisterOperand *source) const;

		const Ceng::BOOL ValidateRegisterOp(BuildParams *params,const RegisterOperand *registerOp) const;

		void EncodeOperandSize(BuildParams *params,EncodeData *encodeData,
								const OPERAND_SIZE::value opSize) const;

		void Opcode_RM_R(BuildParams *params,EncodeData *encodeData,
								const OPERAND_SIZE::value opSize,
								const Ceng::UINT8 opcode_rm8_r8,
								const Ceng::UINT8 opcode_rm32_r32) const;		

		const Ceng::CRESULT Standard_R_R(BuildParams *params,EncodeData *encodeData,
											const Ceng::UINT8 opcode_rm8_r8,
											const Ceng::UINT8 opcode_rm32_r32,
											const RegisterOperand *dest,
											const RegisterOperand *source) const;

		const Ceng::CRESULT Standard_M_R(BuildParams *params,EncodeData *encodeData,
											const Ceng::UINT8 opcode_rm8_r8,
											const Ceng::UINT8 opcode_rm32_r32,
											const MemoryOperand *dest,
											const RegisterOperand *source) const;

		const Ceng::CRESULT Standard_R_M(BuildParams *params,EncodeData *encodeData,
											const Ceng::UINT8 opcode_r8_rm8,
											const Ceng::UINT8 opcode_r32_rm32,
											const RegisterOperand *dest,
											const MemoryOperand *source) const;
		
	};
}

#endif