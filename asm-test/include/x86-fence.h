/*****************************************************************************
*
* x86-fence.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_FENCE_H
#define X86_FENCE_H

#include "x86-instruction.h"

namespace X86
{
	class MemoryOperand;

	class FenceOp : public Instruction
	{
	protected:
		const Ceng::UINT8 opcode;

		const Ceng::UINT8 option;

		const Ceng::UINT32 paramLists;

	public:
		FenceOp(const Ceng::UINT8 opcode,const Ceng::UINT8 option,
					const Ceng::UINT32 paramLists);

		virtual ~FenceOp();

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,EncodeData *encodeData) const override;

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *operand) const override;
	
	protected:

		const Ceng::CRESULT Select_M(BuildParams *params,EncodeData *encodeData,
											const MemoryOperand *operand) const;
	};
}

#endif