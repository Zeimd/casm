/*****************************************************************************
*
* x86-operand.h
*
* By Jari Korkala 1/2014
*
******************************************************************************/

#ifndef X86_OPERAND_H
#define X86_OPERAND_H

#include <datatypes/basic-types.h>
#include <datatypes/boolean.h>
#include <datatypes/return-val.h>

#include "enums/x86-operand-types.h"
#include "enums/x86-operand-sizes.h"

namespace X86
{
	class BuildParams;
	class EncodeData;

	class Operand
	{
	protected:
		OPERAND_TYPE::value type;
		Ceng::BOOL usesREX;
		OPERAND_SIZE::value size;

	public:

		Operand();

		Operand(const OPERAND_TYPE::value type,const Ceng::BOOL usesREX,
					const OPERAND_SIZE::value size);

		virtual ~Operand();

		const OPERAND_SIZE::value Size() const;
		const Ceng::BOOL UsesREX() const;

		const Ceng::BOOL IsRegisterOperand() const;
		const Ceng::BOOL IsMemoryOperand() const;
		const Ceng::BOOL IsImmediateOperand() const;
		const Ceng::BOOL IsMemoryRegisterOperand() const;

		virtual const Ceng::CRESULT EncodeAsOperand(BuildParams *params,EncodeData *encodeData,
														const Ceng::UINT32 operandIndex) const;
	};
}

#endif