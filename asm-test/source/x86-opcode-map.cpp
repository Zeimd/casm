/*****************************************************************************
*
* x86-opcode-map.cpp
*
* By Jari Korkala 6/2014
*
*****************************************************************************/

#include "../include/x86-opcode-map.h"

#include "../include/x86-opcodes-alu.h"

#include "../include/x86-opcodes-sse.h"
#include "../include/x86-opcodes-sse2.h"
#include "../include/x86-opcodes-sse3.h"
#include "../include/x86-opcodes-sse41.h"
#include "../include/x86-opcodes-avx.h"
#include "../include/x86-opcodes-avx2.h"

#include "../include/parser-opcode.h"

#include <ceng/lib/timerlib.h>

/*

using namespace X86;

std::shared_ptr<OpcodeMap> OpcodeMap::instance = nullptr;

OpcodeMap::OpcodeMap()
{
}

OpcodeMap::~OpcodeMap()
{
}

const Instruction* OpcodeMap::FindOpcode(const Ceng::String &name) const
{
	auto iter = opcodeMap.find(std::string(name.ToCString()));

	if (iter == opcodeMap.end())
	{
		return nullptr;
	}

	const std::pair<const std::string,const Instruction*> pair = *iter;

	const Instruction *temp = pair.second;

	return temp;
}

Casm::ParserToken* OpcodeMap::FindKeyword(const Ceng::String &name) const
{
	auto *temp = FindOpcode(name);

	if (temp == nullptr)
	{
		return nullptr;
	}	

	return new Casm::ParserOpcode(temp,Casm::TokenData());
}

std::shared_ptr<OpcodeMap> OpcodeMap::GetInstance()
{
	if (instance == nullptr)
	{
		instance = std::shared_ptr<OpcodeMap>(new OpcodeMap());

		instance->BuildMap();
	}

	return instance;
}

void OpcodeMap::BuildMap()
{
	Ceng::FLOAT64 start = Ceng_HighPrecisionTimer();

	//*****************************************************
	// Subroutines

	opcodeMap.emplace("call",&X86::CALL);
	opcodeMap.emplace("ret",&X86::RET_NEAR);

	opcodeMap.emplace("leave",&X86::LEAVE);

	opcodeMap.emplace("iret",&X86::IRET);
	opcodeMap.emplace("iretd",&X86::IRETD);
	opcodeMap.emplace("iretq",&X86::IRETQ);

	//**********************************************
	// Conditional jumps

	opcodeMap.emplace("ja",&X86::JA);
	opcodeMap.emplace("jae",&X86::JAE);
	
	opcodeMap.emplace("jb",&X86::JB);
	opcodeMap.emplace("jbe",&X86::JBE);
	
	opcodeMap.emplace("jc",&X86::JC);
	
	opcodeMap.emplace("jcxz",&X86::JCXZ);
	opcodeMap.emplace("jecxz",&X86::JECXZ);
	opcodeMap.emplace("jrcxz",&X86::JRCXZ);

	opcodeMap.emplace("je",&X86::JE);
	
	opcodeMap.emplace("jg",&X86::JG);
	opcodeMap.emplace("jge",&X86::JGE);

	opcodeMap.emplace("jl",&X86::JL);
	opcodeMap.emplace("jle",&X86::JLE);

	opcodeMap.emplace("jna",&X86::JNA);
	opcodeMap.emplace("jnae",&X86::JNAE);

	opcodeMap.emplace("jnb",&X86::JNB);
	opcodeMap.emplace("jnbe",&X86::JNBE);

	opcodeMap.emplace("jnc",&X86::JNC);
	
	opcodeMap.emplace("jne",&X86::JNE);

	opcodeMap.emplace("jng",&X86::JNG);
	opcodeMap.emplace("jnge",&X86::JNGE);

	opcodeMap.emplace("jnl",&X86::JNL);
	opcodeMap.emplace("jnle",&X86::JNLE);

	opcodeMap.emplace("jno",&X86::JNO);
	opcodeMap.emplace("jnp",&X86::JNP);
	opcodeMap.emplace("jns",&X86::JNS);
	opcodeMap.emplace("jnz",&X86::JNZ);

	opcodeMap.emplace("jo",&X86::JO);
	opcodeMap.emplace("jp",&X86::JP);
	opcodeMap.emplace("jpe",&X86::JPE);
	opcodeMap.emplace("jpo",&X86::JPO);

	opcodeMap.emplace("js",&X86::JS);
	opcodeMap.emplace("jz",&X86::JZ);

	//**********************************************
	// SetCC

	opcodeMap.emplace("seta",&X86::SETA);
	opcodeMap.emplace("setae",&X86::SETAE);
	
	opcodeMap.emplace("setb",&X86::SETB);
	opcodeMap.emplace("setbe",&X86::SETBE);
	
	opcodeMap.emplace("setc",&X86::SETC);
	
	opcodeMap.emplace("sete",&X86::SETE);
	
	opcodeMap.emplace("setg",&X86::SETG);
	opcodeMap.emplace("setge",&X86::SETGE);

	opcodeMap.emplace("setl",&X86::SETL);
	opcodeMap.emplace("setle",&X86::SETLE);

	opcodeMap.emplace("setna",&X86::SETNA);
	opcodeMap.emplace("setnae",&X86::SETNAE);

	opcodeMap.emplace("setnb",&X86::SETNB);
	opcodeMap.emplace("setnbe",&X86::SETNBE);

	opcodeMap.emplace("setnc",&X86::SETNC);
	
	opcodeMap.emplace("setne",&X86::SETNE);

	opcodeMap.emplace("setng",&X86::SETNG);
	opcodeMap.emplace("setnge",&X86::SETNGE);

	opcodeMap.emplace("setnl",&X86::SETNL);
	opcodeMap.emplace("setnle",&X86::SETNLE);

	opcodeMap.emplace("setno",&X86::SETNO);
	opcodeMap.emplace("setnp",&X86::SETNP);
	opcodeMap.emplace("setns",&X86::SETNS);
	opcodeMap.emplace("setnz",&X86::SETNZ);

	opcodeMap.emplace("seto",&X86::SETO);
	opcodeMap.emplace("setp",&X86::SETP);
	opcodeMap.emplace("setpe",&X86::SETPE);
	opcodeMap.emplace("setpo",&X86::SETPO);

	opcodeMap.emplace("sets",&X86::SETS);
	opcodeMap.emplace("setz",&X86::SETZ);

	//*********************************************
	// Memory instructions

	opcodeMap.emplace("clflush",&X86::CLFLUSH);
	
	opcodeMap.emplace("lfence",&X86::LFENCE);
	opcodeMap.emplace("mfence",&X86::MFENCE);
	opcodeMap.emplace("sfence",&X86::SFENCE);

	opcodeMap.emplace("prefetcht0",&X86::PREFETCHT0);
	opcodeMap.emplace("prefetcht1",&X86::PREFETCHT1);
	opcodeMap.emplace("prefetcht2",&X86::PREFETCHT2);
	
	opcodeMap.emplace("prefetchnta",&X86::PREFETCHNTA);

	opcodeMap.emplace("prefetchw",&X86::PREFETCHW);

	//**********************************************
	// Uncategorized

	opcodeMap.emplace("xlatb",&X86::XLATB);

	//**********************************************
	// Debugging

	opcodeMap.emplace("ud2",&X86::UD2);

	//**********************************************
	// System instructions

	opcodeMap.emplace("sgdt",&X86::SGDT);
	opcodeMap.emplace("sidt",&X86::SIDT);

	opcodeMap.emplace("xsave",&X86::XSAVE);
	opcodeMap.emplace("xsave64",&X86::XSAVE64);

	opcodeMap.emplace("xsaveopt",&X86::XSAVEOPT);
	opcodeMap.emplace("xsaveopt64",&X86::XSAVEOPT64);

	opcodeMap.emplace("xrstor",&X86::XRSTOR);
	opcodeMap.emplace("xrstor64",&X86::XRSTOR64);

	opcodeMap.emplace("clts",&X86::CLTS);	
	
	opcodeMap.emplace("cpuid",&X86::CPUID);

	opcodeMap.emplace("halt",&X86::HALT);
	opcodeMap.emplace("pause",&X86::PAUSE);

	opcodeMap.emplace("invd",&X86::INVD);
	opcodeMap.emplace("wbinvd",&X86::WBINDV);

	opcodeMap.emplace("monitor",&X86::MONITOR);
	opcodeMap.emplace("mwait",&X86::MWAIT);

	opcodeMap.emplace("rsm",&X86::RSM);

	opcodeMap.emplace("syscall",&X86::SYSCALL);
	opcodeMap.emplace("sysret",&X86::SYSRET);

	opcodeMap.emplace("sysenter",&X86::SYSENTER);
	opcodeMap.emplace("sysexit",&X86::SYSEXIT);

	opcodeMap.emplace("wrmsr",&X86::WRMSR);
	opcodeMap.emplace("rdmsr",&X86::RDMSR);

	opcodeMap.emplace("rdpmc",&X86::RDPMC);
	
	opcodeMap.emplace("rdtsc",&X86::RDTSC);
	opcodeMap.emplace("rdtscp",&X86::RDTSCP);

	opcodeMap.emplace("xtest",&X86::XTEST);

	opcodeMap.emplace("xend",&X86::XEND);

	opcodeMap.emplace("xsetbv",&X86::XSETBV);
	opcodeMap.emplace("xgetbv",&X86::XGETBV);

	opcodeMap.emplace("swapgs",&X86::SWAPGS);

	//**********************************************
	// BCD arithmetic

	opcodeMap.emplace("aaa",&X86::AAA);
	opcodeMap.emplace("aad",&X86::AAD);
	opcodeMap.emplace("aam",&X86::AAM);
	opcodeMap.emplace("aas",&X86::AAS);
	opcodeMap.emplace("daa",&X86::DAA);
	opcodeMap.emplace("das",&X86::DAS);


	//********************************************
	// ALU

	opcodeMap.emplace("mov",&X86::MOV);

	opcodeMap.emplace("bswap",&X86::BSWAP);

	opcodeMap.emplace("xchg",&X86::XCHG);

	opcodeMap.emplace("inc",&X86::INC);
	opcodeMap.emplace("dec",&X86::DEC);

	opcodeMap.emplace("adc",&X86::ADC);
	opcodeMap.emplace("add",&X86::ADD);	
	
	opcodeMap.emplace("sub",&X86::SUB);
	opcodeMap.emplace("sbb",&X86::SBB);

	opcodeMap.emplace("cmp",&X86::CMP);

	opcodeMap.emplace("and",&X86::AND);
	opcodeMap.emplace("or",&X86::OR);
	opcodeMap.emplace("xor",&X86::XOR);

	opcodeMap.emplace("sal",&X86::SAL);
	opcodeMap.emplace("sar",&X86::SAR);

	opcodeMap.emplace("shl",&X86::SHL);
	opcodeMap.emplace("shr",&X86::SHR);

	opcodeMap.emplace("rcl",&X86::RCL);
	opcodeMap.emplace("rcr",&X86::RCR);

	opcodeMap.emplace("rol",&X86::ROL);
	opcodeMap.emplace("ror",&X86::ROR);

	opcodeMap.emplace("shld",&X86::SHLD);
	opcodeMap.emplace("shrd",&X86::SHRD);

	opcodeMap.emplace("div",&X86::DIV);
	opcodeMap.emplace("idiv",&X86::IDIV);
	opcodeMap.emplace("mul",&X86::MUL);

	opcodeMap.emplace("neg",&X86::NEG);
	opcodeMap.emplace("not",&X86::NOT);

	opcodeMap.emplace("bsf",&X86::BSF);
	opcodeMap.emplace("bsr",&X86::BSR);

	opcodeMap.emplace("bt",&X86::BT);
	opcodeMap.emplace("btc",&X86::BTC);
	opcodeMap.emplace("btr",&X86::BTR);
	opcodeMap.emplace("bts",&X86::BTS);

	opcodeMap.emplace("cbw",&X86::CBW);
	opcodeMap.emplace("cwde",&X86::CWDE);
	opcodeMap.emplace("cdqe",&X86::CDQE);

	opcodeMap.emplace("cwd",&X86::CWD);
	opcodeMap.emplace("cdq",&X86::CDQ);
	opcodeMap.emplace("cqo",&X86::CQO);	

	//********************************************
	// Stack instructions

	opcodeMap.emplace("popf",&X86::POPF);
	opcodeMap.emplace("popfd",&X86::POPFD);
	opcodeMap.emplace("popfq",&X86::POPFQ);

	opcodeMap.emplace("pushf",&X86::PUSHF);
	opcodeMap.emplace("pushfd",&X86::PUSHFD);
	opcodeMap.emplace("pushfq",&X86::PUSHFQ);

	opcodeMap.emplace("popa",&X86::POPA);
	opcodeMap.emplace("popad",&X86::POPAD);

	opcodeMap.emplace("pusha",&X86::PUSHA);
	opcodeMap.emplace("pushad",&X86::PUSHAD);

	//***************************************************
	// Flag manipulation

	opcodeMap.emplace("lahf",&X86::LAHF);
	opcodeMap.emplace("sahf",&X86::SAHF);

	opcodeMap.emplace("clc",&X86::CLC);
	opcodeMap.emplace("stc",&X86::STC);
	opcodeMap.emplace("cmc",&X86::CMC);

	opcodeMap.emplace("cld",&X86::CLD);
	opcodeMap.emplace("std",&X86::STD);

	opcodeMap.emplace("cli",&X86::CLI);
	opcodeMap.emplace("sti",&X86::STI);

	

	//******************************************************
	// Conditional moves

	opcodeMap.emplace("cmova",&X86::CMOVA);
	opcodeMap.emplace("cmovae",&X86::CMOVAE);
	
	opcodeMap.emplace("cmovb",&X86::CMOVB);
	opcodeMap.emplace("cmovbe",&X86::CMOVBE);
	
	opcodeMap.emplace("cmovc",&X86::CMOVC);
	
	opcodeMap.emplace("cmove",&X86::CMOVE);
	
	opcodeMap.emplace("cmovg",&X86::CMOVG);
	opcodeMap.emplace("cmovge",&X86::CMOVGE);
	
	opcodeMap.emplace("cmovl",&X86::CMOVL);
	opcodeMap.emplace("cmovle",&X86::CMOVLE);
	
	opcodeMap.emplace("cmovna",&X86::CMOVNA);
	opcodeMap.emplace("cmovnae",&X86::CMOVNAE);

	opcodeMap.emplace("cmovnb",&X86::CMOVNB);
	opcodeMap.emplace("cmovnbe",&X86::CMOVNBE);

	opcodeMap.emplace("cmovnc",&X86::CMOVNC);
	
	opcodeMap.emplace("cmovne",&X86::CMOVNE);

	opcodeMap.emplace("cmovng",&X86::CMOVNG);
	opcodeMap.emplace("cmovnge",&X86::CMOVNGE);

	opcodeMap.emplace("cmovnl",&X86::CMOVNL);
	opcodeMap.emplace("cmovnle",&X86::CMOVNLE);

	opcodeMap.emplace("cmovno",&X86::CMOVNO);
	opcodeMap.emplace("cmovnp",&X86::CMOVNP);
	opcodeMap.emplace("cmovns",&X86::CMOVNS);
	opcodeMap.emplace("cmovnz",&X86::CMOVNZ);

	opcodeMap.emplace("cmovo",&X86::CMOVO);
	opcodeMap.emplace("cmovp",&X86::CMOVP);
	opcodeMap.emplace("cmovpe",&X86::CMOVPE);
	opcodeMap.emplace("cmovpo",&X86::CMOVPO);

	opcodeMap.emplace("cmovs",&X86::CMOVS);
	opcodeMap.emplace("cmovz",&X86::CMOVZ);

	//***********************************************
	// FPU

	opcodeMap.emplace("fwait",&X86::FWAIT);

	//***********************************************
	// MMX

	opcodeMap.emplace("emms",&X86::EMMS);

	//******************************************
	// SSE

	opcodeMap.emplace("movaps",&X86::MOVAPS);
	opcodeMap.emplace("movups",&X86::MOVUPS);

	opcodeMap.emplace("movss",&X86::MOVSS);

	opcodeMap.emplace("movlps",&X86::MOVLPS);
	opcodeMap.emplace("movhps",&X86::MOVHPS);
	opcodeMap.emplace("movhlps",&X86::MOVHLPS);
	opcodeMap.emplace("movlhps",&X86::MOVLHPS);

	opcodeMap.emplace("movntps",&X86::MOVNTPS);
	
	opcodeMap.emplace("unpcklps",&X86::UNPCKLPS);
	opcodeMap.emplace("uncpkhps",&X86::UNPCKHPS);

	opcodeMap.emplace("shufps",&X86::SHUFPS);
	
	opcodeMap.emplace("andps",&X86::ANDPS);
	opcodeMap.emplace("andnps",&X86::ANDNPS);
	opcodeMap.emplace("orps",&X86::ORPS);
	opcodeMap.emplace("xorps",&X86::XORPS);
	
	opcodeMap.emplace("addps",&X86::ADDPS);
	opcodeMap.emplace("addss",&X86::ADDSS);

	opcodeMap.emplace("subps",&X86::SUBPS);
	opcodeMap.emplace("subss",&X86::SUBSS);	

	opcodeMap.emplace("divps",&X86::DIVPS);
	opcodeMap.emplace("divss",&X86::DIVSS);

	opcodeMap.emplace("mulps",&X86::MULPS);
	opcodeMap.emplace("mulss",&X86::MULSS);
	
	opcodeMap.emplace("minps",&X86::MINPS);
	opcodeMap.emplace("minss",&X86::MINSS);

	opcodeMap.emplace("maxps",&X86::MAXPS);
	opcodeMap.emplace("maxss",&X86::MAXSS);

	opcodeMap.emplace("sqrtps",&X86::SQRTPS);
	opcodeMap.emplace("sqrtss",&X86::SQRTSS);

	opcodeMap.emplace("rsqrtps",&X86::RSQRTPS);
	opcodeMap.emplace("rsqrtss",&X86::RSQRTSS);

	opcodeMap.emplace("rcpps",&X86::RCPPS);
	opcodeMap.emplace("rcpss",&X86::RCPSS);

	opcodeMap.emplace("cmpeqps",&X86::CMPEQPS);
	opcodeMap.emplace("cmpltps",&X86::CMPLTPS);
	opcodeMap.emplace("cmpleps",&X86::CMPLEPS);
	opcodeMap.emplace("cmpunordps",&X86::CMPUNORDPS);
	opcodeMap.emplace("cmpneqps",&X86::CMPNEQPS);
	opcodeMap.emplace("cmpnltps",&X86::CMPNLTPS);
	opcodeMap.emplace("cmpnleps",&X86::CMPNLEPS);
	opcodeMap.emplace("cmpordps",&X86::CMPORDPS);

	opcodeMap.emplace("cmpeqss",&X86::CMPEQSS);
	opcodeMap.emplace("cmpltss",&X86::CMPLTSS);
	opcodeMap.emplace("cmpless",&X86::CMPLESS);
	opcodeMap.emplace("cmpunordss",&X86::CMPUNORDSS);
	opcodeMap.emplace("cmpneqss",&X86::CMPNEQSS);
	opcodeMap.emplace("cmpnltss",&X86::CMPNLTSS);
	opcodeMap.emplace("cmpnless",&X86::CMPNLESS);
	opcodeMap.emplace("cmpordss",&X86::CMPORDSS);

	opcodeMap.emplace("comiss",&X86::COMISS);
	opcodeMap.emplace("ucomiss",&X86::UCOMISS);

	//***************************************************
	// SSE 2

	opcodeMap.emplace("cvtdq2ps",&X86::CVTDQ2PS);
	opcodeMap.emplace("cvtdq2pd",&X86::CVTDQ2PD);

	opcodeMap.emplace("cvtps2dq",&X86::CVTPS2DQ);
	opcodeMap.emplace("cvtpd2dq",&X86::CVTPD2DQ);

	opcodeMap.emplace("cvttps2dq",&X86::CVTTPS2DQ);
	opcodeMap.emplace("cvttpd2dq",&X86::CVTTPD2DQ);

	opcodeMap.emplace("cvtps2pd",&X86::CVTPS2PD);
	opcodeMap.emplace("cvtpd2ps",&X86::CVTPD2PS);

	opcodeMap.emplace("cvtss2sd",&X86::CVTSS2SD);
	opcodeMap.emplace("cvtsd2ss",&X86::CVTSD2SS);

	opcodeMap.emplace("movapd",&X86::MOVAPD);
	opcodeMap.emplace("movupd",&X86::MOVUPD);

	opcodeMap.emplace("movsd",&X86::MOVSD);

	opcodeMap.emplace("movlpd",&X86::MOVLPD);
	opcodeMap.emplace("movhpd",&X86::MOVHPD);

	opcodeMap.emplace("movntpd",&X86::MOVNTPD);

	opcodeMap.emplace("unpcklpd",&X86::UNPCKLPD);
	opcodeMap.emplace("uncpkhpd",&X86::UNPCKHPD);

	opcodeMap.emplace("shufpd",&X86::SHUFPD);

	opcodeMap.emplace("andpd",&X86::ANDPD);
	opcodeMap.emplace("andnpd",&X86::ANDNPD);
	opcodeMap.emplace("orpd",&X86::ORPD);
	opcodeMap.emplace("xorpd",&X86::XORPD);

	opcodeMap.emplace("addpd",&X86::ADDPD);
	opcodeMap.emplace("addsd",&X86::ADDSD);	

	opcodeMap.emplace("subpd",&X86::SUBPD);
	opcodeMap.emplace("subsd",&X86::SUBSD);

	opcodeMap.emplace("divpd",&X86::DIVPD);
	opcodeMap.emplace("divsd",&X86::DIVSD);

	opcodeMap.emplace("mulpd",&X86::MULPD);
	opcodeMap.emplace("mulsd",&X86::MULSD);

	opcodeMap.emplace("minpd",&X86::MINPD);
	opcodeMap.emplace("minsd",&X86::MINSD);

	opcodeMap.emplace("maxpd",&X86::MAXPD);
	opcodeMap.emplace("maxsd",&X86::MAXSD);

	opcodeMap.emplace("sqrtpd",&X86::SQRTPD);
	opcodeMap.emplace("sqrtsd",&X86::SQRTSD);

	opcodeMap.emplace("cmpeqpd",&X86::CMPEQPD);
	opcodeMap.emplace("cmpltpd",&X86::CMPLTPD);
	opcodeMap.emplace("cmplepd",&X86::CMPLEPD);
	opcodeMap.emplace("cmpunordpd",&X86::CMPUNORDPD);
	opcodeMap.emplace("cmpneqpd",&X86::CMPNEQPD);
	opcodeMap.emplace("cmpnltpd",&X86::CMPNLTPD);
	opcodeMap.emplace("cmpnlepd",&X86::CMPNLEPD);
	opcodeMap.emplace("cmpordpd",&X86::CMPORDPD);

	opcodeMap.emplace("cmpeqsd",&X86::CMPEQSD);
	opcodeMap.emplace("cmpltsd",&X86::CMPLTSD);
	opcodeMap.emplace("cmplesd",&X86::CMPLESD);
	opcodeMap.emplace("cmpunordsd",&X86::CMPUNORDSD);
	opcodeMap.emplace("cmpneqsd",&X86::CMPNEQSD);
	opcodeMap.emplace("cmpnltsd",&X86::CMPNLTSD);
	opcodeMap.emplace("cmpnlesd",&X86::CMPNLESD);
	opcodeMap.emplace("cmpordsd",&X86::CMPORDSD);

	opcodeMap.emplace("comisd",&X86::COMISD);
	opcodeMap.emplace("ucomisd",&X86::UCOMISD);

	//**************************************************
	// SSE 3

	opcodeMap.emplace("movsldup",&X86::MOVSLDUP);
	opcodeMap.emplace("movshdup",&X86::MOVSHDUP);

	opcodeMap.emplace("movddup",&X86::MOVDDUP);

	opcodeMap.emplace("addsubpd",&X86::ADDSUBPD);
	opcodeMap.emplace("addsubps",&X86::ADDSUBPS);

	opcodeMap.emplace("haddps",&X86::HADDPS);
	opcodeMap.emplace("haddpd",&X86::HADDPD);

	opcodeMap.emplace("hsubps",&X86::HSUBPS);
	opcodeMap.emplace("hsubpd",&X86::HSUBPD);

	//**************************************************
	// SSE 4.1

	opcodeMap.emplace("insertps",&X86::INSERTPS);
	
	opcodeMap.emplace("blendpd",&X86::BLENDPD);
	opcodeMap.emplace("blendps",&X86::BLENDPS);

	opcodeMap.emplace("blendvpd",&X86::BLENDVPD);
	opcodeMap.emplace("blendvps",&X86::BLENDVPS);

	opcodeMap.emplace("roundps",&X86::ROUNDPS);
	opcodeMap.emplace("roundpd",&X86::ROUNDPD);

	opcodeMap.emplace("roundss",&X86::ROUNDSS);
	opcodeMap.emplace("roundsd",&X86::ROUNDSD);

	opcodeMap.emplace("dpps",&X86::DPPS);
	opcodeMap.emplace("dppd",&X86::DPPD);

	//**************************************************
	// AVX

	opcodeMap.emplace("vmaskmovps",&X86::VMASKMOVPS);
	opcodeMap.emplace("vmaskmovpd",&X86::VMASKMOVPD);

	opcodeMap.emplace("vtestps",&X86::VTESTPS);
	opcodeMap.emplace("vtestpd",&X86::VTESTPD);

	opcodeMap.emplace("vperm2f128",&X86::VPERM2F128);

	// AVX versions for float32 SIMD

	opcodeMap.emplace("vmovaps",&X86::VMOVAPS);
	opcodeMap.emplace("vmovups",&X86::VMOVUPS);

	opcodeMap.emplace("vmovss",&X86::VMOVSS);

	opcodeMap.emplace("vmovlps",&X86::VMOVLPS);
	opcodeMap.emplace("vmovhps",&X86::VMOVHPS);
	opcodeMap.emplace("vmovhlps",&X86::VMOVHLPS);
	opcodeMap.emplace("vmovlhps",&X86::VMOVLHPS);

	opcodeMap.emplace("vmovntps",&X86::VMOVNTPS);
	
	opcodeMap.emplace("vunpcklps",&X86::VUNPCKLPS);
	opcodeMap.emplace("vuncpkhps",&X86::VUNPCKHPS);

	opcodeMap.emplace("vshufps",&X86::VSHUFPS);
	
	opcodeMap.emplace("vandps",&X86::VANDPS);
	opcodeMap.emplace("vandnps",&X86::VANDNPS);
	opcodeMap.emplace("vorps",&X86::VORPS);
	opcodeMap.emplace("vxorps",&X86::VXORPS);
	
	opcodeMap.emplace("vaddps",&X86::VADDPS);
	opcodeMap.emplace("vaddss",&X86::VADDSS);

	opcodeMap.emplace("vsubps",&X86::VSUBPS);
	opcodeMap.emplace("vsubss",&X86::VSUBSS);	

	opcodeMap.emplace("vdivps",&X86::VDIVPS);
	opcodeMap.emplace("vdivss",&X86::VDIVSS);

	opcodeMap.emplace("vmulps",&X86::VMULPS);
	opcodeMap.emplace("vmulss",&X86::VMULSS);
	
	opcodeMap.emplace("vminps",&X86::VMINPS);
	opcodeMap.emplace("vminss",&X86::VMINSS);

	opcodeMap.emplace("vmaxps",&X86::VMAXPS);
	opcodeMap.emplace("vmaxss",&X86::VMAXSS);

	opcodeMap.emplace("vsqrtps",&X86::VSQRTPS);
	opcodeMap.emplace("vsqrtss",&X86::VSQRTSS);

	opcodeMap.emplace("vrsqrtps",&X86::VRSQRTPS);
	opcodeMap.emplace("vrsqrtss",&X86::VRSQRTSS);

	opcodeMap.emplace("vrcpps",&X86::VRCPPS);
	opcodeMap.emplace("vrcpss",&X86::VRCPSS);

	opcodeMap.emplace("vcmpeqps",&X86::VCMPEQPS);
	opcodeMap.emplace("vcmpltps",&X86::VCMPLTPS);
	opcodeMap.emplace("vcmpleps",&X86::VCMPLEPS);
	opcodeMap.emplace("vcmpunordps",&X86::VCMPUNORDPS);
	opcodeMap.emplace("vcmpneqps",&X86::VCMPNEQPS);
	opcodeMap.emplace("vcmpnltps",&X86::VCMPNLTPS);
	opcodeMap.emplace("vcmpnleps",&X86::VCMPNLEPS);
	opcodeMap.emplace("vcmpordps",&X86::VCMPORDPS);

	opcodeMap.emplace("vcmpeqss",&X86::VCMPEQSS);
	opcodeMap.emplace("vcmpltss",&X86::VCMPLTSS);
	opcodeMap.emplace("vcmpless",&X86::VCMPLESS);
	opcodeMap.emplace("vcmpunordss",&X86::VCMPUNORDSS);
	opcodeMap.emplace("vcmpneqss",&X86::VCMPNEQSS);
	opcodeMap.emplace("vcmpnltss",&X86::VCMPNLTSS);
	opcodeMap.emplace("vcmpnless",&X86::VCMPNLESS);
	opcodeMap.emplace("vcmpordss",&X86::VCMPORDSS);

	opcodeMap.emplace("vcomiss",&X86::VCOMISS);
	opcodeMap.emplace("vucomiss",&X86::VUCOMISS);

	// AVX versions for float64 SIMD

	opcodeMap.emplace("vcvtdq2ps",&X86::VCVTDQ2PS);
	opcodeMap.emplace("vcvtdq2pd",&X86::VCVTDQ2PD);

	opcodeMap.emplace("vcvtps2dq",&X86::VCVTPS2DQ);
	opcodeMap.emplace("vcvtpd2dq",&X86::VCVTPD2DQ);

	opcodeMap.emplace("vcvttps2dq",&X86::VCVTTPS2DQ);
	opcodeMap.emplace("vcvttpd2dq",&X86::VCVTTPD2DQ);

	opcodeMap.emplace("vcvtps2pd",&X86::VCVTPS2PD);
	opcodeMap.emplace("vcvtpd2ps",&X86::VCVTPD2PS);

	opcodeMap.emplace("vcvtss2sd",&X86::VCVTSS2SD);
	opcodeMap.emplace("vcvtsd2ss",&X86::VCVTSD2SS);

	opcodeMap.emplace("vmovapd",&X86::VMOVAPD);
	opcodeMap.emplace("vmovupd",&X86::VMOVUPD);

	opcodeMap.emplace("vmovsd",&X86::VMOVSD);

	opcodeMap.emplace("vmovlpd",&X86::VMOVLPD);
	opcodeMap.emplace("vmovhpd",&X86::VMOVHPD);

	opcodeMap.emplace("vmovntpd",&X86::VMOVNTPD);

	opcodeMap.emplace("vunpcklpd",&X86::VUNPCKLPD);
	opcodeMap.emplace("vuncpkhpd",&X86::VUNPCKHPD);

	opcodeMap.emplace("vshufpd",&X86::VSHUFPD);

	opcodeMap.emplace("vandpd",&X86::VANDPD);
	opcodeMap.emplace("vandnpd",&X86::VANDNPD);
	opcodeMap.emplace("vorpd",&X86::VORPD);
	opcodeMap.emplace("vxorpd",&X86::VXORPD);

	opcodeMap.emplace("vaddpd",&X86::VADDPD);
	opcodeMap.emplace("vaddsd",&X86::VADDSD);	

	opcodeMap.emplace("vsubpd",&X86::VSUBPD);
	opcodeMap.emplace("vsubsd",&X86::VSUBSD);

	opcodeMap.emplace("vdivpd",&X86::VDIVPD);
	opcodeMap.emplace("vdivsd",&X86::VDIVSD);

	opcodeMap.emplace("vmulpd",&X86::VMULPD);
	opcodeMap.emplace("vmulsd",&X86::VMULSD);

	opcodeMap.emplace("vminpd",&X86::VMINPD);
	opcodeMap.emplace("vminsd",&X86::VMINSD);

	opcodeMap.emplace("vmaxpd",&X86::VMAXPD);
	opcodeMap.emplace("vmaxsd",&X86::VMAXSD);

	opcodeMap.emplace("vsqrtpd",&X86::VSQRTPD);
	opcodeMap.emplace("vsqrtsd",&X86::VSQRTSD);

	opcodeMap.emplace("vcmpeqpd",&X86::VCMPEQPD);
	opcodeMap.emplace("vcmpltpd",&X86::VCMPLTPD);
	opcodeMap.emplace("vcmplepd",&X86::VCMPLEPD);
	opcodeMap.emplace("vcmpunordpd",&X86::VCMPUNORDPD);
	opcodeMap.emplace("vcmpneqpd",&X86::VCMPNEQPD);
	opcodeMap.emplace("vcmpnltpd",&X86::VCMPNLTPD);
	opcodeMap.emplace("vcmpnlepd",&X86::VCMPNLEPD);
	opcodeMap.emplace("vcmpordpd",&X86::VCMPORDPD);

	opcodeMap.emplace("vcmpeqsd",&X86::VCMPEQSD);
	opcodeMap.emplace("vcmpltsd",&X86::VCMPLTSD);
	opcodeMap.emplace("vcmplesd",&X86::VCMPLESD);
	opcodeMap.emplace("vcmpunordsd",&X86::VCMPUNORDSD);
	opcodeMap.emplace("vcmpneqsd",&X86::VCMPNEQSD);
	opcodeMap.emplace("vcmpnltsd",&X86::VCMPNLTSD);
	opcodeMap.emplace("vcmpnlesd",&X86::VCMPNLESD);
	opcodeMap.emplace("vcmpordsd",&X86::VCMPORDSD);

	opcodeMap.emplace("vcomisd",&X86::VCOMISD);
	opcodeMap.emplace("vucomisd",&X86::VUCOMISD);

	//**************************************************
	// AVX 2

	opcodeMap.emplace("vpmaskmovd",&X86::VPMASKMOVD);
	opcodeMap.emplace("vpmaskmovq",&X86::VPMASKMOVQ);

	opcodeMap.emplace("vpsllvd",&X86::VPSLLVD);
	opcodeMap.emplace("vpsllvq",&X86::VPSLLVQ);

	opcodeMap.emplace("vpsravd",&X86::VPSRAVD);

	opcodeMap.emplace("vpsrlvd",&X86::VPSRLVD);
	opcodeMap.emplace("vpsrlvq",&X86::VPSRLVQ);

	opcodeMap.emplace("vblendd",&X86::VBLENDD);

	opcodeMap.emplace("vpermps",&X86::VPERMPS);
	opcodeMap.emplace("vpermpd",&X86::VPERMPD);

	opcodeMap.emplace("vpermd",&X86::VPERMD);
	opcodeMap.emplace("vpermq",&X86::VPERMQ);

	// Fused multiply-add

	opcodeMap.emplace("vfmadd132ps",&X86::VFMADD132PS);
	opcodeMap.emplace("vfmadd213ps",&X86::VFMADD213PS);
	opcodeMap.emplace("vfmadd231ps",&X86::VFMADD231PS);

	opcodeMap.emplace("vfmadd132pd",&X86::VFMADD132PD);
	opcodeMap.emplace("vfmadd213pd",&X86::VFMADD213PD);
	opcodeMap.emplace("vfmadd231pd",&X86::VFMADD231PD);

	opcodeMap.emplace("vfmadd132ss",&X86::VFMADD132SS);
	opcodeMap.emplace("vfmadd213ss",&X86::VFMADD213SS);
	opcodeMap.emplace("vfmadd231ss",&X86::VFMADD231SS);

	opcodeMap.emplace("vfmadd132sd",&X86::VFMADD132SD);
	opcodeMap.emplace("vfmadd213sd",&X86::VFMADD213SD);
	opcodeMap.emplace("vfmadd231sd",&X86::VFMADD231SD);

	// Fused neg-multiply-add

	opcodeMap.emplace("vfnmadd132ps",&X86::VFNMADD132PS);
	opcodeMap.emplace("vfnmadd213ps",&X86::VFNMADD213PS);
	opcodeMap.emplace("vfnmadd231ps",&X86::VFNMADD231PS);

	opcodeMap.emplace("vfnmadd132pd",&X86::VFNMADD132PD);
	opcodeMap.emplace("vfnmadd213pd",&X86::VFNMADD213PD);
	opcodeMap.emplace("vfnmadd231pd",&X86::VFNMADD231PD);

	opcodeMap.emplace("vfnmadd132ss",&X86::VFNMADD132SS);
	opcodeMap.emplace("vfnmadd213ss",&X86::VFNMADD213SS);
	opcodeMap.emplace("vfnmadd231ss",&X86::VFNMADD231SS);

	opcodeMap.emplace("vfnmadd132sd",&X86::VFNMADD132SD);
	opcodeMap.emplace("vfnmadd213sd",&X86::VFNMADD213SD);
	opcodeMap.emplace("vfnmadd231sd",&X86::VFNMADD231SD);

	// Fused multiply-sub

	opcodeMap.emplace("vfmsub132ps",&X86::VFMSUB132PS);
	opcodeMap.emplace("vfmsub213ps",&X86::VFMSUB213PS);
	opcodeMap.emplace("vfmsub231ps",&X86::VFMSUB231PS);

	opcodeMap.emplace("vfmsub132pd",&X86::VFMSUB132PD);
	opcodeMap.emplace("vfmsub213pd",&X86::VFMSUB213PD);
	opcodeMap.emplace("vfmsub231pd",&X86::VFMSUB231PD);

	opcodeMap.emplace("vfmsub132ss",&X86::VFMSUB132SS);
	opcodeMap.emplace("vfmsub213ss",&X86::VFMSUB213SS);
	opcodeMap.emplace("vfmsub231ss",&X86::VFMSUB231SS);

	opcodeMap.emplace("vfmsub132sd",&X86::VFMSUB132SD);
	opcodeMap.emplace("vfmsub213sd",&X86::VFMSUB213SD);
	opcodeMap.emplace("vfmsub231sd",&X86::VFMSUB231SD);

	// Fused neg-multiply-sub

	opcodeMap.emplace("vfnmsub132ps",&X86::VFNMSUB132PS);
	opcodeMap.emplace("vfnmsub213ps",&X86::VFNMSUB213PS);
	opcodeMap.emplace("vfnmsub231ps",&X86::VFNMSUB231PS);

	opcodeMap.emplace("vfnmsub132pd",&X86::VFNMSUB132PD);
	opcodeMap.emplace("vfnmsub213pd",&X86::VFNMSUB213PD);
	opcodeMap.emplace("vfnmsub231pd",&X86::VFNMSUB231PD);

	opcodeMap.emplace("vfnmsub132ss",&X86::VFNMSUB132SS);
	opcodeMap.emplace("vfnmsub213ss",&X86::VFNMSUB213SS);
	opcodeMap.emplace("vfnmsub231ss",&X86::VFNMSUB231SS);

	opcodeMap.emplace("vfnmsub132sd",&X86::VFNMSUB132SD);
	opcodeMap.emplace("vfnmsub213sd",&X86::VFNMSUB213SD);
	opcodeMap.emplace("vfnmsub231sd",&X86::VFNMSUB231SD);

	// Fused multiply-add-sub

	opcodeMap.emplace("vfmaddsub132ps",&X86::VFMADDSUB132PS);
	opcodeMap.emplace("vfmaddsub213ps",&X86::VFMADDSUB213PS);
	opcodeMap.emplace("vfmaddsub231ps",&X86::VFMADDSUB231PS);

	opcodeMap.emplace("vfmaddsub132pd",&X86::VFMADDSUB132PD);
	opcodeMap.emplace("vfmaddsub213pd",&X86::VFMADDSUB213PD);
	opcodeMap.emplace("vfmaddsub231pd",&X86::VFMADDSUB231PD);

	// Fused multiply-sub-add

	opcodeMap.emplace("vfmsubadd132ps",&X86::VFMSUBADD132PS);
	opcodeMap.emplace("vfmsubadd213ps",&X86::VFMSUBADD213PS);
	opcodeMap.emplace("vfmsubadd231ps",&X86::VFMSUBADD231PS);

	opcodeMap.emplace("vfmsubadd132pd",&X86::VFMSUBADD132PD);
	opcodeMap.emplace("vfmsubadd213pd",&X86::VFMSUBADD213PD);
	opcodeMap.emplace("vfmsubadd231pd",&X86::VFMSUBADD231PD);

	//*************************************************
	// Timing

	Ceng::FLOAT64 time = Ceng_HighPrecisionTimer() - start;

	Ceng::FileLog tempLog;

	tempLog.OpenFile("opcodemap.txt");

	tempLog.Print("opcode map debug");

	tempLog.Print(Ceng::String("build time = ") + time);

	//return Ceng::CE_OK;
}
*/