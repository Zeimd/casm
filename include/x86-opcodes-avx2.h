/*****************************************************************************
*
* x86-opcodes-avx2.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_OPCODES_AVX2_H
#define X86_OPCODES_AVX2_H

#include "sse-instruction.h"

namespace X86
{
	// VECTOR GATHER

	/** HALF-PRECISION
	 *
	 * vcvtph2ps ymm,xmm/m128
	 * vcvtph2ps xmm,xmm/m128
	 *
	 * vcvtps2ph xmm/m128,ymm,imm8
	 * vcvtps2ph xmm/m64,xmm,imm8
	 */

	/** WIDE INSERT / EXTRACT
	 * vextracti128 xmm/m128,ymm,imm8
	 * vinserti128 ymm,ymm,xmm/m128,imm8
	 */

	//*****************************************************************************************
	// AVX2 : Integer masked move

	extern const X86::SSE_Instruction VPMASKMOVD;

	extern const X86::SSE_Instruction VPMASKMOVQ;

	//***********************************************************************************
	// AVX 2 : Variable shift

	extern const X86::SSE_Instruction VPSLLVD;

	extern const X86::SSE_Instruction VPSLLVQ;

	extern const X86::SSE_Instruction VPSRAVD;

	extern const X86::SSE_Instruction VPSRLVD;

	extern const X86::SSE_Instruction VPSRLVQ;

	//***********************************************************************************
	// AVX2 : Blend int32

	extern const X86::SSE_Instruction VBLENDD;

	//************************************************************************************
	// AVX2 : Permutation

	extern const X86::SSE_Instruction VPERMPS;

	extern const X86::SSE_Instruction VPERMPD;

	extern const X86::SSE_Instruction VPERMD;

	extern const X86::SSE_Instruction VPERMQ;

	extern const X86::SSE_Instruction VPERM2I128;

	//******************************************************************************************
	// AVX 2 : Fused MADD

	extern const X86::SSE_Instruction VFMADD132PS;

	extern const X86::SSE_Instruction VFMADD213PS;

	extern const X86::SSE_Instruction VFMADD231PS;

	extern const X86::SSE_Instruction VFMADD132PD;

	extern const X86::SSE_Instruction VFMADD213PD;

	extern const X86::SSE_Instruction VFMADD231PD;

	extern const X86::SSE_Instruction VFMADD132SS;

	extern const X86::SSE_Instruction VFMADD213SS;

	extern const X86::SSE_Instruction VFMADD231SS;

	extern const X86::SSE_Instruction VFMADD132SD;

	extern const X86::SSE_Instruction VFMADD213SD;

	extern const X86::SSE_Instruction VFMADD231SD;

	//******************************************************************************************
	// AVX 2 : Fused NMADD

	extern const X86::SSE_Instruction VFNMADD132PS;

	extern const X86::SSE_Instruction VFNMADD213PS;

	extern const X86::SSE_Instruction VFNMADD231PS;

	extern const X86::SSE_Instruction VFNMADD132PD;

	extern const X86::SSE_Instruction VFNMADD213PD;

	extern const X86::SSE_Instruction VFNMADD231PD;

	extern const X86::SSE_Instruction VFNMADD132SS;

	extern const X86::SSE_Instruction VFNMADD213SS;

	extern const X86::SSE_Instruction VFNMADD231SS;

	extern const X86::SSE_Instruction VFNMADD132SD;

	extern const X86::SSE_Instruction VFNMADD213SD;

	extern const X86::SSE_Instruction VFNMADD231SD;

	//******************************************************************************************
	// AVX 2 : Fused MSUB

	extern const X86::SSE_Instruction VFMSUB132PS;

	extern const X86::SSE_Instruction VFMSUB213PS;

	extern const X86::SSE_Instruction VFMSUB231PS;

	extern const X86::SSE_Instruction VFMSUB132PD;

	extern const X86::SSE_Instruction VFMSUB213PD;

	extern const X86::SSE_Instruction VFMSUB231PD;


	extern const X86::SSE_Instruction VFMSUB132SS;

	extern const X86::SSE_Instruction VFMSUB213SS;

	extern const X86::SSE_Instruction VFMSUB231SS;

	extern const X86::SSE_Instruction VFMSUB132SD;

	extern const X86::SSE_Instruction VFMSUB213SD;

	extern const X86::SSE_Instruction VFMSUB231SD;

	//******************************************************************************************
	// AVX 2 : Fused MNSUB

	extern const X86::SSE_Instruction VFNMSUB132PS;

	extern const X86::SSE_Instruction VFNMSUB213PS;

	extern const X86::SSE_Instruction VFNMSUB231PS;

	extern const X86::SSE_Instruction VFNMSUB132PD;

	extern const X86::SSE_Instruction VFNMSUB213PD;

	extern const X86::SSE_Instruction VFNMSUB231PD;

	extern const X86::SSE_Instruction VFNMSUB132SS;

	extern const X86::SSE_Instruction VFNMSUB213SS;

	extern const X86::SSE_Instruction VFNMSUB231SS;

	extern const X86::SSE_Instruction VFNMSUB132SD;

	extern const X86::SSE_Instruction VFNMSUB213SD;

	extern const X86::SSE_Instruction VFNMSUB231SD;
	
	//******************************************************************************************
	// AVX 2 : Fused MADDSUB

	extern const X86::SSE_Instruction VFMADDSUB132PS;

	extern const X86::SSE_Instruction VFMADDSUB213PS;

	extern const X86::SSE_Instruction VFMADDSUB231PS;

	extern const X86::SSE_Instruction VFMADDSUB132PD;

	extern const X86::SSE_Instruction VFMADDSUB213PD;

	extern const X86::SSE_Instruction VFMADDSUB231PD;	

	//******************************************************************************************
	// AVX 2 : Fused MSUBADD
														
	extern const X86::SSE_Instruction VFMSUBADD132PS;

	extern const X86::SSE_Instruction VFMSUBADD213PS;

	extern const X86::SSE_Instruction VFMSUBADD231PS;

	extern const X86::SSE_Instruction VFMSUBADD132PD;

	extern const X86::SSE_Instruction VFMSUBADD213PD;

	extern const X86::SSE_Instruction VFMSUBADD231PD;	
}

#endif