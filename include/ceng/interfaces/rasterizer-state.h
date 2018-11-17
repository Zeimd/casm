/*****************************************************************************
*
* rasterizer-state.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_RASTERIZER_STATE_H
#define _CENG_RASTERIZER_STATE_H

#include "../datatypes/boolean.h"

#include "render-resource.h"
#include "../enums/culling-mode.h"

namespace Ceng
{
	class RasterizerState
	{
	public:
		CULLING_MODE::value cullingMode;
		Ceng::BOOL frontClockwise; // If true, assumes front faces have clockwise vertex winding

		Ceng::BOOL scissorEnable;

	public:
		RasterizerState()
		{
			cullingMode = Ceng::CULLING_MODE::BACK;
			frontClockwise = false;
			scissorEnable = false;
		}
	};
};

#endif