/*****************************************************************************
*
* vertex-shader.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_VERTEX_SHADER_H
#define _CENG_VERTEX_SHADER_H

#include "base-interface.h"
#include "shader-const.h"

namespace Ceng
{
	class VertexShader : public BASE_INTERFACE
	{
	protected:
		virtual ~VertexShader()
		{
		}
	
	public:
		VertexShader()
		{
		}
		
		virtual CRESULT GetConstant(const char *variableName,
									Ceng::ShaderConstant **handle)=0;

		virtual const Ceng::CRESULT GetLog(Ceng::StringUtf8 **log) = 0;

		virtual const Ceng::BOOL Compiled() = 0;
	};
	
};

#endif
