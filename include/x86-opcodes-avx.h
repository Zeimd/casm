/*****************************************************************************
*
* x86-avx-opcodes.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_AVX_OPCODES_H
#define X86_AVX_OPCODES_H

#include "sse-instruction.h"

namespace X86
{
	//**************************************************************************
	// SPECIAL CASES

	/** BROADCAST
	 *
	 * vbroadcastss xmm,m32
	 * vbroadcastss ymm,m32
	 * vbroadcastsd ymm,m64
	 *
	 * vbroadcastf128 ymm,m128
	 *
	 * vbroadcastss xmm,xmm
	 * vbroadcastss ymm,xmm
	 * vbroadcastsd ymm,xmm
	 */

	/** WIDE EXTRACT / INSERT
	 *
	 * vextractf128 xmm/m128,ymm,imm8
	 * vinsertf128 ymm,ymm,xmm/m128,imm8
	 *
	 */	

	//**********************************************************************************
	// Cleaning

	// VZEROALL
	// VZEROUPPER


	//**********************************************************************************
	// Masked moves

	extern const X86::SSE_Instruction VMASKMOVPS;

	extern const X86::SSE_Instruction VMASKMOVPD;

	//***********************************************************************************
	// AVX : Bit test

	extern const X86::SSE_Instruction VTESTPS;

	extern const X86::SSE_Instruction VTESTPD;

	//******************************************************************************************
	// AVX : Permutation

	/** Special case:
	 *
	 * These have different opcodes
	 *
	 * vpermilps xmm,xmm,xmm/m128
	 * vpermilps xmm,xmm,imm
	 *
	 */
	
	extern const X86::SSE_Instruction VPERM2F128;
	
}

#endif