/*****************************************************************************
*
* initializer.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_INITIALIZER_H
#define X86_INITIALIZER_H

#include <datatypes/basic-types.h>
#include <datatypes/return-val.h>

namespace X86
{
	class InitializerType
	{
	public:
		InitializerType()
		{
		}

		virtual ~InitializerType()
		{
		}

		virtual Ceng::UINT32 Size() const
		{
			return 0;
		}

		virtual Ceng::CRESULT WriteValues(Ceng::UINT8 *destBuffer) const
		{
			return Ceng::CE_OK;
		}
	};

	template<class T>
	class Initializer : public InitializerType
	{
	protected:
		T data;
	public:
		Initializer()
		{
		}

		Initializer(const T value)
		{
			data = value;
		}

		virtual ~Initializer()
		{
		}

		virtual Ceng::UINT32 Size() const
		{
			return sizeof(T);
		}

		virtual Ceng::CRESULT WriteValues(Ceng::UINT8 *destBuffer) const
		{
			T *ptr = (T*)destBuffer;

			*ptr = data;

			return Ceng::CE_OK;
		}
	};

	template<class T>
	class InitializerList : public InitializerType
	{
	protected:
		std::vector<T> data;
	public:
		InitializerList()
		{
		}

		virtual ~InitializerList()
		{
		}

		virtual Ceng::UINT32 Size() const
		{
			return sizeof(T)*data.size();
		}
	};
}

#endif