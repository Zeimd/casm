/*****************************************************************************
*
* promise.h
*
* Created By Jari Korkala 2/2015
*
* Stores a value that can be subsequently read by any promise obtained
* from this object.
*
* Similar to std::promise, but uses status variable instead of exception.
*
*****************************************************************************/

#ifndef CENG_PROMISE_H
#define CENG_PROMISE_H

#include <memory>

#include "../platform.h"

namespace Ceng
{
	template<class t_ElemType>
	class Promise
	{
	protected:

		std::shared_ptr<t_ElemType> value;

	public:

		Promise();
		~Promise();
	};
}

#endif