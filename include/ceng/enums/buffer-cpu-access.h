/*****************************************************************************
*
* buffer-cpu-access.h
*
* Created By Jari Korkala 2/3/2015
*
*****************************************************************************/

#ifndef CENG_BUFFER_CPU_ACCESS_H
#define CENG_BUFFER_CPU_ACCESS_H

namespace Ceng
{
	namespace Buffer_CPU_Access
	{
		enum value
		{
			write = 1 ,
			read = 2 ,

			force32b = 1 << 30,
		};
	}
}

#endif