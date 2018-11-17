/*****************************************************************************
*
* scanline-order.h
*
* Created By Jari Korkala 3/3/2015
*
*****************************************************************************/

#ifndef CENG_SCANLINE_ORDER_H
#define CENG_SCANLINE_ORDER_H

namespace Ceng
{
	namespace ScanlineOrder
	{
		enum value
		{
			unspecified = 0 ,
			progressive = 1 ,
			upper_field_first = 2 ,
			lower_field_first = 3 ,

			force32b = 1 << 30 ,
		};
	}
}

#endif