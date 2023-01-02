/********************************************************************************
*
* asm-test.cpp
*
* By Jari Korkala 1/2014
*
* Test program for X86 code generation.
*
********************************************************************************/


// Debug information
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#include <crtdbg.h>

#endif

#include "assembler.h"

#include "program-builder.h"
#include "section.h"

#include "program.h"

#include "executable.h"

#include "initializer.h"

#include "linker.h"

#include "x86-opcodes-alu.h"
#include "x86-regs-alu.h"

#include "x86-immediate-op.h"
#include "x86-memory-op.h"

#include "data-descriptor.h"

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/boolean.h>
//#include <ceng/datatypes/string-manipulator.h>

#include <ceng/lib/liblog.h>

using namespace Ceng;

#include <io.h>
#include <fcntl.h>

namespace Ceng
{
	namespace CONST_TYPE
	{
		enum value
		{
			INTEGER = 0 ,
			FLOAT = 1 ,

			FORCE_32B = 1 << 30 ,
		};
	}
}

int main()
{
	
#ifdef _DEBUG
	// Detect memory leaks after main-function ends
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
#endif

	//_setmode(_fileno(stdout),_O_U8TEXT);

	Ceng::INT32 k=0;

	Casm::Assembler assembler = Casm::Assembler(64);

	//*********************************************************************
	// Assembler test

	FileLog fileLog;

	fileLog.OpenFile("asm-debug.txt");

	Log::SetLog(&fileLog);

	_declspec(align(64)) FLOAT32 vector[256][4] = 
	{ 
		{1.0f,1.0f,1.0f,1.0f} ,
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0}
	};

	std::wcout << "Code generator test:" << std::endl;

	std::wcout << "Test array: " << std::endl;

	for(k=0;k<4;k++)
	{
		std::wcout << vector[k][0] << "," << vector[k][1] <<
			"," << vector[k][2] << "," << vector[k][3] << std::endl;
	}

	Ceng::INT32 work[4] = {0,1,2,3};

	Ceng::FLOAT32 floatWork = 0.0f;

	Ceng::CRESULT cresult = Ceng::CE_OK;

	//************************************************************
	// New code generator test
	
	Casm::ObjectCode *testObject;
	
	Casm::ProgramBuilder *programBuild;

	assembler.CreateProgram(Casm::BuilderOptions(false),&programBuild);

	//programBuild->AddData(X86::DataDescriptor(0,X86::OPERAND_SIZE::DWORD),"test",
		//new X86::Initializer<Ceng::INT32>(1));


	std::shared_ptr<Casm::Section> dataSection;

	programBuild->AddSection(Casm::SectionOptions::writable | Casm::SectionOptions::alloc_mem,
		X86::PROTECTED_MODE, X86::PRIVILEDGE_LEVEL::ANY, ".data", dataSection);

	dataSection->AddData(Casm::DataDescriptor(), "hello_str", "Hello World!\n");

	//*****************************************
	// TestFunction

	/*
	std::shared_ptr<Casm::Section>  codeSection;

	programBuild->AddSection(Casm::SectionOptions::executable | Casm::SectionOptions::alloc_mem,
		X86::PROTECTED_MODE, X86::PRIVILEDGE_LEVEL::ANY, ".code", codeSection);
	*/

	//X86::FunctionBuilder *testFunc;
	//programBuild->AddFunction(0,X86::PROTECTED_MODE,X86::PRIVILEDGE_LEVEL::USER,"main",&testFunc);

	//******************************************'
	// printf test

	/*

	codeSection->AddLabel("main");
	
	// mov eax, hello_str
	codeSection->MoveAddress(&X86::EAX, "hello_str");

	// mov ecx, [esp+4]
	codeSection->AddInstruction(X86::MOV, &X86::ECX, new X86::MemoryOperand(X86::ESP, 4));

	// push ecx
	codeSection->AddInstruction(X86::PUSH, &X86::ECX);

	// push printf params to stack

	// push eax
	codeSection->AddInstruction(X86::PUSH, &X86::EAX);

	//codeSection->MoveAddress(&X86::ECX, "printf");
	//codeSection->AddInstruction(X86::CALL, &X86::ECX);
	codeSection->Call("printf");

	// clear printf param from stack
	codeSection->AddInstruction(X86::POP, &X86::ECX);

	// pop ecx
	codeSection->AddInstruction(X86::POP, &X86::ECX);

	// mov [ecx], eax
	codeSection->AddInstruction(X86::MOV, new X86::MemoryOperand(X86::ECX), &X86::EAX);

	// ret
	codeSection->AddInstruction(X86::RET_NEAR);
	*/
	

	//*****************************************
	// test for calling generated function
	
	/*
	codeSection->AddLabel("main");

	// mov eax, 1
	codeSection->AddInstruction(X86::MOV, &X86::EAX, new X86::ImmediateOperand(1));

	// mov ecx, [esp+4]
	codeSection->AddInstruction(X86::MOV, &X86::ECX, new X86::MemoryOperand(X86::ESP, 4));

	// push ecx
	codeSection->AddInstruction(X86::PUSH, &X86::ECX);

	// indirect call via register
	//codeSection->MoveAddress(&X86::ECX, "incr");
	//codeSection->AddInstruction(X86::CALL, &X86::ECX);
	codeSection->Call("incr");

	// pop ecx
	codeSection->AddInstruction(X86::POP, &X86::ECX);

	// mov [ecx], eax
	codeSection->AddInstruction(X86::MOV, new X86::MemoryOperand(X86::ECX), &X86::EAX);

	// ret
	codeSection->AddInstruction(X86::RET_NEAR);

	codeSection->AddLabel("incr");

	// inc eax
	codeSection->AddInstruction(X86::INC, &X86::EAX);

	// ret
	codeSection->AddInstruction(X86::RET_NEAR);
	*/

	//************************************************'
	// build program

	programBuild->Print(std::wcout);

	cresult = programBuild->Build(&testObject);
	if (cresult != Ceng::CE_OK)
	{
		std::wcout << "Error : Build failed" << std::endl;
		return 0;
	}

	std::wcout << "object code dump:" << std::endl;

	testObject->Print(std::wcout);

	std::wcout << "object code end" << std::endl;

	return 0;

	delete programBuild;

	Casm::Linker linker = Casm::Linker(64);

	std::vector<Casm::ObjectCode*> objects;

	objects.push_back(testObject);

	Casm::Program *testLink;

	cresult = linker.LinkProgram("main",objects, &testLink);

	if (cresult != Ceng::CE_OK)
	{
		std::wcout << "Error : Linking failed" << std::endl;
		return 0;
	}

	std::wcout << "program dump:" << std::endl;

	testLink->Print(std::wcout);

	std::wcout << "program end" << std::endl;

	delete testObject;

	Casm::ExternSymbol externs[] =
	{
		{"printf", &printf}
	};

	Casm::Executable *testProgram;

	cresult = testLink->GetExecutable(externs,
		sizeof(externs) / sizeof(Casm::ExternSymbol), &testProgram);

	if (cresult != Ceng::CE_OK)
	{
		std::wcout << "Error : relocation failed" << std::endl;
		return 0;
	}

	std::wcout << "&printf = " << std::hex << (Ceng::POINTER)&printf << std::dec << std::endl;

	std::wcout << "&test = " << std::hex << (Ceng::POINTER)&work << std::dec << std::endl;

	std::wcout << "executable dump:" << std::endl;

	testProgram->Print(std::wcout);

	std::wcout << "executable end" << std::endl;

	//return 0;

	delete testLink;
	
	std::wcout << "test in = " << work[0] << " (0x" << std::hex << work[0] << std::dec << ")" << std::endl;
	//std::wcout << "ftest in = " << floatWork << std::endl;

	testProgram->Execute((Ceng::POINTER)&work[0]);
	//testProgram->Execute((Ceng::POINTER)&floatWork);
	//testProgram->Execute((Ceng::POINTER)&vector[0]);

	std::wcout << "test out = " << work[0] << " (0x" << std::hex << work[0] << std::dec << ")" << std::endl;
	//std::wcout << "float test out = " << floatWork << std::endl;

	/*
	std::wcout << "Output: " << std::endl;

	for(k=0;k<4;k++)
	{
		std::wcout << vector[k][0] << "," << vector[k][1] <<
			"," << vector[k][2] << "," << vector[k][3] << std::endl;
	}
	*/

	delete testProgram;

	return 0;
}