/*****************************************************************************
*
* x86-prefix-bytes.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_PREFIX_BYTES_H
#define X86_PREFIX_BYTES_H

namespace X86
{
	namespace PREFIX_BYTE
	{
		enum value
		{
			// 0x66 : operand size override
			// 
			// Real mode: Use 32-bit operand size.
			// Protected mode / x64 : Use 16-bit operand size.
			OPERAND_SIZE = 1 ,

			// 0x66 : For those cases where it's used without a named meaning.
			BYTE_66 = 1 ,

			// 0xF2 : string operations
			// Repeat ECX times.
			// Terminate if string1[n] == 0
			REPEAT_NOT_ZERO = 2 ,

			// 0xF2 : string operations
			// Repeat ECX times.
			// Terminate if string1[n] == string2[n].
			REPEAT_NOT_EQUAL = 2 ,

			// 0xF2 : For those cases where it's used without a named meaning.
			BYTE_F2 = 2 ,

			// 0xF2 : Hint to start lock elision on memory operand's address.
			XACQUIRE = 2 ,
			
			// 0xF3 : For string operations, repeat ECX times.
			REPEAT = 1 << 2 ,

			// 0xF3 : string operations
			// Repeat ECX times.
			// Terminate if string1[n] != string2[n].
			REPEAT_WHILE_EQUAL = 1 << 2 ,

			// TBA
			REPEAT_ZERO = 1 << 2 ,

			// 0xF3 : For cases where it's explicitly required without being one of the named cases
			BYTE_F3 = 1 << 2 ,

			// 0xF3 : Hint to release lock elision on memory operand's address.
			XRELEASE = 1 << 2 ,

			// 0x2E : Memory operand is from code segment.
			CS_OVERRIDE = 1 << 3 ,

			// 0x36 : Memory operand is from stack segment.
			SS_OVERRIDE = 1 << 4 ,

			// 0x3E : Memory operand is from data segment.
			DS_OVERRIDE = 1 << 5 ,

			// 0x26 : Memory operand is from extra segment.
			ES_OVERRIDE = 1 << 6 ,

			// 0x64 : Memory operand is from F-segment.
			FS_OVERRIDE = 1 << 7 ,

			// 0x65 : Memory operand is from G-segment.
			GS_OVERRIDE = 1 << 8 ,

			// 0x2E : branch not taken hint (only with Jcc instructions)
			BRANCH_TAKEN = 1 << 9 ,

			// 0x3E : branch taken hint (only with Jcc instructions)
			BRANCH_NOT_TAKEN = 1 << 10 ,

			// 0x67 : Protected mode / x64: Use real mode addressing.
			ADDRESS_SIZE = 1 << 11 ,

			// 0xF0 : Do as atomic operation.
			LOCK = 1 << 12 ,

			NONE = 1 << 13 ,

			// Forces enum storage to int32
			FORCE_32B = 1 << 30 ,
		};
	}
}

#endif