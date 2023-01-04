/*****************************************************************************
*
* program-builder.cpp
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

//#include <ceng/datatypes/string-manipulator.h>

#include "program-builder.h"

#include "assembler.h"
#include "object-code.h"

#include "data-item.h"

#include "x86-immediate-op.h"
#include "x86-memory-op.h"

#include "section.h"


#include "parser-float.h"
#include "parser-uint64.h"

#include "parser-operator.h"
#include "parser-variable.h"
#include "parser-group.h"

#include "parser-memory.h"
#include "parser-opcode.h"

#include "parser-comma.h"

#include "parser-instruction.h"

#include "x86-register-map.h"
#include "x86-opcode-map.h"

#include "parser-op-add.h"
#include "parser-op-sub.h"
#include "parser-op-mul.h"
#include "parser-op-div.h"

#include "parser-op-size.h"
#include "parser-op-bracket.h"

#include "parser-c-global.h"

#include "data-descriptor.h"

#include "code-label.h"

#include "relocation-data.h"

#include "symbol-ref.h"

#include "object-section.h"

using namespace Casm;

namespace Casm
{
	const wchar_t unicodeWhiteList[] =
	{
		L' ',L'\t',L'\v',L'\n',L'\r',L'\f',
		L'\u00a0',L'\u1680',
		L'\u2000',L'\u2001',L'\u2002',
		L'\u2003',L'\u2004',L'\u2005',
		L'\u2006',L'\u2007',L'\u2008',
		L'\u2009',L'\u200a',
		L'\u2028',L'\u2029',
		L'\u202f',L'\u205f',
		L'\u3000'
	};

	/**
	 * Characters with special meaning.
	 */
	const char reservedChars[] = "+-*,.:;[] ";

	/**
	 * Characters not allowed in symbol names.
	 */
	const char illegalChars[] = "!\"#¤%&/(){}\\=´`\'¨^~<>|";

}

ProgramBuilder::~ProgramBuilder()
{
	/*
	if (dataSection != nullptr)
	{
		delete dataSection;
	}

	if (bssSection != nullptr)
	{
		delete bssSection;
	}
	*/
}

const Assembler* ProgramBuilder::Assembler() const
{
	return assembler;
}

const Casm::BuilderOptions* ProgramBuilder::BuildOptions() const
{
	return &options;
}

std::shared_ptr<Symbol> ProgramBuilder::FindSymbol(const Ceng::String& name)
{
	for (auto& x : symbols)
	{
		if (x->name == name)
		{
			return x;
		}
	}

	// Create undefined symbol

	symbols.emplace_back(std::make_shared<Symbol>(name, nullptr, SymbolType::unknown,
		false, false));

	return symbols.back();
}

Ceng::CRESULT ProgramBuilder::AddSection(const Ceng::UINT32 options,
	const X86::CPU_Mode& startMode, const X86::PRIVILEDGE_LEVEL::value prLevel,
	const Ceng::String& name, std::shared_ptr<Section>& out_section)
{
	Ceng::UINT32 k;

	for (k = 0; k < sections.size(); k++)
	{
		if (sections[k]->name == name)
		{
			return Ceng::CE_ERR_INVALID_PARAM;
		}
	}

	std::shared_ptr<Section> temp = 
		std::shared_ptr<Section>(new Section(name, options, &startMode, prLevel, this));

	sections.push_back(temp);

	symbols.push_back(temp);

	out_section = temp;

	return Ceng::CE_OK;
}

Ceng::CRESULT ProgramBuilder::AddSymbolRef(std::shared_ptr<SymbolRef>& ref)
{
	references.push_back(ref);
	return Ceng::CE_OK;
}

