/*****************************************************************************
*
* cubemap.h
*
* By Jari Korkala 20/11/2015
*
* For purposes of OpenGL compatibility. Otherwise TextureArray2D would
* be used for cube maps.
*
*****************************************************************************/

#ifndef CENG_CUBEMAP_H
#define CENG_CUBEMAP_H

#include "base-interface.h"

#include "../datatypes/return-val.h"

#include "../datatypes/shader-resource-view-desc.h"

#include "../enums/cubemap-face.h"

namespace Ceng
{
	struct BufferData2D;

	class ShaderResourceView;

	class Cubemap : public BASE_INTERFACE
	{
	protected:
		virtual ~Cubemap()
		{
		}

	public:
		Cubemap()
		{
		}

		virtual const CRESULT GetBufferData2D(Ceng::BufferData2D *dataPtr) = 0;

		virtual const Ceng::CRESULT GetShaderViewCubemap(const Ceng::ShaderResourceViewDesc &desc, Ceng::ShaderResourceView **resourceView) = 0;

		virtual const Ceng::CRESULT GetSubResourceData(const Ceng::CubemapFace::value face,const Ceng::UINT32 mipLevel, const Ceng::IMAGE_FORMAT::value destFormat,void *destPtr) = 0;

		virtual const Ceng::CRESULT SetSubResourceData(const Ceng::CubemapFace::value face, const Ceng::UINT32 mipLevel, const Ceng::IMAGE_FORMAT::value sourceFormat, void *sourcePtr) = 0;
	};
}

#endif