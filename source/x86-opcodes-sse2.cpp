/*****************************************************************************
*
* x86-opcodes-sse2.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-opcodes-sse2.h"

namespace X86
{
	//******************************************************************************************
	// SSE2 : convert int32->float

	static const Ceng::UINT8 OPCODE_CVT_DQ_PS = 0x5b;

	const X86::SSE_Instruction CVTDQ2PS = SSE_Instruction(PREFIX_BYTE::NONE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_CVT_DQ_PS,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VCVTDQ2PS = SSE_Instruction(PREFIX_BYTE::NONE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_CVT_DQ_PS,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction CVTPS2DQ = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_CVT_DQ_PS,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VCVTPS2DQ = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_CVT_DQ_PS,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction CVTTPS2DQ = SSE_Instruction(PREFIX_BYTE::BYTE_F3,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_CVT_DQ_PS,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VCVTTPS2DQ = SSE_Instruction(PREFIX_BYTE::BYTE_F3,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_CVT_DQ_PS,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															SSE_BASIC_PARAM_LIST);

	//******************************************************************************************
	// SSE2 : convert int32->double

	static const Ceng::UINT8 OPCODE_CVT_DQ_PD = 0xe6;

	const X86::SSE_Instruction CVTDQ2PD = SSE_Instruction(PREFIX_BYTE::BYTE_F3,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_CVT_DQ_PD,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VCVTDQ2PD = SSE_Instruction(PREFIX_BYTE::BYTE_F3,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_CVT_DQ_PD,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction CVTPD2DQ = SSE_Instruction(PREFIX_BYTE::BYTE_F2,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_CVT_DQ_PD,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VCVTPD2DQ = SSE_Instruction(PREFIX_BYTE::BYTE_F2,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_CVT_DQ_PD,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction CVTTPD2DQ = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_CVT_DQ_PD,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VCVTTPD2DQ = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_CVT_DQ_PD,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															SSE_BASIC_PARAM_LIST);

	//******************************************************************************************
	// SSE2 : convert float->double

	static const Ceng::UINT8 OPCODE_CVT_PS_PD = 0x5a;

	const X86::SSE_Instruction CVTPS2PD = SSE_Instruction(PREFIX_BYTE::NONE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_CVT_PS_PD,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VCVTPS2PD = SSE_Instruction(PREFIX_BYTE::NONE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_CVT_PS_PD,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction CVTPD2PS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_CVT_PS_PD,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VCVTPD2PS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_CVT_PS_PD,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction CVTSD2SS = SSE_Instruction(PREFIX_BYTE::BYTE_F2,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_CVT_PS_PD,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VCVTSD2SS = SSE_Instruction(PREFIX_BYTE::BYTE_F2,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_CVT_PS_PD,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															AVX_BASIC_PARAM_LIST);

	const X86::SSE_Instruction CVTSS2SD = SSE_Instruction(PREFIX_BYTE::BYTE_F3,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_CVT_PS_PD,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VCVTSS2SD = SSE_Instruction(PREFIX_BYTE::BYTE_F3,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_CVT_PS_PD,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															AVX_BASIC_PARAM_LIST);
}