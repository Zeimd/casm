/*****************************************************************************
*
* swap-options.h
*
* Created By Jari Korkala 3/3/2015
*
*****************************************************************************/

#ifndef CENG_SWAP_OPTIONS_H
#define CENG_SWAP_OPTIONS_H

namespace Ceng
{
	namespace SwapOptions
	{
		enum value
		{
			// Turn off automatic image rotation when monitor is rotated.
			// Full-screen mode only.
			not_prerotated = 1 ,
			
			// Allow resizing of window. Automatic windowed to full screen
			// mode selection.
			allow_mode_switch = 1 << 1 ,

			// Require interoperability with window manager graphics.
			window_manager_support = 1 << 2 ,

			// Swap chain might contain protected content. Creation succeeds only
			// when GPU and display support protected content.
			restricted_content = 1 << 3 ,

			// Shared objects created within the swap chain must be protected
			// from access to shared surfaces.
			restrict_shared_resource = 1 << 4 ,

			// Restrict output to local displays. Prevents screen capture.
			display_only = 1 << 5 ,

			// Rendering doesn't begin while a frame is being presented.
			frame_latency_waitable = 1 << 6 ,

			// Foreground layer of a multi-plane rendering.
			foreground_layer = 1 << 7 ,

			force32b = 1 << 30 ,
		};
	}
}

#endif