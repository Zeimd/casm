/*****************************************************************************
*
* ce-cpu-info.h
*
* By Jari Korkala 10/2012
*
*****************************************************************************/

#ifndef _CONCEPT2_CE_CPU_INFO_H
#define _CONCEPT2_CE_CPU_INFO_H

#include "../interfaces/base-interface.h"

#include "../datatypes/basic-types.h"
#include "../datatypes/return-val.h"
#include "../datatypes/ce-string.h"

#include "../enums/cpu-feature-info.h"
#include "../enums/cpu-core-type.h"

namespace Ceng
{
	struct CoreData
	{
		E_CpuCoreType::value type;

		/**
		 * Which physical core is it.
		 */
		Ceng::UINT32 physicalCoreIndex;

		/**
		 * If true, logical cores share execution resources.
		 */
		Ceng::BOOL hyperThreading;

		/**
		 * Logical core mask.
		 */
		Ceng::UINT32 coreMask;

		/**
		 * Number of logical cores.
		 */
		Ceng::UINT32 coreCount;
	};

	class CPU_Info : public Ceng::BASE_INTERFACE
	{
	protected:
		virtual ~CPU_Info() 
		{
		}

		CPU_Info() 
		{
		}

	public:

		
		virtual const CRESULT Brand(String &output)=0;
		virtual const CRESULT Model(String &output)=0;
		
		virtual const CRESULT CheckFeature(const String &feature,E_CpuFeatureInfo::value *result)=0;
		
		virtual const Ceng::UINT32 CacheLine()=0;
		virtual const Ceng::UINT32 PhysicalCores()=0;
		virtual const Ceng::UINT32 LogicalCores()=0;

		virtual const CRESULT GetPhysicalCoreData(const Ceng::UINT32 core,CoreData *output)=0;
		virtual const CRESULT GetLogicalCoreData(const Ceng::UINT32 core,CoreData *output)=0;

		
	};

} // Namespace Ceng

#endif // Include guard