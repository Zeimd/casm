/*****************************************************************************
*
* swap-chain-usage.h
*
* Created By Jari Korkala 3/3/2015
*
*****************************************************************************/

#ifndef CENG_SWAP_CHAIN_USAGE_H
#define CENG_SWAP_CHAIN_USAGE_H

namespace Ceng
{
	namespace SwapChainUsage
	{
		enum value
		{

			back_buffer = 1 << 16 ,
			
			// For internal use only
			discard_on_present = 1 << 17 ,

			read_only = 1 << 18 ,

			render_target = 1 << 19 ,

			shader_input = 1 << 20 ,

			shared = 1 << 21 ,

			unordered_access = 1 << 22 ,

			force32b = 1 << 30 ,
		};
	}
}


#endif