/*****************************************************************************
*
* resource-type.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_RESOURCE_TYPE_H
#define _CENG_RESOURCE_TYPE_H

namespace Ceng
{
	namespace RESOURCE_TYPE 
	{
		enum value
		{
			UNKNOWN,
			
			TEXTURE,
			
			RENDER_TARGET,
			VERTEX_BUFFER,
			INDEX_BUFFER,
			
			VERTEX_FORMAT,
			VERTEX_SHADER,
		
			PIXEL_SHADER,
		
			FORCE32B = 1 << 30 ,
		};
	};
	
};

#endif