/*****************************************************************************
*
* graphics-adapter-desc.h
*
* Created By Jari Korkala 1/3/2015
***********************************************
* Updated By Jari Korkala 3/3/2015
*
* - GraphicsAdapter refactored as an interface. Platform abstract
*   information here.
*
*****************************************************************************/

#ifndef GRAPHICS_ADAPTER_H
#define GRAPHICS_ADAPTER_H

#include "ce-string.h"

#include "../enums/graphics-adapter-state.h"

namespace Ceng
{
	class GraphicsAdapterDesc
	{
	public:
		Ceng::String description;
		
		Ceng::UINT32 stateFlags;
	};
}

#endif