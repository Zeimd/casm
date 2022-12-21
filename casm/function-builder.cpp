/*****************************************************************************
*
* function.cpp
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#include "function-builder.h"
#include "condition-jump.h"
#include "data-item.h"
#include "program-builder.h"

#include "code-element.h"
#include "basic-block.h"

#include "obj-function.h"

#include "x86-opcodes-alu.h"

#include "x86-memory-op.h"
#include "x86-immediate-op.h"

#include "x86-opcode-map.h"

using namespace X86;

FunctionBuilder::FunctionBuilder()
	: currentMode(nullptr), currentPR(PRIVILEDGE_LEVEL::ANY), references(nullptr),program(nullptr)
{

}

FunctionBuilder::FunctionBuilder(const Ceng::String &name,ProgramBuilder *program)
	: Symbol(name,SectionType::text, SymbolType::function,false,false),
	program(program),
	currentMode(nullptr), currentPR(PRIVILEDGE_LEVEL::ANY)
{
	InitializeParams();

	references = new std::vector<std::shared_ptr<SymbolRef>>();
}

FunctionBuilder::FunctionBuilder(const Ceng::String &name,ProgramBuilder *program,
								 const CPU_Mode *startMode,const PRIVILEDGE_LEVEL::value prLevel) 
	: Symbol(name,SectionType::text, SymbolType::function,true,false),
	program(program),currentMode(startMode),currentPR(prLevel)
{
	InitializeParams();

	references = new std::vector<std::shared_ptr<SymbolRef>>();
}

Ceng::CRESULT FunctionBuilder::InitializeParams()
{
	params = std::shared_ptr<BuildParams>(new BuildParams());
	
	params->function = this;
	params->mode = currentMode;
	params->priviledgeLevel = currentPR;

	return Ceng::CE_OK;
}

FunctionBuilder::~FunctionBuilder()
{
	if (references != nullptr)
	{
		delete references;
	}
}

Ceng::CRESULT FunctionBuilder::AddSymbolRef(SymbolRef* symbolRef)
{
	references->push_back(std::shared_ptr<SymbolRef>(symbolRef));

	return Ceng::CE_OK;
}

/*
Ceng::CRESULT FunctionBuilder::AddSymbolRef(std::shared_ptr<Symbol> symbol, const Ceng::UINT64 offset,
	const OPERAND_SIZE::value encodeSize,
	const Casm::REFERENCE_TYPE::value refType)
{
	references->emplace_back(symbol, offset, encodeSize, refType);

	return Ceng::CE_OK;
}
*/

Ceng::CRESULT FunctionBuilder::SetStartMode(const CPU_Mode *startMode,
											const PRIVILEDGE_LEVEL::value prLevel)
{
	currentMode = startMode;
	currentPR = prLevel;

	InitializeParams();

	return Ceng::CE_OK;
}

