/*****************************************************************************
*
* condition-variable.h
*
* Created By Jari Korkala 16/9/2014
*
*****************************************************************************/

#ifndef CENG_CONDITION_VARIABLE_H
#define CENG_CONDITION_VARIABLE_H

#include "../interfaces/base-interface.h"

#include "return-val.h"

namespace Ceng
{
	class CriticalSection;

	class ConditionVariable : public BASE_INTERFACE
	{
	protected:

		virtual ~ConditionVariable()
		{
		}

	public:

		ConditionVariable()
		{
		}

		virtual const Ceng::CRESULT Wait(CriticalSection *critSection)=0;

		virtual const Ceng::CRESULT WaitFor(CriticalSection *critSection,
												const Ceng::UINT32 maxWaitTimeMs)=0;

		virtual const Ceng::CRESULT WakeOne()=0;
		virtual const Ceng::CRESULT WakeAll()=0;
	};
}

#endif