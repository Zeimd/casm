/*****************************************************************************
*
* x86-register-map.h
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#ifndef CASM_X86_REGISTER_MAP_H
#define CASM_X86_REGISTER_MAP_H

#include "keyword-map.h"
#include "x86-register-op.h"

#include <memory>

#include <string>
#include <unordered_map>

namespace X86
{
	class RegisterMap : public Casm::KeywordMap
	{
	protected:

		static std::shared_ptr<RegisterMap> instance;

		std::unordered_map<std::string,const RegisterOperand*> registerMap;

		RegisterMap();

	public:

		virtual ~RegisterMap();

		static std::shared_ptr<RegisterMap> GetInstance();

		virtual Casm::ParserToken* FindKeyword(const Ceng::String &name) const;

		const RegisterOperand* FindRegister(const Ceng::String &name) const;

	protected:

		void BuildMap();

	};
}

#endif