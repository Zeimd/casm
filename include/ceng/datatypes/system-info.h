/*****************************************************************************
*
* system-info.h
*
* Created By Jari Korkala 14/9/2014
*
*****************************************************************************/

#ifndef CENG_SYSTEM_INFO_H
#define CENG_SYSTEM_INFO_H

#include "../interfaces/base-interface.h"

#include "../enums/system-architecture.h"

namespace Ceng
{
	class SystemInfo : public BASE_INTERFACE
	{
	protected:

		virtual ~SystemInfo();

	public:

		SystemInfo();

		virtual const E_SysArchitecture::value GetArchitecture()=0;

		/**
		 * Granularity for size of virtual memory allocations.
		 */
		virtual const Ceng::UINT32 PageSize()=0;

		/**
		 * Granularity for start address of virtual memory allocations.
		 */
		virtual const Ceng::UINT32 GetAllocGranularity()=0;
	};
}

#endif