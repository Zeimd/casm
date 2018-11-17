/*****************************************************************************
*
* render-device.h
*
* By Jari Korkala 6/2011
*
* Update 10/2012 : Removed references to platform layer
*
* Update 4/2013 : Moved all interfaces to separate files
*
* Platform-independent interface for 3d render devices.
*
*****************************************************************************/

#ifndef _CONCEPT2_RENDER_DEVICE_H
#define _CONCEPT2_RENDER_DEVICE_H

#include <vector>

#include "base-interface.h"

#include "image-buffer.h"

#include "render-enums.h"
#include "../math/ce-vector.h"
#include "../math/ce-matrix.h"

#include "render-resource.h"

#include "vertex-decl.h"

#include "depth-stencil-desc.h"

#include "rasterizer-state.h"

#include "../datatypes/sampler-state-desc.h"

#include "../datatypes/shader-resource-view-desc.h"

#include "../datatypes/tex2d-desc.h"
#include "../datatypes/tex2d-desc-gl.h"

#include "../datatypes/sub-resource-data.h"

#include "../datatypes/blend-state-desc.h"

#include "../datatypes/render-target-view-desc.h"

namespace Ceng
{
	class CE_Color;

	class Cubemap;
	class Texture2D;
	
	class VertexBuffer;
	class VertexFormat;

	class VertexShader;
	class PixelShader;

	class RenderTargetView;
	class ShaderResourceView;
	class SamplerState;

	class DepthStencilState;

	class IndexBuffer;

	class BlendState;

	class ShaderProgram;

	class ShaderConstant;
		
	//**************************************************
	// Render device interface

	class RenderDevice : public Ceng::BASE_INTERFACE
	{
	protected:
		virtual ~RenderDevice()
		{
		}
	
	public:
		RenderDevice()
		{
		}

		virtual const Ceng::CRESULT CreateVertexShader(const Ceng::StringUtf8 &shaderText, Ceng::VertexShader **shaderPtr) = 0;
		
		virtual CRESULT CreateVertexFormat(const std::vector<Ceng::VertexDeclData> 
											&vertexDecl,
											Ceng::VertexFormat **format)=0;
		
		virtual CRESULT CreateVertexBuffer(UINT32 vertexSizeBytes,
											UINT32 vertexNum,
											UINT32 usage,
											Ceng::VertexBuffer **destPtr)=0;

		virtual const Ceng::CRESULT CreateIndexBuffer(const Ceng::UINT32 elementSize, const Ceng::UINT32 elements,
			const Ceng::UINT32 usage, void *initialData,Ceng::IndexBuffer **destPtr) = 0;

		/**
		 * Returns recommended maximum number of vertices in a vertex buffer.
		 */
		virtual const Ceng::UINT32 GetOptimalVertexElements() = 0;

		/**
		* Returns recommended maximum number of indices in an index buffer.
		*/
		virtual const Ceng::UINT32 GetOptimalIndexElements() = 0;

		virtual const Ceng::CRESULT CreatePixelShader(const Ceng::StringUtf8 &shaderText, Ceng::PixelShader **shaderPtr) = 0;

		virtual const Ceng::CRESULT CreateShaderProgram(Ceng::VertexShader *vertexShader, Ceng::PixelShader *pixelShader, Ceng::ShaderProgram **program) = 0;

		virtual const CRESULT CreateSamplerState(const SamplerStateDesc &desc,
			Ceng::SamplerState **out_state) = 0;

		virtual const CRESULT CreateShaderResourceView(RenderResource *resource,
			ShaderResourceViewDesc &desc,
			ShaderResourceView **out_resourceView) = 0;

		virtual const CRESULT CreateBlendState(BlendStateDesc *desc,BlendState **statePtr) = 0;

		virtual const Ceng::CRESULT CreateDepthStencilState(const DepthStencilDesc &desc, DepthStencilState **statePtr) = 0;

		virtual const CRESULT CreateTexture2D(const Texture2dDesc &desc,
										const SubResourceData *initialData,
										Ceng::Texture2D **texturePtr)=0;

		virtual const CRESULT CreateTexture2D(const GL_Texture2dDesc &desc,
										const SubResourceData *initialData,
										Ceng::Texture2D **texturePtr) = 0;

		virtual const CRESULT CreateCubemap(const Texture2dDesc &desc,
										const SubResourceData *initialData,
										Ceng::Cubemap **texturePtr) = 0;

		virtual const CRESULT CreateProjectionMatrix(const Ceng::INT32 displayWidth,const Ceng::INT32 displayHeight,
												const Ceng::FLOAT32 horizontalField,
												const Ceng::FLOAT32 zNear,
												const Ceng::FLOAT32 zFar,
												Ceng::Matrix4 *dest)=0;
		
	};

} // Namespace Ceng

#endif // Include guard