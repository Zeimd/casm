/*****************************************************************************
*
* x86-operand-place.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_OperandPlace_H
#define X86_OperandPlace_H

namespace X86
{
	// Indicates where the operand should be encoded.
	namespace OperandPlace
	{
		enum value
		{
			// Register operand's index added to opcode field.
			// In 64-bit mode, REX.b holds highest bit of operand index.
			opcode = 1 ,

			// Register operand to regField of mod-byte.
			reg_field = 2 ,

			// Register operand to rmField of mod-byte.
			// Memory operand in modRM (+sib).
			rm_field = 3 ,

			// Register operand to VEX.vvvv.
			vex_vvvv = 4 ,

			// Register operand to immediate field.
			imm = 5 ,

			// Do not encode this operand.
			unused = 6 ,

			// Encode operand to imm8 bits [6:4].
			// Used with SSE/AVX instructions in 32-bit mode.
			imm8_bits_6_4 = 7,

			// Encode operand to imm8 bits [7:4] 
			// Used with SSE/AVX instructions in 64-bit mode.
			imm8_bits_7_4 = 8,

			// Encode operand to imm8 bits [3:0]
			// Used with SSE/AVX instructions.
			imm8_bits_3_0 = 9,

			// Unused. Forces enumeration storage format to int32
			force_32b = 1 << 30 ,
		};
	}
}

#endif