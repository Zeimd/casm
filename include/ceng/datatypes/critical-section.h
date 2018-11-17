/*****************************************************************************
*
* critical-section.h
*
* Created By Jari Korkala 15/9/2014
*
*****************************************************************************/

#ifndef CENG_CRITICAL_SECTION_H
#define CENG_CRITICAL_SECTION_H

#include "return-val.h"

#include "../interfaces/base-interface.h"

namespace Ceng
{
	class CriticalSection : public BASE_INTERFACE
	{
	protected:

		virtual ~CriticalSection()
		{
		}

	public:

		CriticalSection()
		{
		}

		virtual void Release()=0;

		virtual const CRESULT Lock()=0;

		virtual const CRESULT AttemptLock()=0;

		virtual const CRESULT Unlock()=0;


	};
}

#endif