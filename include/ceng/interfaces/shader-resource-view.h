/*****************************************************************************
*
* shader-resource-view.h
*
* Created By Jari Korkala 5/3/2015
*
*****************************************************************************/

#ifndef CENG_SHADER_RESOURCE_VIEW_H
#define CENG_SHADER_RESOURCE_VIEW_H

#include "base-interface.h"

namespace Ceng
{
	class ShaderResourceView : public BASE_INTERFACE
	{
	protected:
		virtual ~ShaderResourceView()
		{
		}

	public:

		ShaderResourceView()
		{
		}

		virtual void Release() = 0;

	};
}

#endif