/*****************************************************************************
*
* cpu-feature-info.h
*
* Created By Jari Korkala 12/9/2014
*
*****************************************************************************/

#ifndef CENG_CPU_FEATURE_INFO_H
#define CENG_CPU_FEATURE_INFO_H

namespace Ceng
{
	namespace E_CpuFeatureInfo
	{
		enum value
		{
			ok = 1 ,
			not_supported = 2 ,
			no_os_support = 4 ,

			unknown_feature = 8 ,

			force_32b = 1 << 30 ,
		};
	}
}

#endif

