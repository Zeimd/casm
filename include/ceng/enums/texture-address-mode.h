/*****************************************************************************
*
* texture-address-mode.h
*
* Created By Jari Korkala 5/3/2015
*
*****************************************************************************/

#ifndef CENG_TEXTURE_ADDRESS_MODE_H
#define CENG_TEXTURE_ADDRESS_MODE_H

namespace Ceng
{
	namespace TextureAddressMode
	{
		enum value
		{
			// Use u-floor(u) as texture coordinate.
			wrap = 1 ,

			// u values between [0,1] use normal addressing,
			// values between [1,2] are mirrored, between [2,3] normal
			// and so on.
			mirror = 2 ,

			// Limit u to [0,1] so that u < 0 becomes 0 and u > 1 becomes 1.
			clamp = 3 ,

			// Texture samples out of borders are set to border color.
			border = 4 ,

			// Clamps abs(u).
			mirror_once = 5 ,

			force32b = 1 << 30 ,
		};
	}
}

#endif