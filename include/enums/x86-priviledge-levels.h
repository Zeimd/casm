/*****************************************************************************
*
* x86-priviledge-levels.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_PRIVILEDGE_LEVELS_H
#define X86_PRIVILEDGE_LEVELS_H

namespace X86
{
	namespace PRIVILEDGE_LEVEL
	{
		enum value
		{
			SYSTEM = 1 ,
			USER = 1 << 3 ,
			
			ANY = SYSTEM | USER ,

			FORCE_32B = 1 << 30 ,
		};
	}
}

#endif