/*****************************************************************************
*
* code-line.h
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#ifndef CASM_CODE_LINE_H
#define CASM_CODE_LINE_H

#include <ceng/datatypes/basic-types.h>

#include "build-params.h"

#include "x86-instruction.h"

#include "x86-operand.h"

#include <vector>

#include "code-element.h"

#include <ostream>

namespace Casm
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

		virtual Ceng::CRESULT Encode(X86::BuildParams *params,
										std::vector<Ceng::UINT8> &destBuffer)
		{
			return Ceng::CE_OK;
		};

		virtual void Print(std::wostream& out) const
		{
			out << "CodeLine" << std::endl;;
		}
	};

	class BareOp : public CodeLine
	{
	protected:
		const X86::Instruction *instruction;
	public:
		BareOp()
		{
		}

		BareOp(const X86::Instruction &instruction) :
			instruction(&instruction)
		{
		}

		virtual ~BareOp()
		{
		}

		virtual Ceng::CRESULT Encode(X86::BuildParams *params,
										std::vector<Ceng::UINT8> &destBuffer)
		{
			return instruction->EncodeBare(params,destBuffer);
		};

		void Print(std::wostream& out) const override
		{
			out << '\t' << instruction->Name() << std::endl;
		}

	};

	class UnaryOp : public BareOp
	{
	protected:
		const X86::Operand *operand;
	public:
		UnaryOp()
		{
		}

		UnaryOp(const X86::Instruction &instruction,const X86::Operand *operand) :
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

		virtual Ceng::CRESULT Encode(X86::BuildParams *params,
										std::vector<Ceng::UINT8> &destBuffer) override
		{
			return instruction->EncodeOneForm(params,destBuffer,operand);
		};

		void Print(std::wostream& out) const override
		{
			out << '\t' << instruction->Name() << ' ' << operand->ToString() << std::endl;
		}

	};

	class BinaryOp : public UnaryOp
	{
	protected:
		const X86::Operand *source;
	public:
		BinaryOp()
		{
		}

		BinaryOp(const X86::Instruction &instruction,const X86::Operand *dest,
					const X86::Operand *source) :
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

		virtual Ceng::CRESULT Encode(X86::BuildParams *params,
										std::vector<Ceng::UINT8> &destBuffer) override
		{
			return instruction->EncodeTwoForm(params,destBuffer,operand,source);
		};

		void Print(std::wostream& out) const override
		{
			out << '\t' << instruction->Name() << ' ' << operand->ToString() 
				<< ", " << source->ToString() << std::endl;
		}

	};

	class ThreeOp : public BinaryOp
	{
	protected:
		const X86::Operand *source2;

	public:

		ThreeOp()
		{
		}

		ThreeOp(const X86::Instruction &instruction,const X86::Operand *dest,
					const X86::Operand *source,const X86::Operand *source2) :
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

		virtual Ceng::CRESULT Encode(X86::BuildParams *params,
										std::vector<Ceng::UINT8> &destBuffer) override
		{
			return instruction->EncodeThreeForm(params,destBuffer,operand,source,source2);
		};

		void Print(std::wostream& out) const override
		{
			out << '\t' << instruction->Name() << ' ' << operand->ToString() <<
				", " << source->ToString() << ", " << source2->ToString() << std::endl;
		}

	};


	class FourOp : public ThreeOp
	{
	protected:
		const X86::Operand* source3;

	public:

		FourOp()
		{
		}

		FourOp(const X86::Instruction& instruction, const X86::Operand* dest,
			const X86::Operand* source, const X86::Operand* source2, 
			const X86::Operand* source3) :
			ThreeOp(instruction, dest, source,source2), source3(source3)
		{
		}

		virtual ~FourOp()
		{
			if (!source3->IsRegisterOperand())
			{
				delete source3;
			}
		}

		virtual Ceng::CRESULT Encode(X86::BuildParams* params,
			std::vector<Ceng::UINT8>& destBuffer) override
		{
			return instruction->EncodeFourForm(params, destBuffer, operand, 
				source, source2,source3);
		};

		void Print(std::wostream& out) const override
		{
			out << '\t' << instruction->Name() << ' ' << operand->ToString() <<
				", " << source->ToString() << ", " << source2->ToString()
				<< ", " << source3->ToString() << std::endl;
		}
	};

}

#endif