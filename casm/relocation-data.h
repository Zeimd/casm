/*****************************************************************************
*
* relocation-data.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_RELOCATION_DATA_H
#define X86_RELOCATION_DATA_H

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/return-val.h>
#include <ceng/datatypes/ce-string.h>

#include "enums/reference-type.h"
#include "enums/x86-operand-sizes.h"

#include "extern-symbol.h"

namespace X86
{
	class RelocationData
	{
	public:
		enum SECTION
		{
			CODE_SECTION = 0 ,
			DATA_SECTION = 1 ,

			EXTERNAL = 2,
			
			SECTION_FORCE_32B = 1 << 30 ,
		};

		/**
		 * Which section the relocation value is written to.
		 */
		SECTION writeSection;

		/**
		 * Which offset the relocation value is written to.
		 */
		Ceng::UINT64 writeOffset;

		/**
		 * Which section's base address is added.
		 */
		SECTION relocationSection;	

		OPERAND_SIZE::value offsetSize;

		Casm::REFERENCE_TYPE::value type;

		Ceng::String externName;

		Ceng::INT64 negativeExtra;

		RelocationData(const SECTION writeSection,const Ceng::UINT64 writeOffset,
						const SECTION relocationSection,
						const OPERAND_SIZE::value offsetSize,
						const Casm::REFERENCE_TYPE::value type,
						const Ceng::String externName,
						const Ceng::INT64 negativeExtra)
			: writeSection(writeSection),writeOffset(writeOffset),
			relocationSection(relocationSection),offsetSize(offsetSize),type(type),
			externName(externName),negativeExtra(negativeExtra)
		{

		}

		Ceng::CRESULT Relocate(const Ceng::UINT64 dataSectionBase,
								const Ceng::UINT64 codeSectionBase,
			Casm::ExternSymbol* externs, uint32_t externCount) const;
	};
}

#endif