/*****************************************************************************
*
* x86-operand-types.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_OPERAND_TYPES_H
#define X86_OPERAND_TYPES_H

namespace X86
{
	namespace OPERAND_TYPE
	{
		enum value
		{
			// Register operand
			REG = 1 ,
			
			// Register or memory operand
			REG_MEM = 3 ,

			// Memory operand
			MEM = 2 ,

			// Immediate operand
			IMM = 4 ,

			FORCE_32B = 1 << 30 ,
		};
	}
	
}

#endif