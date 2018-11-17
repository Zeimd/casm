/*****************************************************************************
*
* graphics-adapter.h
*
* Created By Jari Korkala 3/3/2015
*
*****************************************************************************/

#ifndef CENG_GRAPHICS_ADAPTER_H
#define CENG_GRAPHICS_ADAPTER_H

#include "base-interface.h"
#include "../datatypes/graphics-adapter-desc.h"
#include "../datatypes/return-val.h"

namespace Ceng
{
	class GraphicsAdapter : public BASE_INTERFACE
	{
	protected:

		virtual ~GraphicsAdapter()
		{
		}

	public:

		GraphicsAdapter()
		{
		}

		virtual void Release() = 0;

		virtual const CRESULT GetDesc(GraphicsAdapterDesc &desc) = 0;
	};
}

#endif