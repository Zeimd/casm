/*****************************************************************************
*
* image-buffer.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_IMAGE_BUFFER_H
#define _CENG_IMAGE_BUFFER_H

#include "../enums/image-formats.h"
#include "../datatypes/basic-types.h"
#include "../datatypes/return-val.h"

#include "base-interface.h"

namespace Ceng
{
	struct Rectangle;

	struct BufferData
	{
		Ceng::UINT32 width;
		Ceng::UINT32 height;

		Ceng::IMAGE_FORMAT::value format;

		Ceng::POINTER pitch;

		void *data;
	};

	class ImageBuffer : public Ceng::BASE_INTERFACE
	{
	protected:

		virtual ~ImageBuffer()
		{
		}

	public:

		ImageBuffer()
		{
		}

		virtual void Release()=0;

		virtual const CRESULT ToFrameBuffer(const Ceng::Rectangle &sourceArea,
										const Ceng::BufferData &destBuffer)=0;

		virtual const Ceng::UINT32 GetWidth()=0;
		virtual const Ceng::UINT32 GetHeight()=0;
	};
};

#endif