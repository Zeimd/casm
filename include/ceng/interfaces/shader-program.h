/*****************************************************************************
*
* shader-program.h
*
* Created By Jari Korkala 25/10/2015
*
* For purposes of OpenGL compatibility.
*
*****************************************************************************/

#ifndef CENG_SHADER_PROGRAM_H
#define CENG_SHADER_PROGRAM_H

#include "../datatypes/ce-string.h"

#include "base-interface.h"

#include "../datatypes/return-val.h"

namespace Ceng
{
	class ShaderConstant;

	class ShaderProgram : public BASE_INTERFACE
	{
	public:
		ShaderProgram()
		{
		}

		virtual ~ShaderProgram()
		{
		}

		virtual void Release() = 0;

		virtual const Ceng::CRESULT GetConstant(const char *variableName,Ceng::ShaderConstant **handle) = 0;

		virtual const Ceng::CRESULT GetLog(Ceng::StringUtf8 **log) = 0;

		virtual const Ceng::BOOL Linked() = 0;
	};
}

#endif