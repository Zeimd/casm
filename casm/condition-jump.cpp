/*****************************************************************************
*
* cond-jump.cpp
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#include "../include/condition-jump.h"

#include "../include/x86-opcodes-alu.h"

#include "../include/x86-immediate-op.h"


using namespace X86;

ConditionJump::ConditionJump(const Ceng::UINT32 position, const Casm::CONDITION::value condition,
							 const Label *label) 
							 : CodeElement(position),condition(condition),label(label)
{
	jumpSize = X86::OPERAND_SIZE::BYTE;
	type = CONDITION_JUMP;
	jumpCommand = nullptr;
}	

Ceng::CRESULT ConditionJump::AdjustOffset(BuildParams *params,const Ceng::INT32 offset)
{
	if (jumpSize == X86::OPERAND_SIZE::BYTE)
	{
		Ceng::INT8 *byte = (Ceng::INT8*)&codeBuffer[1];

		if ( Ceng::INT32(*byte)+offset >= -128 && Ceng::INT32(*byte)+offset < 127)
		{
			*byte += offset;
		}
		else
		{
			// Expand to 32-bit offset

			Ceng::INT32 newOffset = Ceng::INT32(*byte) + offset;

			jumpSize = X86::OPERAND_SIZE::DWORD;

			codeBuffer.clear();

			Ceng::CRESULT cresult;

			cresult = jumpCommand->EncodeOneForm(params,codeBuffer,&X86::ImmediateOperand(jumpSize,newOffset));
			if (cresult != Ceng::CE_OK)
			{
				return cresult;
			}

			// Signal all affected backward jumps about the offset change
			Ceng::UINT32 k;

			
			for(k=0;k<backwardJumps.size();k++)
			{
				// All jumps that skip this jump backwards
				//
				// EXAMPLE:
				// label a
				// jump b : forward_skips(a)
				// jump a : backward_skips(a)
				// label b
				backwardJumps[k]->AdjustOffset(params,-4);
			}

			for(k=0;k<forwardJumps.size();k++)
			{
				// Jump that crosses this jump forward
				forwardJumps[k]->AdjustOffset(params,4);
			}	
		}
	}
	else
	{
		Ceng::INT32 *dword = (Ceng::INT32*)&codeBuffer[2];

		*dword += offset;
	}

	return Ceng::CE_OK;
}

Ceng::UINT32 ConditionJump::SizeBytes() const
{
	if (codeBuffer.size() == 0)
	{
		return 2; // Assume short jump
	}
	return codeBuffer.size();
}

Ceng::CRESULT ConditionJump::Build(BuildParams *params,
								   const std::vector<std::shared_ptr<Label>> &labels,
								   const std::vector<std::shared_ptr<CodeElement>> &codeList)
{
	Ceng::UINT32 k;

	if (label->Undefined())
	{
		return Ceng::CE_ERR_FAIL;
	}

	CodeElement *target = label->Target();

	// Calculate jump offset

	Ceng::INT32 skipCount = 0;
	Ceng::INT32 offset = 0;

	Ceng::INT32 encodeSize;

	if (target->Position() > position)
	{
		// Label comes after jump command

		// NOTE: Skip the jump item at codeList[position] because
		//       its size is undefined at this time

		for(k = position+1; k < target->Position();k++)
		{
			// NOTE: All conditional jumps count as 2 bytes until their
			//       exact size is known (2 or 6)
			offset += codeList[k]->SizeBytes();

			if (codeList[k]->Type() == CONDITION_JUMP)
			{
				ConditionJump *jump = (ConditionJump*)(codeList[k].get());

				jump->forwardJumps.push_back(this);
			}
		}
	}
	else if (position > target->Position())
	{
		// Label comes before jump command

		for(k = target->Position(); k < position;k++)
		{
			offset -= codeList[k]->SizeBytes();

			if (codeList[k]->Type() == CONDITION_JUMP)
			{
				ConditionJump *jump = (ConditionJump*)(codeList[k].get());

				jump->backwardJumps.push_back(this);
			}
		}

		// NOTE: Offset is from the start address of next instruction,
		//       so jump instruction encoding affects offset

		if (offset-2 >= -128)
		{
			// Offset fits within short jump
			offset -= 2;
		}
		else
		{
			// Must use near jump
			offset -= 6;
		}
	}

	if ( offset >= -128 && offset < 127)
	{
		encodeSize = 2;
		jumpSize = X86::OPERAND_SIZE::BYTE;
	}
	else
	{
		encodeSize = 6;
		jumpSize = X86::OPERAND_SIZE::DWORD;
	}
	
	switch(condition)
	{
	case Casm::CONDITION::ABOVE:
		jumpCommand = &X86::JA;
		break;
	case Casm::CONDITION::ABOVE_EQUAL:
		jumpCommand = &X86::JAE;
		break;
	case Casm::CONDITION::BELOW:
		jumpCommand = &X86::JB;
		break;
	case Casm::CONDITION::BELOW_EQUAL:
		jumpCommand = &X86::JBE;
		break;
	case Casm::CONDITION::EQUAL:
		jumpCommand = &X86::JE;
		break;
	case Casm::CONDITION::NOT_EQUAL:
		jumpCommand = &X86::JNE;
		break;
	case Casm::CONDITION::GREATER:
		jumpCommand = &X86::JG;
		break;
	case Casm::CONDITION::GREATER_EQUAL:
		jumpCommand = &X86::JGE;
		break;
	case Casm::CONDITION::LESS:
		jumpCommand = &X86::JL;
		break;
	case Casm::CONDITION::LESS_EQUAL:
		jumpCommand = &X86::JLE;
		break;

	case Casm::CONDITION::OVERFLOW_FLAG:
		jumpCommand = &X86::JO;
		break;
	case Casm::CONDITION::NOT_OVERFLOW_FLAG:
		jumpCommand = &X86::JNO;
		break;

	case Casm::CONDITION::SIGN:
		jumpCommand = &X86::JS;
		break;
	case Casm::CONDITION::NOT_SIGN:
		jumpCommand = &X86::JNS;
		break;

	case Casm::CONDITION::PARITY:
		jumpCommand = &X86::JP;
		break;
	case Casm::CONDITION::NOT_PARITY:
		jumpCommand = &X86::JNP;
		break;

	case Casm::CONDITION::CX_ZERO:
		jumpCommand = &X86::JCXZ;
		break;
	default:
		return Ceng::CE_ERR_INVALID_PARAM;
	}
	
	Ceng::CRESULT cresult;

	cresult = jumpCommand->EncodeOneForm(params,codeBuffer,&X86::ImmediateOperand(jumpSize,offset));
	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	// Adjust offsets of crossing jumps if necessary

	if (encodeSize > 2)
	{
		for(k=0;k<forwardJumps.size();k++)
		{
			forwardJumps[k]->AdjustOffset(params,encodeSize-2);
		}
	}

	return Ceng::CE_OK;
}

Ceng::CRESULT ConditionJump::Append(std::vector<Ceng::UINT8> &destBuffer) const
{
	std::copy(codeBuffer.begin(),codeBuffer.end(),std::back_inserter(destBuffer));

	return Ceng::CE_OK;
}