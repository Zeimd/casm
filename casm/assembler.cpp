/*****************************************************************************
*
* assembler.cpp
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#include "assembler.h"
#include "program-builder.h"

#include "x86-register-map.h"
#include "x86-opcode-map.h"

#include "object-code.h"

#include "parser-op-func.h"
#include "parser-op-add.h"
#include "parser-op-sub.h"

#include "parser-endline.h"

#include "keyword-hash.h"

#include <ceng/lib/liblog.h>

using namespace X86;

Assembler::Assembler()
{
	cacheLineSize = 16;
}

Assembler::~Assembler()
{
}

Assembler::Assembler(const Ceng::UINT32 cacheLineSize) 
	: cacheLineSize(cacheLineSize)
{
	/*
	testKeywords = new Casm::KeywordGroup();

	testKeywords->groups.push_back(X86::RegisterMap::GetInstance());
	testKeywords->groups.push_back(X86::OpcodeMap::GetInstance());
	*/

	// Set up global keywords

	
	//Casm::KeywordHashMap *globalMarkers = new Casm::KeywordHashMap();

	
	//globalMarkers->map.emplace("\n",new Casm::Endline() );

	
	/*
	Casm::KeywordHashMap *rootOperators = new Casm::KeywordHashMap();

	rootOperators->map.emplace("function",new Casm::ParserOp_FunctionDecl(Casm::TokenData()));
	rootOperators->map.emplace("+",new Casm::ParserOp_Add(Casm::TokenData()));
	rootOperators->map.emplace("++",new Casm::ParserOp_Sub(Casm::TokenData()));
	*/

	//rootKeywords = std::shared_ptr<Casm::KeywordGroup>(new Casm::KeywordGroup());

	//rootKeywords->groups.push_back(std::shared_ptr<Casm::KeywordMap>(globalMarkers));
	//rootKeywords->groups.push_back(std::shared_ptr<Casm::KeywordMap>(rootOperators));
}

Ceng::UINT32 Assembler::CacheLine() const
{
	return cacheLineSize;
}

Ceng::CRESULT Assembler::CreateProgram(const Casm::BuilderOptions &options,ProgramBuilder **output)
{
	*output = new ProgramBuilder(options,this);

	return Ceng::CE_OK;
}

/*
Ceng::CRESULT Assembler::CreateProgram(const Ceng::String &code,ObjectCode **output)
{
	ProgramBuilder *builder = new ProgramBuilder(Casm::BuilderOptions(),this);

	Ceng::CRESULT cresult;

	cresult = builder->AddFromString(code);

	if (cresult != Ceng::CE_OK)
	{
		delete builder;
		return cresult;
	}

	//cresult = builder->Build(output);

	delete builder;
	return cresult;
}
*/