/*****************************************************************************
*
* render-enums.h
*
* By Jari Korkala 10/2012
*
*****************************************************************************/

#ifndef _CONCEPT2_RENDER_TYPES_H
#define _CONCEPT2_RENDER_TYPES_H

#include "../enums/image-formats.h"
#include "../enums/resource-usage.h"

#include "../enums/swap-effect.h"

#include "../enums/vtx-datatype.h"

#include "../enums/primitive-type.h"
#include "../enums/resource-type.h"

#include "../enums/test-type.h"
#include "../enums/stencil-action.h"

#include "../enums/culling-mode.h"

#include "../enums/shader-semantic.h"
#include "../enums/shader-datatype.h"

#include "../enums/renderer-type.h"
#include "../enums/device-options.h"

namespace Ceng
{
	//**************************************
	// Buffer types
	
	enum CE_BUFFER_TYPE
	{ 
		CE_BUFFER_TYPE_NONE = 0,
		CE_BUFFER_TYPE_COLOR = 1,
		CE_BUFFER_TYPE_DEPTH_STENCIL = 2,
		CE_BUFFER_TYPE_AUX = 4,
		CE_BUFFER_TYPE_DATA = 8, // For internal allocations
		
		CE_BUFFER_TYPE_FORCE32B = UINT32(1) << 30 ,
	};
	
	//******************************
	// Render device types
	
	
	
	//****************************************************************************
	// Multisampling types
	
	
	//******************************************
	// Display mode options
	
	// NOTE: Power of two values only to allow bitwise combining
	enum CE_DISPLAY_FLAG
	{
		CE_DISPLAY_CLIP_TO_WINDOW = 1 , // Clip output to window's client area
		
		// Invalidate depth-stencil after Present() or SetDepthStencil()
		// calls
		CE_DISPLAY_DISCARD_DEPTH_STENCIL = 2 , 
		
		CE_DISPLAY_BACKBUFFER_LOCK = 4 , // Allow application to read backbuffer
		
		CE_DISPLAY_NO_AUTO_ROTATE = 8 , // Application performs display rotation
		
		CE_DISPLAY_FORCE32B = UINT32(1) << 30 ,
	};

} // Namespace Ceng

#endif // Include guard