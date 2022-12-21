/*****************************************************************************
*
* x86-opcode-map.h
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#ifndef CASM_X86_OPCODE_MAP_H
#define CASM_X86_OPCODE_MAP_H

/*
#include "keyword-map.h"
#include "x86-instruction.h"

#include <memory>

#include <ceng/datatypes/ce-string.h>

#include <string>
#include <unordered_map>

namespace X86
{
	class OpcodeMap : public Casm::KeywordMap
	{
	protected:

		static std::shared_ptr<OpcodeMap> instance;

		std::unordered_map<std::string,const Instruction*> opcodeMap;

		OpcodeMap();

	public:
		
		virtual ~OpcodeMap();

		//virtual Casm::ParserToken* FindKeyword(const Ceng::String &name) const;
		
		static std::shared_ptr<OpcodeMap> GetInstance();

		const X86::Instruction* FindOpcode(const Ceng::String &name) const;

	protected:

		void BuildMap();
	};
}
*/


#endif