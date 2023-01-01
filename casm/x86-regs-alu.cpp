/*****************************************************************************
*
* x86-regs-alu.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "x86-regs-alu.h"

#include "enums/x86-cpu-modes.h"
#include "enums/x86-register-types.h"

namespace X86
{
	static const Ceng::UINT32 MODE_X86_X64 = CPU_MODE::PROTECTED | CPU_MODE::X64;
	static const Ceng::UINT32 MODE_ALL = -1;

	const RegisterOperand RIP = RegisterOperand("rip",CPU_MODE::X64, false, REGISTER_FILE::RIP,
															OPERAND_SIZE::QWORD,16);

	//***************************************************************************************
	// x64 64-bit register file

	const RegisterOperand RAX = RegisterOperand("rax",MODE_X86_X64, false, REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,0);

	const RegisterOperand RCX = RegisterOperand("rcx",MODE_X86_X64, false, REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,1);

	const RegisterOperand RDX = RegisterOperand("rdx",MODE_X86_X64, false, REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,2);

	const RegisterOperand RBX = RegisterOperand("rbx",MODE_X86_X64, false, REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,3);

	const RegisterOperand RSP = RegisterOperand("rsp",MODE_X86_X64, false, REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,4);

	const RegisterOperand RBP = RegisterOperand("rbp",MODE_X86_X64, false, REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,5);

	const RegisterOperand RSI = RegisterOperand("rsi",MODE_X86_X64, false, REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,6);

	const RegisterOperand RDI = RegisterOperand("rdi",MODE_X86_X64, false, REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,7);

	const RegisterOperand R8 = RegisterOperand("r8",CPU_MODE::X64, true, REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,8);

	const RegisterOperand R9 = RegisterOperand("r9",CPU_MODE::X64, true, REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,9);

	const RegisterOperand R10 = RegisterOperand("r10",CPU_MODE::X64, true, REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,10);

	const RegisterOperand R11 = RegisterOperand("r11",CPU_MODE::X64, true, REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,11);

	const RegisterOperand R12 = RegisterOperand("r12",CPU_MODE::X64, true, REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,12);

	const RegisterOperand R13 = RegisterOperand("r13",CPU_MODE::X64, true, REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,13);

	const RegisterOperand R14 = RegisterOperand("r14",CPU_MODE::X64, true, REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,14);

	const RegisterOperand R15 = RegisterOperand("r15",CPU_MODE::X64, true, REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,15);

	//***************************************************************************************
	// x86 32-bit register file

	const RegisterOperand EAX = RegisterOperand("eax",MODE_X86_X64, false, REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,0);

	const RegisterOperand ECX = RegisterOperand("ecx",MODE_X86_X64, false, REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,1);

	const RegisterOperand EDX = RegisterOperand("edx",MODE_X86_X64, false, REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,2);

	const RegisterOperand EBX = RegisterOperand("ebx",MODE_X86_X64, false, REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,3);

	const RegisterOperand ESP = RegisterOperand("esp",MODE_X86_X64, false, REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,4);

	const RegisterOperand EBP = RegisterOperand("ebp",MODE_X86_X64, false, REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,5);

	const RegisterOperand ESI = RegisterOperand("esi",MODE_X86_X64, false, REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,6);

	const RegisterOperand EDI = RegisterOperand("edi",MODE_X86_X64, false, REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,7);

	// ************************************************************************
	// X64 Extra 32-bit registers

	const RegisterOperand R8D = RegisterOperand("r8d",CPU_MODE::X64, true, REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,8);

	const RegisterOperand R9D = RegisterOperand("r9d",CPU_MODE::X64, true, REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,9);

	const RegisterOperand R10D = RegisterOperand("r10d",CPU_MODE::X64, true, REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,10);

	const RegisterOperand R11D = RegisterOperand("r11d",CPU_MODE::X64, true, REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,11);

	const RegisterOperand R12D = RegisterOperand("r12d",CPU_MODE::X64, true, REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,12);

	const RegisterOperand R13D = RegisterOperand("e13d",CPU_MODE::X64, true, REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,13);

	const RegisterOperand R14D = RegisterOperand("r14d",CPU_MODE::X64, true, REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,14);

	const RegisterOperand R15D = RegisterOperand("r15d",CPU_MODE::X64, true, REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,15);

	//*********************************************************************************
	// x86 16-bit registers

	const RegisterOperand AX = RegisterOperand("ax",MODE_X86_X64, false, REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,0);

	const RegisterOperand CX = RegisterOperand("cx",MODE_X86_X64, false, REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,1);

	const RegisterOperand DX = RegisterOperand("dx",MODE_X86_X64, false, REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,2);

	const RegisterOperand BX = RegisterOperand("bx",MODE_X86_X64, false, REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,3);

	const RegisterOperand SP = RegisterOperand("sp",MODE_X86_X64, false, REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,4);

	const RegisterOperand BP = RegisterOperand("bp",MODE_X86_X64, false, REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,5);

	const RegisterOperand SI = RegisterOperand("si",MODE_X86_X64, false, REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,6);

	const RegisterOperand DI = RegisterOperand("di",MODE_X86_X64, false, REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,7);

	// ************************************************************************
	// X64 Extra 16-bit registers

	const RegisterOperand R8W = RegisterOperand("r8w",CPU_MODE::X64, true, REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,8);

	const RegisterOperand R9W = RegisterOperand("r9w",CPU_MODE::X64, true, REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,9);

	const RegisterOperand R10W = RegisterOperand("r10w",CPU_MODE::X64, true, REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,10);

	const RegisterOperand R11W = RegisterOperand("r11w",CPU_MODE::X64, true, REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,11);

	const RegisterOperand R12W = RegisterOperand("r12w",CPU_MODE::X64, true, REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,12);

	const RegisterOperand R13W = RegisterOperand("r13w",CPU_MODE::X64, true, REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,13);

	const RegisterOperand R14W = RegisterOperand("r14w",CPU_MODE::X64, true, REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,14);

	const RegisterOperand R15W = RegisterOperand("r15w",CPU_MODE::X64, true, REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,15);

	//***********************************************************************************
	// x86 8-bit registers

	static const Ceng::UINT32 REG_FILE_X86_X64 = X86::REGISTER_FILE::REG_8_X86 | X86::REGISTER_FILE::REG_8_X64;

	// NOTE: These are available with REX prefix as well

	const RegisterOperand AL = RegisterOperand("al",MODE_X86_X64, false,
															REG_FILE_X86_X64, 
															OPERAND_SIZE::BYTE,0);

	const RegisterOperand CL = RegisterOperand("cl",MODE_X86_X64, false,
															REG_FILE_X86_X64, 
															OPERAND_SIZE::BYTE,1);

	const RegisterOperand DL = RegisterOperand("dl",MODE_X86_X64, false,
															REG_FILE_X86_X64, 
															OPERAND_SIZE::BYTE,2);

	const RegisterOperand BL = RegisterOperand("bl",MODE_X86_X64, false,
															REG_FILE_X86_X64, 
															OPERAND_SIZE::BYTE,3);

	// NOTE: Not available with REX prefix. 

	const RegisterOperand AH = RegisterOperand("ah",MODE_X86_X64, false,
															REGISTER_FILE::REG_8_X86, 
															OPERAND_SIZE::BYTE,4);

	const RegisterOperand CH = RegisterOperand("ch",MODE_X86_X64, false,
															REGISTER_FILE::REG_8_X86, 
															OPERAND_SIZE::BYTE,5);
		
	const RegisterOperand DH = RegisterOperand("dh",MODE_X86_X64, false,
															REGISTER_FILE::REG_8_X86, 
															OPERAND_SIZE::BYTE,6);

	const RegisterOperand BH = RegisterOperand("bh",MODE_X86_X64, false,
															REGISTER_FILE::REG_8_X86, 
															OPERAND_SIZE::BYTE,7);

	//*******************************************************************************
	// x64 new 8-bit registers

	const RegisterOperand SPL = RegisterOperand("spl",MODE_X86_X64, true,
															REGISTER_FILE::REG_8_X64, 
															OPERAND_SIZE::BYTE,4);

	const RegisterOperand BPL = RegisterOperand("bpl",MODE_X86_X64, true,
															REGISTER_FILE::REG_8_X64, 
															OPERAND_SIZE::BYTE,5);
		
	const RegisterOperand SIL = RegisterOperand("sil",MODE_X86_X64, true,
															REGISTER_FILE::REG_8_X64, 
															OPERAND_SIZE::BYTE,6);

	const RegisterOperand DIL = RegisterOperand("dil",MODE_X86_X64, true,
															REGISTER_FILE::REG_8_X64, 
															OPERAND_SIZE::BYTE,7);
	
	const RegisterOperand R8L = RegisterOperand("r8l",CPU_MODE::X64, true, REGISTER_FILE::REG_8_X64,
															OPERAND_SIZE::BYTE,8);

	const RegisterOperand R9L = RegisterOperand("r9l",CPU_MODE::X64, true, REGISTER_FILE::REG_8_X64,
															OPERAND_SIZE::BYTE,9);

	const RegisterOperand R10L = RegisterOperand("r10l",CPU_MODE::X64, true, REGISTER_FILE::REG_8_X64,
															OPERAND_SIZE::BYTE,10);

	const RegisterOperand R11L = RegisterOperand("r11l",CPU_MODE::X64, true, REGISTER_FILE::REG_8_X64,
															OPERAND_SIZE::BYTE,11);

	const RegisterOperand R12L = RegisterOperand("r12l",CPU_MODE::X64, true, REGISTER_FILE::REG_8_X64,
															OPERAND_SIZE::BYTE,12);

	const RegisterOperand R13L = RegisterOperand("r13l",CPU_MODE::X64, true, REGISTER_FILE::REG_8_X64,
															OPERAND_SIZE::BYTE,13);

	const RegisterOperand R14L = RegisterOperand("r14l",CPU_MODE::X64, true, REGISTER_FILE::REG_8_X64,
															OPERAND_SIZE::BYTE,14);

	const RegisterOperand R15L = RegisterOperand("r15l",CPU_MODE::X64, true, REGISTER_FILE::REG_8_X64,
															OPERAND_SIZE::BYTE,15);

	//*******************************************************************************
	// Segment registers

	const RegisterOperand CS = RegisterOperand("CS",MODE_X86_X64, false, REGISTER_FILE::REG_SEGMENT,
		OPERAND_SIZE::SEGMENT, 0);

	const RegisterOperand DS = RegisterOperand("DS",MODE_X86_X64, false, REGISTER_FILE::REG_SEGMENT,
		OPERAND_SIZE::SEGMENT, 1);

	const RegisterOperand SS = RegisterOperand("SS",MODE_X86_X64, false, REGISTER_FILE::REG_SEGMENT,
		OPERAND_SIZE::SEGMENT, 2);

	const RegisterOperand ES = RegisterOperand("ES",MODE_X86_X64, false, REGISTER_FILE::REG_SEGMENT,
		OPERAND_SIZE::SEGMENT, 3);

	const RegisterOperand FS = RegisterOperand("FS",MODE_X86_X64, false, REGISTER_FILE::REG_SEGMENT,
		OPERAND_SIZE::SEGMENT, 4);

	const RegisterOperand GS = RegisterOperand("GS",MODE_X86_X64, false, REGISTER_FILE::REG_SEGMENT,
		OPERAND_SIZE::SEGMENT, 5);

}
