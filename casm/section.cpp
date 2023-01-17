
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

#include "data-item.h"

#include "data-descriptor.h"

#include <ceng/datatypes/return-val.h>

using namespace Casm;

Section::Section() :
	currentMode(nullptr),currentPR(X86::PRIVILEDGE_LEVEL::ANY),program(nullptr),
	options(0),objectSection(nullptr)
{

}

Section::~Section()
{

}

Section::Section(const Ceng::String& name, const uint32_t options,
	const X86::CPU_Mode* startMode,
	X86::PRIVILEDGE_LEVEL::value prLevel, ProgramBuilder* program)
	: Symbol(name, this, Casm::SymbolType::section,true,true),
	currentMode(startMode), options(options), currentPR(prLevel), program(program),
	objectSection(nullptr)
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

ObjectSection* Section::GetObjectSection()
{
	return objectSection;
}


Ceng::CRESULT Section::FlushCurrentBlock()
{
	if (currentBlock != nullptr)
	{
		codeList.push_back(currentBlock);
		currentBlock = nullptr;
	}

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::StartBlock()
{
	if (currentBlock == nullptr)
	{
		currentBlock = std::make_shared<BasicBlock>(codeList.size());
	}

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::AddLabel(const Ceng::String& name, bool isGlobal)
{
	SymbolType::value symbolType = SymbolType::data;

	if (options & SectionOptions::executable)
	{
		symbolType = SymbolType::function;
	}

	std::shared_ptr<Symbol> symbol = program->FindSymbol(name);

	if (symbol->IsDefined())
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	FlushCurrentBlock();

	symbol->MarkDefined(this, symbolType, isGlobal);

	labels.emplace_back(
		std::make_shared<CodeLabel>(codeList.size(), symbol));

	codeList.push_back(labels.back());

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::AttachLabels()
{
	for (size_t k = 0; k < codeList.size(); ++k)
	{
		if (codeList[k]->Type() == CodeElement::LABEL)
		{
			std::shared_ptr<CodeLabel> temp = 
				std::static_pointer_cast<CodeLabel>(codeList[k]);
			
			size_t next = k++;
			if (next < codeList.size())
			{
				temp->SetTarget(codeList[next].get());
			}
			else
			{
				// TODO: how to indicate label to end of section?
			}
		}
		
	}

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::AppendRelocationData(std::vector<RelocationData>& out)
{
	for (auto& x : codeList)
	{
		Ceng::CRESULT cresult;

		cresult = x->AppendRelocationData(out);

		if (cresult != Ceng::CE_OK)
		{
			return cresult;
		}
	}

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::Build(std::shared_ptr<ObjectSection>& output)
{
	output = nullptr;

	Ceng::CRESULT cresult;

	cresult = FlushCurrentBlock();

	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	AttachLabels();

	for (auto& x : codeList)
	{
		cresult = x->PreBuild(params.get());

		if (cresult != Ceng::CE_OK)
		{
			return cresult;
		}
	}

	std::vector<Ceng::UINT8> codeBuffer;

	std::vector<Casm::RelocationData> relocationData;

	for (size_t k = 0; k < codeList.size(); k++)
	{
		codeList[k]->SetOffset(codeBuffer.size());

		cresult = codeList[k]->Append(codeBuffer);
		if (cresult != Ceng::CE_OK)
		{
			return cresult;
		}
	}

	output = std::make_shared<ObjectSection>(name,options, 
		std::move(codeBuffer));

	objectSection = output.get();

	return Ceng::CE_OK;
}

void Section::Print(std::wostream& out) const
{
	size_t size = codeList.size();

	if (currentBlock != nullptr)
	{
		++size;
	}

	out << "section " << name << std::endl;

	for (auto& item : codeList)
	{
		item->Print(out);
	}

	if (currentBlock != nullptr)
	{
		currentBlock->Print(out);
	}
}


Ceng::CRESULT Section::AddData(const DataDescriptor& dataDesc, const Ceng::String& name,
	const InitializerType* initializer)
{
	AddLabel(name);

	StartBlock();

	std::shared_ptr<CodeLine> item =
		std::make_shared<DataItem>(dataDesc.options, dataDesc.size, this, initializer);

	currentBlock->AddLine(item);

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::AddData(const DataDescriptor& dataDesc, const Ceng::String& name,
	const char* initializer)
{
	AddLabel(name);

	StartBlock();

	std::shared_ptr<CodeLine> item =
		std::make_shared<DataItem>(dataDesc.options, dataDesc.size, this,
			new StringLiteralInitializer(initializer));

	currentBlock->AddLine(item);

	return Ceng::CE_OK;
}


Ceng::CRESULT Section::AddData(const DataDescriptor& dataDesc, const Ceng::String& name)
{
	AddLabel(name);

	StartBlock();

	std::shared_ptr<CodeLine> item =
		std::make_shared<DataItem>(dataDesc.options, dataDesc.size, this, nullptr);

	currentBlock->AddLine(item);

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

	std::shared_ptr<CodeLine> line =
		std::make_shared<BinaryOp>(X86::MOV, dest, new X86::ImmediateOperand(source,
			params->mode->addressSize));

	currentBlock->AddLine(line);
	return Ceng::CE_OK;
}

Ceng::CRESULT Section::Call(const Ceng::String& functionName)
{
	std::shared_ptr<Symbol> target = program->FindSymbol(functionName);

	if (target == nullptr)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	target->SetType(SymbolType::function);

	StartBlock();

	std::shared_ptr<CodeLine> line =
		std::make_shared<UnaryOp>(X86::CALL,
			new X86::ImmediateOperand(target, params->mode->defaultOpSize));

	currentBlock->AddLine(line);

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::AddInstruction(const X86::Instruction& instruction)
{
	StartBlock();

	std::shared_ptr<CodeLine> line = std::make_shared<BareOp>(instruction);

	currentBlock->AddLine(line);

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::AddInstruction(const X86::Instruction& instruction, const Ceng::String& destSymbol,
	const X86::Operand* source)
{
	std::shared_ptr<Symbol> dest = program->FindSymbol(destSymbol);

	if (dest == nullptr)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	StartBlock();

	std::shared_ptr<CodeLine> line =
		std::make_shared<BinaryOp>(instruction, new X86::MemoryOperand(dest), source);

	currentBlock->AddLine(line);
	return Ceng::CE_OK;
}

Ceng::CRESULT Section::AddInstruction(const X86::Instruction& instruction, 
	const X86::Operand* dest, const Ceng::String& sourceSymbol)
{
	std::shared_ptr<Symbol> source = program->FindSymbol(sourceSymbol);

	if (source == nullptr)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	StartBlock();

	std::shared_ptr<CodeLine> line =
		std::make_shared<BinaryOp>(instruction, dest,
			new X86::MemoryOperand(source));

	currentBlock->AddLine(line);

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::AddInstruction(const X86::Instruction& instruction, 
	const X86::Operand* operand)
{
	StartBlock();

	std::shared_ptr<CodeLine> line =
		std::make_shared<UnaryOp>(instruction, operand);

	currentBlock->AddLine(line);

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::AddInstruction(const X86::Instruction& instruction, 
	const X86::Operand* dest, const X86::Operand* source)
{
	StartBlock();

	Ceng::CRESULT cresult;

	std::shared_ptr<CodeLine> line =
		std::make_shared<BinaryOp>(instruction, dest, source);

	cresult = currentBlock->AddLine(line);

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

	std::shared_ptr<CodeLine> line =
		std::make_shared<ThreeOp>(instruction, dest, source1, source2);

	currentBlock->AddLine(line);

	return Ceng::CE_OK;
}

Ceng::CRESULT Section::ConditionalJump(const Casm::CONDITION::value condition,
	const Ceng::String& label)
{
	FlushCurrentBlock();

	/*

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
		labels.emplace_back(std::make_shared<Label>(this, label, true));
	}

	codeList.push_back(std::shared_ptr<CodeElement>(new ConditionJump(codeList.size(),
		condition, labels[k].get())));

	Ceng::CRESULT cresult;

	cresult = AttachLabels();
	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}
	*/

	return Ceng::CE_OK;
}