/*****************************************************************************
*
* x86-regs-simd.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-regs-simd.h"

#include "../include/enums/x86-cpu-modes.h"
#include "../include/enums/x86-register-types.h"

namespace X86
{
	static const Ceng::UINT32 MODE_X86_X64 = CPU_MODE::PROTECTED | CPU_MODE::X64;

	//*********************************************************************************
	// x86 SSE register file

	const RegisterOperand XMM0 = RegisterOperand(-1,false,REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,0);

	const RegisterOperand XMM1 = RegisterOperand(-1,false,REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,1);

	const RegisterOperand XMM2 = RegisterOperand(-1,false,REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,2);

	const RegisterOperand XMM3 = RegisterOperand(-1,false,REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,3);

	const RegisterOperand XMM4 = RegisterOperand(-1,false,REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,4);

	const RegisterOperand XMM5 = RegisterOperand(-1,false,REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,5);

	const RegisterOperand XMM6 = RegisterOperand(-1,false,REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,6);

	const RegisterOperand XMM7 = RegisterOperand(-1,false,REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,7);

	//*********************************************************************************
	// x64 additional SSE register file

	const RegisterOperand XMM8 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,8);

	const RegisterOperand XMM9 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,9);

	const RegisterOperand XMM10 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,10);

	const RegisterOperand XMM11 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,11);

	const RegisterOperand XMM12 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,12);

	const RegisterOperand XMM13 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,13);

	const RegisterOperand XMM14 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,14);

	const RegisterOperand XMM15 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_XMM,
															OPERAND_SIZE::XMMWORD,15);

	//*********************************************************************************
	// x86 AVX register file

	const RegisterOperand YMM0 = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,0);

	const RegisterOperand YMM1 = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,1);

	const RegisterOperand YMM2 = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,2);

	const RegisterOperand YMM3 = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,3);

	const RegisterOperand YMM4 = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,4);

	const RegisterOperand YMM5 = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,5);

	const RegisterOperand YMM6 = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,6);

	const RegisterOperand YMM7 = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,7);

	//*********************************************************************************
	// x64 additional AVX register file

	const RegisterOperand YMM8 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,8);

	const RegisterOperand YMM9 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,9);

	const RegisterOperand YMM10 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,10);

	const RegisterOperand YMM11 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,11);

	const RegisterOperand YMM12 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,12);

	const RegisterOperand YMM13 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,13);

	const RegisterOperand YMM14 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,14);

	const RegisterOperand YMM15 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_YMM,
															OPERAND_SIZE::YMMWORD,15);
}