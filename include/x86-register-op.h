/*****************************************************************************
*
* x86-register-op.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_REGISTER_OP_H
#define X86_REGISTER_OP_H

#include "x86-operand.h"

namespace X86
{
	class RegisterOperand : public Operand
	{
	public:
		Ceng::UINT32 cpuModes;

		Ceng::UINT32 registerFiles;
		Ceng::INT32 index;

	public:

		RegisterOperand();

		virtual ~RegisterOperand();

		RegisterOperand(const Ceng::UINT32 cpuModes,const Ceng::BOOL usesREX, const Ceng::UINT32 registerFiles,
							 const OPERAND_SIZE::value size,const Ceng::INT32 index);

		virtual const Ceng::CRESULT EncodeAsOperand(BuildParams *params,EncodeData *encodeData,
												const Ceng::UINT32 operandIndex) const override;

		const Ceng::UINT32 RegisterFiles() const;
	};
}

#endif