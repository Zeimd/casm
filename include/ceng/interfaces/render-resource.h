/*****************************************************************************
*
* render-resource.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_RENDER_RESOURCE_H
#define _CENG_RENDER_RESOURCE_H

#include "base-interface.h"

#include "../enums/buffer-type.h"

namespace Ceng
{
	/**
	* Base class for renderer resources.
	*/
	class RenderResource : public Ceng::BASE_INTERFACE
	{
	protected:
		
		virtual ~RenderResource()
		{
		}
	
	public:
		RenderResource()
		{
		}

		virtual void Release() = 0;

		virtual const BufferType::value GetResourceType() = 0;
	};
	
};

#endif