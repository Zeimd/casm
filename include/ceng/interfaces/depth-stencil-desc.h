/*****************************************************************************
*
* depth-stencil-desc.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_DEPTH_STENCIL_DESC_H
#define _CENG_DEPTH_STENCIL_DESC_H

#include "render-resource.h"

#include "../enums/test-type.h"
#include "../enums/stencil-action.h"

#include "../datatypes/boolean.h"

namespace Ceng
{
	struct DepthStencilTest
	{
		Ceng::TEST_TYPE::value stencilTest;

		UINT32 stencilReadMask;
		UINT32 stencilWriteMask;

		UINT32 stencilRef;

		Ceng::STENCIL_ACTION::value stencilFail;
		Ceng::STENCIL_ACTION::value depthFail;
		Ceng::STENCIL_ACTION::value depthPass;
	};

	class DepthStencilDesc
	{
	public:
		Ceng::BOOL stencilEnable; // Do stencil tests
		Ceng::BOOL depthEnable; // Do depth tests

		Ceng::BOOL depthWrite; // Allow writes to depth buffer

		Ceng::TEST_TYPE::value depthTest;

		DepthStencilTest frontFace;
		DepthStencilTest backFace;

	public:
		DepthStencilDesc()
		{
			stencilEnable = false;
			depthEnable = false;

			depthWrite = false;

			depthTest = Ceng::TEST_TYPE::ALWAYS_PASS;

			frontFace.stencilTest = Ceng::TEST_TYPE::ALWAYS_PASS;

			frontFace.stencilReadMask = -1;
			frontFace.stencilWriteMask = -1;
			frontFace.stencilRef = 0;

			frontFace.stencilFail = Ceng::STENCIL_ACTION::KEEP;
			frontFace.depthFail = Ceng::STENCIL_ACTION::KEEP;
			frontFace.depthPass = Ceng::STENCIL_ACTION::KEEP;

			backFace.stencilTest = Ceng::TEST_TYPE::ALWAYS_PASS;

			backFace.stencilReadMask = -1;
			backFace.stencilWriteMask = -1;
			backFace.stencilRef = 0;

			backFace.stencilFail = Ceng::STENCIL_ACTION::KEEP;
			backFace.depthFail = Ceng::STENCIL_ACTION::KEEP;
			backFace.depthPass = Ceng::STENCIL_ACTION::KEEP;
		}
	};

};

#endif