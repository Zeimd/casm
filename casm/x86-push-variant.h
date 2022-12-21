
#ifndef X86_PUSH_VARIANT_H
#define X86_PUSH_VARIANT_H

#include "x86-instruction.h"

namespace X86
{
	class PushTypeInstruction : public Instruction
	{
	public:

		// PUSH/POP rm16 / rm32 / rm64
		const uint8_t opcode_rm32;

		// PUSH/POP r16 / r32 / r64
		const uint8_t opcode_r32;

		// is opcode_cs valid?
		const bool allowCS;

		// PUSH/POP CS register
		const uint8_t opcode_cs;

		// PUSH/POP SS register
		const uint8_t opcode_ss;

		// PUSH/POP DS register
		const uint8_t opcode_ds;

		// PUSH/POP ES register
		const uint8_t opcode_es;

		// PUSH/POP FS register
		const uint8_t opcode_fs;

		// PUSH/POP GS register
		const uint8_t opcode_gs;

		// Are opcode_imm valid?
		const bool allowImm;

		// PUSH imm8
		const uint8_t opcode_imm8;

		// PUSH imm16 / imm32
		const uint8_t opcode_imm32;

	public:

		PushTypeInstruction(const uint8_t opcode_rm32, const uint8_t opcode_r32,
			const bool allowCS, const uint8_t opcode_cs, const uint8_t opcode_ss,
			const uint8_t opcode_ds, const uint8_t opcode_es, const uint8_t opcode_fs,
			const uint8_t opcode_gs, const bool allowImm, const uint8_t opcode_imm8,
			const uint8_t opcode_imm32);

		~PushTypeInstruction() override;

		const Ceng::CRESULT SelectOpcode(BuildParams* params,
			EncodeData* encodeData, const Operand* operand) const override;
	};
}

#endif