/*****************************************************************************
*
* render-target-view.h
*
* Created By Jari Korkala 9/11/2015
*
*****************************************************************************/

#ifndef CENG_RENDER_TARGET_VIEW_H
#define CENG_RENDER_TARGET_VIEW_H

#include "base-interface.h"

namespace Ceng
{
	class RenderTargetView : public BASE_INTERFACE
	{
	protected:
		virtual ~RenderTargetView()
		{
		}
	public:
		RenderTargetView()
		{
		}
	};
};

#endif
