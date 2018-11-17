/*****************************************************************************
*
* culling-mode.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_CULLING_MODE_H
#define _CENG_CULLING_MODE_H

namespace Ceng
{
	namespace CULLING_MODE
	{
		enum value
		{
			NONE = 1 ,
			FRONT = 2 ,
			BACK = 3 ,

			FORCE32B = 1 << 30 ,
		};
	}
};

#endif