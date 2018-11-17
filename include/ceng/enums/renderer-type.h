/*****************************************************************************
*
* renderer-type.h
*
* By Jari Korkala 5/2013
*
*****************************************************************************/

#ifndef _CENG_RENDERER_TYPE_H
#define _CENG_RENDERER_TYPE_H

namespace Ceng
{
	namespace RENDERER_TYPE
	{
		enum value
		{
			SOFTWARE = 1 , // Use software rendering

			D3D_9 = 2 , // Use Direct3D 9

			opengl_32 = 3 ,

			FORCE32B = 1 << 30 ,
		};
	};
};

#endif