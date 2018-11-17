/*****************************************************************************
*
* x86-xsave.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_XSAVE_H
#define X86_XSAVE_H

#include "x86-instruction.h"

#include <datatypes/boolean.h>

namespace X86
{
	class MemoryOperand;

	class SaveExtState : public Instruction
	{
	protected:

		static const Ceng::UINT8 opcode = 0xae;

		const Ceng::UINT8 option;
		const Ceng::BOOL x64; 

	public:

		SaveExtState(const Ceng::UINT8 option,const Ceng::BOOL x64);

		virtual ~SaveExtState();

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *operand) const override;

	protected:

		const Ceng::CRESULT Select_M(BuildParams *params,EncodeData *encodeData,
											const MemoryOperand *operand) const;
	};
}


#endif