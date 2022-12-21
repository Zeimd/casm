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

			// Unused. Forces enumeration storage format to int32
			force_32b = 1 << 30 ,
		};
	}
}

#endif