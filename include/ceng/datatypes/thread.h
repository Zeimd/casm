/*****************************************************************************
*
* thread.h
*
* Created By Jari Korkala 10/9/2014
*
*****************************************************************************/

#ifndef CENG_THREAD_H
#define CENG_THREAD_H

#include <memory>

#include "basic-types.h"
#include "boolean.h"
#include "return-val.h"

#include "../enums/thread-priority.h"

#include "../interfaces/base-interface.h"

namespace Ceng
{
	class ThreadTask;

	class Thread : public BASE_INTERFACE
	{
	protected:

		virtual ~Thread()
		{
		}

	public:	

		Thread()
		{
		}

		/**
		 * Resume execution after pause.
		 */
		virtual const CRESULT Resume()=0;

		virtual const CRESULT Pause()=0;

		/**
		 * Inform the thread that it should exit.
		 */
		virtual const CRESULT Exit()=0;

		/**
		 * Wait until the thread completes.
		 */
		virtual const CRESULT Wait(const Ceng::UINT32 msMaxWaitTime)=0;

		/**
		 * Immediately stop and delete thread.
		 */
		virtual const CRESULT Terminate()=0;

		virtual const CRESULT SetPriority(const E_ThreadPriority::value level)=0;

		virtual const E_ThreadPriority::value GetPriority()=0;


		virtual const CRESULT SetProcessorAffinity(const Ceng::UINT32 mask)=0;

		virtual const Ceng::UINT32 GetProcessorAffinity() const =0;	
	};
}

#endif