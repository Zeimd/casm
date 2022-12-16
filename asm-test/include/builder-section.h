#ifndef CASM_BUILDER_SECTION_H
#define CASM_BUILDER_SECTION_H

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/return-val.h>
#include <ceng/datatypes/ce-string.h>

#include "enums/condition-codes.h"

#include "enums/section-type.h"

namespace X86
{
	class DataDescriptor;
	class InitializerType;

	class Instruction;
	class Operand;

	class CodeElement;
	class Label;

	class ProgramBuilder;

	class BuildParams;

	class SymbolRef;

	class BasicBlock;

	class BuilderSection
	{
	protected:

		Ceng::String name;

		SectionType::value type;

		ProgramBuilder* builder;

		std::shared_ptr<BuildParams> params;

		//std::vector<std::shared_ptr<SymbolRef>>* references;

		std::vector<std::shared_ptr<CodeElement>> codeList;

		std::vector<std::shared_ptr<Label>> labels;

		std::shared_ptr<BasicBlock> currentBlock;

		BuilderSection();

	public:

		BuilderSection(Ceng::String& name, SectionType::value type, ProgramBuilder* builder);

		~BuilderSection();

		Ceng::String Name();

		// Add data. Create a label at start of data
		Ceng::CRESULT AddData(const DataDescriptor & dataDesc, const Ceng::String & name,
			const InitializerType * initializer);

		// Add data without creating a label
		Ceng::CRESULT AddData(const DataDescriptor& dataDesc, const InitializerType* initializer);

		Ceng::CRESULT AddLabel(const Ceng::String& label);

		Ceng::CRESULT ConditionalJump(const Casm::CONDITION::value condition, const Ceng::String& label);

		Ceng::CRESULT Call(const Ceng::String& functionName);

		Ceng::CRESULT AddInstruction(const Instruction& instruction);

		Ceng::CRESULT AddInstruction(const Instruction& instruction,
			const Operand* operand);

		Ceng::CRESULT AddInstruction(const Instruction& instruction,
			const Operand* dest, const Operand* source);

		const Ceng::CRESULT AddInstruction(const Instruction& instruction,
			const Operand* dest, const Operand* source1,
			const Operand* source2);

		Ceng::CRESULT AddInstruction(const Instruction& instruction, const Ceng::String& destSymbol, const Operand* source);

		Ceng::CRESULT AddInstruction(const Instruction& instruction, const Operand* dest, const Ceng::String& sourceSymbol);

		Ceng::CRESULT MoveAddress(const Operand* dest, const Ceng::String& sourceSymbol);

	};
}

#endif