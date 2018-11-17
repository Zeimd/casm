/*****************************************************************************
*
* x86-regs-simd.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_REGS_SIMD_H
#define X86_REGS_SIMD_H

#include "x86-register-op.h"

namespace X86
{
	//*********************************************************************************
	// x86 SSE register file

	extern const RegisterOperand XMM0;

	extern const RegisterOperand XMM1;

	extern const RegisterOperand XMM2;

	extern const RegisterOperand XMM3;

	extern const RegisterOperand XMM4;

	extern const RegisterOperand XMM5;

	extern const RegisterOperand XMM6;

	extern const RegisterOperand XMM7;

	//*********************************************************************************
	// x64 additional SSE register file

	extern const RegisterOperand XMM8;

	extern const RegisterOperand XMM9;

	extern const RegisterOperand XMM10;

	extern const RegisterOperand XMM11;

	extern const RegisterOperand XMM12;

	extern const RegisterOperand XMM13;

	extern const RegisterOperand XMM14;

	extern const RegisterOperand XMM15;

	//*********************************************************************************
	// x86 AVX register file

	extern const RegisterOperand YMM0;

	extern const RegisterOperand YMM1;

	extern const RegisterOperand YMM2;

	extern const RegisterOperand YMM3;

	extern const RegisterOperand YMM4;

	extern const RegisterOperand YMM5;

	extern const RegisterOperand YMM6;

	extern const RegisterOperand YMM7;

	//*********************************************************************************
	// x64 additional AVX register file

	extern const RegisterOperand YMM8;

	extern const RegisterOperand YMM9;

	extern const RegisterOperand YMM10;

	extern const RegisterOperand YMM11;

	extern const RegisterOperand YMM12;

	extern const RegisterOperand YMM13;

	extern const RegisterOperand YMM14;

	extern const RegisterOperand YMM15;
}

#endif