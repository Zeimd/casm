/*****************************************************************************
*
* cubemap-face.h
*
* By Jari Korkala 25/11/2015
*
*****************************************************************************/

#ifndef CENG_CUBEMAP_FACE_H
#define CENG_CUBEMAP_FACE_H

namespace Ceng
{
	namespace CubemapFace
	{
		enum value
		{
			positive_x = 0 ,
			negative_x = 1 ,
			positive_y = 2 ,
			negative_y = 3 ,
			positive_z = 4 ,
			negative_z = 5 ,

			force_32b = 1 << 30 ,
		};
	}
}

#endif