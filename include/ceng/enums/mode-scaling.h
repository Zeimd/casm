/*****************************************************************************
*
* mode-scaling.h
*
* Created By Jari Korkala 3/3/2015
*
*****************************************************************************/

#ifndef CENG_MODE_SCALING_H
#define CENG_MODE_SCALING_H

namespace Ceng
{
	namespace ModeScaling
	{
		enum value
		{
			unspecified = 0 ,
			centered = 1 ,
			stretched = 2 ,

			force32b = 1 << 30 ,
		};
	}
}

#endif