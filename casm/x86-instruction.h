/*****************************************************************************
*
* x86-instruction.h
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#ifndef X86_INSTRUCTION_H
#define X86_INSTRUCTION_H

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/return-val.h>

#include <vector>

namespace X86
{
	class Operand;

	class BuildParams;
	class EncodeData;
	class InstructionPrefix;

	class Instruction
	{
	public:
		Instruction();

		virtual ~Instruction();

	public:

		virtual const Ceng::CRESULT EncodeBare(BuildParams *params,
												std::vector<Ceng::UINT8> &destBuffer) const;

		virtual const Ceng::CRESULT EncodeOneForm(BuildParams *params,
												std::vector<Ceng::UINT8> &destBuffer,
												const Operand *operand) const;

		virtual const Ceng::CRESULT EncodeTwoForm(BuildParams *params,std::vector<Ceng::UINT8> &destBuffer,
								const Operand *dest,const Operand *source) const;

		virtual const Ceng::CRESULT EncodeThreeForm(BuildParams *params,std::vector<Ceng::UINT8> &destBuffer,
								const Operand *dest,const Operand *source1,
								const Operand *source2) const;

		virtual const Ceng::CRESULT EncodeFourForm(BuildParams* params, std::vector<Ceng::UINT8>& destBuffer,
			const Operand* dest, const Operand* source1,
			const Operand* source2,const Operand* source3) const;

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,EncodeData *encodeData) const;
		
		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *operand) const;

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *dest,
											const Operand *source) const;

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *dest,
											const Operand *source1,
											const Operand *source2) const;

		virtual const Ceng::CRESULT SelectOpcode(BuildParams* params,
			EncodeData* encodeData, const Operand* dest,
			const Operand* source1,	const Operand* source2,
			const Operand* source3) const;

		virtual const Ceng::CRESULT ValidatePrefixes(const Ceng::UINT32 prefixes) const;

		virtual const char* Name() const
		{
			return "undefined";
		}

	protected:

		/*
		const Ceng::CRESULT EncodeInstruction(BuildParams *params,std::vector<Ceng::UINT8> &destBuffer,
											 InstructionPrefix *prefix,EncodeData *encodeData) const;
											 */
	};

	

	
}

#endif