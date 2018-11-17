/*****************************************************************************
*
* render-target-view-desc.h
*
* Created By Jari Korkala 9/11/2015
*
*****************************************************************************/

#ifndef CENG_RENDER_TARGET_VIEW_DESC_H
#define CENG_RENDER_TARGET_VIEW_DESC_H

#include "basic-types.h"

#include "../enums/image-formats.h"
#include "../enums/buffer-type.h"

namespace Ceng
{
	struct RenderTargetBuffer
	{
		union
		{
			Ceng::UINT32 firstElement;
			Ceng::UINT32 elementOffset;
		};

		union
		{
			Ceng::UINT32 elementCount;
			Ceng::UINT32 elementSize;
		};
	};

	struct RenderTargetTex2D
	{
		Ceng::UINT32 mipSlice;
	};

	typedef RenderTargetTex2D RenderTargetTex1D;

	class RenderTargetViewDesc
	{
	public:
		Ceng::IMAGE_FORMAT::value format;
		Ceng::BufferType::value type;

		union
		{
			RenderTargetBuffer buffer;
			RenderTargetTex1D tex1d;
			RenderTargetTex2D tex2d;
		};	
	};
}

#endif
