/*****************************************************************************
*
* future.h
*
* Created By Jari Korkala 2/2015
*
******************************************************************************/

#ifndef CENG_FUTURE_H
#define CENG_FUTURE_H

#include "boolean.h"
#include "critical-section.h"
#include "../platform.h"

#include <memory>

namespace Ceng
{
	template<class t_ElemType,class t_ReturnValue>
	class Future
	{
	protected:

		enum Status
		{
			// Waiting for result
			pending = 1 ,
			
			// No result will be provided
			abort = 2 ,

			// Result available
			ready = 3 ,

			// Future object is in invalid state
			invalid_state = 4,

			force_32b = 1 << 30 ,
		};

		volatile Ceng::UINT32 status;

		std::shared_ptr<t_ElemType> result;

		volatile t_ReturnValue returnVal;

		Ceng::CriticalSection *mutex;

	public:

		Future();	
		~Future();

		const Ceng::BOOL IsReady() const;

		const Future::Status Status() const;

		const t_ReturnValue ReturnValue() const;

		const Ceng::CRESULT WriteResult(const t_ElemType &value);

	};

	template<class t_ElemType,class t_ReturnValue>
	Future<t_ElemType,t_ReturnValue>::Future()
	{
		status = Future::pending;
		Ceng::CRESULT cresult = Ceng_CreateCriticalSection(&mutex);

		if (cresult != CE_OK)
		{
			status = invalid_state;
		}
	}

	template<class t_ElemType,class t_ReturnValue>
	Future<t_ElemType,t_ReturnValue>::~Future()
	{
	}

	template<class t_ElemType,class t_ReturnValue>
	const Ceng::BOOL Future<t_ElemType,t_ReturnValue>::IsReady() const
	{
		return (status & (ready | abort));
	}

	template<class t_ElemType,class t_ReturnValue>
	const typename Future<t_ElemType,t_ReturnValue>::Status 
		Future<t_ElemType,t_ReturnValue>::Status() const
	{
		return status;
	}

	template<class t_ElemType,class t_ReturnValue>
	const t_ReturnValue Future<t_ElemType,t_ReturnValue>::ReturnValue() const
	{
		return returnVal;
	}

	template<class t_ElemType,class t_ReturnValue>
	const Ceng::CRESULT Future<t_ElemType,t_ReturnValue>::WriteResult(const t_ElemType &value)
	{
		if (status == ready || status == abort)
		{
			return CE_ERR_FAIL;
		}

		Ceng::CRESULT cresult = mutex->AttemptLock();

		if (cresult == CE_OK)
		{
			result = value;

			mutex->Unlock();
		}

		return CE_OK;
	}

}

#endif