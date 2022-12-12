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
			REG = 1 ,
			
			REG_MEM = 3 ,

			MEM = 2 ,
			IMM = 4 ,

			FORCE_32B = 1 << 30 ,
		};
	}
	
}

#endif