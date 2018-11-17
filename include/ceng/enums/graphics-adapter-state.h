/*****************************************************************************
*
* graphics-adapter-state.h
*
* Created By Jari Korkala 1/3/2015
*
*****************************************************************************/

#ifndef CENG_GRAPHICS_ADAPTER_STATE_H
#define CENG_GRAPHICS_ADAPTER_STATE_H

namespace Ceng
{
	namespace GraphicsAdapterState
	{
		enum value
		{
			active = 1,

			// Adapter draws to a remote display
			mirroring_driver = 1 << 1 ,

			// Monitor doesn't support all display modes
			spruned_modes = 1 << 2 ,

			// Primary desktop is on this device
			primary_device = 1 << 3 ,

			// Adapter is removable, cannot be primary device
			removable = 1 << 4 ,

			vga_compatible = 1 << 5 ,

			force_32b = 1 << 30 ,
		};
	}
}

#endif