/*****************************************************************************
*
* rectangle.h
*
* Created By Jari Korkala 4/9/2014
*
*****************************************************************************/

#ifndef CENG_RECTANGLE_H
#define CENG_RECTANGLE_H

#include "basic-types.h"

namespace Ceng
{
	struct Rectangle
	{
		Ceng::INT32 top;
		Ceng::INT32 left;
		Ceng::INT32 bottom;
		Ceng::INT32 right;
	};
}


#endif