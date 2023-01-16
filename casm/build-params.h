/*****************************************************************************
*
* build-params.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_BUILD_PARAMS_H
#define X86_BUILD_PARAMS_H


#include "x86-cpu-mode.h"

#include "enums/reference-type.h"

#include "enums/x86-priviledge-levels.h"

#include <memory>

namespace Casm
{
	class Section;
	class CodeElement;
	class RelocationData;
}

namespace X86
{

	class BuildParams
	{
	public:

		/**
		 * The function the instruction is intended for.
		 */
		Casm::Section *section;

		/**
		 * Code element this instruction is intended for.
		 */
		Casm::CodeElement *codeElement;

		/**
		 * Which level instructions are allowed.
		 */
		PRIVILEDGE_LEVEL::value priviledgeLevel;

		const CPU_Mode *mode;

		/**
		 * Offset of memory operand displacement that must be adjusted
		 * when data segment is relocationed.
		 */
		Ceng::INT64 out_dispOffset;

		OPERAND_SIZE::value out_dispSize;

		/**
		 * Offset of immediate operand that must be adjusted when
		 * data segment is relocationed.
		 */
		Ceng::INT64 out_immOffset;

		X86::OPERAND_SIZE::value out_immSize;

		/**
		 * What type of reference is created when a symbol is given
		 * as immediate operand.
		 */
		Casm::REFERENCE_TYPE::value imm_symbolRefType;

		Ceng::INT64 ipDelta;

		std::shared_ptr<Casm::RelocationData> memRef;
		std::shared_ptr<Casm::RelocationData> immRef;

		void Clean()
		{
			imm_symbolRefType = Casm::REFERENCE_TYPE::ADDRESS;

			memRef = nullptr;
			immRef = nullptr;
		}
	};

}

#endif