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
			/**
			 * Real mode: Use 32-bit operand size.
			 * Protected mode / x64 : Use 16-bit operand size.
			 */
			OPERAND_SIZE = 1 ,
			BYTE_66 = 1 ,

			/**
			 * For string operations, repeat ECX times.
			 * Terminate if string1[n] == string2[n].
			 */
			REPEAT_NOT_ZERO = 2 ,
			REPEAT_NOT_EQUAL = 2 ,

			BYTE_F2 = 2 ,

			/**
			 * Hint to start lock elision on memory operand's address.
			 */
			XACQUIRE = 2 ,
			
			/**
			 * For string operations, repeat ECX times.
			 */
			REPEAT = 1 << 2 ,

			/**
			 * For string operations, repeat ECX times.
			 * Terminate if string1[n] != string2[n].
			 */
			REPEAT_WHILE_EQUAL = 1 << 2 ,
			REPEAT_ZERO = 1 << 2 ,

			BYTE_F3 = 1 << 2 ,

			/**
			 * Hint to release lock elision on memory operand's address.
			 */
			XRELEASE = 1 << 2 ,

			/**
			 * Memory operand is from code segment.
			 */
			CS_OVERRIDE = 1 << 3 ,

			/**
			 * Memory operand is from stack segment.
			 */
			SS_OVERRIDE = 1 << 4 ,

			/**
			 * Memory operand is from data segment.
			 */
			DS_OVERRIDE = 1 << 5 ,

			/**
			 * Memory operand is from extra segment.
			 */
			ES_OVERRIDE = 1 << 6 ,

			/**
			 * Memory operand is from F-segment.
			 */
			FS_OVERRIDE = 1 << 7 ,

			/**
			 * Memory operand is from G-segment.
			 */
			GS_OVERRIDE = 1 << 8 ,

			BRANCH_TAKEN = 1 << 9 ,

			BRANCH_NOT_TAKEN = 1 << 10 ,

			/**
			 * Protected mode / x64: Use real mode addressing.
			 */
			ADDRESS_SIZE = 1 << 11 ,

			/**
			 * Do as atomic operation.
			 */
			LOCK = 1 << 12 ,

			NONE = 1 << 13 ,

			FORCE_32B = 1 << 30 ,
		};
	}
}

#endif