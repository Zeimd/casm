/*****************************************************************************
*
* shader-res-array-tex1d.h
*
* Created By Jari Korkala 5/3/2015
*
*****************************************************************************/

#ifndef CENG_SHADER_RES_ARRAY_TEX1D_H
#define CENG_SHADER_RES_ARRAY_TEX1D_H

#include "shader-res-tex1d.h"
#include "shader-res-array.h"

namespace Ceng
{
	class ShaderResourceViewArrayTexture1D : public ShaderResourceViewTexture1D,public ShaderResourceViewArray
	{
	public:
	
	};
}

#endif