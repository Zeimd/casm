/*****************************************************************************
*
* x86-regs-simd.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "x86-regs-simd.h"

#include "enums/x86-cpu-modes.h"
#include "enums/x86-register-types.h"

namespace X86
{
	static const Ceng::UINT32 MODE_X86_X64 = CPU_MODE::PROTECTED | CPU_MODE::X64;

	//*********************************************************************************
	// x86 SSE register file

	const RegisterOperand XMM0 = RegisterOperand("xmm0", - 1, false, REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,0);

	const RegisterOperand XMM1 = RegisterOperand("xmm1", - 1, false, REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,1);

	const RegisterOperand XMM2 = RegisterOperand("xmm2", - 1, false, REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,2);

	const RegisterOperand XMM3 = RegisterOperand("xmm3", - 1, false, REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,3);

	const RegisterOperand XMM4 = RegisterOperand("xmm4", - 1, false, REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,4);

	const RegisterOperand XMM5 = RegisterOperand("xmm5", - 1, false, REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,5);

	const RegisterOperand XMM6 = RegisterOperand("xmm6", - 1, false, REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,6);

	const RegisterOperand XMM7 = RegisterOperand("xmm7", - 1, false, REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,7);

	//*********************************************************************************
	// x64 additional SSE register file

	const RegisterOperand XMM8 = RegisterOperand("xmm8",CPU_MODE::X64, true, REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,8);

	const RegisterOperand XMM9 = RegisterOperand("xmm9",CPU_MODE::X64, true, REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,9);

	const RegisterOperand XMM10 = RegisterOperand("xmm10",CPU_MODE::X64, true, REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,10);

	const RegisterOperand XMM11 = RegisterOperand("xmm11",CPU_MODE::X64, true, REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,11);

	const RegisterOperand XMM12 = RegisterOperand("xmm12",CPU_MODE::X64, true, REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,12);

	const RegisterOperand XMM13 = RegisterOperand("xmm13",CPU_MODE::X64, true, REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,13);

	const RegisterOperand XMM14 = RegisterOperand("xmm14",CPU_MODE::X64, true, REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,14);

	const RegisterOperand XMM15 = RegisterOperand("xmm15",CPU_MODE::X64, true, REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,15);

	//*********************************************************************************
	// x86 AVX register file

	const RegisterOperand YMM0 = RegisterOperand("ymm0",MODE_X86_X64, false, REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,0);

	const RegisterOperand YMM1 = RegisterOperand("ymm1",MODE_X86_X64, false, REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,1);

	const RegisterOperand YMM2 = RegisterOperand("ymm2",MODE_X86_X64, false, REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,2);

	const RegisterOperand YMM3 = RegisterOperand("ymm3",MODE_X86_X64, false, REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,3);

	const RegisterOperand YMM4 = RegisterOperand("ymm4",MODE_X86_X64, false, REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,4);

	const RegisterOperand YMM5 = RegisterOperand("ymm5",MODE_X86_X64, false, REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,5);

	const RegisterOperand YMM6 = RegisterOperand("ymm6",MODE_X86_X64, false, REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,6);

	const RegisterOperand YMM7 = RegisterOperand("ymm7",MODE_X86_X64, false, REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,7);

	//*********************************************************************************
	// x64 additional AVX register file

	const RegisterOperand YMM8 = RegisterOperand("ymm8",CPU_MODE::X64, true, REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,8);

	const RegisterOperand YMM9 = RegisterOperand("ymm9",CPU_MODE::X64, true, REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,9);

	const RegisterOperand YMM10 = RegisterOperand("ymm10",CPU_MODE::X64, true, REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,10);

	const RegisterOperand YMM11 = RegisterOperand("ymm11",CPU_MODE::X64, true, REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,11);

	const RegisterOperand YMM12 = RegisterOperand("ymm12",CPU_MODE::X64, true, REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,12);

	const RegisterOperand YMM13 = RegisterOperand("ymm13",CPU_MODE::X64, true, REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,13);

	const RegisterOperand YMM14 = RegisterOperand("ymm14",CPU_MODE::X64, true, REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,14);

	const RegisterOperand YMM15 = RegisterOperand("ymm15",CPU_MODE::X64, true, REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,15);
}