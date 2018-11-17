/*****************************************************************************
*
* shader-res-tex2d.h
*
* Created By Jari Korkala 5/3/2015
*
*****************************************************************************/

#ifndef CENG_SHADER_RES_TEX2D_H
#define CENG_SHADER_RES_TEX2D_H

#include "basic-types.h"

namespace Ceng
{
	class ShaderResourceViewTexture2D
	{
	public:

		Ceng::UINT32 baseMipLevel;
		Ceng::UINT32 maxMipLevel;
	};
}

#endif