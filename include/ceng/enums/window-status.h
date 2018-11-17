/*****************************************************************************
*
* window-status.h
*
* Created By Jari Korkala 10/9/2014
*
*****************************************************************************/

#ifndef CENG_WINDOW_STATUS_H
#define CENG_WINDOW_STATUS_H

#include "../datatypes/basic-types.h"

namespace Ceng
{
	namespace E_WindowStatus
	{
		enum value
		{
			active = 1 , // Window receives user input
		
			visible = 2 ,  // Should redraw if set
		
			destroyed = 4 , // Should query user for exit
		
			full_client = 8 , // Entire window used as client
		
			force32b = Ceng::UINT32(1) << 30 ,
		};
	};
}

#endif