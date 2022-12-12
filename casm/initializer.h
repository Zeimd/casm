/*****************************************************************************
*
* initializer.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_INITIALIZER_H
#define X86_INITIALIZER_H

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/return-val.h>

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

		virtual ~Initializer() override
		{
		}

		virtual Ceng::UINT32 Size() const override
		{
			return sizeof(T);
		}

		virtual Ceng::CRESULT WriteValues(Ceng::UINT8 *destBuffer) const override
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

		virtual Ceng::UINT32 Size() const override
		{
			return sizeof(T)*data.size();
		}

		virtual Ceng::CRESULT WriteValues(Ceng::UINT8 *destBuffer) const override
		{
			T *ptr = (T*)destBuffer;

			for (Ceng::UITN32 i = 0; i < data.size(); i++)
			{
				ptr[i] = data[i];
			}

			return Ceng::CE_OK;
		}
	};
}

#endif