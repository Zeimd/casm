/*****************************************************************************
*
* shader-resource-view-desc.h
*
* Created By Jari Korkala 5/3/2015
*
*****************************************************************************/

#ifndef CENG_SHADER_RESOURCE_VIEW_DESC_H
#define CENG_SHADER_RESOURCE_VIEW_DESC_H

#include "../enums/image-formats.h"
#include "../enums/buffer-type.h"

#include "shader-res-buffer.h"
#include "shader-res-tex1d.h"
#include "shader-res-tex2d.h"

#include "shader-res-array-tex1d.h"
#include "shader-res-array-tex2d.h"

#include "shader-res-tex2d-multi.h"
#include "shader-res-array-tex2d-multi.h"

#include "shader-res-tex3d.h"
#include "shader-res-cubemap.h"

namespace Ceng
{
	class ShaderResourceViewDesc
	{
	public:
		IMAGE_FORMAT::value format;

		BufferType::value dimensions;

		union
		{
			ShaderResourceViewBuffer buffer;

			ShaderResourceViewTexture1D tex1d;
			ShaderResourceViewTexture2D tex2d;

			ShaderResourceViewArrayTexture1D arrayTex1d;
			ShaderResourceViewArrayTexture2D arrayTex2d;

			ShaderResourceViewTexture2D_Multi tex2dMulti;
			ShaderResourceViewTexture2D_Multi arrayTex2dMulti;

			ShaderResourceViewTexture3D tex3d;
			ShaderResourceViewCubeMap cubeMap;
		};

	};
}

#endif