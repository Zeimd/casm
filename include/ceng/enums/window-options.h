/*****************************************************************************
*
* window-options.h
*
* Created By Jari Korkala 10/9/2014
*
*****************************************************************************/

#ifndef CENG_WINDOW_OPTIONS_H
#define CENG_WINDOW_OPTIONS_H

#include "../datatypes/basic-types.h"

namespace Ceng
{
	namespace E_WindowOptions
	{
		enum value
		{
			resizable = 1 , // Windowed mode only
		
			topmost = 2 , // Window can't be covered by other windows
		
			// When created, center the window in the given direction
			center_x = 1 << 2 ,
			center_y = 1 << 3 ,
		
			// The window doesn't have caption or system buttons
			popup = 1 << 4 , 
		
			start_minimized = 1 << 5 ,
			start_maximized = 1 << 6 ,

			// The window owns a device context instead of creating one for
			// the duration of drawing.
			own_device_context = 1 << 7,
		
			force32b = Ceng::UINT32(1) << 30 ,
		};
	};
}

#endif