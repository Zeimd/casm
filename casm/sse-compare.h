/*****************************************************************************
*
* sse-compare.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_SSE_COMPARE_H
#define X86_SSE_COMPARE_H

#include "sse-instruction.h"

namespace X86
{
	class SSE_Compare : public SSE_Instruction
	{
	protected:

		static const Ceng::UINT8 opcode = 0xc2;

		const Ceng::UINT8 comparisonType;
		
	public:

		SSE_Compare(const PREFIX_BYTE::value prefixByte,
							const OPCODE_ESCAPE::value escapeCode,
							const Ceng::UINT8 comparisonType,
							const SIMD_ENCODING::value encoding,
							const OPERAND_SIZE::value minVecSize,
							const OPERAND_SIZE::value maxVecSize,
							const VEX_W_FUNCTION::value wFunction,
							const Ceng::UINT32 paramForms)
			: SSE_Instruction(prefixByte,escapeCode,opcode,0,encoding,minVecSize,maxVecSize,
								wFunction,paramForms),comparisonType(comparisonType)
		{
		}

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *dest,
											const Operand *source) const override;

	protected:

		const Ceng::CRESULT Select_R_R(BuildParams *params,EncodeData *encodeData,
									const RegisterOperand *dest,
									const RegisterOperand *source) const;

		const Ceng::CRESULT Select_R_M(BuildParams *params,EncodeData *encodeData,
									const RegisterOperand *dest,
									const MemoryOperand *source) const;
	};
}

#endif