/*****************************************************************************
*
* x86-cbw-variant.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_CBW_VARIANT_H
#define X86_CBW_VARIANT_H

#include "x86-two-form-alu.h"

#include "enums/x86-operand-sizes.h"

namespace X86
{
	class CBW_Variant : public TwoForm_ALU
	{
	protected:
		const Ceng::UINT8 opcode;

		const OPERAND_SIZE::value opSize;

	public:

		CBW_Variant(const Ceng::UINT8 opcode,const OPERAND_SIZE::value opSize);

		virtual ~CBW_Variant();

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,EncodeData *encodeData) const;
	};
}

#endif