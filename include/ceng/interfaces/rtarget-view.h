/*****************************************************************************
*
* rtarget-view.h
*
* Created By Jari Korkala 5/11/2015
*
*****************************************************************************/

#ifndef CENG_RTARGET_VIEW_H
#define CENG_RTARGET_VIEW_H

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
}

#endif