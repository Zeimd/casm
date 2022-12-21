/*****************************************************************************
*
* sse-instruction.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "sse-instruction.h"

#include "x86-register-op.h"
#include "x86-memory-op.h"
#include "x86-immediate-op.h"

#include "build-params.h"

#include "enums/x86-register-types.h"
#include "enums/x86-param-list.h"

#include "encode-data.h"

using namespace X86;

const Ceng::CRESULT SSE_Instruction::SelectOpcode(BuildParams *params,EncodeData *encodeData,
												  const Operand *dest,const Operand *source) const
{
	if (dest->IsRegisterOperand())
	{

		if (encoding == SIMD_ENCODING::LEGACY)
		{
			if (source->IsRegisterOperand())
			{
				if ( !(paramForms & PARAM_LIST::REG_REG) )
				{
					return Ceng::CE_ERR_INVALID_PARAM;
				}

				return SSE_R_R(params,encodeData,
										prefixByte,escapeCode,opcode_r_rm,
										static_cast<const RegisterOperand*>(dest),
										static_cast<const RegisterOperand*>(source));
			}

			if (source->IsMemoryOperand())
			{
				if ( !(paramForms & PARAM_LIST::REG_MEM) )
				{
					return Ceng::CE_ERR_INVALID_PARAM;
				}

				return SSE_R_M(params,encodeData,
										prefixByte,escapeCode,opcode_r_rm,
										static_cast<const RegisterOperand*>(dest),
										static_cast<const MemoryOperand*>(source));
			}
		}
		else if (encoding == SIMD_ENCODING::VEX)
		{
			if (source->IsRegisterOperand())
			{
				if ( !(paramForms & PARAM_LIST::REG_REG) )
				{
					return Ceng::CE_ERR_INVALID_PARAM;
				}

				return AVX_R_R(params,encodeData,
								prefixByte,escapeCode,opcode_r_rm,
								minVecSize,maxVecSize,wFunction,
								static_cast<const RegisterOperand*>(dest),
								static_cast<const RegisterOperand*>(source));
			}

			if (source->IsMemoryOperand())
			{
				if ( !(paramForms & PARAM_LIST::REG_MEM) )
				{
					return Ceng::CE_ERR_INVALID_PARAM;
				}

				return AVX_R_M(params,encodeData,
								prefixByte,escapeCode,opcode_r_rm,
								minVecSize,maxVecSize,wFunction,
								static_cast<const RegisterOperand*>(dest),
								static_cast<const MemoryOperand*>(source));
			}
		}
	}

	if (paramForms & PARAM_LIST::MEM_REG)
	{
		if (source->IsRegisterOperand())
		{
			if (encoding == SIMD_ENCODING::LEGACY)
			{
				return SSE_M_R(params,encodeData,
										prefixByte,escapeCode,opcode_rm_r,
										static_cast<const MemoryOperand*>(dest),
										static_cast<const RegisterOperand*>(source));
			}
			else if (encoding == SIMD_ENCODING::VEX)
			{
				return AVX_M_R(params,encodeData,
										prefixByte,escapeCode,opcode_rm_r,
										minVecSize,maxVecSize,wFunction,
										static_cast<const MemoryOperand*>(dest),
										static_cast<const RegisterOperand*>(source));
			}

		}		
	}

	return Ceng::CE_ERR_INVALID_PARAM;
}

const Ceng::CRESULT SSE_Instruction::SelectOpcode(BuildParams *params,
												  EncodeData *encodeData,const Operand *dest,
												  const Operand *source1,
												  const Operand *source2) const
{
	if (source1->IsRegisterOperand() == false)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (dest->IsRegisterOperand())
	{
		if (source2->IsRegisterOperand())
		{
			if ( !(paramForms & PARAM_LIST::REG_REG_REG) )
			{
				return Ceng::CE_ERR_INVALID_PARAM;
			}

			return AVX_R_R_R(params,encodeData,
								prefixByte,escapeCode,opcode_r_rm,
								minVecSize,maxVecSize,wFunction,
							static_cast<const RegisterOperand*>(dest),
							static_cast<const RegisterOperand*>(source1),
							static_cast<const RegisterOperand*>(source2));
		}

		if (source2->IsMemoryOperand())
		{
			if ( !(paramForms & PARAM_LIST::REG_REG_MEM) )
			{
				return Ceng::CE_ERR_INVALID_PARAM;
			}

			return AVX_R_R_M(params,encodeData,
								prefixByte,escapeCode,opcode_r_rm,
								minVecSize,maxVecSize,wFunction,
							static_cast<const RegisterOperand*>(dest),
							static_cast<const RegisterOperand*>(source1),
							static_cast<const MemoryOperand*>(source2));
		}
	}

	return Ceng::CE_ERR_INVALID_PARAM;
}

const Ceng::BOOL SSE_Instruction::ValidateRegister(BuildParams *params,
											const RegisterOperand *registerOp) const
{
	if (params->mode->cpuMode != CPU_MODE::X64)
	{
		if (registerOp->index > 7)
		{
			return false;
		}
	}

	return registerOp->RegisterFiles() & REGISTER_FILE::REG_XMM;
}

const Ceng::CRESULT SSE_Instruction::SSE_R_R(BuildParams *params,EncodeData *encodeData,
											 const PREFIX_BYTE::value prefixByte,
											 const OPCODE_ESCAPE::value escapeCode,
											 const Ceng::UINT8 opcode_r_rm,
											 const RegisterOperand *dest,
											 const RegisterOperand *source) const
{
	if ( !ValidateRegister(params,dest))
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if ( !ValidateRegister(params,source))
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	StandardOpcode(params,encodeData,prefixByte,escapeCode,opcode_r_rm);

	return Ceng::CE_OK;
}

const Ceng::CRESULT SSE_Instruction::SSE_R_M(BuildParams *params,EncodeData *encodeData,
											 const PREFIX_BYTE::value prefixByte,
											 const OPCODE_ESCAPE::value escapeCode,
											 const Ceng::UINT8 opcode_r_rm,
											 const RegisterOperand *dest,
											 const MemoryOperand *source) const
{
	if ( !ValidateRegister(params,dest))
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	StandardOpcode(params,encodeData,prefixByte,escapeCode,opcode_r_rm);

	return Ceng::CE_OK;
}

const Ceng::CRESULT SSE_Instruction::SSE_M_R(BuildParams *params,EncodeData *encodeData,
											 const PREFIX_BYTE::value prefixByte,
											 const OPCODE_ESCAPE::value escapeCode,
											 const Ceng::UINT8 opcode_rm_r,
											 const MemoryOperand *dest,
											 const RegisterOperand *source) const
{
	if ( !ValidateRegister(params,source))
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->opcodePrefix = prefixByte;

	encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
	encodeData->opcode = opcode_rm_r;

	encodeData->operandPlace[0] = OperandPlace::rm_field;
	encodeData->operandPlace[1] = OperandPlace::reg_field;

	return Ceng::CE_OK;
}

void SSE_Instruction::StandardOpcode(BuildParams *params,EncodeData *encodeData,
									 const PREFIX_BYTE::value prefixByte,
									 const OPCODE_ESCAPE::value escapeCode,
									 const Ceng::UINT8 opcode_r_rm) const
{
	encodeData->opcodePrefix = prefixByte;
	encodeData->escapeCode = escapeCode;
	encodeData->opcode = opcode_r_rm;
	
	encodeData->operandPlace[0] = OperandPlace::reg_field;
	encodeData->operandPlace[1] = OperandPlace::rm_field;

	return;
}

const Ceng::BOOL SSE_Instruction::AVX_CheckRegister(const RegisterOperand *registerOp) const
{
	return (registerOp->RegisterFiles() & (REGISTER_FILE::REG_XMM | REGISTER_FILE::REG_YMM) );
}

const Ceng::CRESULT SSE_Instruction::AVX_R_R_R(BuildParams *params,
													EncodeData *encodeData,
													const PREFIX_BYTE::value prefixByte,
													const OPCODE_ESCAPE::value escapeCode,
													const Ceng::UINT8 opcode_r_rm,
													const OPERAND_SIZE::value minVecSize,
													const OPERAND_SIZE::value maxVecSize,
													const VEX_W_FUNCTION::value wFunction,
													const RegisterOperand *dest,
													const RegisterOperand *source1,
													const RegisterOperand *source2) const
{
	if ( !(dest->RegisterFiles() & source1->RegisterFiles() & source2->RegisterFiles()) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if ( !AVX_CheckRegister(dest) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (dest->Size() < minVecSize || dest->Size() > maxVecSize)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	// Operand size

	VEX_VECTOR_SIZE::value opSize = VEX_VECTOR_SIZE::XMM;

	if (dest->Size() == OPERAND_SIZE::YMMWORD)
	{
		opSize = VEX_VECTOR_SIZE::YMM;
	}

	AVX_StandardOpcode3(params,encodeData,prefixByte,escapeCode,opcode_r_rm,
							wFunction,opSize);

	return Ceng::CE_OK;
}

const Ceng::CRESULT SSE_Instruction::AVX_R_R_M(BuildParams *params,
													EncodeData *encodeData,
													const PREFIX_BYTE::value prefixByte,
													const OPCODE_ESCAPE::value escapeCode,
													const Ceng::UINT8 opcode_r_rm,
													const OPERAND_SIZE::value minVecSize,
													const OPERAND_SIZE::value maxVecSize,
													const VEX_W_FUNCTION::value wFunction,
													const RegisterOperand *dest,
													const RegisterOperand *source1,
													const MemoryOperand *source2) const
{
	if ( !(dest->RegisterFiles() & source1->RegisterFiles()) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if ( !AVX_CheckRegister(dest) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (dest->Size() < minVecSize || dest->Size() > maxVecSize)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	// Operand size

	VEX_VECTOR_SIZE::value opSize = VEX_VECTOR_SIZE::XMM;

	if (dest->Size() == OPERAND_SIZE::YMMWORD)
	{
		opSize = VEX_VECTOR_SIZE::YMM;
	}

	AVX_StandardOpcode3(params,encodeData,prefixByte,escapeCode,opcode_r_rm,
							wFunction,opSize);
	

	return Ceng::CE_OK;
}

void SSE_Instruction::AVX_StandardOpcode3(BuildParams *params,EncodeData *encodeData,
										 const PREFIX_BYTE::value prefixByte,
										 const OPCODE_ESCAPE::value escapeCode,
										 const Ceng::UINT8 opcode_r_rm,
										 const VEX_W_FUNCTION::value wFunction,
										 const VEX_VECTOR_SIZE::value opSize) const
{
	encodeData->useVEX = true;

	encodeData->escapeCode = escapeCode;
	encodeData->opcode = opcode_r_rm;

	encodeData->vex.SetFormat(VEX_FORMAT::TWO_BYTE);

	if (wFunction == VEX_W_FUNCTION::ONE)
	{
		encodeData->vex.SetWideSize();
	}

	encodeData->vex.SetVectorSize(opSize);
	encodeData->vex.SetPrefixCode(prefixByte);
	
	encodeData->operandPlace[0] = OperandPlace::reg_field;
	encodeData->operandPlace[1] = OperandPlace::vex_vvvv;
	encodeData->operandPlace[2] = OperandPlace::rm_field;
}

const Ceng::CRESULT SSE_Instruction::AVX_R_R(BuildParams *params,EncodeData *encodeData,
											 const PREFIX_BYTE::value prefixByte,
											 const OPCODE_ESCAPE::value escapeCode,
											 const Ceng::UINT8 opcode_r_rm,
											 const OPERAND_SIZE::value minVecSize,
											 const OPERAND_SIZE::value maxVecSize,
											 const VEX_W_FUNCTION::value wFunction,
											 const RegisterOperand *dest,
											 const RegisterOperand *source) const
{
	if ( !(dest->RegisterFiles() & source->RegisterFiles()) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if ( !AVX_CheckRegister(dest) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (dest->Size() < minVecSize || dest->Size() > maxVecSize)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	// Operand size

	VEX_VECTOR_SIZE::value opSize = VEX_VECTOR_SIZE::XMM;

	if (dest->Size() == OPERAND_SIZE::YMMWORD)
	{
		opSize = VEX_VECTOR_SIZE::YMM;
	}

	AVX_StandardOpcode2(params,encodeData,prefixByte,escapeCode,opcode_r_rm,
							wFunction,opSize);

	return Ceng::CE_OK;
}

const Ceng::CRESULT SSE_Instruction::AVX_R_M(BuildParams *params,EncodeData *encodeData,
											 const PREFIX_BYTE::value prefixByte,
											 const OPCODE_ESCAPE::value escapeCode,
											 const Ceng::UINT8 opcode_r_rm,
											 const OPERAND_SIZE::value minVecSize,
											 const OPERAND_SIZE::value maxVecSize,
											 const VEX_W_FUNCTION::value wFunction,
											 const RegisterOperand *dest,
											 const MemoryOperand *source) const
{
	if ( !AVX_CheckRegister(dest) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (dest->Size() < minVecSize || dest->Size() > maxVecSize)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	// Operand size

	VEX_VECTOR_SIZE::value opSize = VEX_VECTOR_SIZE::XMM;

	if (dest->Size() == OPERAND_SIZE::YMMWORD)
	{
		opSize = VEX_VECTOR_SIZE::YMM;
	}

	AVX_StandardOpcode2(params,encodeData,prefixByte,escapeCode,opcode_r_rm,
							wFunction,opSize);

	return Ceng::CE_OK;
}

const Ceng::CRESULT SSE_Instruction::AVX_M_R(BuildParams *params,EncodeData *encodeData,
											 const PREFIX_BYTE::value prefixByte,
											 const OPCODE_ESCAPE::value escapeCode,
											 const Ceng::UINT8 opcode_rm_r,
											 const OPERAND_SIZE::value minVecSize,
											 const OPERAND_SIZE::value maxVecSize,
											 const VEX_W_FUNCTION::value wFunction,
											 const MemoryOperand *dest,
											 const RegisterOperand *source) const
{
	if ( !AVX_CheckRegister(source))
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}
	
	VEX_VECTOR_SIZE::value opSize = VEX_VECTOR_SIZE::XMM;

	if (source->Size() == OPERAND_SIZE::YMMWORD)
	{
		opSize = VEX_VECTOR_SIZE::YMM;
	}

	encodeData->useVEX = true;

	encodeData->opcode = opcode_rm_r;

	encodeData->vex.SetFormat(VEX_FORMAT::TWO_BYTE);

	if (wFunction == VEX_W_FUNCTION::ONE)
	{
		encodeData->vex.SetWideSize();
	}

	encodeData->vex.SetVectorSize(opSize);

	encodeData->vex.SetEscapeCode(escapeCode);
	encodeData->vex.SetPrefixCode(prefixByte);

	encodeData->operandPlace[0] = OperandPlace::rm_field;
	encodeData->operandPlace[1] = OperandPlace::reg_field;

	return Ceng::CE_OK;
}

void SSE_Instruction::AVX_StandardOpcode2(BuildParams *params,EncodeData *encodeData,
										 const PREFIX_BYTE::value prefixByte,
										 const OPCODE_ESCAPE::value escapeCode,
										 const Ceng::UINT8 opcode_r_rm,
										 const VEX_W_FUNCTION::value wFunction,
										 const VEX_VECTOR_SIZE::value opSize) const
{
	encodeData->useVEX = true;

	encodeData->opcode = opcode_r_rm;

	encodeData->vex.SetFormat(VEX_FORMAT::TWO_BYTE);

	if (wFunction == VEX_W_FUNCTION::ONE)
	{
		encodeData->vex.SetWideSize();
	}

	encodeData->vex.SetVectorSize(opSize);
	encodeData->vex.SetPrefixCode(prefixByte);
	
	encodeData->operandPlace[0] = OperandPlace::reg_field;
	encodeData->operandPlace[1] = OperandPlace::rm_field;
}