/*****************************************************************************
*
* x86-regs-alu.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_REGS_ALU_H
#define X86_REGS_ALU_H

#include "x86-register-op.h"

#include "x86-regs-alu-cl.h"

#include "x86-regs-alu-adr.h"

namespace X86
{
	// RIP : in "x86-regs-alu-adr.h"


	//***************************************************************************************
	// x64 64-bit register file

	extern const RegisterOperand RAX;

	extern const RegisterOperand RCX;

	extern const RegisterOperand RDX;

	extern const RegisterOperand RBX;

	extern const RegisterOperand RSP;

	extern const RegisterOperand RBP;

	extern const RegisterOperand RSI;

	extern const RegisterOperand RDI;

	extern const RegisterOperand R8;

	extern const RegisterOperand R9;

	extern const RegisterOperand R10;

	extern const RegisterOperand R11;

	// R12 : in "x86-regs-alu-adr.h"

	// R13 : in "x86-regs-alu-adr.h"

	extern const RegisterOperand R14;

	extern const RegisterOperand R15;

	//***************************************************************************************
	// x86 32-bit register file

	extern const RegisterOperand EAX;

	extern const RegisterOperand ECX;

	extern const RegisterOperand EDX;

	extern const RegisterOperand EBX;

	// ESP : in "x86-regs-alu-adr.h"

	// EBP : in "x86-regs-alu-adr.h"

	extern const RegisterOperand ESI;

	extern const RegisterOperand EDI;

	//************************************************************************
	// X64 Extra 32-bit registers

	extern const RegisterOperand R8D;

	extern const RegisterOperand R9D;

	extern const RegisterOperand R10D;

	extern const RegisterOperand R11D;

	extern const RegisterOperand R12D;

	extern const RegisterOperand R13D;

	extern const RegisterOperand R14D;

	extern const RegisterOperand R15D;

	//*********************************************************************************
	// x86 16-bit registers

	extern const RegisterOperand AX;

	extern const RegisterOperand CX;

	extern const RegisterOperand DX;

	extern const RegisterOperand BX;

	extern const RegisterOperand SP;

	extern const RegisterOperand BP;

	extern const RegisterOperand SI;

	extern const RegisterOperand DI;

	// ************************************************************************
	// X64 Extra 16-bit registers

	extern const RegisterOperand R8W;

	extern const RegisterOperand R9W;

	extern const RegisterOperand R10W;

	extern const RegisterOperand R11W;

	extern const RegisterOperand R12W;

	extern const RegisterOperand R13W;

	extern const RegisterOperand R14W;

	extern const RegisterOperand R15W;

	//***********************************************************************************
	// x86 8-bit registers

	// NOTE: These are available with REX prefix as well

	extern const RegisterOperand AL;

	// NOTE: CL declared in header "x86-regs-alu-cl.h" because it is needed with
	//       some instructions.
	

	extern const RegisterOperand DL;

	extern const RegisterOperand BL;

	// NOTE: Not available with REX prefix. 

	extern const RegisterOperand AH;

	extern const RegisterOperand CH;
		
	extern const RegisterOperand DH;

	extern const RegisterOperand BH;

	//*******************************************************************************
	// x64 new 8-bit registers

	extern const RegisterOperand SPL;

	extern const RegisterOperand BPL;
		
	extern const RegisterOperand SIL;

	extern const RegisterOperand DIL;
	
	extern const RegisterOperand R8L;

	extern const RegisterOperand R9L;

	extern const RegisterOperand R10L;

	extern const RegisterOperand R11L;

	extern const RegisterOperand R12L;

	extern const RegisterOperand R13L;

	extern const RegisterOperand R14L;

	extern const RegisterOperand R15L;
}

#endif