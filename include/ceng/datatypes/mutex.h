/*****************************************************************************
*
* mutex.h
*
* Created By Jari Korkala 10/9/2014
*
*****************************************************************************/

#ifndef CENG_MUTEX_H
#define CENG_MUTEX_H

#include "../interfaces/base-interface.h"

#include "return-val.h"

namespace Ceng
{
	class Mutex : public BASE_INTERFACE
	{
	protected:

		virtual ~Mutex()
		{
		}

	public:		

		Mutex()
		{
		}
	
		virtual void Release()=0;

		virtual const CRESULT Lock(const Ceng::UINT32 msMaxWaitTime)=0;

		virtual const CRESULT Unlock()=0;
	};
}

#endif