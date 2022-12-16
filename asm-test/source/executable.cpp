/*****************************************************************************
*
* executable.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/executable.h"

#include "../include/hex-dump.h"

#include <Windows.h>

using namespace X86;

Executable::~Executable()
{
	VirtualFree((void*)callback,pageSize,MEM_RELEASE);
	//dataSegment.Release();
}

Executable* Executable::Create(void *functionPage,const Ceng::UINT32 pageSize,
							   Ceng::AlignedBuffer<Ceng::UINT8> dataSegment)
{
	if (functionPage == nullptr)
	{
		return nullptr;				
	}

	Executable *temp = new Executable();

	temp->pageSize = pageSize;
	temp->callback = (void(*)(Ceng::POINTER))functionPage;

	temp->dataSegment = dataSegment;

	return temp;
}

void Executable::Print(std::wostream& out) const
{
	const int groupSize = 16;

	out << "section data (size=" << dataSegment.GetSize() << ")" << std::endl << std::endl;

	Casm::HexDump(out, 16, dataSegment.GetSize(), &dataSegment[0]);

	uint8_t* textSection = (uint8_t*)callback;

	out << "section code (size=" << pageSize << ")" << std::endl << std::endl;

	Casm::HexDump(out, 16, pageSize, &textSection[0]);

}