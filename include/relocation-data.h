/*****************************************************************************
*
* relocation-data.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_RELOCATION_DATA_H
#define X86_RELOCATION_DATA_H

#include <datatypes/basic-types.h>
#include <datatypes/return-val.h>

#include "enums/reference-type.h"
#include "enums/x86-operand-sizes.h"

namespace X86
{
	class RelocationData
	{
	public:
		enum SECTION
		{
			CODE_SECTION = 0 ,
			DATA_SECTION = 1 ,
			
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

		Ceng::INT64 negativeExtra;

		RelocationData(const SECTION writeSection,const Ceng::UINT64 writeOffset,
						const SECTION relocationSection,
						const OPERAND_SIZE::value offsetSize,
						const Casm::REFERENCE_TYPE::value type,const Ceng::INT64 negativeExtra)
			: writeSection(writeSection),writeOffset(writeOffset),
			relocationSection(relocationSection),offsetSize(offsetSize),type(type),
			negativeExtra(negativeExtra)
		{

		}

		Ceng::CRESULT Relocate(const Ceng::UINT64 dataSectionBase,
								const Ceng::UINT64 codeSectionBase) const;
	};
}

#endif