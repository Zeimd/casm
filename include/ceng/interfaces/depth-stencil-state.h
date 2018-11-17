/*****************************************************************************
*
* depth-stencil-state.h
*
* By Jari Korkala 11/11/2015
*
*****************************************************************************/

#ifndef CENG_DEPTH_STENCIL_STATE_H
#define CENG_DEPTH_STENCIL_STATE_H

#include "base-interface.h"

namespace Ceng
{
	class DepthStencilState : public BASE_INTERFACE
	{
	protected:
		virtual ~DepthStencilState()
		{
		}
	public:
		DepthStencilState()
		{
		}
	};
}

#endif