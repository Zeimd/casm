/*****************************************************************************
*
* x86-opcodes-avx.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-opcodes-avx.h"

#include "../include/enums/x86-opcode-escape.h"
#include "../include/enums/x86-prefix-bytes.h"
#include "../include/enums/x86-param-list.h"
#include "../include/enums/x86-vex-w.h"


namespace X86
{
	//**********************************************************************************
	// Masked moves

	static const Ceng::UINT8 OPCODE_VMASKMOV_PS_REG = 0x2c;
	static const Ceng::UINT8 OPCODE_VMASKMOV_PS_MEM = 0x2e;

	static const Ceng::UINT8 OPCODE_VMASKMOV_PD_REG = 0x2d;
	static const Ceng::UINT8 OPCODE_VMASKMOV_PD_MEM = 0x2f;

	const X86::SSE_Instruction VMASKMOVPS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_VMASKMOV_PS_REG,
															OPCODE_VMASKMOV_PS_MEM,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															PARAM_LIST::REG_REG_MEM |
															PARAM_LIST::MEM_REG_REG);

	const X86::SSE_Instruction VMASKMOVPD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_VMASKMOV_PD_REG,
															OPCODE_VMASKMOV_PD_MEM,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															PARAM_LIST::REG_REG_MEM |
															PARAM_LIST::MEM_REG_REG);

	//***********************************************************************************
	// AVX : Bit test

	static const Ceng::UINT8 OPCODE_VTESTPS = 0x0e;
	static const Ceng::UINT8 OPCODE_VTESTPD = 0x0f;

	const X86::SSE_Instruction VTESTPS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_VTESTPS,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG |
															PARAM_LIST::REG_MEM);

	const X86::SSE_Instruction VTESTPD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_VTESTPD,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG |
															PARAM_LIST::REG_MEM);

	//******************************************************************************************
	// AVX : Permutation

	/** Special case:
	 *
	 * These have different opcodes
	 *
	 * vpermilps xmm,xmm,xmm/m128
	 * vpermilps xmm,xmm,imm
	 *
	 */

	static const Ceng::UINT8 OPCODE_VPERM_F128 = 0x06;

	const X86::SSE_Instruction VPERM2F128 = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_VPERM_F128,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::YMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG_IMM |
															PARAM_LIST::REG_REG_MEM_IMM);
}