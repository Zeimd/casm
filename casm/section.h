
#ifndef CASM_SECTION_H
#define CASM_SECTION_H

#include "symbol.h"

#include "enums/x86-priviledge-levels.h"

#include "enums/section-options.h"

#include "enums/condition-codes.h"

#include "build-params.h"

#include <ceng/datatypes/ce-string.h>

#include <memory>

#include <ostream>

namespace X86
{
	class CPU_Mode;
	class Operand;
	class Instruction;

}

namespace Casm
{
	class ProgramBuilder;

	class CodeElement;
	class BasicBlock;

	class CodeLabel;

	class SymbolRef;

	class ObjectSection;


	class DataDescriptor;
	class InitializerType;

	class Section : public Symbol
	{
	protected:

		uint32_t options;

		ProgramBuilder* program;

		const X86::CPU_Mode* currentMode;

		X86::PRIVILEDGE_LEVEL::value currentPR;

		std::shared_ptr<X86::BuildParams> params;

		std::vector<std::shared_ptr<CodeElement>> codeList;

		std::vector<std::shared_ptr<CodeLabel>> labels;

		std::shared_ptr<BasicBlock> currentBlock;

		std::shared_ptr<ObjectSection> objectSection;

		Section();

	public:

		~Section() override;

		Section(const Ceng::String& name, const uint32_t options, 
			const X86::CPU_Mode* startMode,
			X86::PRIVILEDGE_LEVEL::value prLevel, ProgramBuilder* program);

		std::shared_ptr<ObjectSection> GetObjectSection();

		Ceng::CRESULT SetStartMode(const X86::CPU_Mode* startMode,
			const X86::PRIVILEDGE_LEVEL::value prLevel);

		Ceng::CRESULT Build(std::shared_ptr<ObjectSection>& output);

		Ceng::CRESULT AddLabel(const Ceng::String& label, bool isGlobal=false);

		Ceng::CRESULT AddSymbolRef(std::shared_ptr<SymbolRef>& ref);

		Ceng::CRESULT ConditionalJump(const Casm::CONDITION::value condition,
			const Ceng::String& label);

		Ceng::CRESULT Call(const Ceng::String& functionName);

		Ceng::CRESULT AddInstruction(const X86::Instruction& instruction);

		Ceng::CRESULT AddInstruction(const X86::Instruction& instruction,
			const X86::Operand* operand);

		Ceng::CRESULT AddInstruction(const X86::Instruction& instruction,
			const X86::Operand* dest, const X86::Operand* source);

		const Ceng::CRESULT AddInstruction(const X86::Instruction& instruction,
			const X86::Operand* dest, const X86::Operand* source1,
			const X86::Operand* source2);

		Ceng::CRESULT AddInstruction(const X86::Instruction& instruction, 
			const Ceng::String& destSymbol, const X86::Operand* source);

		Ceng::CRESULT AddInstruction(const X86::Instruction& instruction, 
			const X86::Operand* dest, const Ceng::String& sourceSymbol);

		Ceng::CRESULT MoveAddress(const X86::Operand* dest, const Ceng::String& sourceSymbol);

		// Add initialized data
		Ceng::CRESULT AddData(const DataDescriptor& dataDesc, const Ceng::String& name,
			const InitializerType* initializer);

		// Add string literal
		Ceng::CRESULT AddData(const DataDescriptor& dataDesc, const Ceng::String& name,
			const char* initializer);

		// Add uninitialized data
		Ceng::CRESULT AddData(const DataDescriptor& dataDesc, const Ceng::String& name);

		void Print(std::wostream& out) const;

	protected:

		Ceng::CRESULT AttachLabels();

		Ceng::CRESULT FlushCurrentBlock();
		Ceng::CRESULT StartBlock();

		Ceng::CRESULT InitializeParams();

	};
}

#endif