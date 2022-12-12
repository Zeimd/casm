/*****************************************************************************
*
* x86-opcodes-sse41.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-opcodes-sse41.h"

namespace X86
{
	//******************************************************************************************
	// SSE 4.1 : Float insert

	static const Ceng::UINT8 OPCODE_INSERT_PS = 0x21;

	const X86::SSE_Instruction INSERTPS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_INSERT_PS,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															PARAM_LIST::REG_MEM_IMM | PARAM_LIST::REG_REG_IMM);

	const X86::SSE_Instruction VINSERTPS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_INSERT_PS,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															PARAM_LIST::REG_REG_MEM_IMM | 
															PARAM_LIST::REG_REG_REG_IMM);

	//******************************************************************************************
	// SSE 4.1 : DOT PRODUCT

	static const Ceng::UINT8 OPCODE_DPPS = 0x40;
	static const Ceng::UINT8 OPCODE_DPPD = 0x41;

	const X86::SSE_Instruction DPPS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_DPPS,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															PARAM_LIST::REG_REG_IMM |
															PARAM_LIST::REG_MEM_IMM);

	const X86::SSE_Instruction VDPPS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_DPPS,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															PARAM_LIST::REG_REG_REG_IMM |
															PARAM_LIST::REG_REG_MEM_IMM);

	const X86::SSE_Instruction DPPD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_DPPD,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															PARAM_LIST::REG_REG_IMM |
															PARAM_LIST::REG_MEM_IMM);

	// NOTE: VEX version only supports XMM registers

	const X86::SSE_Instruction VDPPD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_DPPD,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															PARAM_LIST::REG_REG_REG_IMM |
															PARAM_LIST::REG_REG_MEM_IMM);

	//******************************************************************************************
	// SSE 4.1 : BLEND

	static const Ceng::UINT8 OPCODE_BLENDPS = 0x0c;
	static const Ceng::UINT8 OPCODE_BLENDPD = 0x0d;

	const X86::SSE_Instruction BLENDPS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_BLENDPS,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															PARAM_LIST::REG_REG_IMM |
															PARAM_LIST::REG_MEM_IMM);

	const X86::SSE_Instruction VBLENDPS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_BLENDPS,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															PARAM_LIST::REG_REG_REG_IMM |
															PARAM_LIST::REG_REG_MEM_IMM);

	const X86::SSE_Instruction BLENDPD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_BLENDPD,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															PARAM_LIST::REG_REG_IMM |
															PARAM_LIST::REG_MEM_IMM);

	const X86::SSE_Instruction VBLENDPD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_BLENDPD,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															PARAM_LIST::REG_REG_REG_IMM |
															PARAM_LIST::REG_REG_MEM_IMM);

	//******************************************************************************************
	// SSE 4.1 : BLENDV

	static const Ceng::UINT8 OPCODE_BLENDVPS = 0x14;
	static const Ceng::UINT8 OPCODE_BLENDVPD = 0x15;

	const X86::SSE_Instruction BLENDVPS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_BLENDVPS,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const X86::SSE_Instruction VBLENDVPS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_BLENDVPS,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															PARAM_LIST::REG_REG_REG_REG |
															PARAM_LIST::REG_REG_MEM_REG);

	const X86::SSE_Instruction BLENDVPD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_BLENDVPD,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const X86::SSE_Instruction VBLENDVPD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_BLENDVPD,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															PARAM_LIST::REG_REG_REG_REG |
															PARAM_LIST::REG_REG_MEM_REG);

	//******************************************************************************************
	// SSE 4.1 : Rounding

	static const Ceng::UINT8 OPCODE_ROUNDPS = 0x08;
	static const Ceng::UINT8 OPCODE_ROUNDPD = 0x09;
	
	static const Ceng::UINT8 OPCODE_ROUNDSS = 0x0a;
	static const Ceng::UINT8 OPCODE_ROUNDSD = 0x0b;

	const X86::SSE_Instruction ROUNDPS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_ROUNDPS,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															PARAM_LIST::REG_REG_IMM |
															PARAM_LIST::REG_MEM_IMM);

	const X86::SSE_Instruction VROUNDPS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_ROUNDPS,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															PARAM_LIST::REG_REG_IMM |
															PARAM_LIST::REG_MEM_IMM);

	const X86::SSE_Instruction ROUNDSS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_ROUNDSS,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															PARAM_LIST::REG_REG_IMM |
															PARAM_LIST::REG_MEM_IMM);

	const X86::SSE_Instruction VROUNDSS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_ROUNDSS,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															PARAM_LIST::REG_REG_REG_IMM |
															PARAM_LIST::REG_REG_MEM_IMM);

	const X86::SSE_Instruction ROUNDPD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_ROUNDPD,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															PARAM_LIST::REG_REG_IMM |
															PARAM_LIST::REG_MEM_IMM);

	const X86::SSE_Instruction VROUNDPD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_ROUNDPD,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															PARAM_LIST::REG_REG_IMM |
															PARAM_LIST::REG_MEM_IMM);

	const X86::SSE_Instruction ROUNDSD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_ROUNDSD,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															PARAM_LIST::REG_REG_IMM |
															PARAM_LIST::REG_MEM_IMM);

	const X86::SSE_Instruction VROUNDSD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_ROUNDSD,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															PARAM_LIST::REG_REG_REG_IMM |
															PARAM_LIST::REG_REG_MEM_IMM);

}