/*****************************************************************************
*
* x86-vex-prefix.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_VEX_PREFIX_H
#define X86_VEX_PREFIX_H

#include "enums/x86-opcode-escape.h"
#include "enums/x86-prefix-bytes.h"

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/return-val.h>

#include <vector>

namespace X86
{
	class BuildParams;

	class VEX_Prefix
	{
	protected:
		Ceng::UINT32 bytes;

		// VEX prefix encoding:
		// 2 byte form:
		//     byte 1 = 11000101b
		//     byte 2
		//         7   - NOT(REX.R)
		//         6:3 - VVVV : register in 1's complement (1111b = unused)
		//         2   - L    : vector length (0 = scalar/128, 1 = 256)
		//         1:0 - PP   : Legacy SIMD instruction prefix
		//     
		// 3 byte form:
		//      byte 1 = 11000100b
		//      byte 2
		//          7   - not(REX.R)
		//          6   - not(REX.X)
		//          5   - not(REX.B)
		//          4:0 - m-mmmm : opcode bytes
		//      byte 3
		//          7   - not(REX.W)
		//          6:3 - VVVV
		//          2   - L
		//          1:0 - PP
		Ceng::UINT8 vex[3];

		static const Ceng::UINT8 TWO_BYTE_HEADER = 0xc5;
		static const Ceng::UINT8 THREE_BYTE_HEADER = 0xc4;

		OPCODE_ESCAPE::value escapeCode;
		

	public:

		// For 3 byte VEX prefix: legacy SIMD instruction opcode escape
		// NOTE: 2 byte VEX prefix has implicit 0x0F.
		enum VEX_M_MMMMM
		{
			BYTE_0F = 1,
			BYTES_0F_38 = 2,
			BYTES_0F_3A = 3,
		};

		// VEX encoded legacy SIMD instruction opcode prefix
		enum VEX_PP
		{
			NONE = 0,
			BYTE_66 = 1,
			BYTE_F3 = 2,
			BYTE_F2 = 3,

			FORCE_32B = 1 << 30,
		};

		enum VEX_BYTES
		{
			TWO_BYTE = 2 ,
			THREE_BYTE = 3 ,

			FORCE_32B = 1 << 30,
		};

		enum VECTOR_SIZE
		{
			// 16 bytes, 128 bits
			XMM = 0 ,

			// 32 bytes, 256 bits
			YMM = 1 ,

			FORCE_32B = 1 << 30,
		};

		VEX_Prefix();
		
		VEX_Prefix(const VEX_BYTES bytes);

		const Ceng::CRESULT Set_VVVV(const Ceng::INT32 index);

		const Ceng::CRESULT SetWideSize();

		const Ceng::CRESULT SetRegField(const Ceng::INT32 index);
		const Ceng::CRESULT SetIndexReg(const Ceng::INT32 index);
		const Ceng::CRESULT SetBaseReg(const Ceng::INT32 index);

		const Ceng::CRESULT SetVectorSize(const VECTOR_SIZE size);
		
		const Ceng::CRESULT SetPrefixCode(const PREFIX_BYTE::value prefixCode);

		const Ceng::CRESULT SetEscapeCode(const OPCODE_ESCAPE::value escapeCode);

		const Ceng::CRESULT Encode(BuildParams *params,std::vector<Ceng::UINT8> &destBuffer) const;

		void SetBytes(const VEX_BYTES bytes);

	protected:

		

		/**
		 * Move from 2-byte to 3-byte vex.
		 */
		void Promote();

	};
}

#endif