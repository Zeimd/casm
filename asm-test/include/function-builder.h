/*****************************************************************************
*
* code-function.h
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#ifndef X86_CODE_FUNCTION_H
#define X86_CODE_FUNCTION_H

#include <ceng/datatypes/basic-types.h>
#include <memory>

#include "enums/condition-codes.h"
#include "enums/x86-priviledge-levels.h"

#include "code-element.h"
#include "code-label.h"
#include "basic-block.h"

#include "x86-instruction.h"

#include "symbol.h"
#include "symbol-ref.h"

#include "obj-function.h"

namespace X86
{
	class CPU_Mode;

	class ProgramBuilder;

	class FunctionBuilder : public Symbol
	{
	public:

	protected:

		ProgramBuilder *program;

		const CPU_Mode *currentMode;

		PRIVILEDGE_LEVEL::value currentPR;

		std::shared_ptr<BuildParams> params;

		std::vector<std::shared_ptr<CodeElement>> codeList;

		std::vector<std::shared_ptr<Label>> labels;

		std::vector<std::shared_ptr<SymbolRef>> *references;

		std::shared_ptr<ObjectFunction> objectFunction;

		std::shared_ptr<BasicBlock> currentBlock;

		FunctionBuilder()
		{
		}

	public:

		virtual ~FunctionBuilder()
		{
		}

		FunctionBuilder(const Ceng::String &name,ProgramBuilder *program);

		FunctionBuilder(const Ceng::String &name,ProgramBuilder *program,
					const CPU_Mode *startMode,const PRIVILEDGE_LEVEL::value prLevel);

		Ceng::CRESULT SetStartMode(const CPU_Mode *startMode,
									const PRIVILEDGE_LEVEL::value prLevel);

		Ceng::CRESULT Build(std::shared_ptr<ObjectFunction> *output);

		Ceng::CRESULT MoveReferencesToObjectCode();

		Ceng::CRESULT Append(std::vector<Ceng::UINT8> &destBuffer) const;

		Ceng::CRESULT Finalize();

		Ceng::CRESULT AddLabel(const Ceng::String &label);

		Ceng::CRESULT ConditionalJump(const Casm::CONDITION::value condition,const Ceng::String &label);

		Ceng::CRESULT Call(const Ceng::String &functionName);

		//Ceng::CRESULT AddInstruction(const Ceng::String &instruction);

		Ceng::CRESULT AddInstruction(const Instruction &instruction);

		Ceng::CRESULT AddInstruction(Ceng::String &instruction,
								const Operand *operand);		
		
		Ceng::CRESULT AddInstruction(const Instruction &instruction,
								const Operand *operand);

		//const Ceng::CRESULT AddInstruction(const Ceng::String &instruction,
		//						const Ceng::String &dest,const Ceng::String &source);

		//const Operand* ParseOperand(const Ceng::String &operand);
		
		Ceng::CRESULT AddInstruction(Ceng::String &instruction,
								const Operand *dest,const Operand *source);

		Ceng::CRESULT AddInstruction(const Instruction &instruction,
								const Operand *dest,const Operand *source);

		const Ceng::CRESULT AddInstruction(const Instruction &instruction,
								const Operand *dest,const Operand *source1,
								const Operand *source2);

		const Ceng::CRESULT AddInstruction(Ceng::String &instruction,
								const Operand *dest,const Operand *source1,
								const Operand *source2);

		Ceng::CRESULT AddInstruction(const Instruction &instruction,const Ceng::String &destSymbol,const Operand *source);

		Ceng::CRESULT AddInstruction(const Instruction &instruction,const Operand *dest,const Ceng::String &sourceSymbol);

		Ceng::CRESULT MoveAddress(const Operand *dest,const Ceng::String &sourceSymbol);

	protected:
		
		Ceng::CRESULT AttachLabels();

		Ceng::CRESULT FlushCurrentBlock();
		Ceng::CRESULT StartBlock();

		Ceng::CRESULT InitializeParams();
	};
}

#endif