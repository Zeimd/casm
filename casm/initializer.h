/*****************************************************************************
*
* initializer.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_INITIALIZER_H
#define X86_INITIALIZER_H

#include <initializer_list>

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/return-val.h>

#include <ostream>

namespace Casm
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

		virtual Ceng::UINT32 ElementSize() const
		{
			return 0;
		}

		virtual Ceng::UINT32 Size() const
		{
			return 0;
		}

		virtual Ceng::CRESULT WriteValues(Ceng::UINT8 *destBuffer) const
		{
			return Ceng::CE_OK;
		}

		virtual void Print(std::wostream& out) const
		{

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

		~Initializer() override
		{
		}

		Ceng::UINT32 Size() const override
		{
			return sizeof(T);
		}

		Ceng::UINT32 ElementSize() const override
		{
			return sizeof(T);
		}

		Ceng::CRESULT WriteValues(Ceng::UINT8 *destBuffer) const override
		{
			T *ptr = (T*)destBuffer;

			*ptr = data;

			return Ceng::CE_OK;
		}

		void Print(std::wostream& out) const override
		{
			out << data;
		}
	};

	class StringLiteralInitializer : public InitializerType
	{
	protected:
		std::vector<char> data;

		StringLiteralInitializer()
			: data(1, '\0')
		{

		}

	public:

		StringLiteralInitializer(const char* source)
			: data(strlen(source)+1)
		{
			memcpy(&data[0], source, strlen(source));
			data[strlen(source)] = '\0';
		}

		~StringLiteralInitializer()
		{
		}

		Ceng::UINT32 Size() const override
		{
			return data.size();
		}

		Ceng::UINT32 ElementSize() const override
		{
			return sizeof(char);
		}

		Ceng::CRESULT WriteValues(Ceng::UINT8* destBuffer) const override
		{
			for (size_t i = 0; i < data.size(); i++)
			{
				destBuffer[i] = data[i];
			}

			return Ceng::CE_OK;
		}

		void Print(std::wostream& out) const override
		{
			out << '\'';

			for (auto& x : data)
			{
				if (x == '\n')
				{
					out << "\\n";
				}
				else if (x == '\t')
				{
					out << "\\t";
				}
				else
				{
					out << char(x);
				}
			}

			out << '\'';
			out << ",0";
		}

	};

	template<class T>
	class InitializerList : public InitializerType
	{
	protected:
		std::vector<T> data;

		InitializerList()
		{
		}

	public:

		InitializerList(const std::vector<T>& source)
			: data(source)
		{

		}

		InitializerList(std::vector<T>&& source)
			: data(source)
		{

		}

		InitializerList(std::initializer_list<T> source)
			: data(source)
		{
				
		}

		InitializerList(const T* source, const uint32_t length)
			: data(source, source + length)
		{

		}

		~InitializerList() override
		{
		}

		Ceng::UINT32 Size() const override
		{
			return ElementSize()*data.size();
		}

		Ceng::UINT32 ElementSize() const override
		{
			return sizeof(T);
		}

		Ceng::CRESULT WriteValues(Ceng::UINT8 *destBuffer) const override
		{
			T *ptr = (T*)destBuffer;

			for (Ceng::UINT32 i = 0; i < data.size(); i++)
			{
				ptr[i] = data[i];
			}

			return Ceng::CE_OK;
		}

		void Print(std::wostream& out) const override
		{
			for (size_t k=0; k < data.size(); k++)
			{
				out << data[k];

				if (k < data.size() - 1)
				{
					out << ", ";
				}
			}
		}
	};
}

#endif