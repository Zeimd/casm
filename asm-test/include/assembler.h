/*****************************************************************************
*
* asm-state.h
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#ifndef ASM_STATE_H
#define ASM_STATE_H

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/boolean.h>
#include <ceng/datatypes/return-val.h>
#include <ceng/datatypes/ce-string.h>

#include "keyword-group.h"

#include <string>
#include <unordered_map>

namespace Casm
{
	class BuilderOptions;
}

namespace X86
{
	namespace ASSEMBLER_MODE
	{
		enum value
		{
			EMBEDDED = 1 ,

			FORCE_32B = 1 << 30 ,
		};
	}

	class Instruction;
	
	class ProgramBuilder;
	class ObjectCode;

	class Instruction;
	class RegisterOperand;

	class Assembler
	{
	public:

		Ceng::UINT32 cacheLineSize;

		std::shared_ptr<Casm::KeywordGroup> testKeywords;

		/**
		 * All reserved words available at root level
		 */
		std::shared_ptr<Casm::KeywordGroup> rootKeywords;

		Assembler();
		virtual ~Assembler();

		Assembler(const Ceng::UINT32 cacheLineSize);

		Ceng::UINT32 CacheLine() const;

		Ceng::CRESULT CreateProgram(const Casm::BuilderOptions &options,ProgramBuilder **output);

		Ceng::CRESULT CreateProgram(const Ceng::String &code,ObjectCode **output);

		
		const Ceng::INT32 FindReservedWord(const Ceng::String &text) const;

	protected:

		const Ceng::CRESULT BuildReservedMap();
	};
}

#endif