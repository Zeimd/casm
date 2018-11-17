/*****************************************************************************
*
* cpu-core-type.h
*
* Created By Jari Korkala 14/9/2014
*
*****************************************************************************/

#ifndef CENG_CORE_TYPE_H
#define CENG_CORE_TYPE_H

namespace Ceng
{
	namespace E_CpuCoreType
	{
		enum value
		{
			physical = 1 ,
			logical = 2 ,

			force_32b = 1 << 30 ,
		};
	}
}

#endif