Ceng::CRESULT ProgramBuilder::Build(ObjectCode** output)
{
	*output = nullptr;

	Ceng::CRESULT cresult;

	std::vector<std::shared_ptr<ObjectSection>> objSections;

	std::vector<std::shared_ptr<Symbol>> objSymbols;


	for (auto& section : sections)
	{
		std::shared_ptr<ObjectSection> temp;

		cresult = section->Build(temp);

		if (cresult != Ceng::CE_OK)
		{
			return cresult;
		}

		objSections.push_back(temp);

		objSymbols.push_back(temp);
	}

	std::vector<std::shared_ptr<RelocationData>> relocationData;

	for (auto& x : references)
	{
		Section* relocationSection = static_cast<Section*>(x->section);

		ObjectSection* objSect = relocationSection->GetObjectSection();

		if (x->refType == Casm::REFERENCE_TYPE::ADDRESS)
		{
			if (x->symbol->GetSection() == nullptr)
			{
				relocationData.emplace_back(
					std::make_shared<RelocationData>(x->symbol->name,
						x->symbol->Type(),
						x->section->name,
						x->encodeOffset,
						x->encodeSize,
						Casm::RelocationType::full_int32,
						0)
				);

				continue;
			}

			Casm::RelocationType::value relType;

			switch (x->encodeSize)
			{
			case X86::OPERAND_SIZE::DWORD:
			{
				Ceng::UINT32* ptr = (Ceng::UINT32*)&objSect->codeBuffer[x->encodeOffset];

				*ptr = Ceng::UINT32(x->symbol->Offset());

				relType = RelocationType::full_int32;
			}
			break;
			case X86::OPERAND_SIZE::QWORD:
			{
				Ceng::UINT64* ptr = (Ceng::UINT64*)&objSect->codeBuffer[x->encodeOffset];

				*ptr = Ceng::UINT64(x->symbol->Offset());

				relType = RelocationType::full_uint64;
			}
			break;
			}

			relocationData.emplace_back(
				std::make_shared<RelocationData>(x->symbol->GetSection()->name,
					SymbolType::section,
					x->section->name,
					x->encodeOffset,
					x->encodeSize,
					relType,
					0)
			);
		}
		else
		{
			// IP RELATIVE

			switch (x->encodeSize)
			{
			case X86::OPERAND_SIZE::DWORD:
			{
				Ceng::INT32* ptr = (Ceng::INT32*)&objSect->codeBuffer[x->encodeOffset];

				if (x->symbol->GetSection() == x->section)
				{
					*ptr = Ceng::INT32(x->symbol->Offset() - (x->encodeOffset + x->ipDelta));
				}
				else
				{
					relocationData.emplace_back(
						std::make_shared<RelocationData>(x->symbol->name,
							x->symbol->Type(),
							x->section->name,
							x->encodeOffset,
							x->encodeSize,
							Casm::RelocationType::rel32_add,
							x->ipDelta)
					);
				}
			}
			break;
			}
		}
	}

	for (auto& x : symbols)
	{
		if (x->Type() == SymbolType::section)
		{
			continue;
		}

		if (x->IsDefined() == true && x->IsGlobal())
		{
			objSymbols.emplace_back(

				std::make_shared<Symbol>(x->name, x->GetSection()->GetObjectSection(),
					x->Type(), x->IsDefined(), x->IsGlobal())
			);
		}
	}

	*output = new ObjectCode(std::move(objSections), std::move(objSymbols),
		std::move(relocationData));

	return Ceng::CE_OK;
}

void ProgramBuilder::Print(std::wostream& out)
{
	for (auto& sect : sections)
	{
		sect->Print(out);
	}
}

/*
const Ceng::CRESULT ProgramBuilder::AddFromString(const Ceng::String &code)
{
	// Configure parser

	Casm::ParserState parserState;

	parserState.program = this;

	Casm::GlobalContext rootContext;

	rootContext.keywords = assembler->rootKeywords;

	parserState.activeContext = &rootContext;
	
	std::vector<Casm::ParserToken*> tokens;

	LexAnalyze(code,&parserState,tokens);


	return Ceng::CE_OK;
}
*/

const char decNumbers[] = "0123456789";
const char hexNumbers[] = "0123456789abcdef";

const char decNumbersWithSign[] = "0123456789+-";
const char hexNumbersWithSign[] = "0123456789abcdef+-";

const char operatorList[] = " +-/*%&|^!~.,=<>:()[]{}\n";

