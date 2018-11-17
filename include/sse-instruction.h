/*****************************************************************************
*
* sse-instruction.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_SSE_BASE_H
#define X86_SSE_BASE_H

#include "x86-instruction.h"

#include "x86-vex-prefix.h"

#include "enums/x86-operand-sizes.h"

#include "enums/x86-simd-encoding.h"
#include "enums/x86-vex-w.h"

#include "enums/x86-param-list.h"

#include <datatypes/boolean.h>

namespace X86
{
	const OPERAND_SIZE::value AVX_MAX_VEC_SIZE = OPERAND_SIZE::YMMWORD;

	const Ceng::UINT32 SSE_BASIC_PARAM_LIST = PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM;
	
	const Ceng::UINT32 AVX_BASIC_PARAM_LIST = PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM;

	class RegisterOperand;
	class MemoryOperand;
	class ImmediateOperand;

	class SSE_Instruction : public Instruction
	{
	protected:

		const OPCODE_ESCAPE::value escapeCode;
		
		const SIMD_ENCODING::value encoding;

		/**
		 * Parameter lists allowed for 2-op form.
		 */
		const Ceng::UINT32 paramForms;

		/**
		 * Minimum vector size supported.
		 */
		const OPERAND_SIZE::value minVecSize;

		/**
		 * Maximum vector size supported.
		 */
		const OPERAND_SIZE::value maxVecSize;

		/**
		 * Compulsory prefix byte.
		 */
		const PREFIX_BYTE::value prefixByte;

		/**
		 * Opcode when destination is memory.
		 */
		const Ceng::UINT8 opcode_rm_r;

		/**
		 * Opcode when destination is register.
		 */
		const Ceng::UINT8 opcode_r_rm;

		const VEX_W_FUNCTION::value wFunction;

	public:

		SSE_Instruction(const PREFIX_BYTE::value prefixByte,
							const OPCODE_ESCAPE::value escapeCode,
							const Ceng::UINT8 opcode_r_rm,
							const Ceng::UINT8 opcode_rm_r,
							const SIMD_ENCODING::value encoding,
							const OPERAND_SIZE::value minVecSize,
							const OPERAND_SIZE::value maxVecSize,
							const VEX_W_FUNCTION::value wFunction,
							const Ceng::UINT32 paramForms)
			: escapeCode(escapeCode),prefixByte(prefixByte),opcode_r_rm(opcode_r_rm),
			opcode_rm_r(opcode_rm_r),encoding(encoding),
			minVecSize(minVecSize),maxVecSize(maxVecSize),wFunction(wFunction),paramForms(paramForms)
		{
		}

		SSE_Instruction(const PREFIX_BYTE::value prefixByte,
							const OPCODE_ESCAPE::value escapeCode,
							const Ceng::UINT8 opcode_r_rm,
							const Ceng::UINT8 opcode_rm_r,
							const SIMD_ENCODING::value encoding,
							const OPERAND_SIZE::value minVecSize,
							const OPERAND_SIZE::value maxVecSize,
							const Ceng::UINT32 paramForms)
			: escapeCode(escapeCode),prefixByte(prefixByte),opcode_r_rm(opcode_r_rm),
			opcode_rm_r(opcode_rm_r),encoding(encoding),
			minVecSize(minVecSize),maxVecSize(maxVecSize),wFunction(VEX_W_FUNCTION::ZERO),paramForms(paramForms)
		{
		}

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *dest,
											const Operand *source) const override;

		virtual const Ceng::CRESULT SelectOpcode(BuildParams *params,
											EncodeData *encodeData,const Operand *dest,
											const Operand *source1,
											const Operand *source2) const override;

	protected:

		const Ceng::BOOL ValidateRegister(BuildParams *params,const RegisterOperand *registerOp) const;

		const Ceng::CRESULT SSE_R_R(BuildParams *params,EncodeData *encodeData,
											const PREFIX_BYTE::value prefixByte,
											const OPCODE_ESCAPE::value escapeCode,
											const Ceng::UINT8 opcode_r_rm,
											const RegisterOperand *dest,
											const RegisterOperand *source) const;

		const Ceng::CRESULT SSE_R_M(BuildParams *params,EncodeData *encodeData,
											const PREFIX_BYTE::value prefixByte,
											const OPCODE_ESCAPE::value escapeCode,
											const Ceng::UINT8 opcode_r_rm,
											const RegisterOperand *dest,
											const MemoryOperand *source) const;

		const Ceng::CRESULT SSE_M_R(BuildParams *params,EncodeData *encodeData,
											const PREFIX_BYTE::value prefixByte,
											const OPCODE_ESCAPE::value escapeCode,
											const Ceng::UINT8 opcode_rm_r,
											const MemoryOperand *dest,
											const RegisterOperand *source) const;

		void StandardOpcode(BuildParams *params,EncodeData *encodeData,
								const PREFIX_BYTE::value prefixByte,
								const OPCODE_ESCAPE::value escapeCode,
											const Ceng::UINT8 opcode_r_rm) const;

		const Ceng::CRESULT AVX_R_R(BuildParams *params,EncodeData *encodeData,
											const PREFIX_BYTE::value prefixByte,
											const OPCODE_ESCAPE::value escapeCode,
											const Ceng::UINT8 opcode_r_rm,
											const OPERAND_SIZE::value minVecSize,
											const OPERAND_SIZE::value maxVecSize,
											const VEX_W_FUNCTION::value wFunction,
											const RegisterOperand *dest,
											const RegisterOperand *source) const;

		const Ceng::CRESULT AVX_R_M(BuildParams *params,EncodeData *encodeData,
											const PREFIX_BYTE::value prefixByte,
											const OPCODE_ESCAPE::value escapeCode,
											const Ceng::UINT8 opcode_r_rm,
											const OPERAND_SIZE::value minVecSize,
											const OPERAND_SIZE::value maxVecSize,
											const VEX_W_FUNCTION::value wFunction,
											const RegisterOperand *dest,
											const MemoryOperand *source) const;

		const Ceng::CRESULT AVX_M_R(BuildParams *params,EncodeData *encodeData,
											const PREFIX_BYTE::value prefixByte,
											const OPCODE_ESCAPE::value escapeCode,
											const Ceng::UINT8 opcode_rm_r,
											const OPERAND_SIZE::value minVecSize,
											const OPERAND_SIZE::value maxVecSize,
											const VEX_W_FUNCTION::value wFunction,
											const MemoryOperand *dest,
											const RegisterOperand *source) const;


		const Ceng::CRESULT AVX_R_R_R(BuildParams *params,
											EncodeData *encodeData,
											const PREFIX_BYTE::value prefixByte,
											const OPCODE_ESCAPE::value escapeCode,
											const Ceng::UINT8 opcode_r_rm,
											const OPERAND_SIZE::value minVecSize,
											const OPERAND_SIZE::value maxVecSize,
											const VEX_W_FUNCTION::value wFunction,
											const RegisterOperand *dest,
											const RegisterOperand *source1,
											const RegisterOperand *source2) const;

		const Ceng::CRESULT AVX_R_R_M(BuildParams *params,
													EncodeData *encodeData,
													const PREFIX_BYTE::value prefixByte,
													const OPCODE_ESCAPE::value escapeCode,
													const Ceng::UINT8 opcode_r_rm,
													const OPERAND_SIZE::value minVecSize,
													const OPERAND_SIZE::value maxVecSize,
													const VEX_W_FUNCTION::value wFunction,
													const RegisterOperand *dest,
													const RegisterOperand *source1,
													const MemoryOperand *source2) const;

		const Ceng::BOOL AVX_CheckRegister(const RegisterOperand *registerOp) const;

		void AVX_StandardOpcode2(BuildParams *params,
									EncodeData *encodeData,
									const PREFIX_BYTE::value prefixByte,
									const OPCODE_ESCAPE::value escapeCode,
									const Ceng::UINT8 opcode_r_rm,
									const VEX_W_FUNCTION::value wFunction,
									VEX_Prefix::VECTOR_SIZE opSize) const;

		void AVX_StandardOpcode3(BuildParams *params,
									EncodeData *encodeData,
									const PREFIX_BYTE::value prefixByte,
									const OPCODE_ESCAPE::value escapeCode,
									const Ceng::UINT8 opcode_r_rm,
									const VEX_W_FUNCTION::value wFunction,
									VEX_Prefix::VECTOR_SIZE opSize) const;

	};
}

#endif