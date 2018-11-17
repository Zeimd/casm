/*****************************************************************************
*
* thread-task.h
*
* Created By Jari Korkala 4/9/2014
*
*****************************************************************************/

#ifndef CENG_THREAD_TASK_H
#define CENG_THREAD_TASK_H

#include "base-interface.h"

#include "../datatypes/return-val.h"

namespace Ceng
{
	

	class ThreadTask : public BASE_INTERFACE
	{
	protected:

		virtual ~ThreadTask()
		{
		}

	public:

		ThreadTask()
		{
		}

		virtual const CRESULT Execute()=0;

		virtual const CRESULT Exit()=0;
	};
}

#endif