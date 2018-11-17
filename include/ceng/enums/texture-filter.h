/*****************************************************************************
*
* texture-filter.h
*
* Created By Jari Korkala 5/3/2015
*
*****************************************************************************/

#ifndef CENG_TEXTURE_FILTER_H
#define CENG_TEXTURE_FILTER_H

namespace Ceng
{
	namespace TextureMinFilter
	{
		enum value
		{
			nearest = 0 ,

			linear = 1 ,

			nearest_mip_nearest = 2 ,
			nearest_mip_linear = 3 ,

			linear_mip_nearest = 4 ,
			linear_mip_linear = 5 ,

			anisotropic = 6 ,

			texture_one_bit = 7 ,

			compare_nearest = 8 ,
			compare_linear = 9 ,

			compare_nearest_mip_nearest = 10 ,
			compare_nearest_mip_linear = 11 ,

			compare_linear_mip_nearest = 12 ,
			compare_linear_mip_linear = 13 ,

			compare_anisotropic = 14 ,

			force32b = 1 << 30 ,

		};
	}

	namespace TextureMagFilter
	{
		enum value
		{
			nearest = 0 ,

			linear = 1 ,

			anisotropic = 2 ,

			texture_one_bit = 3,

			compare_nearest = 4 ,
			compare_linear = 5 ,
			compare_anisotropic = 6,

			force32b = 1 << 30 ,
		};
	}
}

#endif