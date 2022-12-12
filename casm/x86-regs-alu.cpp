/*****************************************************************************
*
* x86-regs-alu.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-regs-alu.h"

#include "../include/enums/x86-cpu-modes.h"
#include "../include/enums/x86-register-types.h"

namespace X86
{
	static const Ceng::UINT32 MODE_X86_X64 = CPU_MODE::PROTECTED | CPU_MODE::X64;
	static const Ceng::UINT32 MODE_ALL = -1;

	const RegisterOperand RIP = RegisterOperand(CPU_MODE::X64,false,REGISTER_FILE::RIP,
															OPERAND_SIZE::QWORD,16);

	//***************************************************************************************
	// x64 64-bit register file

	const RegisterOperand RAX = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,0);

	const RegisterOperand RCX = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,1);

	const RegisterOperand RDX = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,2);

	const RegisterOperand RBX = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,3);

	const RegisterOperand RSP = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,4);

	const RegisterOperand RBP = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,5);

	const RegisterOperand RSI = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,6);

	const RegisterOperand RDI = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,7);

	const RegisterOperand R8 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,8);

	const RegisterOperand R9 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,9);

	const RegisterOperand R10 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,10);

	const RegisterOperand R11 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,11);

	const RegisterOperand R12 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,12);

	const RegisterOperand R13 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,13);

	const RegisterOperand R14 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,14);

	const RegisterOperand R15 = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_64,
															OPERAND_SIZE::QWORD,15);

	//***************************************************************************************
	// x86 32-bit register file

	const RegisterOperand EAX = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,0);

	const RegisterOperand ECX = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,1);

	const RegisterOperand EDX = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,2);

	const RegisterOperand EBX = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,3);

	const RegisterOperand ESP = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,4);

	const RegisterOperand EBP = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,5);

	const RegisterOperand ESI = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,6);

	const RegisterOperand EDI = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,7);

	// ************************************************************************
	// X64 Extra 32-bit registers

	const RegisterOperand R8D = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,8);

	const RegisterOperand R9D = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,9);

	const RegisterOperand R10D = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,10);

	const RegisterOperand R11D = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,11);

	const RegisterOperand R12D = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,12);

	const RegisterOperand R13D = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,13);

	const RegisterOperand R14D = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,14);

	const RegisterOperand R15D = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_32,
															OPERAND_SIZE::DWORD,15);

	//*********************************************************************************
	// x86 16-bit registers

	const RegisterOperand AX = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,0);

	const RegisterOperand CX = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,1);

	const RegisterOperand DX = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,2);

	const RegisterOperand BX = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,3);

	const RegisterOperand SP = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,4);

	const RegisterOperand BP = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,5);

	const RegisterOperand SI = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,6);

	const RegisterOperand DI = RegisterOperand(MODE_X86_X64,false,REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,7);

	// ************************************************************************
	// X64 Extra 16-bit registers

	const RegisterOperand R8W = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,8);

	const RegisterOperand R9W = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,9);

	const RegisterOperand R10W = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,10);

	const RegisterOperand R11W = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,11);

	const RegisterOperand R12W = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,12);

	const RegisterOperand R13W = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,13);

	const RegisterOperand R14W = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,14);

	const RegisterOperand R15W = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_16,
															OPERAND_SIZE::WORD,15);

	//***********************************************************************************
	// x86 8-bit registers

	static const Ceng::UINT32 REG_FILE_X86_X64 = X86::REGISTER_FILE::REG_8_X86 | X86::REGISTER_FILE::REG_8_X64;

	// NOTE: These are available with REX prefix as well

	const RegisterOperand AL = RegisterOperand(MODE_X86_X64,false,
															REG_FILE_X86_X64, 
															OPERAND_SIZE::BYTE,0);

	const RegisterOperand CL = RegisterOperand(MODE_X86_X64,false,
															REG_FILE_X86_X64, 
															OPERAND_SIZE::BYTE,1);

	const RegisterOperand DL = RegisterOperand(MODE_X86_X64,false,
															REG_FILE_X86_X64, 
															OPERAND_SIZE::BYTE,2);

	const RegisterOperand BL = RegisterOperand(MODE_X86_X64,false,
															REG_FILE_X86_X64, 
															OPERAND_SIZE::BYTE,3);

	// NOTE: Not available with REX prefix. 

	const RegisterOperand AH = RegisterOperand(MODE_X86_X64,false,
															REGISTER_FILE::REG_8_X86, 
															OPERAND_SIZE::BYTE,4);

	const RegisterOperand CH = RegisterOperand(MODE_X86_X64,false,
															REGISTER_FILE::REG_8_X86, 
															OPERAND_SIZE::BYTE,5);
		
	const RegisterOperand DH = RegisterOperand(MODE_X86_X64,false,
															REGISTER_FILE::REG_8_X86, 
															OPERAND_SIZE::BYTE,6);

	const RegisterOperand BH = RegisterOperand(MODE_X86_X64,false,
															REGISTER_FILE::REG_8_X86, 
															OPERAND_SIZE::BYTE,7);

	//*******************************************************************************
	// x64 new 8-bit registers

	const RegisterOperand SPL = RegisterOperand(MODE_X86_X64,true,
															REGISTER_FILE::REG_8_X64, 
															OPERAND_SIZE::BYTE,4);

	const RegisterOperand BPL = RegisterOperand(MODE_X86_X64,true,
															REGISTER_FILE::REG_8_X64, 
															OPERAND_SIZE::BYTE,5);
		
	const RegisterOperand SIL = RegisterOperand(MODE_X86_X64,true,
															REGISTER_FILE::REG_8_X64, 
															OPERAND_SIZE::BYTE,6);

	const RegisterOperand DIL = RegisterOperand(MODE_X86_X64,true,
															REGISTER_FILE::REG_8_X64, 
															OPERAND_SIZE::BYTE,7);
	
	const RegisterOperand R8L = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_8_X64,
															OPERAND_SIZE::BYTE,8);

	const RegisterOperand R9L = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_8_X64,
															OPERAND_SIZE::BYTE,9);

	const RegisterOperand R10L = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_8_X64,
															OPERAND_SIZE::BYTE,10);

	const RegisterOperand R11L = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_8_X64,
															OPERAND_SIZE::BYTE,11);

	const RegisterOperand R12L = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_8_X64,
															OPERAND_SIZE::BYTE,12);

	const RegisterOperand R13L = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_8_X64,
															OPERAND_SIZE::BYTE,13);

	const RegisterOperand R14L = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_8_X64,
															OPERAND_SIZE::BYTE,14);

	const RegisterOperand R15L = RegisterOperand(CPU_MODE::X64,true,REGISTER_FILE::REG_8_X64,
															OPERAND_SIZE::BYTE,15);
}