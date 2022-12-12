/*****************************************************************************
*
* condition-jump.h
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#ifndef X86_CONDITION_JUMP_H
#define X86_CONDITION_JUMP_H

#include "x86-enums.h"
#include "x86-instruction.h"

#include "code-element.h"

#include "code-label.h"

#include "enums/condition-codes.h"

namespace X86
{
	class ConditionJump : public CodeElement
	{
	public:
		Casm::CONDITION::value condition;
		const Label *label;

		const X86::Instruction *jumpCommand;

		X86::OPERAND_SIZE::value jumpSize;

		/**
		 * List of jumps that cross this jump forward.
		 */
		std::vector<ConditionJump*> forwardJumps;

		/**
		 * List of jumps that cross this jump backwards.
		 */
		std::vector<ConditionJump*> backwardJumps;

		std::vector<Ceng::UINT8> codeBuffer;

		ConditionJump()
		{
		}
	public:
		ConditionJump(const Ceng::UINT32 position, const Casm::CONDITION::value condition,
						const Label *label);

		virtual Ceng::CRESULT Build(BuildParams *params,
									 const std::vector<std::shared_ptr<Label>> &labels,
									 const std::vector<std::shared_ptr<CodeElement>> &codeList);

		virtual Ceng::CRESULT Append(std::vector<Ceng::UINT8> &destBuffer) const;

		Ceng::CRESULT AdjustOffset(BuildParams *params,const Ceng::INT32 offset);

		virtual Ceng::UINT32 SizeBytes() const;
	};
}

#endif