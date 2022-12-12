/*****************************************************************************
*
* x86-opcodes-sse3.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_OPCODES_SSE3_H
#define X86_OPCODES_SSE3_H

#include "sse-instruction.h"

#include "enums/x86-param-list.h"

namespace X86
{
	//******************************************************************************************
	// SSE3 : ADDSUB

	extern const X86::SSE_Instruction ADDSUBPS;

	extern const X86::SSE_Instruction VADDSUBPS;

	extern const X86::SSE_Instruction ADDSUBPD;

	extern const X86::SSE_Instruction VADDSUBPD;

	//******************************************************************************************
	// SSE3 : Horizontal add

	extern const X86::SSE_Instruction HADDPS;

	extern const X86::SSE_Instruction VHADDPS;

	extern const X86::SSE_Instruction HADDPD;

	extern const X86::SSE_Instruction VHADDPD;

	//******************************************************************************************
	// SSE3 : Horizontal sub

	extern const X86::SSE_Instruction HSUBPS;

	extern const X86::SSE_Instruction VHSUBPS;

	extern const X86::SSE_Instruction HSUBPD;

	extern const X86::SSE_Instruction VHSUBPD;

	//******************************************************************************************
	// SSE 3 : move and duplicate

	extern const X86::SSE_Instruction MOVSLDUP;

	extern const X86::SSE_Instruction VMOVSLDUP;

	extern const X86::SSE_Instruction MOVSHDUP;

	extern const X86::SSE_Instruction VMOVSHDUP;

	extern const X86::SSE_Instruction MOVDDUP;

	extern const X86::SSE_Instruction VMOVDDUP;
}

#endif