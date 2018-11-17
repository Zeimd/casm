/*****************************************************************************
*
* release-deleter.h
*
* Created By Jari Korkala 2/2015
*
*****************************************************************************/

#ifndef CENG_RELEASE_DELETER_H
#define CENG_RELEASE_DELETER_H

namespace Ceng
{
	template<class t_ElemType>
	class ReleaseDeleter
	{
	public:

		ReleaseDeleter()
		{
		}

		~ReleaseDeleter()
		{
		}

		ReleaseDeleter(const ReleaseDeleter &source)
		{
		}

		void operator()(t_ElemType *ptr)
		{
			if (ptr != nullptr)
			{
				ptr->Release();
			}
		}
	};
}

#endif