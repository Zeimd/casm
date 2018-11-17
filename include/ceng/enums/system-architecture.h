/*****************************************************************************
*
* system-architecture.h
*
* Created By Jari Korkala 14/9/2014
*
*****************************************************************************/

#ifndef CENG_SYSTEM_ARCHITECTURE_H
#define CENG_SYSTEM_ARCHITECTURE_H

namespace Ceng
{
	namespace E_SysArchitecture
	{
		enum value
		{
			x86 = 1 ,
			x64 = 2 ,

			unknown = 1 << 29 , 

			force_32b = 1 << 30 ,
		};
	}
}

#endif