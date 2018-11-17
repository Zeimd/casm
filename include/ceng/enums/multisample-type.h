/*****************************************************************************
*
* multisample-type.h
*
* Created By Jari Korkala 8/2014
*
*****************************************************************************/

#ifndef CENG_MULTISAMPLE_TYPE_H
#define CENG_MULTISAMPLE_TYPE_H

#include "../datatypes/basic-types.h"

namespace Ceng
{
	namespace MULTISAMPLE_TYPE
	{
		enum value
		{
			NONE = 0 ,
		
			NONMASKABLE = 1 ,
		
			SAMPLE_2 = 2 ,
			SAMPLE_3 = 3 ,
			SAMPLE_4 = 4 ,
			SAMPLE_5 = 5 ,
			SAMPLE_6 = 6 ,
			SAMPLE_7 = 7 ,
			SAMPLE_8 = 8 ,
			SAMPLE_9 = 9 ,
			SAMPLE_10 = 10 ,
			SAMPLE_11 = 11 ,
			SAMPLE_12 = 12 ,
			SAMPLE_13 = 13 ,
			SAMPLE_14 = 14 ,
			SAMPLE_15 = 15 ,
			SAMPLE_16 = 16 ,
		
			FORCE32B = Ceng::UINT32(1) << 30 ,
		};
	};
	
}

#endif