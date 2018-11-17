/*****************************************************************************
*
* bufferdata-2d.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_BUFFERDATA_2D_H
#define _CENG_BUFFERDATA_2D_H

#include "basic-types.h"

namespace Ceng
{
	

	struct BufferData2D
	{
		/**
		* Width of the buffer in pixels.
		*/
		UINT32 width;
		
		/**
		* Height of the buffer in pixels.
		*/
		UINT32 height;
		
		/**
		* A Ceng::IMAGE_FORMAT::value value.
		*/
		UINT32 format;

		/**
		* Address step in x-direction
		*/
		UINT32 bytesPerPixel;
		
		/**
		* Address step in y-direction
		*/
		UINT32 pitchBytes;
		
		/**
		* Number of mip-map levels present.
		*/
		UINT32 mipLevels;
		
		/**
		* Address to the beginning (top-left corner)
		* of the buffer.
		*/
		POINTER baseAddress;
	};
};

#endif