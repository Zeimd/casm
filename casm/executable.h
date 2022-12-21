/*****************************************************************************
*
* executable.h
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#ifndef X86_EXECUTABLE_H
#define X86_EXECUTABLE_H

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/aligned-buffer.h>

#include <ostream>

namespace X86
{
	class Executable
	{
	public:

		Ceng::UINT32 pageSize;
		void (*callback)(Ceng::POINTER);

		Ceng::AlignedBuffer<Ceng::UINT8> dataSegment;

	protected:
		Executable();
		
	public:

		~Executable();

		static Executable* Create(void *functionPage,const Ceng::UINT32 pageSize,
								Ceng::AlignedBuffer<Ceng::UINT8> &&dataSegment);

		void Execute(Ceng::POINTER param) const;

		void Print(std::wostream& out) const;
	};

	inline void Executable::Execute(Ceng::POINTER param) const
	{
		(*callback)(param);
	}

	

}

#endif
