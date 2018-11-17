/*****************************************************************************
*
* opcode-prefix.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_OPCODE_PREFIX_H
#define X86_OPCODE_PREFIX_H

#include <vector>

#include <datatypes/basic-types.h>
#include <datatypes/return-val.h>

#include "enums/x86-prefix-bytes.h"

namespace X86
{
	class BuildParams;

	class InstructionPrefix
	{
	public:
		Ceng::UINT8 byte[4];

		Ceng::UINT32 flags;

		InstructionPrefix();

		InstructionPrefix(const PREFIX_BYTE::value group1,const PREFIX_BYTE::value group2,
			const PREFIX_BYTE::value group3,const PREFIX_BYTE::value group4);
	
		const Ceng::CRESULT Encode(BuildParams *params,std::vector<Ceng::UINT8> &destBuffer) const;
	};

}

#endif