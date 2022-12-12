/*****************************************************************************
*
* x86-opcodes-sse.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_OPCODES_SSE_H
#define X86_OPCOEDS_SSE_H

#include "sse-instruction.h"

#include "sse-compare.h"

#include "enums/x86-param-list.h"

namespace X86
{
	//******************************************************************************************
	// SIMD float aligned move

	extern const SSE_Instruction MOVAPS;
	extern const SSE_Instruction VMOVAPS;
	extern const SSE_Instruction MOVAPD;
	extern const SSE_Instruction VMOVAPD;

	//******************************************************************************************
	// SIMD float unaligned move

	extern const SSE_Instruction MOVUPS;
	extern const SSE_Instruction VMOVUPS;
	extern const SSE_Instruction MOVUPD;
	extern const SSE_Instruction VMOVUPD;

	//******************************************************************************************
	// SIMD float scalar moves
	//
	// NOTE: Scalar version of MOVUPS
	
	extern const SSE_Instruction MOVSS;
	extern const SSE_Instruction VMOVSS;
	extern const SSE_Instruction MOVSD;
	extern const SSE_Instruction VMOVSD;
	
	//******************************************************************************************
	// SIMD float half-vector moves
	//

	extern const SSE_Instruction MOVLPS;

	extern const SSE_Instruction VMOVLPS;

	extern const SSE_Instruction MOVHPS;

	extern const SSE_Instruction VMOVHPS;

	extern const SSE_Instruction MOVLPD;

	extern const SSE_Instruction VMOVLPD;

	extern const SSE_Instruction MOVHPD;

	extern const SSE_Instruction VMOVHPD;

	extern const SSE_Instruction MOVLHPS;

	extern const SSE_Instruction VMOVLHPS;

	extern const SSE_Instruction MOVHLPS;
	extern const SSE_Instruction VMOVHLPS;

	//******************************************************************************************
	// SIMD float non-temporal moves

	extern const SSE_Instruction MOVNTPS;

	extern const SSE_Instruction VMOVNTPS;

	extern const SSE_Instruction MOVNTPD;

	extern const SSE_Instruction VMOVNTPD;

	//*****************************************************************************************
	// SIMD float pack

	extern const X86::SSE_Instruction UNPCKLPS;

	extern const X86::SSE_Instruction VUNPCKLPS;	

	extern const X86::SSE_Instruction UNPCKHPS;

	extern const X86::SSE_Instruction VUNPCKHPS;	

	extern const X86::SSE_Instruction UNPCKLPD;

	extern const X86::SSE_Instruction VUNPCKLPD;	

	extern const X86::SSE_Instruction UNPCKHPD;

	extern const X86::SSE_Instruction VUNPCKHPD;	

	//************************************************************************
	// SSE : Shuffle

	extern const X86::SSE_Instruction SHUFPS;

	extern const X86::SSE_Instruction VSHUFPS;

	extern const X86::SSE_Instruction SHUFPD;

	extern const X86::SSE_Instruction VSHUFPD;


	//******************************************************************************************
	// SIMD float bitwise AND

	extern const X86::SSE_Instruction ANDPS;													

	extern const X86::SSE_Instruction VANDPS;

	extern const X86::SSE_Instruction ANDPD;

	extern const X86::SSE_Instruction VANDPD;

	//******************************************************************************************
	// SIMD float bitwise AND NOT

	extern const X86::SSE_Instruction ANDNPS;

	extern const X86::SSE_Instruction VANDNPS;

	extern const X86::SSE_Instruction ANDNPD;

	extern const X86::SSE_Instruction VANDNPD;

	//******************************************************************************************
	// SIMD float bitwise OR

	extern const X86::SSE_Instruction ORPS;													

	extern const X86::SSE_Instruction VORPS;

	extern const X86::SSE_Instruction ORPD;

	extern const X86::SSE_Instruction VORPD;

	//******************************************************************************************
	// SIMD float bitwise XOR

	extern const X86::SSE_Instruction XORPS;													

	extern const X86::SSE_Instruction VXORPS;

	extern const X86::SSE_Instruction XORPD;

	extern const X86::SSE_Instruction VXORPD;

	//************************************************************************
	// SIMD float ADD

	extern const X86::SSE_Instruction ADDPS;

	extern const X86::SSE_Instruction VADDPS;	

	extern const X86::SSE_Instruction ADDSS;

	extern const X86::SSE_Instruction VADDSS;	

	extern const X86::SSE_Instruction ADDPD;

	extern const X86::SSE_Instruction VADDPD;	

	extern const X86::SSE_Instruction ADDSD;

	extern const X86::SSE_Instruction VADDSD;	

	//************************************************************************
	// SIMD float SUB

	extern const X86::SSE_Instruction SUBPS;

	extern const X86::SSE_Instruction VSUBPS;	

	extern const X86::SSE_Instruction SUBSS;

	extern const X86::SSE_Instruction VSUBSS;	

	extern const X86::SSE_Instruction SUBPD;

	extern const X86::SSE_Instruction VSUBPD;	

	extern const X86::SSE_Instruction SUBSD;

	extern const X86::SSE_Instruction VSUBSD;	

	//************************************************************************
	// SIMD float DIV

	extern const X86::SSE_Instruction DIVPS;

	extern const X86::SSE_Instruction VDIVPS;	

	extern const X86::SSE_Instruction DIVSS;

	extern const X86::SSE_Instruction VDIVSS;	

	extern const X86::SSE_Instruction DIVPD;

	extern const X86::SSE_Instruction VDIVPD;	

	extern const X86::SSE_Instruction DIVSD;

	extern const X86::SSE_Instruction VDIVSD;	

	//************************************************************************
	// SIMD float MIN
	
	extern const X86::SSE_Instruction MINPS;

	extern const X86::SSE_Instruction VMINPS;	

	extern const X86::SSE_Instruction MINSS;

	extern const X86::SSE_Instruction VMINSS;	

	extern const X86::SSE_Instruction MINPD;

	extern const X86::SSE_Instruction VMINPD;	

	extern const X86::SSE_Instruction MINSD;

	extern const X86::SSE_Instruction VMINSD;	

	//************************************************************************
	// SIMD float MAX

	extern const X86::SSE_Instruction MAXPS;

	extern const X86::SSE_Instruction VMAXPS;	

	extern const X86::SSE_Instruction MAXSS;

	extern const X86::SSE_Instruction VMAXSS;	

	extern const X86::SSE_Instruction MAXPD;

	extern const X86::SSE_Instruction VMAXPD;	

	extern const X86::SSE_Instruction MAXSD;

	extern const X86::SSE_Instruction VMAXSD;	

	//************************************************************************
	// SIMD float MUL

	extern const X86::SSE_Instruction MULPS;

	extern const X86::SSE_Instruction VMULPS;	

	extern const X86::SSE_Instruction MULSS;

	extern const X86::SSE_Instruction VMULSS;	

	extern const X86::SSE_Instruction MULPD;

	extern const X86::SSE_Instruction VMULPD;	

	extern const X86::SSE_Instruction MULSD;

	extern const X86::SSE_Instruction VMULSD;	

	//************************************************************************
	// SIMD float SQRT

	extern const X86::SSE_Instruction SQRTPS;

	extern const X86::SSE_Instruction VSQRTPS;	

	extern const X86::SSE_Instruction SQRTSS;

	extern const X86::SSE_Instruction VSQRTSS;	

	extern const X86::SSE_Instruction SQRTPD;

	extern const X86::SSE_Instruction VSQRTPD;	

	extern const X86::SSE_Instruction SQRTSD;

	extern const X86::SSE_Instruction VSQRTSD;	

	//************************************************************************
	// SIMD float inverse sqrt

	extern const X86::SSE_Instruction RSQRTPS;

	extern const X86::SSE_Instruction VRSQRTPS;	

	extern const X86::SSE_Instruction RSQRTSS;

	extern const X86::SSE_Instruction VRSQRTSS;	

	//************************************************************************
	// SIMD float RCP

	extern const X86::SSE_Instruction RCPPS;

	extern const X86::SSE_Instruction VRCPPS;	

	extern const X86::SSE_Instruction RCPSS;

	extern const X86::SSE_Instruction VRCPSS;	

	//************************************************************************
	// SSE: float packed compare

	extern const SSE_Compare CMPEQSS;
	extern const SSE_Compare CMPLTSS;
	extern const SSE_Compare CMPLESS;
	extern const SSE_Compare CMPUNORDSS;
	extern const SSE_Compare CMPNEQSS;
	extern const SSE_Compare CMPNLTSS;
	extern const SSE_Compare CMPNLESS;
	extern const SSE_Compare CMPORDSS;

	extern const SSE_Compare VCMPEQSS;
	extern const SSE_Compare VCMPLTSS;
	extern const SSE_Compare VCMPLESS;
	extern const SSE_Compare VCMPUNORDSS;
	extern const SSE_Compare VCMPNEQSS;
	extern const SSE_Compare VCMPNLTSS;
	extern const SSE_Compare VCMPNLESS;
	extern const SSE_Compare VCMPORDSS;

	extern const SSE_Compare CMPEQSD;
	extern const SSE_Compare CMPLTSD;
	extern const SSE_Compare CMPLESD;
	extern const SSE_Compare CMPUNORDSD;
	extern const SSE_Compare CMPNEQSD;
	extern const SSE_Compare CMPNLTSD;
	extern const SSE_Compare CMPNLESD;
	extern const SSE_Compare CMPORDSD;

	extern const SSE_Compare VCMPEQSD;
	extern const SSE_Compare VCMPLTSD;
	extern const SSE_Compare VCMPLESD;
	extern const SSE_Compare VCMPUNORDSD;
	extern const SSE_Compare VCMPNEQSD;
	extern const SSE_Compare VCMPNLTSD;
	extern const SSE_Compare VCMPNLESD;
	extern const SSE_Compare VCMPORDSD;

	extern const SSE_Compare CMPEQPS;
	extern const SSE_Compare CMPLTPS;
	extern const SSE_Compare CMPLEPS;
	extern const SSE_Compare CMPUNORDPS;
	extern const SSE_Compare CMPNEQPS;
	extern const SSE_Compare CMPNLTPS;
	extern const SSE_Compare CMPNLEPS;
	extern const SSE_Compare CMPORDPS;

	extern const SSE_Compare VCMPEQPS;
	extern const SSE_Compare VCMPLTPS;
	extern const SSE_Compare VCMPLEPS;
	extern const SSE_Compare VCMPUNORDPS;
	extern const SSE_Compare VCMPNEQPS;
	extern const SSE_Compare VCMPNLTPS;
	extern const SSE_Compare VCMPNLEPS;
	extern const SSE_Compare VCMPORDPS;

	extern const SSE_Compare CMPEQPD;
	extern const SSE_Compare CMPLTPD;
	extern const SSE_Compare CMPLEPD;
	extern const SSE_Compare CMPUNORDPD;
	extern const SSE_Compare CMPNEQPD;
	extern const SSE_Compare CMPNLTPD;
	extern const SSE_Compare CMPNLEPD;
	extern const SSE_Compare CMPORDPD;

	extern const SSE_Compare VCMPEQPD;
	extern const SSE_Compare VCMPLTPD;
	extern const SSE_Compare VCMPLEPD;
	extern const SSE_Compare VCMPUNORDPD;
	extern const SSE_Compare VCMPNEQPD;
	extern const SSE_Compare VCMPNLTPD;
	extern const SSE_Compare VCMPNLEPD;
	extern const SSE_Compare VCMPORDPD;

	//************************************************************************
	// SSE: float scalar compare

	extern const X86::SSE_Instruction COMISS;

	extern const X86::SSE_Instruction VCOMISS;	

	extern const X86::SSE_Instruction COMISD;

	extern const X86::SSE_Instruction VCOMISD;	

	//************************************************************************
	// SIMD scalar compare unordered

	extern const X86::SSE_Instruction UCOMISS;

	extern const X86::SSE_Instruction VUCOMISS;	

	extern const X86::SSE_Instruction UCOMISD;

	extern const X86::SSE_Instruction VUCOMISD;	
}

#endif