/*****************************************************************************
*
* encode-data.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_ENCODE_DATA_H
#define X86_ENCODE_DATA_H

#include <datatypes/basic-types.h>

#include "enums/x86-operand-place.h"
#include "enums/x86-operand-sizes.h"

#include "x86-modrm.h"
#include "x86-sib.h"
#include "x86-rex-byte.h"
#include "x86-vex-prefix.h"

namespace X86
{
	class BuildParams;
	class InstructionPrefix;

	class EncodeData
	{
	public:

		OPCODE_ESCAPE::value escapeCode;

		/**
		 * Optional prefix bytes.
		 */
		Ceng::UINT32 optionPrefix;

		/**
		 * Compulsory prefix byte.
		 */
		PREFIX_BYTE::value opcodePrefix;

		Ceng::UINT8 opcode;

		Ceng::BOOL useVEX;

		VEX_Prefix vex;

		REX_Byte rex;

		ModRM_Byte modRM;

		SIB_Byte sib;

		Ceng::BOOL hasImmediate;

		OPERAND_SIZE::value immEncoding;
		Ceng::INT64 immediate;

		Ceng::BOOL hasDisplacement;

		OPERAND_SIZE::value dispEncoding;
		Ceng::INT64 displacement;

		OPERAND_PLACE::value operandPlace[4];

	public:
		EncodeData();

		const Ceng::CRESULT EncodeInstruction(BuildParams *params,std::vector<Ceng::UINT8> &destBuffer,
												InstructionPrefix *prefix) const;

	protected:
		const Ceng::CRESULT EncodeDisplacement(BuildParams *params,std::vector<Ceng::UINT8> &destBuffer,
												   const OPERAND_SIZE::value encodeSize,
												   const Ceng::INT64 displacement) const;

		const Ceng::CRESULT EncodeImmediate(BuildParams *params,std::vector<Ceng::UINT8> &destBuffer,
												const OPERAND_SIZE::value encodeSize,
												const Ceng::INT64 immediate) const;

		const Ceng::CRESULT WriteEscapeBytes(BuildParams *params,const OPCODE_ESCAPE::value escapeBytes,
												 std::vector<Ceng::UINT8> &destBuffer) const;
	};
}

#endif