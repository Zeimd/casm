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

#include <ceng/datatypes/boolean.h>

namespace X86
{
	class MemoryOperand;

	class SaveExtState : public Instruction
	{
	protected:

		static const Ceng::UINT8 opcode = 0xae;

		const Ceng::UINT8 option;
		const Ceng::BOOL x64; 

		const char* name;

	public:

		SaveExtState(const char* name, const Ceng::UINT8 option,const Ceng::BOOL x64);

		virtual ~SaveExtState();

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *operand) const override;

		const char* Name() const override
		{
			return name;
		}

	protected:

		const Ceng::CRESULT Select_M(BuildParams *params,EncodeData *encodeData,
											const MemoryOperand *operand) const;
	};
}


#endif