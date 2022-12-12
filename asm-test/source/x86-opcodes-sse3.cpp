/*****************************************************************************
*
* x86-opcodes-sse3.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-opcodes-sse3.h"

namespace X86
{
	//******************************************************************************************
	// SSE3 : ADDSUB

	static const Ceng::UINT8 OPCODE_ADDSUB = 0xd0;

	const X86::SSE_Instruction ADDSUBPS = SSE_Instruction(PREFIX_BYTE::BYTE_F2,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_ADDSUB,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VADDSUBPS = SSE_Instruction(PREFIX_BYTE::BYTE_F2,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_ADDSUB,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);

	const X86::SSE_Instruction ADDSUBPD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_ADDSUB,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VADDSUBPD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_ADDSUB,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);

	//******************************************************************************************
	// SSE3 : Horizontal add

	static const Ceng::UINT8 OPCODE_HADD = 0xd0;

	const X86::SSE_Instruction HADDPS = SSE_Instruction(PREFIX_BYTE::BYTE_F2,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_HADD,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VHADDPS = SSE_Instruction(PREFIX_BYTE::BYTE_F2,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_HADD,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);

	const X86::SSE_Instruction HADDPD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_HADD,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VHADDPD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_HADD,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);

	//******************************************************************************************
	// SSE3 : Horizontal sub

	static const Ceng::UINT8 OPCODE_HSUB = 0x7d;

	const X86::SSE_Instruction HSUBPS = SSE_Instruction(PREFIX_BYTE::BYTE_F2,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_HSUB,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VHSUBPS = SSE_Instruction(PREFIX_BYTE::BYTE_F2,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_HSUB,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);

	const X86::SSE_Instruction HSUBPD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_HSUB,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VHSUBPD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_HSUB,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);

	//******************************************************************************************
	// SSE 3 : move and duplicate

	static const Ceng::UINT8 OPCODE_MOVSLDUP = 0x12;
	static const Ceng::UINT8 OPCODE_MOVSHDUP = 0x16;

	const X86::SSE_Instruction MOVSLDUP = SSE_Instruction(PREFIX_BYTE::BYTE_F3,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MOVSLDUP,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VMOVSLDUP = SSE_Instruction(PREFIX_BYTE::BYTE_F3,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MOVSLDUP,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction MOVSHDUP = SSE_Instruction(PREFIX_BYTE::BYTE_F3,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MOVSHDUP,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VMOVSHDUP = SSE_Instruction(PREFIX_BYTE::BYTE_F3,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MOVSHDUP,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction MOVDDUP = SSE_Instruction(PREFIX_BYTE::BYTE_F2,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MOVSLDUP,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VMOVDDUP = SSE_Instruction(PREFIX_BYTE::BYTE_F2,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MOVSLDUP,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															SSE_BASIC_PARAM_LIST);
}