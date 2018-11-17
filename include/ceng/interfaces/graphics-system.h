/*****************************************************************************
*
* graphics-system.h
*
* Created By Jari Korkala 28/2/2015
*
*****************************************************************************/

#ifndef CENG_GRAPHICS_CONFIG_H
#define CENG_GRAPHICS_CONFIG_H

#include "base-interface.h"

#include "../datatypes/return-val.h"

#include "graphics-adapter.h"
#include "display-mode.h"

#include "../datatypes/graphics-adapter-desc.h"
#include "../datatypes/swap-chain-desc.h"

#include "../enums/renderer-type.h"

#include "../enums/buffer-binding.h"
#include "../enums/buffer-cpu-access.h"
#include "../enums/buffer-usage.h"
#include "../enums/buffer-options.h"
#include "../enums/buffer-type.h"

#include "../datatypes/swap-chain-desc.h"

namespace Ceng
{
	class RenderDevice;
	class RenderContext;
	class SwapChain;

	class GraphicsSystem : public BASE_INTERFACE
	{
	protected:

		virtual ~GraphicsSystem()
		{
		}

	public:

		GraphicsSystem()
		{
		}

		virtual void Release() = 0;

		virtual const Ceng::UINT32 AdapterCount() = 0;

		virtual const Ceng::CRESULT EnumAdapter(const Ceng::UINT32 index, GraphicsAdapter **out_adapter) = 0;

		//virtual const Ceng::CRESULT EnumMonitors(const Ceng::UINT32 index) = 0;

		virtual const Ceng::UINT32 CurrentDisplayMode(GraphicsAdapter *adapter,
														DisplayMode &out_mode) = 0;

		virtual const Ceng::UINT32 DisplayModeCount(GraphicsAdapter *adapter,
														const Ceng::IMAGE_FORMAT::value format) = 0;
		
		virtual const Ceng::CRESULT EnumDisplayMode(GraphicsAdapter *adapter, const Ceng::UINT32 index,
														const Ceng::IMAGE_FORMAT::value format,
														DisplayMode &out_mode) = 0;

		/**
		 * Checks whether the given combination of display format and back buffer format
		 * has hardware acceleration support.
		 */
		virtual const Ceng::CRESULT CheckFramebufferSupport(GraphicsAdapter *adapter,
														const Ceng::IMAGE_FORMAT::value displayFormat,
														const Ceng::IMAGE_FORMAT::value backBufferFormat,
														const Ceng::BOOL windowed) = 0;

		virtual const Ceng::CRESULT CheckBufferSupport(GraphicsAdapter *adapter,
														const Ceng::IMAGE_FORMAT::value displayFormat,
														const Ceng::BufferType::value type,
														const Ceng::IMAGE_FORMAT::value bufferFormat,
														const Ceng::UINT32 binding,
														const Ceng::BufferUsage::value usage,
														const Ceng::UINT32 cpuAccess,
														const Ceng::UINT32 options) = 0;
														
		virtual const CRESULT CreateSwapChain(RenderDevice *device,
												SwapChainDesc &swapChainDesc,
												SwapChain **chainPtr) = 0;

		virtual const CRESULT GetRenderDevice(GraphicsAdapter *adapter,
												const Ceng::UINT64 deviceOptions,
												SwapChainDesc *swapChainDesc,
												SwapChain **swapChainPtr,
												RenderDevice **devicePtr,
												RenderContext **contextPtr) = 0;
	};
}

#endif