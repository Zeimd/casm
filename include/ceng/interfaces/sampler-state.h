/*****************************************************************************
*
* sampler-state.h
*
* Created By Jari Korkala 5/3/2015
*
*****************************************************************************/

#ifndef CENG_SAMPLER_STATE_H
#define CENG_SAMPLER_STATE_H

#include "base-interface.h"

namespace Ceng
{
	class SamplerStateDesc;

	class SamplerState : public BASE_INTERFACE
	{
	protected:

		virtual ~SamplerState()
		{
		}

	public:

		SamplerState()
		{
		}

		virtual void Release() = 0;

		virtual void GetSamplerDesc(SamplerStateDesc &desc) = 0;
	};
}

#endif