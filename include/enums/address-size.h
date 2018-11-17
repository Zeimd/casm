/*****************************************************************************
*
* address-size.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef CASM_ADDRESS_SIZE_H
#define CASM_ADDRESS_SIZE_H

namespace Casm
{
	namespace ADDRESS_SIZE
	{
		enum value
		{
			WORD = 2 ,

			DWORD = 4 ,

			QWORD = 8 ,

			FORCE32_B = 1 << 30 ,
		};
	}
}

#endif