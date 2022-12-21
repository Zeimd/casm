/*****************************************************************************
*
* x86-regs-alu-adr.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_REGS_ALU_ADR_H
#define X86_REGS_ALU_ADR_H

#include "x86-register-op.h"

namespace X86
{
	extern const RegisterOperand RIP;

	/**
	 * Special case as memory operand because of aliasing with RSP.
	 */
	extern const RegisterOperand R12;

	/**
	 * Special case as memory operand because of aliasing with RBP.
	 */
	extern const RegisterOperand R13;

	extern const RegisterOperand ESP;

	extern const RegisterOperand EBP;
}

#endif