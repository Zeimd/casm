/*****************************************************************************
*
* swap-chain-desc.h
*
* Created By Jari Korkala 3/3/2015
*
*****************************************************************************/

#ifndef CENG_SWAP_CHAIN_DESC_H
#define CENG_SWAP_CHAIN_DESC_H

#include "boolean.h"

#include "../enums/swap-effect.h"

#include "../interfaces/display-mode.h"
#include "multisample-desc.h"

#include "../enums/swap-chain-usage.h"
#include "../enums/swap-options.h"

namespace Ceng
{
	class PlatformWindow;

	class SwapChainDesc
	{
	public:

		DisplayMode displayMode;
		MultisampleDesc multisampleDesc;
		Ceng::UINT32 usage;

		// Number of back buffers
		Ceng::UINT32 bufferCount;

		// A depth-stencil buffer is created at the same time.
		// NOTE: Only for those implementations where a swap chain
		//       cannot be created independently of depth-stencil buffer.
		Ceng::BOOL autoDepthStencil;

		// Format of the automatic depth-stencil buffer.
		Ceng::IMAGE_FORMAT::value autoDepthStencilFormat;

		PlatformWindow *outputWindow;

		// Full screen if false.
		Ceng::BOOL windowed;

		// Number of v-syncs to wait before presenting frame.
		// NOTE: For those implementations that don't support this
		//       as SwapChain::Present() parameter.
		Ceng::UINT32 presentInterval;

		// Method of presenting frame.
		SwapEffect::value swapEffect;
		
		Ceng::UINT32 swapOptions;
	};
}

#endif