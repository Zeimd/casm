/*****************************************************************************
*
* x86-cpu-mode.cpp
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#include "x86-cpu-mode.h"

using namespace X86;

CPU_Mode::CPU_Mode(const CPU_MODE::value cpuMode,const OPERAND_SIZE::value addressSize,
				   const OPERAND_SIZE::value defaultOpSize) 
	: cpuMode(cpuMode),addressSize(addressSize),defaultOpSize(defaultOpSize)
{
}

namespace X86
{
	const CPU_Mode REAL_MODE = CPU_Mode(CPU_MODE::REAL,OPERAND_SIZE::WORD,OPERAND_SIZE::WORD);

	const CPU_Mode PROTECTED_MODE = CPU_Mode(CPU_MODE::PROTECTED,OPERAND_SIZE::DWORD,OPERAND_SIZE::DWORD);

	const CPU_Mode LONG_MODE = CPU_Mode(CPU_MODE::X64,OPERAND_SIZE::QWORD,OPERAND_SIZE::DWORD);
}
