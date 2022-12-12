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

#include "include/assembler.h"

#include "include/program-builder.h"
#include "include/function-builder.h"

#include "include/program.h"

#include "include/executable.h"

#include "include/initializer.h"

#include "include/linker.h"

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

	_setmode(_fileno(stdout),_O_U8TEXT);

	Ceng::INT32 k=0;

	int a=2,b=1;

	X86::Assembler assembler = X86::Assembler(64);

	Ceng::UINT64 x = 4;
	Ceng::FLOAT32 y = -5.5;

	std::wcout << x+y << std::endl;

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

	Ceng::INT32 work[4] = {10,20,30,40};

	Ceng::FLOAT32 floatWork = 0.0f;

	Ceng::CRESULT cresult = Ceng::CE_OK;

	//************************************************************
	// New code generator test
	
	X86::ObjectCode *testObject;

	/*
	Ceng::String sourceString;
	
	sourceString += "a+++b\n";
	sourceString +=	"function main\n";
	sourceString += "\tret\n";

	sourceString += "end function\n";

	//std::wcout << sourceString << std::endl;


	cresult = assembler.CreateProgram(sourceString,&testObject);

	return 0;
	*/
	
	X86::ProgramBuilder *programBuild;

	assembler.CreateProgram(Casm::BuilderOptions(false),&programBuild);

	programBuild->AddData(X86::DataDescriptor(0,X86::OPERAND_SIZE::DWORD),"test",new X86::Initializer<Ceng::INT32>(12345));

	//*************************************
	// main()

	//X86::FunctionBuilder *mainFunc;
	//programBuild->AddFunction(0,X86::PROTECTED_MODE,X86::PRIVILEDGE_LEVEL::USER,"main",&mainFunc);

	//mainFunc->AddInstruction("mov ecx,[esp+4]");

	// Integer test

	//mainFunc->AddInstruction("mov edx,-4");
	
	//mainFunc->AddInstruction("mov eax,[ecx]");
	
	//mainFunc->AddInstruction("add eax,dword 4");

	//mainFunc->AddInstruction("add [ecx],dword 4");	

	// Float test

	/*
	mainFunc->AddInstruction(X86::MOVSS,&X86::XMM0,new X86::MemoryOperand(X86::ECX));
	
	mainFunc->AddInstruction("mov eax,-4.0*-4.0");
	mainFunc->AddInstruction(X86::MOV,new X86::MemoryOperand(X86::ECX),&X86::EAX);

	mainFunc->AddInstruction(X86::ADDSS,&X86::XMM0,new X86::MemoryOperand(X86::ECX));

	mainFunc->AddInstruction(X86::MOVSS,new X86::MemoryOperand(X86::ECX),&X86::XMM0);
	*/
	
	

	// Return
	//mainFunc->AddInstruction("ret");

	//*****************************************
	// TestFunction
	
	X86::FunctionBuilder *testFunc;
	programBuild->AddFunction(0,X86::PROTECTED_MODE,X86::PRIVILEDGE_LEVEL::USER,"TestFunction",&testFunc);

	//testFunc->AddInstruction(X86::MOV,&X86::EAX,new X86::ImmediateOperand(12345));

	//testFunc->AddInstruction(X86::RET_NEAR,new X86::ImmediateOperand(0));
	
	cresult = programBuild->Build(&testObject);
	if (cresult != Ceng::CE_OK)
	{
		std::wcout << "Error : Build failed" << std::endl;
		return 0;
	}

	delete programBuild;

	Casm::Linker linker = Casm::Linker(64);

	std::vector<X86::ObjectCode*> objects;

	objects.push_back(testObject);

	X86::Program *testLink;

	linker.LinkProgram("main",objects,&testLink);

	delete testObject;

	X86::Executable *testProgram;

	testLink->GetExecutable(&testProgram);

	delete testLink;
	
	std::wcout << "&test = " << (Ceng::POINTER)&work << std::endl;

	std::wcout << "test in = " << work[0] << std::endl;
	std::wcout << "ftest in = " << floatWork << std::endl;

	testProgram->Execute((Ceng::POINTER)&work[0]);
	//testProgram->Execute((Ceng::POINTER)&floatWork);
	//testProgram->Execute((Ceng::POINTER)&vector[0]);

	std::wcout << "test out = " << work[0] << std::endl;
	std::wcout << "float test out = " << floatWork << std::endl;

	std::wcout << "Output: " << std::endl;

	for(k=0;k<4;k++)
	{
		std::wcout << vector[k][0] << "," << vector[k][1] <<
			"," << vector[k][2] << "," << vector[k][3] << std::endl;
	}

	delete testProgram;

	return 0;
}