/*
const Ceng::CRESULT ProgramBuilder::LexAnalyze(const Ceng::String &code,Casm::ParserState *state,std::vector<Casm::ParserToken*> &output)
{
	Ceng::String::CONST_ITERATOR_TYPE start,end,opStart,opEnd;

	Ceng::String tokenType;

	start = code.ConstBeginIterator();

	while (start != code.ConstEndIterator())
	{
		// Skip any combination and length of white chars

		start = code.FindFirstNotOf(unicodeWhiteList,start);

		end = code.FindFirstOf(operatorList,start);

		opStart = end;

		opEnd = code.FindFirstNotOf(operatorList,end);

		std::wcout << "token: " << code.SubString(start,end) << std::endl;

		char startChar;

		(*start).ToChar(&startChar);

		if ( startChar >= '0' && startChar <= '9')
		{
			// Literal value

			std::wcout << "\ttype : literal" << std::endl;

			Casm::ParserLiteral *temp = nullptr;

			temp = ParseLiteral(start,end);

			if (temp != nullptr) 
			{
				return Ceng::CE_ERR_FAIL;
			}

			std::wcout << "\t" << "value : " << code.SubString(start,end) << std::endl;

			output.push_back(temp);
	
			//start = end;
		}
		else
		{
			if (state->activeContext == nullptr)
			{
				return Ceng::CE_OK;
			}

			Casm::ParserToken *temp = state->activeContext->FindKeyword(code.SubString(start,end));

			if (temp != nullptr)
			{
				std::wcout << "\t" << "type : " << temp->TypeString() << std::endl;

				output.push_back(temp);
			}
			else
			{
				std::wcout << "\t" << "type : unknown" << std::endl;
			}

			start = end;
		}

		// Check for operator

		if (state->activeContext == nullptr)
		{
			return Ceng::CE_OK;
		}

		Casm::ParserToken *old = nullptr;
		Casm::ParserToken *temp = nullptr;



		end = opStart;
		
		// Find the longest sequence of stop characters that is a valid operator / keyword

		do
		{
			++end;

			temp = state->activeContext->FindKeyword(code.SubString(opStart,end));

			if (temp != nullptr)
			{
				old = temp;	
			}
			else
			{
				--end;
				temp = old;
				break;
			}
		} while(end < opEnd);

		if (end > opEnd) end = opEnd;

		std::wcout << "token:" << code.SubString(opStart,end) << std::endl;

		if (temp != nullptr)
		{
			std::wcout << "\t" << "type : " << temp->TypeString() << std::endl;

			output.push_back(temp);
		}
		else
		{
			std::wcout << "\t" << "type : unknown" << std::endl;
		}

		start = end;
	}

	return Ceng::CE_OK;
}
*/

/*
X86::CodeLine* ProgramBuilder::ParseInstruction(const Ceng::String &input)
{
	Ceng::String line = CleanParserLine(input);

	return ParseOperand(input);
}
*/