Ceng::CRESULT FunctionBuilder::FlushCurrentBlock()
{
	Ceng::CRESULT cresult = Ceng::CE_OK;;

	if (currentBlock != nullptr)
	{
		cresult = currentBlock->Build(params.get(),labels,codeList);

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

Ceng::CRESULT FunctionBuilder::StartBlock()
{
	if (currentBlock == nullptr)
	{
		currentBlock = std::shared_ptr<BasicBlock>(new BasicBlock(codeList.size()));
	}

	return Ceng::CE_OK;
}

Ceng::CRESULT FunctionBuilder::MoveAddress(const Operand *dest,const Ceng::String &sourceSymbol)
{
	std::shared_ptr<Symbol> source = program->FindSymbol(sourceSymbol);

	if (source == nullptr)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	StartBlock();

	currentBlock->AddLine(new BinaryOp(X86::MOV,dest,new ImmediateOperand(source)));
	return Ceng::CE_OK;	
}

Ceng::CRESULT FunctionBuilder::Call(const Ceng::String &functionName)
{
	std::shared_ptr<Symbol> target = program->FindFunction(functionName);

	if (target == nullptr)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	StartBlock();

	currentBlock->AddLine(new UnaryOp(X86::CALL,new ImmediateOperand(target)));
	return Ceng::CE_OK;
}

Ceng::CRESULT FunctionBuilder::AddInstruction(const Instruction &instruction)
{
	StartBlock();

	currentBlock->AddLine(new BareOp(instruction));

	return Ceng::CE_OK;
}

Ceng::CRESULT FunctionBuilder::AddInstruction(const Instruction &instruction,const Ceng::String &destSymbol,
											  const Operand *source)
{
	std::shared_ptr<Symbol> dest = program->FindData(destSymbol);

	if (dest == nullptr)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	StartBlock();

	currentBlock->AddLine(new BinaryOp(instruction,new MemoryOperand(dest),source));
	return Ceng::CE_OK;
}

Ceng::CRESULT FunctionBuilder::AddInstruction(const Instruction& instruction, const Operand* dest,
	const Ceng::String& sourceSymbol)
{
	std::shared_ptr<Symbol> source = program->FindData(sourceSymbol);

	if (source == nullptr)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	StartBlock();

	currentBlock->AddLine(new BinaryOp(instruction, dest, new MemoryOperand(source)));
	return Ceng::CE_OK;
}

Ceng::CRESULT FunctionBuilder::AddInstruction(const Instruction& instruction, const Operand* operand)
{
	StartBlock();

	currentBlock->AddLine(new UnaryOp(instruction, operand));

	return Ceng::CE_OK;
}

Ceng::CRESULT FunctionBuilder::AddInstruction(const Instruction& instruction, const Operand* dest, 
	const Operand* source)
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

const Ceng::CRESULT FunctionBuilder::AddInstruction(const Instruction& instruction,
	const Operand* dest, const Operand* source1,
	const Operand* source2)
{
	StartBlock();

	currentBlock->AddLine(new ThreeOp(instruction, dest, source1, source2));

	return Ceng::CE_OK;
}


Ceng::CRESULT FunctionBuilder::AddLabel(const Ceng::String& name)
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

Ceng::CRESULT FunctionBuilder::AttachLabels()
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

Ceng::CRESULT FunctionBuilder::ConditionalJump(const Casm::CONDITION::value condition, 
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

Ceng::CRESULT FunctionBuilder::Finalize()
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

Ceng::CRESULT FunctionBuilder::Build(std::shared_ptr<ObjectFunction>* output)
{
	Ceng::CRESULT cresult;

	cresult = Finalize();
	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	std::vector<Ceng::UINT8>* codeBuffer;

	codeBuffer = new std::vector<Ceng::UINT8>();

	for (size_t k = 0; k < codeList.size(); k++)
	{
		codeList[k]->offset = codeBuffer->size();

		cresult = codeList[k]->Append(*codeBuffer);
		if (cresult != Ceng::CE_OK)
		{
			return cresult;
		}
	}

	*output = std::shared_ptr<ObjectFunction>(new ObjectFunction(name, references, codeBuffer));

	objectFunction = *output;

	codeList.clear();

	return Ceng::CE_OK;
}

Ceng::CRESULT FunctionBuilder::MoveReferencesToObjectCode()
{
	Ceng::UINT32 k;

	for (k = 0; k < references->size(); k++)
	{
		if ((*references)[k]->symbol->Type() == SymbolType::function)
		{
			FunctionBuilder* function = (*references)[k]->symbol->AsFunction();

			(*references)[k]->symbol = static_cast<std::shared_ptr<Symbol>>(function->objectFunction);
		}
	}

	references = nullptr;

	return Ceng::CE_OK;
}


/*
Ceng::CRESULT FunctionBuilder::AddInstruction(const Ceng::String &instruction)
{
	X86::CodeLine *line = nullptr;

	line = program->ParseInstruction(instruction);

	if (line == nullptr)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	StartBlock();

	currentBlock->AddLine(line);

	return Ceng::CE_OK;
}
*/

/*
Ceng::CRESULT FunctionBuilder::AddInstruction(Ceng::String &instruction,
											  const Operand *dest,const Operand *source)
{
	auto opcodeMap = X86::OpcodeMap::GetInstance();

	const Instruction *opcode = opcodeMap->FindOpcode(instruction);

	if (opcode == nullptr)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	return AddInstruction(*opcode,dest,source);
}
*/



/*
Ceng::CRESULT FunctionBuilder::AddInstruction(Ceng::String &instruction,
											  const Operand *operand)
{
	auto opcodeMap = X86::OpcodeMap::GetInstance();

	const Instruction *opcode = opcodeMap->FindOpcode(instruction);

	if (opcode == nullptr)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	return AddInstruction(*opcode,operand);
}
*/



/*
const Operand* FunctionBuilder::ParseOperand(const Ceng::String &operand)
{
	const Operand *output;

	// Test for immediate operand

	if (operand[0] == '[')
	{
		// Memory operand
	}

	// Register operand

	return nullptr;
	//return program->Assembler()->FindRegister(operand);
}
*/

/*
const Ceng::CRESULT FunctionBuilder::AddInstruction(const Ceng::String &instruction,
													const Ceng::String &dest,const Ceng::String &source)
{
	auto opcodeMap = X86::OpcodeMap::GetInstance();

	const Instruction *opcode = opcodeMap->FindOpcode(instruction);

	if (opcode == nullptr)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	const Operand *destOp = ParseOperand(dest);

	if (destOp == nullptr)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	const Operand *sourceOp = ParseOperand(source);

	if (sourceOp == nullptr)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	return AddInstruction(*opcode,destOp,sourceOp);
}
*/



/*
const Ceng::CRESULT FunctionBuilder::AddInstruction(Ceng::String &instruction,
													const Operand *dest,const Operand *source1,
													const Operand *source2)
{
	auto opcodeMap = X86::OpcodeMap::GetInstance();

	const Instruction *opcode = opcodeMap->FindOpcode(instruction);

	if (opcode == nullptr)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	return AddInstruction(*opcode,dest,source1,source2);

	return Ceng::CE_OK;
}
*/




