/*****************************************************************************
*
* x86-register-types.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_REGISTER_TYPES_H
#define X86_REGISTER_TYPES_H

namespace X86
{
	namespace REGISTER_FILE
	{
		enum value
		{
			EMPTY = 0 ,

			/**
			 * Classic 8-bit registers.
			 * AL,BL,CL,DL,AH,BH,CH,DH.
			 */
			REG_8_X86 = 1 ,

			/**
			 * x64 byte registers
			 * AL,BL,CL,DL
			 * REX: SPL,BPL,DIL,SIL, and R8L-R15L.
			 */
			REG_8_X64 = 2 ,

			REG_16 = 1 << 2 ,
			REG_32 = 1 << 3 ,
			REG_64 = 1 << 4 ,

			ALU = REG_8_X86 | REG_8_X64 | REG_16 | REG_32 | REG_64 ,

			REG_MM = 1 << 5 ,
			REG_XMM = 1 << 6 ,
			REG_YMM = 1 << 7 ,

			/**
			 * Instruction pointer for special cases.
			 */
			RIP = 1 << 29 ,

			REGISTER_FILE_FORCE32_B = 1 << 30 ,
		};
	}
}

#endif