/*
X86::CodeLine* ProgramBuilder::ParseOperand(const Ceng::String &operand)
{
	Ceng::String token;

	Ceng::String::CONST_ITERATOR_TYPE start,end,opStart,opEnd;

	Ceng::BOOL isNumber = false;

	start = operand.ConstBeginIterator();

	X86::OPERAND_SIZE::value opSize = X86::OPERAND_SIZE::IMPLICIT;

	std::vector<std::shared_ptr<Casm::TokenGroup>> tokenGroups;

	tokenGroups.push_back(std::shared_ptr<Casm::TokenGroup>(new Casm::TokenGroup('\0',true,Casm::TokenData())));

	Ceng::INT32 currentGroup = 0;

	Ceng::INT32 angleLevel = 0;
	Ceng::INT32 parenthesisLevel = 0;
	Ceng::INT32 bracketLevel = 0;
	Ceng::INT32 curlyBracketLevel = 0;

	std::list<std::shared_ptr<Casm::ParserToken>> *tokens = &tokenGroups[0]->tokens;

	Ceng::ConsoleLog errorLog;

	Casm::ParserState parserState;

	parserState.errorLog = &errorLog;

	while( start != operand.ConstEndIterator())
	{
		start = operand.FindFirstNotOf(unicodeWhiteList,start);

		
		//if (*start == ' ')
		//{
		//	++start;
		//	continue;
		//}
		
		
		end = operand.FindFirstOf(operatorList,start);

		opStart = end;

		opEnd = operand.FindFirstNotOf(operatorList,end);

		Casm::ParserOperator *newOperator = nullptr;
		std::shared_ptr<Casm::TokenGroup> newGroup = nullptr;

		char startChar;

		(*start).ToChar(&startChar);

		if (startChar >= '0' && startChar <= '9')
		{
			std::wcout << "token : literal" << std::endl;

			Casm::ParserLiteral *temp = nullptr;

			temp = ParseLiteral(start,end);

			if (temp == nullptr) 
			{
				return nullptr;
			}

			std::wcout << "\t" << "value : " << operand.SubString(start,end) << std::endl;

			tokens->push_back(std::shared_ptr<Casm::ParserLiteral>(temp));
	
			start = end;
		}
		else
		{
			// Reserved word search

			newOperator = nullptr;
			newGroup = nullptr;

			if (operand.FindFirst("dword",start,end) == start)
			{
				std::wcout << "token : dword : size override" << std::endl;

				newOperator = new Casm::ParserOp_SizeCast(4,Casm::TokenData());
			}
			else if (operand.FindFirst("byte",start,end) == start)
			{
				std::wcout << "token : byte : size override" << std::endl;

				newOperator = new Casm::ParserOp_SizeCast(1,Casm::TokenData());
			}
			else if (operand.FindFirst("qword",start,end) == start)
			{
				std::wcout << "token : qword : size override" << std::endl;

				newOperator = new Casm::ParserOp_SizeCast(8,Casm::TokenData());
			}
			else if (operand.FindFirst("xmmword",start,end) == start)
			{
				std::wcout << "token : xmmword : size override" << std::endl;

				newOperator = new Casm::ParserOp_SizeCast(16,Casm::TokenData());
			}
			else if (operand.FindFirst("word",start,end) == start)
			{
				std::wcout << "token : word : size override" << std::endl;

				newOperator = new Casm::ParserOp_SizeCast(2,Casm::TokenData());
			}
			else if (operand.FindFirst("ymmword",start,end) == start)
			{
				std::wcout << "token : ymmword : size override" << std::endl;

				newOperator = new Casm::ParserOp_SizeCast(32,Casm::TokenData());
			}
			else if (operand.FindFirst("zmmword",start,end) == start)
			{
				std::wcout << "token : zmmword : size override" << std::endl;

				newOperator = new Casm::ParserOp_SizeCast(64,Casm::TokenData());
			}
			else
			{	
				Ceng::String tokenName = operand.SubString(start,end);

				std::wcout << "token string : " << tokenName << std::endl;

				auto registerMap = X86::RegisterMap::GetInstance();

				Casm::ParserToken *reg = nullptr;

				reg = registerMap->FindKeyword(tokenName);

				if (reg != nullptr)
				{
					tokens->push_back(std::shared_ptr<Casm::ParserToken>(reg));
				}
				else
				{
					std::shared_ptr<Symbol> tempSymbol = FindData(operand.SubString(start,end));

					if (tempSymbol != nullptr)
					{
						tokens->push_back(std::shared_ptr<Casm::ParserVariable>(new Casm::ParserVariable(tempSymbol,Casm::TokenData())));
					}
					else
					{
						auto opcodeMap = X86::OpcodeMap::GetInstance();

						Casm::ParserToken *temp = opcodeMap->FindKeyword(operand.SubString(start,end));

						if (temp != nullptr)
						{
							newOperator = static_cast<Casm::ParserOpcode*>(temp);

							newGroup = std::shared_ptr<Casm::TokenGroup>( new Casm::TokenGroup('\0', false, Casm::TokenData()) );

							tokenGroups.push_back(newGroup);						
						}
					}
				}
			}

			if (newOperator != nullptr)
			{
				tokens->push_back( std::shared_ptr<Casm::ParserOperator>(newOperator));

				if (newOperator->Priority() < tokenGroups[currentGroup]->startPriority)
				{
					tokenGroups[currentGroup]->startPriority = newOperator->Priority();
				}

				//errorLog << "operator : " << operand.SubString(start,end) << std::endl;

				std::wcout << "operator : " << operand.SubString(start,end) << std::endl;
			}

			if (newGroup != nullptr)
			{
				tokens->push_back(newGroup);

				++currentGroup;
				
				tokens = &tokenGroups[currentGroup]->tokens;
			}			
		}

		// Stop symbol evaluation

		newOperator = nullptr;
		newGroup = nullptr;
		

		Casm::ParserToken::Type prevType = Casm::ParserToken::op;
			
		if (tokens->size() > 0)
		{
			Casm::ParserToken *prevToken = prevToken = (*(--tokens->end())).get();

			prevType = prevToken->TokenType();
		}
			
		if (*end == '+')
		{
			if (prevType == Casm::ParserToken::op)
			{
				newOperator = new Casm::ParserOp_Unary_Add(Casm::TokenData());
			}
			else
			{
				newOperator = new Casm::ParserOp_Add(Casm::TokenData());
			}
		}
		else if (*end == '-')
		{
			if (prevType == Casm::ParserToken::op)
			{
				newOperator = new Casm::ParserOp_Unary_Sub(Casm::TokenData());
			}
			else
			{
				newOperator = new Casm::ParserOp_Sub(Casm::TokenData());
			}	
		}
		else if (*end == '/')
		{
			newOperator = new Casm::ParserOp_Div(Casm::TokenData());
		}
		else if (*end == '*')
		{
			newOperator = new Casm::ParserOp_Mul(Casm::TokenData());
		}
		else if (*end == ',')
		{
			newOperator = new Casm::ParserComma(Casm::TokenData());
		}
		else if (*end == '[')
		{
			tokenGroups.push_back(std::shared_ptr<Casm::TokenGroup>(new Casm::TokenGroup('[',false,Casm::TokenData())));

			if (prevType == Casm::ParserToken::op)
			{
				// Memory operand

				newOperator = new Casm::ParserOp_Memory(Casm::TokenData());
			}
			else
			{
				// Array index

				//tokens->push_back(new Casm::ParserOp_ArrayIndex(Casm::TokenData());
			}

			newGroup = tokenGroups[tokenGroups.size()-1];

			++bracketLevel;
		}
		else if (*end == ']')
		{
			--currentGroup;
			--bracketLevel;

			if (bracketLevel < 0)
			{
				std::wcout << "syntax error : unmatched ']'" << std::endl;
				return nullptr;
			}
		}
		else if (*end == '(')
		{
			tokenGroups.push_back(std::shared_ptr<Casm::TokenGroup>(new Casm::TokenGroup('(',true,Casm::TokenData())));

			if (prevType == Casm::ParserToken::op)
			{	
				// Priority parenthesis
					
				newOperator = new Casm::ParserOp_Parenthesis(Casm::TokenData());
			}
			else
			{
				// Function call or function-style cast

				//tokens->push_back(new Casm::ParserOp_Call(Casm::TokenData()));
			}

			newGroup = tokenGroups[tokenGroups.size()-1];

			++parenthesisLevel;
		}
		else if (*end == ')')
		{
			--currentGroup;
			--parenthesisLevel;

			if (parenthesisLevel < 0)
			{
				std::wcout << "syntax error : unmatched ')'" << std::endl;
				return nullptr;
			}
		}
		else if (*end == '<')
		{
			if (tokens->size() > 0)
			{
				tokenGroups.push_back(std::shared_ptr<Casm::TokenGroup>(new Casm::TokenGroup('<',false,Casm::TokenData())));

				tokens->push_back(tokenGroups[tokenGroups.size()-1]);

				++currentGroup;
				++angleLevel;
			}
			else
			{
				//temp = new ParserOp_LessThan();
			}
		}
		else if (*end == '>')
		{
			if (angleLevel > 0)
			{
				--currentGroup;
				--angleLevel;
			}
			else
			{
				//temp = new ParserOp_GreaterThan();
			}
		}
		
			
		if (newOperator != nullptr)
		{
			tokens->push_back(std::shared_ptr<Casm::ParserOperator>(newOperator));

			if (newOperator->Priority() < tokenGroups[currentGroup]->startPriority)
			{
				tokenGroups[currentGroup]->startPriority = newOperator->Priority();
			}

			errorLog << "operator : " << *end << std::endl;
		}

		if (newGroup != nullptr)
		{
			tokens->push_back(newGroup);

			++currentGroup;
		}			

		tokens = &tokenGroups[currentGroup]->tokens;

		start = end+1;

		std::wcout << std::endl;
	}

	if (parenthesisLevel > 0)
	{
		std::wcout << "syntax error : unmatched '('" << std::endl;
		return nullptr;
	}

	if (bracketLevel > 0)
	{
		std::wcout << "syntax error : unmatched '['" << std::endl;
		return nullptr;
	}

	Ceng::INT32 k;

	for(k=tokenGroups.size()-1;k>=0;k--)
	{
		tokenGroups[k]->ProcessGroup(&parserState);
	}

	tokens = &tokenGroups[0]->tokens;

	X86::CodeLine *output = nullptr;

	Casm::ParserToken *temp = (*tokens->begin()).get();

	if (temp->TokenType() != Casm::ParserToken::instruction)
	{
		return nullptr;
	}

	Casm::ParserInstruction *instr = (Casm::ParserInstruction*)temp;

	return instr->GetCodeLine();
}
*/

