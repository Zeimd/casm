/*****************************************************************************
*
* x86-immediate-op.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_IMMEDIATE_OP_H
#define X86_IMMEDIATE_OP_H

#include "x86-operand.h"

#include <memory>

namespace Casm
{
	class Symbol;
}

namespace X86
{
	class ImmediateOperand : public Operand
	{
	protected:

		std::shared_ptr<Casm::Symbol> symbol;

		Ceng::UINT32 bytes;
		Ceng::INT64 value;

	public:

		~ImmediateOperand() override;

		ImmediateOperand(std::shared_ptr<Casm::Symbol> &symbol, 
			const X86::OPERAND_SIZE::value addressSize);

		ImmediateOperand(const Ceng::INT64 value);

		ImmediateOperand(const OPERAND_SIZE::value size,const Ceng::INT64 value);

		const Ceng::INT32 SizeBytes() const;
		
		const Ceng::INT8 Value8() const;

		const Ceng::INT16 Value16() const;

		const Ceng::INT32 Value32() const;

		const Ceng::INT64 Value64() const;

		const std::shared_ptr<Casm::Symbol> GetSymbol() const;

		const Ceng::CRESULT EncodeAsOperand(BuildParams *params,EncodeData *encodeData,
			const Ceng::UINT32 operandIndex) const override;

		Ceng::String ToString() const override;
	};
}

#endif