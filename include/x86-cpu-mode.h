/*****************************************************************************
*
* x86-cpu-mode.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_CPU_MODE_H
#define X86_CPU_MODE_H

#include <datatypes/basic-types.h>
#include <datatypes/return-val.h>

#include "enums/address-size.h"

#include "enums/x86-cpu-modes.h"

#include "enums/x86-operand-sizes.h"

namespace X86
{
	class CPU_Mode
	{
	public:
		const CPU_MODE::value cpuMode;

		const Casm::ADDRESS_SIZE::value addressSize;
		const OPERAND_SIZE::value defaultOpSize;

		CPU_Mode(const CPU_MODE::value cpuMode,const Casm::ADDRESS_SIZE::value addressSize,
					const OPERAND_SIZE::value defaultOpSize);
	};

	extern const CPU_Mode REAL_MODE;

	extern const CPU_Mode PROTECTED_MODE;

	extern const CPU_Mode LONG_MODE;
}

#endif