/*
void ProgramBuilder::WalkWhileInteger(Ceng::String::CONST_ITERATOR_TYPE &iter,const Ceng::INT32 numBase)
{
	char maxNum = '9';

	if (numBase == 2)
	{
		maxNum = '1';
	}

	if (numBase == 8)
	{
		maxNum = '7';
	}

	while(*iter != '\0')
	{
		char tempChar;

		(*iter).ToChar(&tempChar);

		if (tempChar >= '0' && tempChar <= maxNum)
		{
		}
		else if (numBase == 16)
		{
			if (tempChar >= 'a' && tempChar <= 'f')
			{
			}
			else
			{
				break;
			}
		}
		else if (*iter == '_')
		{
		}
		else
		{
			break;
		}

		++iter;
	}
}
*/

/*
Casm::ParserLiteral* ProgramBuilder::ParseLiteral(Ceng::String::CONST_ITERATOR_TYPE start,
														Ceng::String::CONST_ITERATOR_TYPE &end)
{
	Ceng::String intPart;

	Ceng::BOOL isFloat = false;

	Ceng::String::CONST_ITERATOR_TYPE localStart,localEnd;

	Ceng::String::CONST_ITERATOR_TYPE intStart,intEnd;
	Ceng::String::CONST_ITERATOR_TYPE fracStart,fracEnd;
	Ceng::String::CONST_ITERATOR_TYPE expStart,expEnd;

	localStart = start;

	Ceng::INT32 numBase = 10;

	if (*localStart == '\0')
	{
		return nullptr;
	}

	while(*localStart != '\0')
	{
		if (*localStart == '0' && localStart[1] == '\0')
		{
			++localStart;
		}
		else
		{
			break;
		}
	}

	char char1;

	localStart[1].ToChar(&char1);

	// Determine numeric base from "0x" style header
	if (*localStart == '0')
	{
		if (localStart[1] != '\0')
		{
			if (localStart[1] == 'b' || localStart[1] == 'y')
			{
				// Binary "0b" or "0y"

				numBase = 2;
				
				localStart += 2;
			}
			else if (localStart[1] == 'x' || localStart[1] == 'h')
			{
				// Hex "0x" or "0h"

				numBase = 16;
				
				localStart += 2;
			}
			else if (localStart[1] == 'o' || localStart[1] == 'q')
			{
				// Octal "0o" or "0q"

				numBase = 8;
				
				localStart += 2;
			}
			else if (localStart[1] == 'd' || localStart[1] == 't')
			{
				// Base 10 (default) "0d" or "0t"

				localStart += 2;
			}
			else if ( ! (char1 >= '0' && char1 <= '9')
						&& localStart[1] != '.' && localStart[1] != 'e')
			{
				std::wcout << "\t" << "syntax error : unknown base : " << localStart[1] << std::endl;

				return nullptr;
			}
		}
	}

	char expSymbol = 'e';

	Ceng::INT32 expBase = 10;

	if (numBase == 2)
	{
		expBase = 2;
	}

	if (numBase == 16)
	{
		expSymbol = 'p';
		expBase = 2;
	}

	localEnd = localStart;

	WalkWhileInteger(localEnd,numBase);

	intStart = localStart;
	intEnd = localEnd;

	Ceng::String::CONST_ITERATOR_TYPE tempIter;

	tempIter = localStart;

	while(tempIter != localEnd)
	{
		char tempChar;
		(*tempIter).ToChar(&tempChar);

		intPart += tempChar;
		++tempIter;
	}

	std::wcout << "\t" << "integer part : " << intPart << std::endl;

	localStart = localEnd;

	Ceng::String fracPart;

	if (*localStart == '.')
	{
		isFloat = true;

		++localStart;
		localEnd = localStart;

		WalkWhileInteger(localEnd,numBase);

		fracStart = localStart;
		fracEnd = localEnd;

		tempIter = localStart;

		while(tempIter != localEnd)
		{
			char tempChar;
			(*tempIter).ToChar(&tempChar);

			fracPart += tempChar;
			++tempIter;
		}

		std::wcout << "\t" << "fractional part : " << fracPart << std::endl;

		localStart = localEnd;
	}

	Ceng::String expPart;
	Ceng::BOOL negativeExp = false;

	if (isFloat)
	{
		expStart = localStart;
		expEnd = localStart;

		if (*localStart == expSymbol)
		{
			++localStart;

			char tempChar;

			(*localStart).ToChar(&tempChar);

			if (*localStart == '+')
			{
				++localStart;
			}
			else if (*localStart == '-')
			{
				++localStart;
				negativeExp = true;
			}
			else if ( !(tempChar >= '0' && tempChar <= '9') )
			{
				std::wcout << "\t" << "syntax error : " << *localStart << std::endl;
				return nullptr;
			}

			localEnd = localStart;

			WalkWhileInteger(localEnd,expBase);

			expStart = localStart;
			expEnd = localEnd;

			tempIter = localStart;

			while(tempIter != localEnd)
			{
				char tempChar;
				(*tempIter).ToChar(&tempChar);

				expPart += tempChar;
				++tempIter;
			}

			localStart = localEnd;
		}

		std::wcout << "\t" << " * " << expBase << " ^ ";

		if (negativeExp == true)
		{
			std::wcout << "-";
		}

		if (expPart.Length() == 0)
		{
			std::wcout << "0" << std::endl;
		}
		else
		{
			std::wcout << expPart << std::endl;
		}
	}
	else
	{
		if (*localStart == '.')
		{
			std::wcout << "\t" << "syntax error : " << *localStart << std::endl;
			return nullptr;
		}
		else if (*localStart == 'b')
		{
			numBase = 2;
			++localStart;
		}
		else if (*localStart == 'h')
		{
			numBase = 16;
			++localStart;
		}
		else if (*localStart == 'o')
		{
			numBase = 8;
			++localStart;
		}
	}

	std::wcout << "\t" << "numeric base : " << numBase << std::endl;

	end = localStart;

	if (isFloat)
	{
		Ceng::FLOAT64 intVal = StringIntToDouble(intStart,intEnd,numBase);
		
		//std::wcout << "\t" << "integer part : " << intVal << std::endl;

		Ceng::FLOAT64 fracVal = 0.0;
		
		if (fracStart < fracEnd)
		{
			fracVal = StringIntToDouble(fracStart,fracEnd,numBase);
		}

		fracVal /= pow(numBase,fracPart.Length());

		//std::wcout << "\t" << "fractional part : " << fracVal << std::endl;

		Ceng::INT32 expVal = 0;
		
		if (expStart < expEnd)
		{
			expVal = StringToUint(expStart,expEnd,expBase);
		}

		if (negativeExp)
		{
			expVal *= -1;
		}

		//std::wcout << "\t" << "10^n : " << expVal << std::endl;

		Ceng::FLOAT64 finalFloat;
		
		finalFloat = (intVal + fracVal) * pow(expBase,expVal);

		//std::wcout << "\t" << "value : " << finalFloat << std::endl;

		return new Casm::FloatLiteral(finalFloat,Casm::TokenData());
	}
	else
	{
		Ceng::INT64 unsignedInt = StringToUint(intStart,intEnd,numBase);

		//std::wcout << "\t" << "value : " << unsignedInt << std::endl;

		return new Casm::Literal_Uint64(unsignedInt,Casm::TokenData());
	}
	
	return nullptr;
}
*/

