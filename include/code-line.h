/*****************************************************************************
*
* code-line.h
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#ifndef X86_CODE_LINE_H
#define X86_CODE_LINE_H

#include <datatypes/basic-types.h>

#include "build-params.h"

#include "x86-instruction.h"

#include "x86-operand.h"

#include <vector>

namespace X86
{
	class CodeLine
	{
	protected:
		
	public:
		CodeLine()
		{
		}

		virtual ~CodeLine()
		{
		}

		virtual Ceng::CRESULT Encode(BuildParams *params,
										std::vector<Ceng::UINT8> &destBuffer)
		{
			return Ceng::CE_OK;
		};
	};

	class BareOp : public CodeLine
	{
	protected:
		const Instruction *instruction;
	public:
		BareOp()
		{
		}

		BareOp(const Instruction &instruction) :
			instruction(&instruction)
		{
		}

		virtual ~BareOp()
		{
		}

		virtual Ceng::CRESULT Encode(BuildParams *params,
										std::vector<Ceng::UINT8> &destBuffer)
		{
			return instruction->EncodeBare(params,destBuffer);
		};
	};

	class UnaryOp : public BareOp
	{
	protected:
		const Operand *operand;
	public:
		UnaryOp()
		{
		}

		UnaryOp(const Instruction &instruction,const Operand *operand) :
			BareOp(instruction),operand(operand)
		{
		}

		virtual ~UnaryOp()
		{
			if (!operand->IsRegisterOperand())
			{
				delete operand;
			}
		}

		virtual Ceng::CRESULT Encode(BuildParams *params,
										std::vector<Ceng::UINT8> &destBuffer) override
		{
			return instruction->EncodeOneForm(params,destBuffer,operand);
		};
	};

	class BinaryOp : public UnaryOp
	{
	protected:
		const Operand *source;
	public:
		BinaryOp()
		{
		}

		BinaryOp(const Instruction &instruction,const Operand *dest,
					const Operand *source) :
			UnaryOp(instruction,dest),source(source)
		{
		}

		virtual ~BinaryOp()
		{
			if (!source->IsRegisterOperand())
			{
				delete source;
			}
		}

		virtual Ceng::CRESULT Encode(BuildParams *params,
										std::vector<Ceng::UINT8> &destBuffer) override
		{
			return instruction->EncodeTwoForm(params,destBuffer,operand,source);
		};
	};

	class ThreeOp : public BinaryOp
	{
	protected:
		const Operand *source2;

	public:

		ThreeOp()
		{
		}

		ThreeOp(const Instruction &instruction,const Operand *dest,
					const Operand *source,const Operand *source2) :
			BinaryOp(instruction,dest,source),source2(source2)
		{
		}

		virtual ~ThreeOp()
		{
			if (!source2->IsRegisterOperand())
			{
				delete source2;
			}
		}

		virtual Ceng::CRESULT Encode(BuildParams *params,
										std::vector<Ceng::UINT8> &destBuffer) override
		{
			return instruction->EncodeThreeForm(params,destBuffer,operand,source,source2);
		};
	};
}

#endif