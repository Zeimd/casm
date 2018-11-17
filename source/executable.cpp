/*****************************************************************************
*
* executable.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/executable.h"

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