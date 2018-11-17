/*****************************************************************************
*
* tex2d-desc.h
*
* Created By Jari Korkala 5/3/2015
*
*****************************************************************************/

#ifndef CENG_TEX2D_DESC_H
#define CENG_TEX2D_DESC_H

#include "basic-types.h"
#include "boolean.h"

#include "../enums/image-formats.h"
#include "multisample-desc.h"

#include "../enums/buffer-usage.h"
#include "../enums/buffer-options.h"
#include "../enums/buffer-binding.h"

namespace Ceng
{
	class Texture2dDesc
	{
	public:
		Ceng::UINT32 width;
		Ceng::UINT32 height;

		Ceng::UINT32 mipLevels;
		Ceng::UINT32 arraySize;

		Ceng::IMAGE_FORMAT::value format;
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