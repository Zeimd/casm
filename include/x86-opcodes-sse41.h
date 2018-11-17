/*****************************************************************************
*
* x86-opcodes-sse41.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_OPCODES_SSE41_H
#define X86_OPCODES_SSE41_H

#include "sse-instruction.h"

#include "enums/x86-param-list.h"

namespace X86
{
	//******************************************************************************************
	// SSE 4.1 : Float insert

	extern const X86::SSE_Instruction INSERTPS;

	extern const X86::SSE_Instruction VINSERTPS;

	//******************************************************************************************
	// SSE 4.1 : Float extract

	// Needs special case

	//******************************************************************************************
	// SSE 4.1 : DOT PRODUCT

	extern const X86::SSE_Instruction DPPS;

	extern const X86::SSE_Instruction VDPPS;

	extern const X86::SSE_Instruction DPPD;

	extern const X86::SSE_Instruction VDPPD;

	//******************************************************************************************
	// SSE 4.1 : BLEND

	extern const X86::SSE_Instruction BLENDPS;

	extern const X86::SSE_Instruction VBLENDPS;

	extern const X86::SSE_Instruction BLENDPD;

	extern const X86::SSE_Instruction VBLENDPD;

	//******************************************************************************************
	// SSE 4.1 : BLENDV

	extern const X86::SSE_Instruction BLENDVPS;

	extern const X86::SSE_Instruction VBLENDVPS;

	extern const X86::SSE_Instruction BLENDVPD;

	extern const X86::SSE_Instruction VBLENDVPD;

	//******************************************************************************************
	// SSE 4.1 : Rounding

	extern const X86::SSE_Instruction ROUNDPS;

	extern const X86::SSE_Instruction VROUNDPS;

	extern const X86::SSE_Instruction ROUNDSS;

	extern const X86::SSE_Instruction VROUNDSS;

	extern const X86::SSE_Instruction ROUNDPD;

	extern const X86::SSE_Instruction VROUNDPD;

	extern const X86::SSE_Instruction ROUNDSD;

	extern const X86::SSE_Instruction VROUNDSD;
}

#endif