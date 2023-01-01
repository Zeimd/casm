
#include "x86-push-variant.h"

#include "x86-operand.h"

#include "encode-data.h"

#include "build-params.h"

#include "x86-register-op.h"

#include "enums/x86-register-types.h"

#include "x86-regs-alu-adr.h"

using namespace X86;

PushTypeInstruction::PushTypeInstruction(const char* name, const uint8_t opcode_rm32, const uint8_t opcode_r32,
	const bool allowCS, const uint8_t opcode_cs, const uint8_t opcode_ss,
	const uint8_t opcode_ds, const uint8_t opcode_es, const uint8_t opcode_fs,
	const uint8_t opcode_gs, const bool allowImm, const uint8_t opcode_imm8,
	const uint8_t opcode_imm32)
	: name(name), opcode_rm32(opcode_rm32), opcode_r32(opcode_r32), allowCS(allowCS),
	opcode_cs(opcode_cs), opcode_ss(opcode_ss), opcode_ds(opcode_ds), opcode_es(opcode_es),
	opcode_fs(opcode_fs), opcode_gs(opcode_gs), allowImm(allowImm), opcode_imm8(opcode_imm8),
	opcode_imm32(opcode_imm32)
{

}

PushTypeInstruction::~PushTypeInstruction()
{

}

const Ceng::CRESULT PushTypeInstruction::SelectOpcode(BuildParams* params,
	EncodeData* encodeData, const Operand* operand) const
{
	if (operand->IsRegisterOperand())
	{
		const RegisterOperand* reg = static_cast<const RegisterOperand*>(operand);

		if (reg->RegisterFiles() == X86::REGISTER_FILE::REG_SEGMENT)
		{
			if (reg == &X86::CS)
			{
				if (allowCS == false)
				{
					return Ceng::CE_ERR_INVALID_PARAM;
				}

				encodeData->opcode = opcode_cs;
			}
			else if (reg == &X86::DS)
			{
				encodeData->opcode = opcode_ds;
			}
			else if (reg == &X86::SS)
			{
				encodeData->opcode = opcode_ss;
			}
			else if (reg == &X86::ES)
			{
				encodeData->opcode = opcode_fs;
			}
			else if (reg == &X86::FS)
			{
				encodeData->escapeCode = X86::OPCODE_ESCAPE::BYTE_0F;
				encodeData->opcode = opcode_gs;
			}
			else if (reg == &X86::GS)
			{
				encodeData->escapeCode = X86::OPCODE_ESCAPE::BYTE_0F;
				encodeData->opcode = opcode_ss;
			}
			else
			{
				return Ceng::CE_ERR_INVALID_PARAM;
			}

			encodeData->operandPlace[0] = X86::OperandPlace::unused;
		}
		else
		{
			encodeData->opcode = opcode_r32;

			encodeData->operandPlace[0] = X86::OperandPlace::opcode;
		}	
	}
	else if (operand->IsMemoryOperand())
	{
		encodeData->opcode = opcode_rm32;

		encodeData->modRM.SetRegField(6);

		encodeData->operandPlace[0] = X86::OperandPlace::rm_field;
	}
	else if (operand->IsImmediateOperand())
	{
		if (allowImm == false)
		{
			return Ceng::CE_ERR_INVALID_PARAM;
		}

		switch (operand->Size())
		{
		case X86::OPERAND_SIZE::BYTE:
			encodeData->opcode = opcode_imm8;
			break;
		case X86::OPERAND_SIZE::WORD:
		case X86::OPERAND_SIZE::DWORD:
			encodeData->opcode = opcode_imm32;

			if (params->mode->defaultOpSize != operand->Size())
			{
				encodeData->optionPrefix |= X86::PREFIX_BYTE::OPERAND_SIZE;
			}
			break;
		default:
			return Ceng::CE_ERR_INVALID_PARAM;
			break;
		}

		encodeData->operandPlace[0] = X86::OperandPlace::imm;

		encodeData->immEncoding = operand->Size();
	}
	else
	{
		return Ceng::CE_ERR_FAIL;
	}

	return Ceng::CE_OK;
}