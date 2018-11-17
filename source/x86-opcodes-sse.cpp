/*****************************************************************************
*
* x86-opcodes-sse.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-opcodes-sse.h"

namespace X86
{
	static const PREFIX_BYTE::value PREFIX_PACKED_FLOAT = PREFIX_BYTE::NONE;
	static const PREFIX_BYTE::value PREFIX_SCALAR_FLOAT = PREFIX_BYTE::BYTE_F3;

	static const PREFIX_BYTE::value PREFIX_SCALAR_DOUBLE = PREFIX_BYTE::BYTE_F2;
	static const PREFIX_BYTE::value PREFIX_PACKED_DOUBLE = PREFIX_BYTE::BYTE_66;

	//******************************************************************************************
	// SIMD float aligned move

	static const Ceng::UINT8 OPCODE_MOVA_REG = 0x28;
	static const Ceng::UINT8 OPCODE_MOVA_MEM = 0x29;

	const SSE_Instruction MOVAPS = SSE_Instruction(PREFIX_PACKED_FLOAT,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVA_REG,OPCODE_MOVA_MEM,
													SIMD_ENCODING::LEGACY,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													SSE_BASIC_PARAM_LIST | PARAM_LIST::MEM_REG);

	const SSE_Instruction VMOVAPS = SSE_Instruction(PREFIX_PACKED_FLOAT,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVA_REG,OPCODE_MOVA_MEM,
													SIMD_ENCODING::VEX,
													OPERAND_SIZE::XMMWORD,
													AVX_MAX_VEC_SIZE,
													SSE_BASIC_PARAM_LIST | PARAM_LIST::MEM_REG);

	const SSE_Instruction MOVAPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVA_REG,OPCODE_MOVA_MEM,
													SIMD_ENCODING::LEGACY,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													SSE_BASIC_PARAM_LIST | PARAM_LIST::MEM_REG);

	const SSE_Instruction VMOVAPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVA_REG,OPCODE_MOVA_MEM,
													SIMD_ENCODING::VEX,
													OPERAND_SIZE::XMMWORD,
													AVX_MAX_VEC_SIZE,
													SSE_BASIC_PARAM_LIST | PARAM_LIST::MEM_REG);

	//******************************************************************************************
	// SIMD float unaligned move

	static const Ceng::UINT8 OPCODE_MOVU_REG = 0x10;
	static const Ceng::UINT8 OPCODE_MOVU_MEM = 0x11;

	const SSE_Instruction MOVUPS = SSE_Instruction(PREFIX_PACKED_FLOAT,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVU_REG,OPCODE_MOVU_MEM,
													SIMD_ENCODING::LEGACY,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													SSE_BASIC_PARAM_LIST | PARAM_LIST::MEM_REG);

	const SSE_Instruction VMOVUPS = SSE_Instruction(PREFIX_PACKED_FLOAT,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVU_REG,OPCODE_MOVU_MEM,
													SIMD_ENCODING::VEX,
													OPERAND_SIZE::XMMWORD,
													AVX_MAX_VEC_SIZE,
													SSE_BASIC_PARAM_LIST | PARAM_LIST::MEM_REG);

	const SSE_Instruction MOVUPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVU_REG,OPCODE_MOVU_MEM,
													SIMD_ENCODING::LEGACY,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													SSE_BASIC_PARAM_LIST | PARAM_LIST::MEM_REG);

	const SSE_Instruction VMOVUPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVU_REG,OPCODE_MOVU_MEM,
													SIMD_ENCODING::VEX,
													OPERAND_SIZE::XMMWORD,
													AVX_MAX_VEC_SIZE,
													SSE_BASIC_PARAM_LIST | PARAM_LIST::MEM_REG);

	//******************************************************************************************
	// SIMD float scalar moves
	//
	// NOTE: Scalar version of MOVUPS
	
	const SSE_Instruction MOVSS = SSE_Instruction(PREFIX_SCALAR_FLOAT,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVU_REG,OPCODE_MOVU_MEM,
													SIMD_ENCODING::LEGACY,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													SSE_BASIC_PARAM_LIST | PARAM_LIST::MEM_REG);

	const SSE_Instruction VMOVSS = SSE_Instruction(PREFIX_SCALAR_FLOAT,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVU_REG,OPCODE_MOVU_MEM,
													SIMD_ENCODING::VEX,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													SSE_BASIC_PARAM_LIST | PARAM_LIST::MEM_REG |
													PARAM_LIST::REG_REG_REG);

	const SSE_Instruction MOVSD = SSE_Instruction(PREFIX_SCALAR_DOUBLE,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVU_REG,OPCODE_MOVU_MEM,
													SIMD_ENCODING::LEGACY,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													SSE_BASIC_PARAM_LIST | PARAM_LIST::MEM_REG);

	const SSE_Instruction VMOVSD = SSE_Instruction(PREFIX_SCALAR_DOUBLE,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVU_REG,OPCODE_MOVU_MEM,
													SIMD_ENCODING::VEX,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													SSE_BASIC_PARAM_LIST | PARAM_LIST::MEM_REG |
													PARAM_LIST::REG_REG_REG);

	//******************************************************************************************
	// SIMD float half-vector moves
	//

	static const Ceng::UINT8 OPCODE_MOVL_REG = 0x12;
	static const Ceng::UINT8 OPCODE_MOVL_MEM = 0x13;

	static const Ceng::UINT8 OPCODE_MOVH_REG = 0x16;
	static const Ceng::UINT8 OPCODE_MOVH_MEM = 0x17;

	const SSE_Instruction MOVLPS = SSE_Instruction(PREFIX_PACKED_FLOAT,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVL_REG,OPCODE_MOVL_MEM,
													SIMD_ENCODING::LEGACY,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													PARAM_LIST::REG_MEM | PARAM_LIST::MEM_REG);

	const SSE_Instruction VMOVLPS = SSE_Instruction(PREFIX_PACKED_FLOAT,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVL_REG,OPCODE_MOVL_MEM,
													SIMD_ENCODING::VEX,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													PARAM_LIST::REG_REG_MEM | PARAM_LIST::MEM_REG);

	const SSE_Instruction MOVHPS = SSE_Instruction(PREFIX_PACKED_FLOAT,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVH_REG,OPCODE_MOVH_MEM,
													SIMD_ENCODING::LEGACY,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													PARAM_LIST::REG_MEM | PARAM_LIST::MEM_REG);

	const SSE_Instruction VMOVHPS = SSE_Instruction(PREFIX_PACKED_FLOAT,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVH_REG,OPCODE_MOVH_MEM,
													SIMD_ENCODING::VEX,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													PARAM_LIST::REG_REG_MEM | PARAM_LIST::MEM_REG);

	const SSE_Instruction MOVLPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVL_REG,OPCODE_MOVL_MEM,
													SIMD_ENCODING::LEGACY,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													PARAM_LIST::REG_MEM | PARAM_LIST::MEM_REG);

	const SSE_Instruction VMOVLPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVL_REG,OPCODE_MOVL_MEM,
													SIMD_ENCODING::VEX,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													PARAM_LIST::REG_REG_MEM | PARAM_LIST::MEM_REG);

	const SSE_Instruction MOVHPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVH_REG,OPCODE_MOVH_MEM,
													SIMD_ENCODING::LEGACY,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													PARAM_LIST::REG_MEM | PARAM_LIST::MEM_REG);

	const SSE_Instruction VMOVHPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVH_REG,OPCODE_MOVH_MEM,
													SIMD_ENCODING::VEX,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													PARAM_LIST::REG_REG_MEM | PARAM_LIST::MEM_REG);

	const SSE_Instruction MOVLHPS = SSE_Instruction(PREFIX_PACKED_FLOAT,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVH_REG,0,
													SIMD_ENCODING::LEGACY,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													PARAM_LIST::REG_REG);

	const SSE_Instruction VMOVLHPS = SSE_Instruction(PREFIX_PACKED_FLOAT,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVH_REG,0,
													SIMD_ENCODING::VEX,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													PARAM_LIST::REG_REG_REG);

	const SSE_Instruction MOVHLPS = SSE_Instruction(PREFIX_PACKED_FLOAT,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVL_REG,0,
													SIMD_ENCODING::LEGACY,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													PARAM_LIST::REG_REG);

	const SSE_Instruction VMOVHLPS = SSE_Instruction(PREFIX_PACKED_FLOAT,OPCODE_ESCAPE::BYTE_0F,
													OPCODE_MOVL_REG,0,
													SIMD_ENCODING::VEX,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													PARAM_LIST::REG_REG_REG);

	//******************************************************************************************
	// SIMD float non-temporal moves
	//

	static const Ceng::UINT8 OPCODE_MOVNT = 0x2b;

	const SSE_Instruction MOVNTPS = SSE_Instruction(PREFIX_PACKED_FLOAT,OPCODE_ESCAPE::BYTE_0F,
													0,OPCODE_MOVNT,
													SIMD_ENCODING::LEGACY,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													PARAM_LIST::MEM_REG);

	const SSE_Instruction VMOVNTPS = SSE_Instruction(PREFIX_PACKED_FLOAT,OPCODE_ESCAPE::BYTE_0F,
													0,OPCODE_MOVNT,
													SIMD_ENCODING::VEX,
													OPERAND_SIZE::XMMWORD,
													AVX_MAX_VEC_SIZE,
													PARAM_LIST::MEM_REG);

	const SSE_Instruction MOVNTPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,OPCODE_ESCAPE::BYTE_0F,
													0,OPCODE_MOVNT,
													SIMD_ENCODING::LEGACY,
													OPERAND_SIZE::XMMWORD,
													OPERAND_SIZE::XMMWORD,
													PARAM_LIST::MEM_REG);

	const SSE_Instruction VMOVNTPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,OPCODE_ESCAPE::BYTE_0F,
													0,OPCODE_MOVNT,
													SIMD_ENCODING::VEX,
													OPERAND_SIZE::XMMWORD,
													AVX_MAX_VEC_SIZE,
													PARAM_LIST::MEM_REG);

	//******************************************************************************************
	// SIMD float bitwise AND

	static const Ceng::UINT8 OPCODE_AND = 0x54;

	const X86::SSE_Instruction ANDPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_AND,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);													

	const X86::SSE_Instruction VANDPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_AND,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);

	const X86::SSE_Instruction ANDPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_AND,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VANDPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_AND,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);

	//******************************************************************************************
	// SIMD float bitwise AND NOT

	static const Ceng::UINT8 OPCODE_ANDN = 0x55;

	const X86::SSE_Instruction ANDNPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_ANDN,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VANDNPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_ANDN,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);

	const X86::SSE_Instruction ANDNPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_ANDN,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VANDNPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_ANDN,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);

	//******************************************************************************************
	// SIMD float bitwise OR

	static const Ceng::UINT8 OPCODE_OR = 0x56;
	
	const X86::SSE_Instruction ORPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_OR,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);													

	const X86::SSE_Instruction VORPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_OR,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);

	const X86::SSE_Instruction ORPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_OR,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VORPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_OR,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);

	//******************************************************************************************
	// SIMD float bitwise XOR

	static const Ceng::UINT8 OPCODE_XOR = 0x57;

	const X86::SSE_Instruction XORPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_XOR,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);													

	const X86::SSE_Instruction VXORPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_XOR,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);

	const X86::SSE_Instruction XORPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_XOR,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VXORPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_XOR,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);

	//*****************************************************************************************
	// SIMD float pack

	static const Ceng::UINT8 OPCODE_UNPCKL = 0x14;
	static const Ceng::UINT8 OPCODE_UNPCKH = 0x15;

	const X86::SSE_Instruction UNPCKLPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_UNPCKL,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VUNPCKLPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_UNPCKL,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction UNPCKHPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_UNPCKH,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VUNPCKHPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_UNPCKH,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction UNPCKLPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_UNPCKL,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VUNPCKLPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_UNPCKL,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction UNPCKHPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_UNPCKH,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VUNPCKHPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_UNPCKH,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);	

	//************************************************************************
	// SIMD float ADD

	static const Ceng::UINT8 OPCODE_ADD = 0x58;

	const X86::SSE_Instruction ADDPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_ADD,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VADDPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_ADD,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction ADDSS = SSE_Instruction(PREFIX_SCALAR_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_ADD,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VADDSS = SSE_Instruction(PREFIX_SCALAR_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_ADD,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction ADDPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_ADD,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VADDPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_ADD,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction ADDSD = SSE_Instruction(PREFIX_SCALAR_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_ADD,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VADDSD = SSE_Instruction(PREFIX_SCALAR_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_ADD,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															AVX_BASIC_PARAM_LIST);	

	//************************************************************************
	// SIMD float SUB

	static const Ceng::UINT8 OPCODE_SUB = 0x5c;

	const X86::SSE_Instruction SUBPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_SUB,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VSUBPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_SUB,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction SUBSS = SSE_Instruction(PREFIX_SCALAR_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_SUB,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VSUBSS = SSE_Instruction(PREFIX_SCALAR_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_SUB,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction SUBPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_SUB,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VSUBPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_SUB,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction SUBSD = SSE_Instruction(PREFIX_SCALAR_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_SUB,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VSUBSD = SSE_Instruction(PREFIX_SCALAR_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_SUB,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															AVX_BASIC_PARAM_LIST);	

	//************************************************************************
	// SIMD float DIV

	static const Ceng::UINT8 OPCODE_DIV = 0x5e;

	const X86::SSE_Instruction DIVPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_DIV,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VDIVPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_DIV,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction DIVSS = SSE_Instruction(PREFIX_SCALAR_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_DIV,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VDIVSS = SSE_Instruction(PREFIX_SCALAR_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_DIV,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction DIVPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_DIV,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VDIVPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_DIV,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction DIVSD = SSE_Instruction(PREFIX_SCALAR_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_DIV,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VDIVSD = SSE_Instruction(PREFIX_SCALAR_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_DIV,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															AVX_BASIC_PARAM_LIST);

	//************************************************************************
	// SIMD float MIN

	static const Ceng::UINT8 OPCODE_MIN = 0x5d;
	
	const X86::SSE_Instruction MINPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MIN,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VMINPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MIN,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction MINSS = SSE_Instruction(PREFIX_SCALAR_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MIN,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VMINSS = SSE_Instruction(PREFIX_SCALAR_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MIN,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction MINPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MIN,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VMINPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MIN,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction MINSD = SSE_Instruction(PREFIX_SCALAR_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MIN,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VMINSD = SSE_Instruction(PREFIX_SCALAR_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MIN,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															AVX_BASIC_PARAM_LIST);

	//************************************************************************
	// SIMD float MAX

	static const Ceng::UINT8 OPCODE_MAX = 0x5f;

		
	const X86::SSE_Instruction MAXPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MAX,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VMAXPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MAX,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction MAXSS = SSE_Instruction(PREFIX_SCALAR_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MAX,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VMAXSS = SSE_Instruction(PREFIX_SCALAR_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MAX,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction MAXPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MAX,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VMAXPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MAX,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction MAXSD = SSE_Instruction(PREFIX_SCALAR_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MAX,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VMAXSD = SSE_Instruction(PREFIX_SCALAR_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MAX,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															AVX_BASIC_PARAM_LIST);	

	//************************************************************************
	// SIMD float MUL

	static const Ceng::UINT8 OPCODE_MUL = 0x59;

	const X86::SSE_Instruction MULPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MUL,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VMULPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MUL,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction MULSS = SSE_Instruction(PREFIX_SCALAR_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MUL,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VMULSS = SSE_Instruction(PREFIX_SCALAR_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MUL,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction MULPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MUL,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VMULPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MUL,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction MULSD = SSE_Instruction(PREFIX_SCALAR_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MUL,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VMULSD = SSE_Instruction(PREFIX_SCALAR_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_MUL,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															AVX_BASIC_PARAM_LIST);	

	//************************************************************************
	// SIMD float SQRT

	static const Ceng::UINT8 OPCODE_SQRT = 0x51;

	const X86::SSE_Instruction SQRTPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_SQRT,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VSQRTPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_SQRT,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);	

	const X86::SSE_Instruction SQRTSS = SSE_Instruction(PREFIX_SCALAR_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_SQRT,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VSQRTSS = SSE_Instruction(PREFIX_SCALAR_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_SQRT,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															AVX_BASIC_PARAM_LIST);	

	const X86::SSE_Instruction SQRTPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_SQRT,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VSQRTPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_SQRT,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);	

	const X86::SSE_Instruction SQRTSD = SSE_Instruction(PREFIX_SCALAR_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_SQRT,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VSQRTSD = SSE_Instruction(PREFIX_SCALAR_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_SQRT,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															AVX_BASIC_PARAM_LIST);	

	//************************************************************************
	// SIMD float inverse sqrt

	static const Ceng::UINT8 OPCODE_RSQRT = 0x52;

	const X86::SSE_Instruction RSQRTPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_RSQRT,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VRSQRTPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_RSQRT,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);	

	const X86::SSE_Instruction RSQRTSS = SSE_Instruction(PREFIX_SCALAR_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_RSQRT,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VRSQRTSS = SSE_Instruction(PREFIX_SCALAR_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_RSQRT,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															AVX_BASIC_PARAM_LIST);	

	//************************************************************************
	// SIMD float reciprocal

	static const Ceng::UINT8 OPCODE_RCP = 0x53;

	const X86::SSE_Instruction RCPPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_RCP,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VRCPPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_RCP,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);	

	const X86::SSE_Instruction RCPSS = SSE_Instruction(PREFIX_SCALAR_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_RCP,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VRCPSS = SSE_Instruction(PREFIX_SCALAR_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_RCP,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															AVX_BASIC_PARAM_LIST);	

	//************************************************************************
	// SSE: float compare equal

	static const Ceng::UINT8 OPCODE_COMPARE_EQ = 0;

	const SSE_Compare CMPEQPS = SSE_Compare(PREFIX_PACKED_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_EQ,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPEQPS = SSE_Compare(PREFIX_PACKED_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_EQ,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												AVX_MAX_VEC_SIZE,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPEQPD = SSE_Compare(PREFIX_PACKED_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_EQ,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPEQPD = SSE_Compare(PREFIX_PACKED_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_EQ,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												AVX_MAX_VEC_SIZE,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPEQSS = SSE_Compare(PREFIX_SCALAR_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_EQ,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPEQSS = SSE_Compare(PREFIX_SCALAR_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_EQ,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPEQSD = SSE_Compare(PREFIX_SCALAR_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_EQ,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPEQSD = SSE_Compare(PREFIX_SCALAR_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_EQ,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	//************************************************************************
	// SSE: float compare less than

	static const Ceng::UINT8 OPCODE_COMPARE_LT = 1;

	const SSE_Compare CMPLTPS = SSE_Compare(PREFIX_PACKED_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_LT,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPLTPS = SSE_Compare(PREFIX_PACKED_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_LT,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												AVX_MAX_VEC_SIZE,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPLTPD = SSE_Compare(PREFIX_PACKED_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_LT,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPLTPD = SSE_Compare(PREFIX_PACKED_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_LT,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												AVX_MAX_VEC_SIZE,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPLTSS = SSE_Compare(PREFIX_SCALAR_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_LT,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPLTSS = SSE_Compare(PREFIX_SCALAR_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_LT,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPLTSD = SSE_Compare(PREFIX_SCALAR_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_LT,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPLTSD = SSE_Compare(PREFIX_SCALAR_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_LT,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	//************************************************************************
	// SSE: float compare less or equal

	static const Ceng::UINT8 OPCODE_COMPARE_LE = 2;

	const SSE_Compare CMPLEPS = SSE_Compare(PREFIX_PACKED_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_LE,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPLEPS = SSE_Compare(PREFIX_PACKED_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_LE,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												AVX_MAX_VEC_SIZE,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPLEPD = SSE_Compare(PREFIX_PACKED_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_LE,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPLEPD = SSE_Compare(PREFIX_PACKED_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_LE,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												AVX_MAX_VEC_SIZE,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPLESS = SSE_Compare(PREFIX_SCALAR_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_LE,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPLESS = SSE_Compare(PREFIX_SCALAR_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_LE,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPLESD = SSE_Compare(PREFIX_SCALAR_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_LE,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPLESD = SSE_Compare(PREFIX_SCALAR_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_LE,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	//************************************************************************
	// SSE: float compare for unordered

	static const Ceng::UINT8 OPCODE_COMPARE_UNORD = 3;

	const SSE_Compare CMPUNORDPS = SSE_Compare(PREFIX_PACKED_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_UNORD,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPUNORDPS = SSE_Compare(PREFIX_PACKED_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_UNORD,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												AVX_MAX_VEC_SIZE,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPUNORDPD = SSE_Compare(PREFIX_PACKED_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_UNORD,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPUNORDPD = SSE_Compare(PREFIX_PACKED_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_UNORD,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												AVX_MAX_VEC_SIZE,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPUNORDSS = SSE_Compare(PREFIX_SCALAR_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_UNORD,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPUNORDSS = SSE_Compare(PREFIX_SCALAR_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_UNORD,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPUNORDSD = SSE_Compare(PREFIX_SCALAR_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_UNORD,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPUNORDSD = SSE_Compare(PREFIX_SCALAR_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_UNORD,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	//************************************************************************
	// SSE: float compare not equal

	static const Ceng::UINT8 OPCODE_COMPARE_NEQ = 4;

	const SSE_Compare CMPNEQPS = SSE_Compare(PREFIX_PACKED_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NEQ,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPNEQPS = SSE_Compare(PREFIX_PACKED_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NEQ,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												AVX_MAX_VEC_SIZE,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPNEQPD = SSE_Compare(PREFIX_PACKED_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NEQ,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPNEQPD = SSE_Compare(PREFIX_PACKED_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NEQ,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												AVX_MAX_VEC_SIZE,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPNEQSS = SSE_Compare(PREFIX_SCALAR_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NEQ,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPNEQSS = SSE_Compare(PREFIX_SCALAR_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NEQ,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPNEQSD = SSE_Compare(PREFIX_SCALAR_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NEQ,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPNEQSD = SSE_Compare(PREFIX_SCALAR_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NEQ,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	//************************************************************************
	// SSE: float compare not less than

	static const Ceng::UINT8 OPCODE_COMPARE_NLT = 5;

	const SSE_Compare CMPNLTPS = SSE_Compare(PREFIX_PACKED_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NLT,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPNLTPS = SSE_Compare(PREFIX_PACKED_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NLT,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												AVX_MAX_VEC_SIZE,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPNLTPD = SSE_Compare(PREFIX_PACKED_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NLT,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPNLTPD = SSE_Compare(PREFIX_PACKED_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NLT,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												AVX_MAX_VEC_SIZE,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPNLTSS = SSE_Compare(PREFIX_SCALAR_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NLT,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPNLTSS = SSE_Compare(PREFIX_SCALAR_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NLT,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPNLTSD = SSE_Compare(PREFIX_SCALAR_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NLT,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPNLTSD = SSE_Compare(PREFIX_SCALAR_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NLT,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	//************************************************************************
	// SSE: float compare not less equal

	static const Ceng::UINT8 OPCODE_COMPARE_NLE = 6;

	const SSE_Compare CMPNLEPS = SSE_Compare(PREFIX_PACKED_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NLE,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPNLEPS = SSE_Compare(PREFIX_PACKED_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NLE,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												AVX_MAX_VEC_SIZE,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPNLEPD = SSE_Compare(PREFIX_PACKED_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NLE,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPNLEPD = SSE_Compare(PREFIX_PACKED_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NLE,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												AVX_MAX_VEC_SIZE,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPNLESS = SSE_Compare(PREFIX_SCALAR_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NLE,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPNLESS = SSE_Compare(PREFIX_SCALAR_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NLE,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPNLESD = SSE_Compare(PREFIX_SCALAR_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NLE,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPNLESD = SSE_Compare(PREFIX_SCALAR_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_NLE,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	//************************************************************************
	// SSE: float compare not less equal

	static const Ceng::UINT8 OPCODE_COMPARE_ORD = 7;

	const SSE_Compare CMPORDPS = SSE_Compare(PREFIX_PACKED_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_ORD,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPORDPS = SSE_Compare(PREFIX_PACKED_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_ORD,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												AVX_MAX_VEC_SIZE,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPORDPD = SSE_Compare(PREFIX_PACKED_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_ORD,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPORDPD = SSE_Compare(PREFIX_PACKED_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_ORD,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												AVX_MAX_VEC_SIZE,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPORDSS = SSE_Compare(PREFIX_SCALAR_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_ORD,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPORDSS = SSE_Compare(PREFIX_SCALAR_FLOAT,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_ORD,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	const SSE_Compare CMPORDSD = SSE_Compare(PREFIX_SCALAR_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_ORD,
												SIMD_ENCODING::LEGACY,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);

	const SSE_Compare VCMPORDSD = SSE_Compare(PREFIX_SCALAR_DOUBLE,
												OPCODE_ESCAPE::BYTE_0F,
												OPCODE_COMPARE_ORD,
												SIMD_ENCODING::VEX,
												OPERAND_SIZE::XMMWORD,
												OPERAND_SIZE::XMMWORD,
												VEX_W_FUNCTION::ZERO,
												PARAM_LIST::REG_REG_REG | PARAM_LIST::REG_REG_MEM);

	//************************************************************************
	// SSE: float scalar compare

	static const Ceng::UINT8 OPCODE_COMI = 0x2f;

	// NOTE: These don't have packed versions, so use packed prefix

	const X86::SSE_Instruction COMISS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_COMI,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VCOMISS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_COMI,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);	

	const X86::SSE_Instruction COMISD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_COMI,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VCOMISD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_COMI,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);	

	//************************************************************************
	// SIMD scalar compare unordered

	static const Ceng::UINT8 OPCODE_UCOMI = 0x2e;

	const X86::SSE_Instruction UCOMISS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_UCOMI,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VUCOMISS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_UCOMI,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);	

	const X86::SSE_Instruction UCOMISD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_UCOMI,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															SSE_BASIC_PARAM_LIST);

	const X86::SSE_Instruction VUCOMISD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_UCOMI,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															PARAM_LIST::REG_REG | PARAM_LIST::REG_MEM);	

	//************************************************************************
	// SSE : Shuffle

	static const Ceng::UINT8 OPCODE_SHUFFLE = 0xc6;

	const X86::SSE_Instruction SHUFPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_SHUFFLE,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															PARAM_LIST::REG_REG_IMM | PARAM_LIST::REG_MEM_IMM);

	const X86::SSE_Instruction VSHUFPS = SSE_Instruction(PREFIX_PACKED_FLOAT,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_SHUFFLE,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															PARAM_LIST::REG_REG_REG_IMM | PARAM_LIST::REG_REG_MEM_IMM);

	const X86::SSE_Instruction SHUFPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_SHUFFLE,0,
															SIMD_ENCODING::LEGACY,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															PARAM_LIST::REG_REG_IMM | PARAM_LIST::REG_MEM_IMM);

	const X86::SSE_Instruction VSHUFPD = SSE_Instruction(PREFIX_PACKED_DOUBLE,
															OPCODE_ESCAPE::BYTE_0F,
															OPCODE_SHUFFLE,0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															PARAM_LIST::REG_REG_REG_IMM | PARAM_LIST::REG_REG_MEM_IMM);

}