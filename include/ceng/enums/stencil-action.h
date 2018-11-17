/*****************************************************************************
*
* stencil-action.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_STENCIL_ACTION_H
#define _CENG_STENCIL_ACTION_H

namespace Ceng
{
	namespace STENCIL_ACTION
	{
		enum value
		{
			KEEP = 1 ,
			ZERO = 2 ,
			SET_REF = 3 ,
			BIT_INVERT = 4 ,

			INCREMENT = 5 ,
			INCREMENT_SAT = 6 ,

			DECREMENT = 7 ,
			DECREMENT_SAT = 8 ,

			FORCE32B = 1 << 30 ,
		};
	};
};

#endif