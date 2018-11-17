/*****************************************************************************
*
* pixel-shader.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_PIXEL_SHADER_H
#define _CENG_PIXEL_SHADER_H

#include "base-interface.h"
#include "shader-const.h"

namespace Ceng
{
	class PixelShader : public BASE_INTERFACE
	{
	protected:
		
		// Set to 1 if shader writes depth value
		// NOTE: Disables early z-culling
		UINT32 depthWrite; 
		
		// Set to 1 if shader writes stencil value
		// NOTE: Disables early stencil test
		UINT32 stencilWrite;
		
		virtual ~PixelShader()
		{
		}
	
	public:
		PixelShader()
		{
			depthWrite = 0;
			stencilWrite = 0;
		}
		
		virtual CRESULT GetConstant(const char *variableName,
									Ceng::ShaderConstant **handle)=0;

		virtual const Ceng::CRESULT GetLog(Ceng::StringUtf8 **log) = 0;

		virtual const Ceng::BOOL Compiled() = 0;
		
		const UINT32 WritesDepth() const
		{
			return depthWrite;
		}
		
		const UINT32 WritesStencil() const
		{
			return stencilWrite;
		}
	
	};

};

#endif