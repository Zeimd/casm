/*****************************************************************************
*
* x86-param-list.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_PARAM_LIST_H
#define X86_PARAM_LIST_H

namespace X86
{
	namespace PARAM_LIST
	{
		enum value
		{
			REG_REG = 1 ,
			REG_MEM = 1 << 1 ,
			MEM_REG = 1 << 2 ,

			REG_IMM = 1 << 3 ,

			TWO_OP = REG_REG | REG_MEM | MEM_REG | REG_IMM ,

			REG_REG_IMM = 1 << 4 ,
			REG_MEM_IMM = 1 << 5 ,

			LEGACY_THREE_OP = REG_REG_IMM | REG_MEM_IMM ,

			// Available in VEX encoding

			REG_REG_REG = 1 << 6 ,
			REG_REG_MEM = 1 << 7 ,
			MEM_REG_REG = 1 << 8 ,

			VEX_THREE_OP = REG_REG_REG | REG_REG_MEM | MEM_REG_REG ,

			/**
			 * Four register operands.
			 */
			REG_REG_REG_REG = 1 << 9 ,

			REG_REG_MEM_REG = 1 << 10 ,

			/**
			 * Three register operands. 
			 * Fourth operand is immediate byte.
			 */
			REG_REG_REG_IMM = 1 << 11 ,

			REG_REG_MEM_IMM = 1 << 12 ,
			
			VEX_FOUR_OP = REG_REG_REG_REG | REG_REG_MEM_REG | REG_REG_REG_IMM | REG_REG_MEM_IMM ,

			REG = 1 << 13 ,
			MEM = 1 << 14 ,
			IMM = 1 << 15 ,

			ONE_OP = REG | MEM | IMM ,

			FORCE_32B = 1 << 30 ,
		};
	};
}

#endif
