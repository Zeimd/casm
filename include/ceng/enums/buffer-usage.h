/*****************************************************************************
*
* buffer-usage.h
*
* Created By Jari Korkala 2/3/2015
*
*****************************************************************************/

#ifndef CENG_BUFFER_USAGE_H
#define CENG_BUFFER_USAGE_H

namespace Ceng
{
	namespace BufferUsage
	{
		enum value
		{

			gpu_read_write = 0 ,
			gpu_read_only = 1 ,

			// GPU read-write, CPU write
			gpu_cpu_write = 2 ,
			
			// GPU read-write, CPU read-write
			gpu_to_cpu = 3 ,

			force32b = 1 << 30 ,
		};
	}
}

#endif