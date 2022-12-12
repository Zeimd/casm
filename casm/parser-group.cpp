/*****************************************************************************
*
* token-group.cpp
*
* By Jari Korkala 5/2014
*
*****************************************************************************/

#include "../include/parser-group.h"
#include "../include/parser-operator.h"
#include "../include/parser-operand.h"

using namespace Casm;

const Ceng::CRESULT TokenGroup::ProcessGroup(ParserState *state)
{
	std::list<std::shared_ptr<Casm::ParserToken>>::iterator iter,next,previous;

	Ceng::INT32 priority = startPriority;

	Ceng::BOOL continueLoop = true;

	if (tokens.size() == 0)
	{
		return Ceng::CE_OK;
	}

	while(continueLoop)
	{
		startPriority = 10000;
		continueLoop = false;

		iter = tokens.begin();

		while(iter != tokens.end())
		{
			if ( (*iter)->TokenType() == Casm::ParserToken::op)
			{
				if (iter != tokens.begin())
				{
					previous = iter;
					--previous;
				}

				next = iter;
				++next;

				/*
				if (next == tokens.end())
				{
					std::wcout << "syntax error" << std::endl;
					break;
				}
				*/

				std::shared_ptr<ParserOperator> op = std::static_pointer_cast<ParserOperator>(*iter);

				if (op->Priority() <= priority)
				{
					std::shared_ptr<ParserOperand> leftSide = nullptr;
					std::shared_ptr<ParserOperand> rightSide = nullptr;

					if (iter != tokens.begin())
					{
						leftSide = std::static_pointer_cast<ParserOperand>(*previous);
					}

					if (next != tokens.end())
					{
						rightSide = std::static_pointer_cast<ParserOperand>(*next);
					}

					std::shared_ptr<ParserOperand> temp = nullptr;

					temp = op->Action(state,leftSide,rightSide);

					if (temp == nullptr)
					{
						std::wcout << "operator : unavailable" << std::endl;
						//break;
					}
					else
					{	
						if (op->Affects() == 3)
						{
							// For binary operators
							iter = tokens.erase(previous,next);
						}
						else
						{
							// Unary operators
							iter = tokens.erase(iter,next);
						}

						*iter = temp;	
					}
				}
				else
				{
					if (op->Priority() > priority)
					{
						continueLoop = true;

						if (op->Priority() < startPriority)
						{
							startPriority = op->Priority();
						}
					}
				}
			}

			++iter;
		}

		priority = startPriority;
	}

	std::shared_ptr<ParserToken> temp = *tokens.begin();

	if (tokens.size() == 1)
	{
		/*
		if (temp->TokenType() == ParserToken::group)
		{
			TokenGroup *tempGroup = (Casm::TokenGroup*)(Casm::ParserToken*)temp;
			temp = tempGroup->resolved;
		}
		*/
		
		resolved = *tokens.begin();
	}
	else
	{
		resolved = nullptr;
	}

	return Ceng::CE_OK;
}