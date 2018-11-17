/*****************************************************************************
*
* sub-resource-data.h
*
* Created By Jari Korkala 5/3/2015
*
*****************************************************************************/

#ifndef CENG_SUB_RESOURCE_DATA_H
#define CENG_SUB_RESOURCE_DATA_H

#include "basic-types.h"

namespace Ceng
{
	class SubResourceData
	{
	public:
		const void *sourcePtr;

		/**
		 * Size of the resource if compressed.
		 */
		Ceng::UINT32 compressedSize;

		/**
		 * Step in y direction.
		 */
		Ceng::UINT32 rowPitch;

		// Used for 3d textures to step in z direction.
		Ceng::UINT32 depthPitch;
	};
}

#endif