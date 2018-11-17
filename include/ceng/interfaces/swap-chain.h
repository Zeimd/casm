/*****************************************************************************
*
* swap-chain.h
*
* Created By Jari Korkala 3/3/2015
*
*****************************************************************************/

#ifndef CENG_SWAP_CHAIN_H
#define CENG_SWAP_CHAIN_H

#include "base-interface.h"

#include "../datatypes/return-val.h"

#include "../enums/present-options.h"

namespace Ceng
{
	struct Rectangle;
	class RenderTarget;

	class SwapChain : public BASE_INTERFACE
	{
	protected:

		virtual ~SwapChain()
		{
		}

	public:

		SwapChain()
		{
		}

		virtual void Release() = 0;

		// Default present according to device config
		virtual const CRESULT Present() = 0;

		virtual const CRESULT Present(const Ceng::UINT32 syncInterval, const Ceng::UINT32 options,
			const Ceng::UINT32 dirtyRectCount,
			const Ceng::Rectangle *dirtyRects,
			const Ceng::Rectangle *scrollRect,
			const Ceng::UINT32 scrollOffsetX,
			const Ceng::UINT32 scrollOffsetY) = 0;

		virtual const Ceng::CRESULT GetFrameBufferTarget(Ceng::RenderTarget **renderTarget) = 0;


	};
}

#endif