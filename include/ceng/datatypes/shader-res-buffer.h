/*****************************************************************************
*
* shader-res-buffer.h
*
* Created By Jari Korkala 5/3/2015
*
*****************************************************************************/

#ifndef CENG_SHADER_RES_BUFFER_H
#define CENG_SHADER_RES_BUFFER_H

#include "../datatypes/basic-types.h"

namespace Ceng
{
	class ShaderResourceViewBuffer
	{
	public:

		union
		{
			// Number of bytes before first element to access.
			Ceng::UINT32 firstElement;

			// 
			Ceng::UINT32 elementOffset;
		};

		union
		{
			// Total number of elements in the view
			Ceng::UINT32 numElements;

			// Size of an element in bytes.
			Ceng::UINT32 elementWidth;
		};
	};
}

#endif