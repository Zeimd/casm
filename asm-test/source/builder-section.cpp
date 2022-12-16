
#include "../include/builder-section.h"

using namespace X86;

BuilderSection::BuilderSection() : type(SectionType::undefined), builder(nullptr)
{

}

BuilderSection::BuilderSection(Ceng::String& name, SectionType::value type, ProgramBuilder* builder)
	: name(name), builder(builder), type(type)
{

}


BuilderSection::~BuilderSection()
{

}

Ceng::String BuilderSection::Name()
{
	return name;
}

Ceng::CRESULT BuilderSection::AddData(const DataDescriptor& dataDesc, const Ceng::String& name,
	const InitializerType* initializer)
{
	/*
	DataItem* temp = new DataItem();

	temp->options = dataDesc.options;
	temp->elementSize = dataDesc.size;
	temp->name = name;
	temp->initializer = initializer;

	dataSection->push_back(std::shared_ptr<DataItem>(temp));
	*/

	return Ceng::CE_OK;
}

Ceng::CRESULT BuilderSection::AddData(const DataDescriptor& dataDesc, const InitializerType* initializer)
{
	return Ceng::CE_OK;
}

Ceng::CRESULT BuilderSection::AddLabel(const Ceng::String& label)
{
	return Ceng::CE_OK;
}

Ceng::CRESULT BuilderSection::ConditionalJump(const Casm::CONDITION::value condition,
	const Ceng::String& label)
{
	return Ceng::CE_OK;
}

Ceng::CRESULT BuilderSection::Call(const Ceng::String& functionName)
{
	return Ceng::CE_OK;
}

Ceng::CRESULT BuilderSection::AddInstruction(const Instruction& instruction)
{
	return Ceng::CE_OK;
}

Ceng::CRESULT BuilderSection::AddInstruction(const Instruction& instruction,
	const Operand* operand)
{
	return Ceng::CE_OK;
}

Ceng::CRESULT BuilderSection::AddInstruction(const Instruction& instruction,
	const Operand* dest, const Operand* source)
{
	return Ceng::CE_OK;
}

const Ceng::CRESULT BuilderSection::AddInstruction(const Instruction& instruction,
	const Operand* dest, const Operand* source1,
	const Operand* source2)
{
	return Ceng::CE_OK;
}

Ceng::CRESULT BuilderSection::AddInstruction(const Instruction& instruction,
	const Ceng::String& destSymbol, const Operand* source)
{
	return Ceng::CE_OK;
}

Ceng::CRESULT BuilderSection::AddInstruction(const Instruction& instruction,
	const Operand* dest, const Ceng::String& sourceSymbol)
{
	return Ceng::CE_OK;
}

Ceng::CRESULT BuilderSection::MoveAddress(const Operand* dest, const Ceng::String& sourceSymbol)
{
	return Ceng::CE_OK;
}


