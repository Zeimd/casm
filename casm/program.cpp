/*****************************************************************************
*
* program.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "program.h"

#include "hex-dump.h"

#include <Windows.h>

#include <iostream>

using namespace Casm;

Program::Program()
{
}

Program::Program(std::vector<X86::RelocationData>&& relocationData,
	std::vector<ProgramSection>&& sections)
	: relocationData(relocationData), sections(sections)
{

}


Program::~Program()
{
	//codeBuffer.Release();
	//dataSection.Release();
}

Ceng::CRESULT Program::GetExecutable(Casm::ExternSymbol* externs, uint32_t externCount,
	Executable **output)
{
	/*

	Ceng::UINT32 k;

	Ceng::UINT32 programSize = codeBuffer.GetElements();

	// Pad size to nearest multiple of 4096

	Ceng::UINT32 allocSize = programSize;
	
	if (allocSize & 4095)
	{
		allocSize = (allocSize + 4095) & ~4095;
	}

	Ceng::UINT8 *execPage = nullptr;

	execPage = (Ceng::UINT8*)VirtualAlloc(nullptr, allocSize,MEM_COMMIT | MEM_RESERVE,PAGE_EXECUTE_READWRITE);

	if (execPage == nullptr)
	{
		return Ceng::CE_ERR_OUT_OF_MEMORY;
	}

	// Copy data section
	
	Ceng::AlignedBuffer<Ceng::UINT8> dataCopy;
	
	dataCopy = Ceng::AlignedBuffer<Ceng::UINT8>::AlignedBuffer(dataSection.GetElements(),
		dataSection.GetAlignment());

	memcpy(&dataCopy[0],&dataSection[0],dataSection.GetElements());

	// Copy code to executable memory block

	memcpy(&execPage[0],&codeBuffer[0],codeBuffer.GetElements());

	std::wcout << "GetExecutable:" << std::endl;

	std::wcout << "data section base = 0x" << std::hex << &dataCopy[0] << std::dec << std::endl;

	std::wcout << "code section base = 0x" << std::hex << &execPage[0] << std::dec << std::endl;

	std::wcout << "data section size = " << dataCopy.GetElements() << std::endl;

	// Relocate code and data

	std::wcout << "Perform relocation" << std::endl;

	for(k=0;k<relocationData.size();k++)
	{
		std::wcout << "item " << k << ":" << std::endl;
		relocationData[k].Relocate((Ceng::UINT64)&dataCopy[0],(Ceng::UINT64)&execPage[0],
			externs, externCount);
	}

	Executable *temp = Executable::Create(execPage,programSize,std::move(dataCopy));

	*output = temp;
	*/

	return Ceng::CE_OK;
}

void Program::Print(std::wostream& out) const
{
	const int groupSize = 16;

	for (auto& x : sections)
	{
		out << "section " << x.name << " (size = " << x.buffer.size() << ")" << std::endl << std::endl;

		Casm::HexDump(out, 16, x.buffer.size(), &x.buffer[0]);

	}
}
