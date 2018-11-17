/*****************************************************************************
*
* multisample-desc.h
*
* Created By Jari Korkala 3/3/2015
*
*****************************************************************************/

#ifndef CENG_MULTISAMPLE_DESC_H
#define CENG_MULTISAMPLE_DESC_H

#include "basic-types.h"

namespace Ceng
{
	class MultisampleDesc
	{
	public:
		Ceng::UINT32 count;
		Ceng::UINT32 quality;
	};
}

#endif