/*
const Ceng::FLOAT64 ProgramBuilder::StringIntToDouble(const Ceng::String::CONST_ITERATOR_TYPE start,
													  const Ceng::String::CONST_ITERATOR_TYPE end,
													  const Ceng::INT32 base)
{
	Ceng::String::CONST_ITERATOR_TYPE tempIter = start;

	Ceng::FLOAT64 output = 0.0;

	while(tempIter != end)
	{
		char tempChar;

		(*tempIter).ToChar(&tempChar);

		if (*tempIter == '_')
		{
		}
		else if (tempChar >= '0' && tempChar <= '9')
		{
			output *= base;

			output += Ceng::FLOAT64(tempChar - '0');
		}
		else if (tempChar >= 'a' && tempChar <= 'f')
		{
			output *= base;
			output += Ceng::FLOAT64(tempChar - 'a' + 10);
		}
		else
		{
			return output;
		}

		++tempIter;
	}

	return output;
}
*/

/*
const Ceng::UINT64 ProgramBuilder::StringToUint(const Ceng::String::CONST_ITERATOR_TYPE start,
											  const Ceng::String::CONST_ITERATOR_TYPE end,
											  const Ceng::INT32 base)
{
	Ceng::BOOL negative = false;

	Ceng::String::CONST_ITERATOR_TYPE iter = start;

	Ceng::UINT64 output = 0;

	while(iter != end)
	{
		char tempChar;
		(*iter).ToChar(&tempChar);

		if (*iter == '_')
		{
		}
		else if (tempChar >= '0' && tempChar <= '9')
		{
			output *= base;

			output += Ceng::INT64(tempChar - '0');
		}
		else if (tempChar >= 'a' && tempChar <= 'f')
		{
			output *= base;
			output += Ceng::INT64(tempChar - 'a' + 10);
		}
		else
		{
			return output;
		}

		++iter;
	}

	return output;
}
*/

