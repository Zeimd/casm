/*****************************************************************************
*
* resource-usage.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_RESOURCE_USAGE_H
#define _CENG_RESOURCE_USAGE_H

namespace Ceng
{
	namespace RESOURCE_USAGE
	{
		enum value
		{
			TEXTURE = 1 ,
			RENDER_TARGET = 2,
			DEPTH_STENCIL = 4,
		
			FORCE_32B = 1 << 30 ,
		};

	}; // namespace RESOURCE_USAGE

}; // namespace Ceng

#endif