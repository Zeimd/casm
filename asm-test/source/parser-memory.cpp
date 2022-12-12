/*****************************************************************************
*
* parser-memory.cpp
*
* By Jari Korkala 5/2014
*
*****************************************************************************/

#include "../include/parser-memory.h"

/*

using namespace Casm;

ParserMemory::ParserMemory(const X86::RegisterOperand *baseReg,const X86::RegisterOperand *indexReg,
						   const Ceng::UINT32 indexScale,const Ceng::INT32 offset,
						   const X86::OPERAND_SIZE::value opSize,
						   const TokenData &data)
	: ParserOperand(ParserToken::memoryOp,ParserBasicType::unknown,0,data),
	baseReg(baseReg),indexReg(indexReg),indexScale(indexScale),offset(offset),opSize(opSize),data(data)
{
}

ParserMemory::~ParserMemory()
{
}

const X86::RegisterOperand* ParserMemory::BaseReg() const
{
	return baseReg;
}

const X86::RegisterOperand* ParserMemory::IndexReg() const
{
	return indexReg;
}

const Ceng::UINT32 ParserMemory::IndexScale() const
{
	return indexScale;
}

const Ceng::INT32 ParserMemory::Offset() const
{
	return offset;
}

const X86::OPERAND_SIZE::value ParserMemory::OpSize() const
{
	return opSize;
}

const std::shared_ptr<ParserOperand> ParserMemory::SizeCast(ParserState *state,
															std::shared_ptr<ParserOperand> right_this,
															const Ceng::UINT32 newSize)
{
	X86::OPERAND_SIZE::value temp = X86::OPERAND_SIZE::IMPLICIT;

	switch(newSize)
	{
	case 1:
		temp = X86::OPERAND_SIZE::BYTE;
		break;
	case 2:
		temp = X86::OPERAND_SIZE::WORD;
		break;
	case 4:
		temp = X86::OPERAND_SIZE::DWORD;
		break;
	case 8:
		temp = X86::OPERAND_SIZE::QWORD;
		break;
	case 16:
		temp = X86::OPERAND_SIZE::XMMWORD;
		break;
	case 32:
		temp = X86::OPERAND_SIZE::YMMWORD;
		break;
	};

	return std::shared_ptr<ParserOperand>(new ParserMemory(baseReg,indexReg,indexScale,offset,temp,data));
}

//******************************************************************************
// Memory operator

ParserOp_Memory::ParserOp_Memory(const TokenData data) 
	: ParserOperator(ParserOpType::memory,ParserOpMode::unary_prefix,ParserOpRange::nearest,
				ParserOpAssocDir::right,parser_priority_parenthesis,2,data)
{
}

ParserOp_Memory::~ParserOp_Memory()
{
}

const std::shared_ptr<ParserOperand> ParserOp_Memory::LocalAction(ParserState *state,
																  std::shared_ptr<ParserOperand> left,
																  std::shared_ptr<ParserOperand> right)
{
	if (right->TokenType() != ParserToken::group)
	{
		return nullptr;
	}

	TokenGroup *tempGroup = (TokenGroup*)right.get();

	const X86::RegisterOperand *baseReg = nullptr;
	const X86::RegisterOperand *indexReg = nullptr;

	Ceng::UINT32 indexScale = 1;

	Ceng::INT32 offset = 0;

	Ceng::CHAR currentOperator = '+';

	auto iter = tempGroup->tokens.begin();

	while(iter != tempGroup->tokens.end())
	{
		if ( (*iter)->TokenType() == ParserToken::registerOp )
		{
			if (currentOperator != '+')
			{
				// Can only sum register operands

				return nullptr;
			}

			ParserRegister *reg = (ParserRegister*)(*iter).get();

			if ( reg->IsIndexReg() )
			{
				if (indexReg != nullptr)
				{
					// Index register already present
					return nullptr;
				}

				if ( reg->IsComposite() )
				{
					if (baseReg != nullptr)
					{
						// Error : can't use base+scale*index = (scale+1)*index
						return nullptr;
					}

					indexReg = reg->RegisterOp();
					indexScale = reg->Scale()-1;

					baseReg = indexReg;
				}
				else
				{
					indexReg = reg->RegisterOp();
					indexScale = reg->Scale();
				}
			}
			else
			{
				if (baseReg != nullptr)
				{
					if (indexReg == nullptr)
					{
						indexReg = reg->RegisterOp();
					}
					else
					{
						// All register slots in use
						return nullptr;
					}
				}
				else
				{
					baseReg = reg->RegisterOp();
				}
			}

		}
		else if ( (*iter)->TokenType() == ParserToken::op)
		{
			ParserOperator *op = (ParserOperator*)(*iter).get();

			if (op->OperatorType() == ParserOpType::add)
			{
				currentOperator = '+';
			}
			else if (op->OperatorType() == ParserOpType::sub)
			{
				currentOperator = '-';
			}
			else
			{
				// not allowed
				return nullptr;
			}
		}
		else if ( (*iter)->TokenType() == ParserToken::literal_value)
		{
			ParserLiteral *literal = (ParserLiteral*)(*iter).get();

			if (literal->Datatype() & ParserBasicType::floating)
			{
				// not allowed
				return nullptr;
			}

			if ( !literal->RangeCheck(LONG_MIN,Ceng::UINT64(LONG_MAX)) )
			{
				// offset too large
				return nullptr;
			}

			Ceng::INT64 temp;

			literal->ToBuffer(&temp);

			if (currentOperator == '-')
			{
				temp *= -1;
			}

			offset += Ceng::INT32(temp);
		}
		else if ( (*iter)->TokenType() == ParserToken::variable )
		{
		}
		else
		{
			return nullptr;
		}

		++iter;
	}

	return std::shared_ptr<ParserOperand>(new ParserMemory(baseReg,indexReg,indexScale,offset,
								X86::OPERAND_SIZE::IMPLICIT,data));
}

*/