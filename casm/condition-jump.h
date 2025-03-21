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

#include "enums/x86-operand-sizes.h"

namespace Casm
{
	class ConditionJump : public Casm::CodeElement
	{
	public:
		Casm::CONDITION::value condition;
		const CodeLabel *label;

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
						const CodeLabel *label);

		virtual Ceng::CRESULT Build(X86::BuildParams *params,
									 const std::vector<std::shared_ptr<CodeLabel>> &labels,
									 const std::vector<std::shared_ptr<CodeElement>> &codeList);

		virtual Ceng::CRESULT Append(std::vector<Ceng::UINT8> &destBuffer) const;

		Ceng::CRESULT AdjustOffset(X86::BuildParams *params,const Ceng::INT32 offset);

		virtual Ceng::UINT32 SizeBytes() const;
	};
}

#endif