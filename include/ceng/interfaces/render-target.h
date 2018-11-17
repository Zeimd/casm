/*****************************************************************************
*
* render-target.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_RENDER_TARGET_H
#define _CENG_RENDER_TARGET_H

#include "render-resource.h"

namespace Ceng
{
	class RenderTarget : public Ceng::RenderResource
	{
	protected:
		virtual ~RenderTarget()
		{
		}
	
	public:
		RenderTarget()
		{
		}
	};

};

#endif