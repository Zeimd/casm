/*****************************************************************************
*
* display-mode.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_DISPLAY_MODE_H
#define _CENG_DISPLAY_MODE_H

#include "../datatypes/basic-types.h"

#include "../enums/image-formats.h"
#include "../enums/scanline-order.h"
#include "../enums/mode-scaling.h"

namespace Ceng
{	
	struct DisplayMode
	{
		Ceng::UINT32 width;
		Ceng::UINT32 height;
		Ceng::UINT32 refreshHz;
		Ceng::IMAGE_FORMAT::value format;
		Ceng::ScanlineOrder::value scanlineOrder;
		Ceng::ModeScaling::value scaling;		
	};	
};

#endif