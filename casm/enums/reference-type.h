/*****************************************************************************
*
* reference-type.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef CASM_REFERENCE_TYPE_H
#define CASM_REFERENCE_TYPE_H

namespace Casm
{
	namespace REFERENCE_TYPE
	{
		enum value
		{
			ADDRESS = 1 ,
			IP_RELATIVE = 2 ,

			FORCE_32B = 1 << 30 ,
		};
	}
}

#endif