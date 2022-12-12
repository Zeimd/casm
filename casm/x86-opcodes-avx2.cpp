/*****************************************************************************
*
* x86-opcodes-avx2.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-opcodes-avx2.h"

#include "../include/enums/x86-opcode-escape.h"
#include "../include/enums/x86-prefix-bytes.h"
#include "../include/enums/x86-param-list.h"
#include "../include/enums/x86-vex-w.h"

namespace X86
{
	//*****************************************************************************************
	// AVX2 : Integer masked move

	static const Ceng::UINT8 OPCODE_VPMASKMOV_REG = 0x8c;
	static const Ceng::UINT8 OPCODE_VPMASKMOV_MEM = 0x8e;

	const X86::SSE_Instruction VPMASKMOVD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_VPMASKMOV_REG,
															OPCODE_VPMASKMOV_MEM,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_MEM |
															PARAM_LIST::MEM_REG_REG);

	const X86::SSE_Instruction VPMASKMOVQ = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_VPMASKMOV_REG,
															OPCODE_VPMASKMOV_MEM,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_MEM |
															PARAM_LIST::MEM_REG_REG);

	//***********************************************************************************
	// AVX 2 : Variable shift

	static const Ceng::UINT8 OPCODE_VPSRLV = 0x45;
	static const Ceng::UINT8 OPCODE_VPSRAV = 0x46;
	static const Ceng::UINT8 OPCODE_VPSLLV = 0x47;

	const X86::SSE_Instruction VPSLLVD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_VPSLLV,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	const X86::SSE_Instruction VPSLLVQ = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_VPSLLV,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	const X86::SSE_Instruction VPSRAVD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_VPSLLV,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	const X86::SSE_Instruction VPSRLVD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_VPSRLV,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	const X86::SSE_Instruction VPSRLVQ = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_VPSRLV,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	//***********************************************************************************
	// AVX2 : Blend int32

	static const Ceng::UINT8 OPCODE_VBLENDD = 0x02;

	const X86::SSE_Instruction VBLENDD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_VBLENDD,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															PARAM_LIST::REG_REG_MEM_IMM |
															PARAM_LIST::REG_REG_REG_IMM);

	//************************************************************************************
	// AVX2 : Permutation

	static const Ceng::UINT8 OPCODE_VPERM_PS = 0x16;

	const X86::SSE_Instruction VPERMPS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_VPERM_PS,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::YMMWORD,
															AVX_MAX_VEC_SIZE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	static const Ceng::UINT8 OPCODE_VPERM_PD = 0x01;

	const X86::SSE_Instruction VPERMPD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_VPERM_PD,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::YMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_IMM |
															PARAM_LIST::REG_MEM_IMM);

	static const Ceng::UINT8 OPCODE_VPERM_D = 0x36;

	const X86::SSE_Instruction VPERMD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_VPERM_D,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::YMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	static const Ceng::UINT8 OPCODE_VPERM_Q = 0x00;

	const X86::SSE_Instruction VPERMQ = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_VPERM_Q,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::YMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_IMM |
															PARAM_LIST::REG_MEM_IMM);

	static const Ceng::UINT8 OPCODE_VPERM_I128 = 0x46;

	const X86::SSE_Instruction VPERM2I128 = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_3A,
															OPCODE_VPERM_I128,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::YMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG_IMM |
															PARAM_LIST::REG_REG_MEM_IMM);

	//******************************************************************************************
	// AVX 2 : Fused MADD

	static const Ceng::UINT8 OPCODE_FMADD_132 = 0x98;
	static const Ceng::UINT8 OPCODE_FMADD_213 = 0xa8;
	static const Ceng::UINT8 OPCODE_FMADD_231 = 0xb8;

	const X86::SSE_Instruction VFMADD132PS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMADD_132,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMADD213PS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMADD_213,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMADD231PS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMADD_231,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	const X86::SSE_Instruction VFMADD132PD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMADD_132,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMADD213PD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMADD_213,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMADD231PD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMADD_231,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	static const Ceng::UINT8 OPCODE_FMADD_132_SCALAR = 0x99;
	static const Ceng::UINT8 OPCODE_FMADD_213_SCALAR = 0xa9;
	static const Ceng::UINT8 OPCODE_FMADD_231_SCALAR = 0xb9;

	const X86::SSE_Instruction VFMADD132SS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMADD_132_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMADD213SS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMADD_213_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMADD231SS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMADD_231_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	const X86::SSE_Instruction VFMADD132SD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMADD_132_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMADD213SD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMADD_213_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMADD231SD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMADD_231_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	//******************************************************************************************
	// AVX 2 : Fused NMADD

	static const Ceng::UINT8 OPCODE_FNMADD_132 = 0x9c;
	static const Ceng::UINT8 OPCODE_FNMADD_213 = 0xac;
	static const Ceng::UINT8 OPCODE_FNMADD_231 = 0xbc;

	const X86::SSE_Instruction VFNMADD132PS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMADD_132,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFNMADD213PS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMADD_213,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFNMADD231PS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMADD_231,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	const X86::SSE_Instruction VFNMADD132PD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMADD_132,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFNMADD213PD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMADD_213,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFNMADD231PD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMADD_231,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	static const Ceng::UINT8 OPCODE_FNMADD_132_SCALAR = 0x9d;
	static const Ceng::UINT8 OPCODE_FNMADD_213_SCALAR = 0xad;
	static const Ceng::UINT8 OPCODE_FNMADD_231_SCALAR = 0xbd;

	const X86::SSE_Instruction VFNMADD132SS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMADD_132_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFNMADD213SS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMADD_213_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFNMADD231SS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMADD_231_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	const X86::SSE_Instruction VFNMADD132SD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMADD_132_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFNMADD213SD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMADD_213_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFNMADD231SD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMADD_231_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	//******************************************************************************************
	// AVX 2 : Fused MSUB

	static const Ceng::UINT8 OPCODE_FMSUB_132 = 0x9a;
	static const Ceng::UINT8 OPCODE_FMSUB_213 = 0xaa;
	static const Ceng::UINT8 OPCODE_FMSUB_231 = 0xba;

	const X86::SSE_Instruction VFMSUB132PS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMSUB_132,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMSUB213PS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMSUB_213,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMSUB231PS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMSUB_231,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	const X86::SSE_Instruction VFMSUB132PD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMSUB_132,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMSUB213PD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMSUB_213,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMSUB231PD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMSUB_231,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	static const Ceng::UINT8 OPCODE_FMSUB_132_SCALAR = 0x9b;
	static const Ceng::UINT8 OPCODE_FMSUB_213_SCALAR = 0xab;
	static const Ceng::UINT8 OPCODE_FMSUB_231_SCALAR = 0xbb;

	const X86::SSE_Instruction VFMSUB132SS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMSUB_132_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMSUB213SS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMSUB_213_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMSUB231SS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMSUB_231_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	const X86::SSE_Instruction VFMSUB132SD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMSUB_132_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMSUB213SD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMSUB_213_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMSUB231SD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMSUB_231_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	//******************************************************************************************
	// AVX 2 : Fused MNSUB

	static const Ceng::UINT8 OPCODE_FNMSUB_132 = 0x9e;
	static const Ceng::UINT8 OPCODE_FNMSUB_213 = 0xae;
	static const Ceng::UINT8 OPCODE_FNMSUB_231 = 0xbe;

	const X86::SSE_Instruction VFNMSUB132PS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMSUB_132,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFNMSUB213PS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMSUB_213,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFNMSUB231PS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMSUB_231,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	const X86::SSE_Instruction VFNMSUB132PD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMSUB_132,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFNMSUB213PD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMSUB_213,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFNMSUB231PD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMSUB_231,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	static const Ceng::UINT8 OPCODE_FNMSUB_132_SCALAR = 0x9f;
	static const Ceng::UINT8 OPCODE_FNMSUB_213_SCALAR = 0xaf;
	static const Ceng::UINT8 OPCODE_FNMSUB_231_SCALAR = 0xbf;

	const X86::SSE_Instruction VFNMSUB132SS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMSUB_132_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFNMSUB213SS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMSUB_213_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFNMSUB231SS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMSUB_231_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	const X86::SSE_Instruction VFNMSUB132SD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMSUB_132_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFNMSUB213SD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMSUB_213_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFNMSUB231SD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FNMSUB_231_SCALAR,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															OPERAND_SIZE::XMMWORD,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	//******************************************************************************************
	// AVX 2 : Fused MADDSUB
															
	static const Ceng::UINT8 OPCODE_FMADDSUB_132 = 0x96;
	static const Ceng::UINT8 OPCODE_FMADDSUB_213 = 0xa6;
	static const Ceng::UINT8 OPCODE_FMADDSUB_231 = 0xb6;

	const X86::SSE_Instruction VFMADDSUB132PS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMADDSUB_132,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMADDSUB213PS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMADDSUB_213,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMADDSUB231PS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMADDSUB_231,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	const X86::SSE_Instruction VFMADDSUB132PD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMADDSUB_132,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMADDSUB213PD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMADDSUB_213,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMADDSUB231PD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMADDSUB_231,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	//******************************************************************************************
	// AVX 2 : Fused MSUBADD
															
	static const Ceng::UINT8 OPCODE_FMSUBADD_132 = 0x97;
	static const Ceng::UINT8 OPCODE_FMSUBADD_213 = 0xa7;
	static const Ceng::UINT8 OPCODE_FMSUBADD_231 = 0xb7;

	const X86::SSE_Instruction VFMSUBADD132PS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMSUBADD_132,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMSUBADD213PS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMSUBADD_213,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMSUBADD231PS = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMSUBADD_231,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ZERO,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	const X86::SSE_Instruction VFMSUBADD132PD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMSUBADD_132,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMSUBADD213PD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMSUBADD_213,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);

	

	const X86::SSE_Instruction VFMSUBADD231PD = SSE_Instruction(PREFIX_BYTE::BYTE_66,
															OPCODE_ESCAPE::BYTES_0F_38,
															OPCODE_FMADDSUB_231,
															0,
															SIMD_ENCODING::VEX,
															OPERAND_SIZE::XMMWORD,
															AVX_MAX_VEC_SIZE,
															VEX_W_FUNCTION::ONE,
															PARAM_LIST::REG_REG_REG |
															PARAM_LIST::REG_REG_MEM);	
}