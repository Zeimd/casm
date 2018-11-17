/*****************************************************************************
*
* device-options.h
*
* By Jari Korkala 5/2013
*
*****************************************************************************/

#ifndef _CENG_DEVICE_OPTIONS_H
#define _CENG_DEVICE_OPTIONS_H

namespace Ceng
{
	namespace E_DeviceOption
	{
		enum value
		{
			disable_print_screen = 1 ,
		
			multi_threaded = 2 ,
		
			no_window_changes = 4 ,
		
			allow_screen_saver = 8 ,
		
			force_32b = 1 << 30 ,
		};
	};	
};

#endif