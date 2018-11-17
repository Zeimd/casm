/*****************************************************************************
*
* render-context.h
*
* Created By Jari Korkala 2/3/2015
*
*****************************************************************************/

#ifndef CENG_RENDER_CONTEXT_H
#define CENG_RENDER_CONTEXT_H

#include "base-interface.h"

#include "../datatypes/return-val.h"

#include "../enums/primitive-type.h"

#include "shader-resource-view.h"
#include "sampler-state.h"

namespace Ceng
{
	class RenderTarget;
	class VertexShader;
	class PixelShader;

	class VertexFormat;
	class VertexBuffer;
	class CE_Color;

//	class DepthStencilDesc;
	class RasterizerState;
	struct Rectangle;

	class BlendState;

	class ShaderProgram;

	class IndexBuffer;

	class RenderTargetView;

	class DepthStencilState;

	class RenderContext : public BASE_INTERFACE
	{
	protected:

		virtual ~RenderContext()
		{
		}

	public:

		RenderContext()
		{
		}

		virtual void Release() = 0;

		virtual const Ceng::CRESULT ClearTarget(Ceng::RenderTarget *renderTarget, const CE_Color &color) = 0;

		virtual const Ceng::CRESULT ClearDepth(const FLOAT32 depth) = 0;

		virtual const Ceng::CRESULT ClearDepthStencil(const FLOAT32 depth, const UINT32 stencil) = 0;

		virtual const Ceng::CRESULT SetVertexFormat(Ceng::VertexFormat *formatPtr) = 0;
	
		virtual const Ceng::CRESULT SetVertexStream(const Ceng::UINT32 index, Ceng::VertexBuffer *source,const Ceng::UINT32 stride,const Ceng::UINT32 offset) = 0;

		virtual const Ceng::CRESULT SetIndexBuffer(Ceng::IndexBuffer *indexBuffer) = 0;

		virtual const Ceng::CRESULT SetShaderProgram(Ceng::ShaderProgram *program) = 0;

		virtual const Ceng::CRESULT StartScene() = 0;
		virtual const Ceng::CRESULT EndScene() = 0;
	
		virtual const Ceng::CRESULT DrawPrimitive(const Ceng::PRIMITIVE_TYPE::value type,
										const Ceng::UINT32 firstVertex,const Ceng::UINT32 primitives) = 0;

		virtual const Ceng::CRESULT DrawIndexed(const Ceng::PRIMITIVE_TYPE::value type, const Ceng::UINT32 firstVertex, const Ceng::UINT32 primitives) = 0;

		virtual const Ceng::CRESULT SetDepthStencilState(Ceng::DepthStencilState *state) = 0;

		virtual const Ceng::CRESULT SetRasterizerState(const Ceng::RasterizerState *state) = 0;

		virtual const Ceng::CRESULT SetScissorRect(const Ceng::Rectangle *rect) = 0;

		/**
		 * x,y = bottom-left corner of viewport.
		 */
		virtual const Ceng::CRESULT SetViewport(const Ceng::INT32 x, const Ceng::INT32 y, const Ceng::INT32 width, const Ceng::INT32 height) = 0;

		virtual const Ceng::CRESULT SetPixelShaderResource(const Ceng::UINT32 index,ShaderResourceView *resource) = 0;
		
		virtual const Ceng::CRESULT SetPixelShaderSamplerState(const Ceng::UINT32 index, SamplerState *sampler) = 0;

		virtual const Ceng::CRESULT SetRenderTarget(const Ceng::UINT32 index, RenderTargetView *view) = 0;

		virtual const Ceng::CRESULT SetBlendState(BlendState *state, Ceng::FLOAT32 *blendFactor) = 0;

		virtual const Ceng::CRESULT SetDepth(RenderTargetView *view) = 0;

		virtual const Ceng::CRESULT SetDepthStencil(RenderTargetView *view) = 0;

		virtual const Ceng::CRESULT GetFrontBufferTarget(RenderTargetView **frontBuffer) = 0;

	};
}

#endif