/*****************************************************************************
*
* shader-res-array.h
*
* Created By Jari Korkala 5/3/2015
*
*****************************************************************************/

#ifndef CENG_SHADER_RES_ARRAY_H
#define CENG_SHADER_RES_ARRAY_H

#include "basic-types.h"

namespace Ceng
{
	class ShaderResourceViewArray
	{
		Ceng::UINT32 firstArraySlice;
		Ceng::UINT32 arraySize;
	};
}

#endif