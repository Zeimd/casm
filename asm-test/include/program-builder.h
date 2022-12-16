/*****************************************************************************
*
* program-builder.h
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#ifndef X86_PROGRAM_BUILDER_H
#define X86_PROGRAM_BUILDER_H

#include "builder-options.h"

#include "function-builder.h"

#include "enums/x86-operand-sizes.h"
#include "enums/x86-priviledge-levels.h"

#include "object-code.h"

#include "parser-token.h"

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/return-val.h>
#include <ceng/datatypes/ce-string.h>
#include <memory>

#include <sstream>
#include <list>
#include <iterator>

namespace Casm
{
	class ParserLiteral;
}

namespace X86
{
	class Assembler;
	class InitializerType;
	
	class CodeLine;

	class CPU_Mode;

	class DataDescriptor;

	class ImmediateOperand;
	class MemoryOperand;

	class Symbol;

	class ProgramBuilder
	{
	protected:

		const Casm::BuilderOptions options;

		std::stringstream errorLog;

		std::vector<std::shared_ptr<FunctionBuilder>> functions;

		std::vector<std::shared_ptr<Symbol>> *dataSection;

		std::list<std::shared_ptr<Symbol>> undefinedList; 

		const Assembler *assembler;

		ProgramBuilder() : options(Casm::BuilderOptions())
		{
		}
	public:

		ProgramBuilder(const Casm::BuilderOptions &options,const Assembler *assembler) :
			options(options),assembler(assembler)
		{
			dataSection = new std::vector<std::shared_ptr<Symbol>>();
		}

		const Casm::BuilderOptions* BuildOptions() const; 

		~ProgramBuilder();

		const Assembler* Assembler() const;

		Ceng::CRESULT AddData(const DataDescriptor &dataDesc,const Ceng::String &name,
								const InitializerType *initializer);

		std::shared_ptr<Symbol> FindData(const Ceng::String &name);

		std::shared_ptr<Symbol> FindFunction(const Ceng::String &name);

		std::shared_ptr<Symbol> FindSymbol(const Ceng::String &name);

		Ceng::CRESULT AddFunction(const Ceng::UINT32 options,
									const CPU_Mode &startMode,const PRIVILEDGE_LEVEL::value prLevel,
									const Ceng::String &name,FunctionBuilder **function);

		//const Ceng::CRESULT AddFromString(const Ceng::String &code);
		
		Ceng::CRESULT Build(ObjectCode **output);

		//X86::CodeLine* ParseInstruction(const Ceng::String &input);

	protected:

		//static const Ceng::String CleanParserLine(const Ceng::String &line);

		//Casm::ParserLiteral* ParseLiteral(Ceng::String::CONST_ITERATOR_TYPE start,
		//												Ceng::String::CONST_ITERATOR_TYPE &end);

		//const Ceng::CRESULT LexAnalyze(const Ceng::String &code,
		//									Casm::ParserState *state,
		//									std::vector<Casm::ParserToken*> &output);

		//void WalkWhileInteger(Ceng::String::CONST_ITERATOR_TYPE &iter,const Ceng::INT32 numBase);

		//static const Ceng::UINT64 StringToUint(const Ceng::String::CONST_ITERATOR_TYPE start,
		//											  const Ceng::String::CONST_ITERATOR_TYPE end,
		//											  const Ceng::INT32 base);

		//static const Ceng::FLOAT64 StringIntToDouble(const Ceng::String::CONST_ITERATOR_TYPE start,
		//											  const Ceng::String::CONST_ITERATOR_TYPE end,
		//											  const Ceng::INT32 base);

		//X86::CodeLine* ProgramBuilder::ParseOperand(const Ceng::String &operand);
	};
}

#endif