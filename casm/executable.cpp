/*****************************************************************************
*
* executable.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "executable.h"

#include "hex-dump.h"

#include <Windows.h>

using namespace Casm;

Executable::Executable()
	: entryPoint(nullptr), codeBuffer(nullptr), pageSize(0)
{

}

Executable::~Executable()
{
	if (codeBuffer != nullptr)
	{
		VirtualFree((void*)codeBuffer, 0, MEM_RELEASE);
	}
}

Executable* Executable::Create(void* entryPoint, void *codeBuffer,const Ceng::UINT32 pageSize,
							   Ceng::AlignedBuffer<Ceng::UINT8> &&dataSegment)
{
	if (entryPoint == nullptr)
	{
		return nullptr;
	}

	if (codeBuffer == nullptr)
	{
		return nullptr;				
	}

	Executable *temp = new Executable();

	temp->entryPoint = (void(*)(Ceng::POINTER))entryPoint;
	temp->pageSize = pageSize;
	temp->codeBuffer = codeBuffer;

	temp->dataSegment = std::move(dataSegment);

	return temp;
}

void Executable::Print(std::wostream& out) const
{
	const int groupSize = 16;

	out << "section .data (base=0x" << std::hex << &dataSegment[0] << std::dec <<
		", size = " << dataSegment.GetSize() << ")" << std::endl << std::endl;

	Casm::HexDump(out, 16, dataSegment.GetSize(), &dataSegment[0]);

	uint8_t* textSection = (uint8_t*)codeBuffer;

	out << "section .text (base=0x" << std::hex << codeBuffer << std::dec <<
		", size = " << pageSize << ")" << std::endl << std::endl;

	Casm::HexDump(out, 16, pageSize, &textSection[0]);
}