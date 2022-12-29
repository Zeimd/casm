
#include "section.h"

#include "build-params.h"

#include "basic-block.h"

#include "program-builder.h"

#include "x86-opcodes-alu.h"

#include "x86-memory-op.h"
#include "x86-immediate-op.h"
#include "x86-opcode-map.h"

#include "code-label.h"

#include "condition-jump.h"

#include "object-section.h"

using namespace Casm;

Section::Section() :
	currentMode(nullptr),currentPR(X86::PRIVILEDGE_LEVEL::ANY),program(nullptr)
{

}

Section::~Section()
{

}

Section::Section(const Ceng::String& name, const uint32_t options,
	X86::PRIVILEDGE_LEVEL::value prLevel, ProgramBuilder* program)
	: Symbol(name, nullptr, X86::SymbolType::section,true,false),
	currentMode(nullptr), options(options), currentPR(prLevel), program(program)
{
	InitializeParams();
}

Ceng::CRESULT Section::InitializeParams()
{
	params = std::make_shared<X86::BuildParams>();

	params->section = this;
	params->mode = currentMode;
	params->priviledgeLevel = currentPR;

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::SetStartMode(const X86::CPU_Mode* startMode,
	const X86::PRIVILEDGE_LEVEL::value prLevel)
{
	currentMode = startMode;
	currentPR = prLevel;

	InitializeParams();

	return Ceng::CE_OK;
}


Ceng::CRESULT Section::AddData(const DataDescriptor& dataDesc, const Ceng::String& name,
	const InitializerType* initializer)
{
	/*
	dataSection->push_back(std::make_shared<DataItem>(
		name, dataDesc.options, dataDesc.size, SectionType::data,
		initializer));
		*/

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::AddData(const DataDescriptor& dataDesc, const Ceng::String& name,
	const char* initializer)
{
	/*
	dataSection->push_back(std::make_shared<DataItem>(
		name, dataDesc.options, X86::OPERAND_SIZE::BYTE, SectionType::data,
		new StringLiteralInitializer(initializer)));
		*/

	return Ceng::CE_OK;
}


Ceng::CRESULT Section::AddData(const DataDescriptor& dataDesc, const Ceng::String& name)
{
	/*
	bssSection->push_back(std::make_shared<DataItem>(
		name, dataDesc.options, dataDesc.size, SectionType::bss,
		nullptr));
		*/

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::FlushCurrentBlock()
{
	Ceng::CRESULT cresult = Ceng::CE_OK;;

	if (currentBlock != nullptr)
	{
		cresult = currentBlock->Build(params.get(), labels, codeList);

		if (cresult != Ceng::CE_OK)
		{
			return cresult;
		}

		codeList.push_back(currentBlock);
		AttachLabels();

		currentBlock = nullptr;
	}

	return cresult;
}

Ceng::CRESULT Section::StartBlock()
{
	if (currentBlock == nullptr)
	{
		currentBlock = std::shared_ptr<BasicBlock>(new BasicBlock(codeList.size()));
	}

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::MoveAddress(const X86::Operand* dest, const Ceng::String& sourceSymbol)
{
	std::shared_ptr<Symbol> source = program->FindSymbol(sourceSymbol);

	if (source == nullptr)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	StartBlock();

	currentBlock->AddLine(new BinaryOp(X86::MOV, dest, new X86::ImmediateOperand(source,
		params->mode->addressSize)));
	return Ceng::CE_OK;
}

Ceng::CRESULT Section::Call(const Ceng::String& functionName)
{
	std::shared_ptr<Symbol> target = program->FindFunction(functionName);

	if (target == nullptr)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	StartBlock();

	currentBlock->AddLine(new UnaryOp(X86::CALL,
		new X86::ImmediateOperand(target, params->mode->defaultOpSize)));

	return Ceng::CE_ERR_NOT_SUPPORTED;
}

Ceng::CRESULT Section::AddInstruction(const X86::Instruction& instruction)
{
	StartBlock();

	currentBlock->AddLine(new BareOp(instruction));

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::AddInstruction(const X86::Instruction& instruction, const Ceng::String& destSymbol,
	const X86::Operand* source)
{
	std::shared_ptr<Symbol> dest = program->FindData(destSymbol);

	if (dest == nullptr)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	StartBlock();

	currentBlock->AddLine(new BinaryOp(instruction, new X86::MemoryOperand(dest), source));
	return Ceng::CE_OK;
}

Ceng::CRESULT Section::AddInstruction(const X86::Instruction& instruction, 
	const X86::Operand* dest, const Ceng::String& sourceSymbol)
{
	std::shared_ptr<Symbol> source = program->FindData(sourceSymbol);

	if (source == nullptr)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	StartBlock();

	currentBlock->AddLine(new BinaryOp(instruction, dest, 
		new X86::MemoryOperand(source)));

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::AddInstruction(const X86::Instruction& instruction, 
	const X86::Operand* operand)
{
	StartBlock();

	currentBlock->AddLine(new UnaryOp(instruction, operand));

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::AddInstruction(const X86::Instruction& instruction, 
	const X86::Operand* dest, const X86::Operand* source)
{
	StartBlock();

	Ceng::CRESULT cresult;

	cresult = currentBlock->AddLine(new BinaryOp(instruction, dest, source));

	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	return Ceng::CE_OK;
}

const Ceng::CRESULT Section::AddInstruction(const X86::Instruction& instruction,
	const X86::Operand* dest, const X86::Operand* source1,
	const X86::Operand* source2)
{
	StartBlock();

	currentBlock->AddLine(new ThreeOp(instruction, dest, source1, source2));

	return Ceng::CE_OK;
}


Ceng::CRESULT Section::AddLabel(const Ceng::String& name)
{
	Ceng::UINT32 k;

	for (k = 0; k < labels.size(); k++)
	{
		if (labels[k]->CompareName(name))
		{
			break;
		}
	}

	if (k < labels.size())
	{
		if (labels[k]->Undefined())
		{
			FlushCurrentBlock();
			labels[k]->MarkDefined();
		}
		else
		{
			return Ceng::CE_ERR_INVALID_PARAM;
		}
	}
	else
	{
		FlushCurrentBlock();
		labels.push_back(std::shared_ptr<Label>(new Label(name, false)));
	}

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::AttachLabels()
{
	if (labels.size() == 0) return Ceng::CE_OK;

	if (codeList.size() == 0) return Ceng::CE_OK;

	CodeElement* target = codeList[codeList.size() - 1].get();

	for (size_t k = 0; k < labels.size(); k++)
	{
		if (labels[k]->Undefined() == false)
		{
			if (labels[k]->Target() == nullptr)
			{
				labels[k]->SetTarget(target);
			}
		}
	}

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::ConditionalJump(const Casm::CONDITION::value condition,
	const Ceng::String& label)
{
	FlushCurrentBlock();

	Ceng::UINT32 k;

	for (k = 0; k < labels.size(); k++)
	{
		if (labels[k]->CompareName(label))
		{
			break;
		}
	}

	// If label does not exist, declare an undefined label
	if (k == labels.size())
	{
		labels.push_back(std::shared_ptr<Label>(new Label(label, true)));
	}

	codeList.push_back(std::shared_ptr<CodeElement>(new ConditionJump(codeList.size(),
		condition, labels[k].get())));

	Ceng::CRESULT cresult;

	cresult = AttachLabels();
	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::Finalize()
{
	Ceng::CRESULT cresult;


	cresult = FlushCurrentBlock();

	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	Ceng::UINT32 k;

	for (k = 0; k < codeList.size(); k++)
	{
		if (codeList[k]->Type() == CodeElement::BASIC_BLOCK) continue;

		cresult = codeList[k]->Build(params.get(), labels, codeList);
		if (cresult != Ceng::CE_OK)
		{
			return cresult;
		}

	}

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::Build(std::shared_ptr<ObjectSection>& output)
{
	Ceng::CRESULT cresult;

	cresult = Finalize();
	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	std::vector<Ceng::UINT8> codeBuffer;

	for (size_t k = 0; k < codeList.size(); k++)
	{
		codeList[k]->offset = codeBuffer.size();

		cresult = codeList[k]->Append(codeBuffer);
		if (cresult != Ceng::CE_OK)
		{
			return cresult;
		}
	}

	output = std::make_shared<ObjectSection>(name, std::move(labels), std::move(references), 
		std::move(codeBuffer));

	objectSection = output;

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::MoveReferencesToObjectCode()
{
	Ceng::UINT32 k;

	for (k = 0; k < references.size(); k++)
	{
		if (references[k]->symbol->Type() == X86::SymbolType::function)
		{
			/*
			FunctionBuilder* function = references[k]->symbol->AsFunction();

			references[k]->symbol = 
				static_cast<std::shared_ptr<Symbol>>(function->objectFunction);
			*/
		}
	}

	return Ceng::CE_OK;
}
