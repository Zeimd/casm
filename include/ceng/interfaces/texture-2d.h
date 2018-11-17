/*****************************************************************************
*
* texture-2d.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_TEXTURE_2D_H
#define _CENG_TEXTURE_2D_H

#include "../datatypes/return-val.h"

#include "render-resource.h"

namespace Ceng
{
	struct BufferData2D;

	class ShaderResourceViewDesc;
	class ShaderResourceView;

	class RenderTargetView;
	class RenderTargetViewDesc;

	class RenderTarget;

	class Texture2D : public RenderResource
	{
	protected:
		
		bool renderTarget;
		
		virtual ~Texture2D()
		{
		}
	
	public:
		Texture2D()
		{
			renderTarget = false;
		}
		
		virtual const CRESULT GetBufferData2D(Ceng::BufferData2D *dataPtr)=0;
		
		virtual const Ceng::CRESULT GetShaderViewTex2D(const Ceng::ShaderResourceViewDesc &desc,Ceng::ShaderResourceView **resourceView) = 0;

		virtual const Ceng::CRESULT GetRenderTargetView(const Ceng::RenderTargetViewDesc &desc,
			Ceng::RenderTargetView **targetView) = 0;

		virtual const Ceng::CRESULT GetSubResourceData(const Ceng::UINT32 mipLevel,void *destPtr) = 0;
	};
	
};

#endif