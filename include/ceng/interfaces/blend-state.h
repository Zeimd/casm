/*****************************************************************************
*
* blend-state.h
*
* Created By Jari Korkala 10/11/2015
*
*****************************************************************************/

#ifndef CENG_BLEND_STATE_H
#define CENG_BLEND_STATE_H

#include "base-interface.h"

namespace Ceng
{
	class BlendState : public BASE_INTERFACE
	{
	protected:
		virtual ~BlendState()
		{
		}
	public:
		BlendState()
		{
		}
	};
}

#endif