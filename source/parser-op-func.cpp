/*****************************************************************************
*
* parser-op-func.cpp
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#include "../include/parser-op-func.h"

#include "../include/program-builder.h"

#include "../include/parser-name.h"

using namespace Casm;

ParserOp_FunctionDecl::ParserOp_FunctionDecl(const TokenData &data) 
	: ParserOperator(ParserOpType::func_decl,ParserOpMode::unary_prefix,
	ParserOpRange::nearest,ParserOpAssocDir::right,parser_priority_block_decl,2,data)
{
}

ParserOp_FunctionDecl::~ParserOp_FunctionDecl()
{
}

const char* ParserOp_FunctionDecl::TypeString() const
{
	return "function declaration";
}

const std::shared_ptr<ParserOperand> ParserOp_FunctionDecl::LocalAction(ParserState *state,
															std::shared_ptr<ParserOperand> left,
															std::shared_ptr<ParserOperand> right)
{
	if (right == nullptr)
	{
		return nullptr;
	}

	ParserName *name = dynamic_cast<ParserName*>(right.get());

	if (name == nullptr)
	{
		return nullptr;
	}

	X86::FunctionBuilder *function;

	Ceng::CRESULT cresult;

	cresult = state->program->AddFunction(0,X86::PROTECTED_MODE,X86::PRIVILEDGE_LEVEL::USER,name->Name(),&function);

	if (cresult != Ceng::CE_OK)
	{
		return nullptr;
	}

	//state->function = function;
	
	//state->activeContext = functionContext;

	return nullptr;
	//return new ParserOperand(;
}