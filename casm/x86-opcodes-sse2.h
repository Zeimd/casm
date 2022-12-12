/*****************************************************************************
*
* x86-opcodes-sse2.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_OPCODES_SSE2_H
#define X86_OPCODES_SSE2_H

#include "sse-instruction.h"

#include "enums/x86-param-list.h"

namespace X86
{
	//******************************************************************************************
	// SSE2 : convert int32->float

	extern const X86::SSE_Instruction CVTDQ2PS;

	extern const X86::SSE_Instruction VCVTDQ2PS;

	extern const X86::SSE_Instruction CVTPS2DQ;

	extern const X86::SSE_Instruction VCVTPS2DQ;

	extern const X86::SSE_Instruction CVTTPS2DQ;

	extern const X86::SSE_Instruction VCVTTPS2DQ;

	//******************************************************************************************
	// SSE2 : convert int32->double

	extern const X86::SSE_Instruction CVTDQ2PD;

	extern const X86::SSE_Instruction VCVTDQ2PD;

	extern const X86::SSE_Instruction CVTPD2DQ;

	extern const X86::SSE_Instruction VCVTPD2DQ;

	extern const X86::SSE_Instruction CVTTPD2DQ;

	extern const X86::SSE_Instruction VCVTTPD2DQ;

	//******************************************************************************************
	// SSE2 : convert float->double

	extern const X86::SSE_Instruction CVTPS2PD;

	extern const X86::SSE_Instruction VCVTPS2PD;

	extern const X86::SSE_Instruction CVTPD2PS;

	extern const X86::SSE_Instruction VCVTPD2PS;

	extern const X86::SSE_Instruction CVTSD2SS;

	extern const X86::SSE_Instruction VCVTSD2SS;

	extern const X86::SSE_Instruction CVTSS2SD;

	extern const X86::SSE_Instruction VCVTSS2SD;

	//******************************************************************************************
	// SSE2 : special case conversions

	// CVTSI2SS xmm,rm32
	// CVTSS2SI r32,xmm

	// CVTSI2SD xmm,rm32
	// CVTSD2SI r32,xmm
}

#endif