/*
const Ceng::String ProgramBuilder::CleanParserLine(const Ceng::String &line)
{
	Ceng::String::CONST_ITERATOR_TYPE start,end;
	
	start = line.FindFirstNotOf(unicodeWhiteList,line.ConstBeginIterator());
	
	// Remove trailing comment

	end = line.FindFirst(';',line.ConstBeginIterator());
	
	Ceng::String output = line.SubString(start,end);
	
	output = Ceng::StringManipulator::RightStrip(output,unicodeWhiteList);
	
	// Replace all whitechars with spaces
	output = Ceng::StringManipulator::ReplaceWith(output,unicodeWhiteList,' ');
	
	// Truncate sequences of white chars to single white char
	
	output = Ceng::StringManipulator::StripRepeatsOf(output," ");

	return output;
}
*/


/*
Ceng::CRESULT ProgramBuilder::LinkProgram(const Ceng::String &entryFunction,
										  ObjectCode *objectCode,
										  Executable **output)
{
	// Find entry point function

	std::shared_ptr<ObjectFunction> entryPoint = nullptr;

	Ceng::UINT32 k;

	for(k=0;k<objectCode->functions->size();k++)
	{
		std::vector<std::shared_ptr<ObjectFunction>> *temp = objectCode->functions;

		if ( (*temp)[k]->name == entryFunction)
		{
			entryPoint = (*temp)[k];
		}
	}

	entryPoint->IncRefCount();

	std::vector<std::shared_ptr<SymbolRef>> *linkDisplacements;
	std::vector<std::shared_ptr<Symbol>> *linkData;
		
	std::vector<std::shared_ptr<Symbol>> *linkFunctions;

	linkData = new std::vector<std::shared_ptr<Symbol>>();
	linkFunctions = new std::vector<std::shared_ptr<Symbol>>();
	linkDisplacements = new std::vector<std::shared_ptr<SymbolRef>>();

	// Gather symbols that will be present in the final executable

	linkFunctions->push_back(entryPoint);

	k = 0;
	do
	{
		// NOTE: ReferenceAll adds all functions called to linkFunctions
		//       if they are currently unreferenced

		ObjectFunction *objFunc = (*linkFunctions)[k]->AsObjectFunction();

		objFunc->ReferenceAll(linkData,linkFunctions);

		k++;
	} while (k < linkFunctions->size());

	// Allocate variables to data segment

	Ceng::UINT32 dataSegmentSize = 0;

	for(k=0;k<linkData->size();k++)
	{
		(*linkData)[k]->SetOffset(dataSegmentSize);
		
		DataItem *item = (*linkData)[k]->AsData();

		dataSegmentSize += item->elementSize;
	}

	// Build code section

	Ceng::UINT32 codeSegSize = 0;
	
	for(k=0;k<linkFunctions->size();k++)
	{
		// TODO: Pad function offset to start at cache line if necessary

		(*linkFunctions)[k]->SetOffset(codeSegSize);

		ObjectFunction *objFunc = (*linkFunctions)[k]->AsObjectFunction();

		codeSegSize += objFunc->SizeBytes();
	}

	Ceng::AlignedMemory<Ceng::UINT8> dataSegment; 
	
	dataSegment = Ceng::AlignedMemory<Ceng::UINT8>::Allocate(dataSegmentSize,assembler->CacheLine());

	// Write initial values of data items

	for(k=0;k< linkData->size();k++)
	{
		DataItem *item = (*linkData)[k]->AsData(); 

		item->initializer->WriteValues(&dataSegment[(UINT32)(*linkData)[k]->Offset()]);
	}

	// Build linked program

	Program *program = new Program();

	Ceng::AlignedMemory<Ceng::UINT8> codeBuffer;

	codeBuffer = Ceng::AlignedMemory<Ceng::UINT8>::Allocate(codeSegSize,assembler->CacheLine());

	program->entryPoint = 0;
	program->codeBuffer = codeBuffer;
	program->dataSection = dataSegment;

	for(k=0;k<linkFunctions->size();k++)
	{
		ObjectFunction *objFunc = (*linkFunctions)[k]->AsObjectFunction();

		objFunc->WriteAllOffsets();
		objFunc->ToCodeBuffer(&codeBuffer[0]);
		objFunc->AppendRelocationData(program->relocationData);
	}

	program->GetExecutable(output);

	delete linkData;
	delete linkDisplacements;
	delete linkFunctions;

	delete objectCode;
	delete program;

	return Ceng::CE_OK;
}
*/