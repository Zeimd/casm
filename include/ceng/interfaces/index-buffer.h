/*****************************************************************************
*
* index-buffer.h
*
* By Jari Korkala 28/10/2015
*
*****************************************************************************/

#ifndef CENG_INDEX_BUFFER_H
#define CENG_INDEX_BUFFER_H

#include "base-interface.h"

namespace Ceng
{
	class IndexBuffer : public BASE_INTERFACE
	{
	protected:
		virtual ~IndexBuffer()
		{
		}
	public:
		IndexBuffer()
		{
		}

		virtual void Release() = 0;
	};
}

#endif