/*****************************************************************************
*
* x86-operand-place.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_OPERAND_PLACE_H
#define X86_OPERAND_PLACE_H

namespace X86
{
	namespace OPERAND_PLACE
	{
		enum value
		{
			/**
			 * Register operand's index added to opcode field.
			 */
			OPCODE = 1 ,

			/**
			 * Register operand to regField of mod-byte.
			 */
			REG_FIELD = 2 ,

			/**
			 * Register operand to rmField of mod-byte.
			 * Memory operand in modRM (+sib).
			 */
			RM_FIELD = 3 ,

			/**
			 * Register operand to VEX.vvvv.
			 */
			VEX_VVVV = 4 ,

			/**
			 * Register operand to immediate field.
			 */
			IMM = 5 ,

			/**
			 * Do not encode this operand.
			 */
			NOT_USED = 6 ,

			FORCE_32B = 1 << 30 ,
		};
	}
}

#endif