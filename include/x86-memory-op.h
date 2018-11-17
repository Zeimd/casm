/*****************************************************************************
*
* x86-memory-operand.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_MEMORY_OPERAND_H
#define X86_MEMORY_OPERAND_H

#include <memory>

#include "x86-operand.h"
#include "x86-register-op.h"

#include "symbol.h"


namespace X86
{
	class MemoryOperand : public Operand
	{
	public:
		std::shared_ptr<Symbol> symbol;

		Ceng::UINT32 cpuModes;

		Ceng::INT32 baseReg;
		
		Ceng::INT32 indexReg;
		Ceng::UINT32 indexScale;

		Ceng::INT32 displacement;

	private:

		MemoryOperand();

	public:
		MemoryOperand(const Ceng::INT32 displacement);

		MemoryOperand(std::shared_ptr<Symbol> symbol);

		MemoryOperand(const RegisterOperand &base);
		MemoryOperand(const OPERAND_SIZE::value operandSize,const RegisterOperand &base);

		MemoryOperand(const RegisterOperand &base,const Ceng::INT32 displacement);
		MemoryOperand(const OPERAND_SIZE::value operandSize,
									 const RegisterOperand &base,const Ceng::INT32 displacement);

		MemoryOperand(const RegisterOperand &base,const RegisterOperand &indexReg,
									 const Ceng::INT32 indexScale);

		MemoryOperand(const OPERAND_SIZE::value operandSize,
									 const RegisterOperand &base,const RegisterOperand &indexReg,
									 const Ceng::INT32 indexScale);

		MemoryOperand(const OPERAND_SIZE::value operandSize,
									 const RegisterOperand *base,const RegisterOperand *indexReg,
									 const Ceng::INT32 indexScale,const Ceng::INT32 displacement);

									

		virtual const Ceng::CRESULT EncodeAsOperand(BuildParams *params,EncodeData *encodeData,
												const Ceng::UINT32 operandIndex) const override;

	protected:

		void SetCPUmode();
	};
}

#endif