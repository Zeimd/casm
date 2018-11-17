/*****************************************************************************
*
* thread-priority.h
*
* Created By Jari Korkala 4/9/2014
*
*****************************************************************************/

#ifndef CENG_THREAD_PRIORITY_H
#define CENG_THREAD_PRIORITY_H

#include "../datatypes/basic-types.h"

namespace Ceng
{
	namespace E_ThreadPriority
	{
		enum value
		{
			background_start = 1 ,

			background_end = 2 ,

			idle = 3 ,

			lowest = 4 ,

			below_normal = 5 ,

			normal = 6 ,

			above_normal = 7 ,

			highest = 8 ,

			real_time = 9 ,

			force32_b = Ceng::UINT32(1) << 30 ,
		};
	}
}

#endif