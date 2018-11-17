/*****************************************************************************
*
* swap-effect.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_SWAP_EFFECT_H
#define _CENG_SWAP_EFFECT_H

namespace Ceng
{
	namespace SwapEffect
	{
		enum value
		{
			// Swap by copy. Only back buffer 0 can be accessed.
			// Can be used with multisampling.
			discard = 0 ,
			
			// Swap by buffer flip. Retains back buffer. Cannot be used with multisampling.
			flip = 1 ,
		
			// Swap by copy. Retains back buffer. Cannot be used with multisampling.
			copy = 2 ,
		
			force32b = 1 << 30 ,
		};
	};
};

#endif