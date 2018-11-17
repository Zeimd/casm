/*****************************************************************************
*
* tex2d-desc-gl.h
*
* Created By Jari Korkala 5/3/2015
*
* Texture descriptor that uses OpenGL format values.
*
*****************************************************************************/

#ifndef CENG_TEX2D_DESC_GL_H
#define CENG_TEX2D_DESC_GL_H

#include "boolean.h"

#include "basic-types.h"

#include "../enums/image-formats.h"
#include "multisample-desc.h"

#include "../enums/buffer-usage.h"
#include "../enums/buffer-options.h"

namespace Ceng
{
	class GL_Texture2dDesc
	{
	public:
		Ceng::UINT32 width;
		Ceng::UINT32 height;

		Ceng::UINT32 mipLevels;
		Ceng::UINT32 arraySize;

		Ceng::INT32 gl_type;
		Ceng::INT32 gl_format;
		Ceng::INT32 gl_internalFormat;
		Ceng::INT32 gl_baseInternalFormat;

		Ceng::MultisampleDesc multisampleDesc;

		Ceng::BOOL sRGB;

		/**
		* GPU access patterns.
		*/
		Ceng::BufferUsage::value usage;

		/**
		* Which pipeline stages this resource must support binding to.
		* A combination of Ceng::BufferUsage values.
		*/
		Ceng::UINT32 bindFlags;

		/**
		* Which ways CPU needs to access this resource.
		* A combination of Ceng::Buffer_CPU_Access values.
		*/
		Ceng::UINT32 cpuAccessFlags;

		/**
		* A combination of Ceng::BufferOptions values.
		*/
		Ceng::UINT32 optionFlags;
	};
}

#endif