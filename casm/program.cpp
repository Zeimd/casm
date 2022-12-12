/*****************************************************************************
*
* program.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/program.h"

#include <Windows.h>

using namespace X86;

Program::Program()
{
}

Program::~Program()
{
	//codeBuffer.Release();
	//dataSection.Release();
}

Ceng::CRESULT Program::GetExecutable(Executable **output)
{
	Ceng::UINT32 k;

	Ceng::UINT32 programSize = codeBuffer.GetElements();

	// Pad size to nearest multiple of 4096

	if (programSize & 4095)
	{
		programSize = (programSize + 4095) & ~4095;
	}

	Ceng::UINT8 *execPage = nullptr;

	execPage = (Ceng::UINT8*)VirtualAlloc(nullptr,programSize,MEM_COMMIT | MEM_RESERVE,PAGE_EXECUTE_READWRITE);

	if (execPage == nullptr)
	{
		return Ceng::CE_ERR_OUT_OF_MEMORY;
	}

	// Copy data section
	
	Ceng::AlignedBuffer<Ceng::UINT8> dataCopy;
	
	dataCopy = Ceng::AlignedBuffer<Ceng::UINT8>::AlignedBuffer(dataSection.GetElements(),dataCopy.GetAlignment());

	memcpy(&dataCopy[0],&dataSection[0],dataSection.GetElements());

	// Copy code to executable memory block

	memcpy(&execPage[0],&codeBuffer[0],codeBuffer.GetElements());

	// Relocate code and data

	for(k=0;k<relocationData.size();k++)
	{
		relocationData[k].Relocate((Ceng::UINT64)&dataCopy[0],(Ceng::UINT64)&execPage[0]);
	}

	Executable *temp = Executable::Create(execPage,programSize,dataCopy);

	*output = temp;

	return Ceng::CE_OK;
}