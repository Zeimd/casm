/*****************************************************************************
*
* x86-register-map.cpp
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#include<ceng/datatypes/ce-string.h>

#include "x86-register-map.h"

#include "parser-register.h"

#include "x86-regs-alu.h"
#include "x86-regs-simd.h"

using namespace X86;

std::shared_ptr<RegisterMap> RegisterMap::instance = nullptr;

RegisterMap::RegisterMap()
{
}

RegisterMap::~RegisterMap()
{
}

const RegisterOperand* RegisterMap::FindRegister(const Ceng::String &name) const
{
	auto iter = registerMap.find(std::string(name.ToCString()));

	if (iter == registerMap.end())
	{
		return nullptr;
	}

	auto pair = *iter;

	const RegisterOperand *temp = pair.second;

	return temp;
}

/*
Casm::ParserToken* RegisterMap::FindKeyword(const Ceng::String &name) const
{
	auto *temp = FindRegister(name);

	if (temp == nullptr)
	{
		return nullptr;
	}	

	return new Casm::ParserRegister(temp,Casm::TokenData());
}
*/

std::shared_ptr<RegisterMap> RegisterMap::GetInstance()
{
	if (instance == nullptr)
	{
		instance = std::shared_ptr<RegisterMap>(new RegisterMap());

		instance->BuildMap();
	}

	return instance;
}

void RegisterMap::BuildMap()
{
	registerMap.emplace("al",&X86::AL);
	registerMap.emplace("ah",&X86::AH);
	
	registerMap.emplace("bl",&X86::BL);
	registerMap.emplace("bh",&X86::BH);

	registerMap.emplace("cl",&X86::CL);
	registerMap.emplace("ch",&X86::CH);

	registerMap.emplace("dl",&X86::DL);
	registerMap.emplace("dh",&X86::DH);

	registerMap.emplace("bpl",&X86::BPL);
	registerMap.emplace("spl",&X86::SPL);
	registerMap.emplace("sil",&X86::SIL);
	registerMap.emplace("dil",&X86::DIL);

	registerMap.emplace("r8l",&X86::R8L);
	registerMap.emplace("r9l",&X86::R9L);
	registerMap.emplace("r10l",&X86::R10L);
	registerMap.emplace("r11l",&X86::R11L);
	registerMap.emplace("r12l",&X86::R12L);
	registerMap.emplace("r13l",&X86::R13L);
	registerMap.emplace("r14l",&X86::R14L);
	registerMap.emplace("r15l",&X86::R15L);

	registerMap.emplace("ax",&X86::AX);
	registerMap.emplace("bx",&X86::BX);
	registerMap.emplace("cx",&X86::CX);
	registerMap.emplace("dx",&X86::DX);
	
	registerMap.emplace("sp",&X86::SP);
	registerMap.emplace("bp",&X86::BP);
	registerMap.emplace("si",&X86::SI);
	registerMap.emplace("di",&X86::DI);

	registerMap.emplace("r8w",&X86::R8W);
	registerMap.emplace("r9w",&X86::R9W);
	registerMap.emplace("r10w",&X86::R10W);
	registerMap.emplace("r11w",&X86::R11W);
	registerMap.emplace("r12w",&X86::R12W);
	registerMap.emplace("r13w",&X86::R13W);
	registerMap.emplace("r14w",&X86::R14W);
	registerMap.emplace("r15w",&X86::R15W);

	registerMap.emplace("eax",&X86::EAX);
	registerMap.emplace("ebx",&X86::EBX);
	registerMap.emplace("ecx",&X86::ECX);
	registerMap.emplace("edx",&X86::EDX);
	
	registerMap.emplace("esp",&X86::ESP);
	registerMap.emplace("ebp",&X86::EBP);
	registerMap.emplace("esi",&X86::ESI);
	registerMap.emplace("edi",&X86::EDI);

	registerMap.emplace("r8d",&X86::R8D);
	registerMap.emplace("r9d",&X86::R9D);
	registerMap.emplace("r10d",&X86::R10D);
	registerMap.emplace("r11d",&X86::R11D);
	registerMap.emplace("r12d",&X86::R12D);
	registerMap.emplace("r13d",&X86::R13D);
	registerMap.emplace("r14d",&X86::R14D);
	registerMap.emplace("r15d",&X86::R15D);

	registerMap.emplace("rax",&X86::RAX);
	registerMap.emplace("rbx",&X86::RBX);
	registerMap.emplace("rcx",&X86::RCX);
	registerMap.emplace("rdx",&X86::RDX);
	
	registerMap.emplace("rsp",&X86::RSP);
	registerMap.emplace("rbp",&X86::RBP);
	registerMap.emplace("rsi",&X86::RSI);
	registerMap.emplace("rdi",&X86::RDI);

	registerMap.emplace("r8",&X86::R8);
	registerMap.emplace("r9",&X86::R9);
	registerMap.emplace("r10",&X86::R10);
	registerMap.emplace("r11",&X86::R11);
	registerMap.emplace("r12",&X86::R12);
	registerMap.emplace("r13",&X86::R13);
	registerMap.emplace("r14",&X86::R14);
	registerMap.emplace("r15",&X86::R15);

	registerMap.emplace("xmm0",&X86::XMM0);
	registerMap.emplace("xmm1",&X86::XMM1);
	registerMap.emplace("xmm2",&X86::XMM2);
	registerMap.emplace("xmm3",&X86::XMM3);
	registerMap.emplace("xmm4",&X86::XMM4);
	registerMap.emplace("xmm5",&X86::XMM5);
	registerMap.emplace("xmm6",&X86::XMM6);
	registerMap.emplace("xmm7",&X86::XMM7);

	registerMap.emplace("rip",&X86::RIP);

	registerMap.emplace("xmm8",&X86::XMM8);
	registerMap.emplace("xmm9",&X86::XMM9);
	registerMap.emplace("xmm10",&X86::XMM10);
	registerMap.emplace("xmm11",&X86::XMM11);
	registerMap.emplace("xmm12",&X86::XMM12);
	registerMap.emplace("xmm13",&X86::XMM13);
	registerMap.emplace("xmm14",&X86::XMM14);
	registerMap.emplace("xmm15",&X86::XMM15);

	registerMap.emplace("ymm0",&X86::YMM0);
	registerMap.emplace("ymm1",&X86::YMM1);
	registerMap.emplace("ymm2",&X86::YMM2);
	registerMap.emplace("ymm3",&X86::YMM3);
	registerMap.emplace("ymm4",&X86::YMM4);
	registerMap.emplace("ymm5",&X86::YMM5);
	registerMap.emplace("ymm6",&X86::YMM6);
	registerMap.emplace("ymm7",&X86::YMM7);

	registerMap.emplace("ymm8",&X86::YMM8);
	registerMap.emplace("ymm9",&X86::YMM9);
	registerMap.emplace("ymm10",&X86::YMM10);
	registerMap.emplace("ymm11",&X86::YMM11);
	registerMap.emplace("ymm12",&X86::YMM12);
	registerMap.emplace("ymm13",&X86::YMM13);
	registerMap.emplace("ymm14",&X86::YMM14);
	registerMap.emplace("ymm15",&X86::YMM15);

}



