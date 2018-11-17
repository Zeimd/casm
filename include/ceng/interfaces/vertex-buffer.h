/*****************************************************************************
*
* vertex-buffer.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_VERTEX_BUFFER_H
#define _CENG_VERTEX_BUFFER_H

#include "../datatypes/return-val.h"

#include "render-resource.h"

namespace Ceng
{
	class VertexBuffer : public RenderResource
	{
	protected:
		virtual ~VertexBuffer()
		{
		}
	
	public:
		VertexBuffer()
		{
		}
		
		virtual const CRESULT BufferPtr(Ceng::UINT8 **bufferPtr)=0;
		virtual const CRESULT ElementSize(Ceng::UINT32 *size)=0;
		virtual const CRESULT ElementCount(Ceng::UINT32 *elements)=0;

		// Loads entire buffer's worth of data
		virtual const Ceng::CRESULT LoadData(void *dataPtr)=0;

		// Loads partial buffer's worth of data
		virtual const Ceng::CRESULT LoadPartialData(const Ceng::UINT32 startOffset,const Ceng::UINT32 size, void *dataPtr) = 0;
	};
};

#endif