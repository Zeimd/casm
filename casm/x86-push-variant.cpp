
#include "x86-push-variant.h"

using namespace X86;

PushTypeInstruction::PushTypeInstruction(const uint8_t opcode_rm32, const uint8_t opcode_r32,
	const bool allowCS, const uint8_t opcode_cs, const uint8_t opcode_ss,
	const uint8_t opcode_ds, const uint8_t opcode_es, const uint8_t opcode_fs,
	const uint8_t opcode_gs, const bool allowImm, const uint8_t opcode_imm8,
	const uint8_t opcode_imm32)
	: opcode_rm32(opcode_rm32), opcode_r32(opcode_r32), allowCS(allowCS),
	opcode_cs(opcode_cs), opcode_ss(opcode_ss), opcode_ds(opcode_ds), opcode_es(opcode_es),
	opcode_fs(opcode_fs), opcode_gs(opcode_gs), allowImm(allowImm), opcode_imm8(opcode_imm8),
	opcode_imm32(opcode_imm32)
{

}

PushTypeInstruction::~PushTypeInstruction()
{

}