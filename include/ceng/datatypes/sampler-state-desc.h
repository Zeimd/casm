/*****************************************************************************
*
* sampler-state-desc.h
*
* Created By Jari Korkala 5/3/2015
*
******************************************************************************/

#ifndef CENG_SAMPLER_STATE_DESC_H
#define CENG_SAMPLER_STATE_DESC_H

#include "basic-types.h"

#include "../enums/texture-filter.h"
#include "../enums/texture-address-mode.h"
#include "../enums/test-type.h"

namespace Ceng
{
	class SamplerStateDesc
	{
	public:
		TextureMinFilter::value minFilter;
		TextureMagFilter::value magFilter;

		TextureAddressMode::value addressU;
		TextureAddressMode::value addressV;
		TextureAddressMode::value addressW;

		Ceng::FLOAT32 mipLodBias;
		Ceng::UINT32 maxAnisotrophy;

		Ceng::TEST_TYPE::value comparisonType;

		Ceng::FLOAT32 borderColor[4];
		Ceng::FLOAT32 minLod;
		Ceng::FLOAT32 maxLod;
	};
}

#endif