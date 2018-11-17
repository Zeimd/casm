/*****************************************************************************
*
* buffer-options.h
*
* Created By Jari Korkala 2/3/2015
*
*****************************************************************************/

#ifndef CENG_BUFFER_OPTIONS_H
#define CENG_BUFFER_OPTIONS_H

namespace Ceng
{
	namespace BufferOptions
	{
		enum value
		{
			// Supports mip map generation. Buffer must be a render
			// target and shader resource.
			generate_mip_maps = 1,

			// Share between multiple render devices of the same type.
			shared = 2,

			// Create a cube map from a Texture2DArray with 6 textures.
			texture_cube = 4,

			// Share with mutex.
			shared_mutex = 16,

			// Require interoperability with desktop graphics manager.
			window_manager_compatible = 32 ,

			force32b = 1 << 30 ,
		};
	}
}

#endif