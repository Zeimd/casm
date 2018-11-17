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

#include <datatypes/basic-types.h>
#include <datatypes/return-val.h>

#include <vector>

namespace X86
{
	class BuildParams;

	class VEX_Prefix
	{
	protected:
		Ceng::UINT32 bytes;
		Ceng::UINT8 vex[3];

		static const Ceng::UINT8 TWO_BYTE_HEADER = 0xc5;
		static const Ceng::UINT8 THREE_BYTE_HEADER = 0xc4;

		OPCODE_ESCAPE::value escapeCode;
		

	public:

		enum VEX_BYTES
		{
			TWO_BYTE = 2 ,
			THREE_BYTE = 3 ,
		};

		enum VECTOR_SIZE
		{
			XMM = 0 ,
			YMM = 1 ,
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