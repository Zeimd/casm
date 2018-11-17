/*****************************************************************************
*
* buffer-type.h
*
* Created By Jari Korkala 2/3/2015
*
*****************************************************************************/

#ifndef CENG_BUFFER_TYPE_H
#define CENG_BUFFER_TYPE_H

namespace Ceng
{
	namespace BufferType
	{
		enum value
		{
			unknown = 0 ,

			// For vertex,index and constant buffer
			buffer = 1 ,

			texture_1d = 2 ,
			texture_2d = 3 ,
			texture_3d = 4 ,

			texture_array_1d = 5 ,
			texture_array_2d = 6 ,
			texture_array_3d = 7 ,

			cube_map = 8 ,
			array_cube_map = 9 ,

			back_buffer = 10 ,

			texture_2d_multi = 11 ,
			array_texture_2d_multi = 12 ,

			force_32b = 1 << 30 ,

		};
	}
}

#endif