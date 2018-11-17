/*****************************************************************************
*
* x86-opcodes-alu.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_OPCODES_ALU_H
#define X86_OPCODES_ALU_H

#include "x86-add-variant.h"

#include "x86-alu-div.h"

#include "x86-move.h"
#include "x86-cond-jump.h"

#include "x86-call.h"
#include "x86-return.h"

#include "x86-alu-shift.h"
#include "x86-wide-shift.h"

#include "x86-bit-test.h"
#include "x86-bit-scan.h"

/*
	const SSE_SignMask MOVMSKPS = SSE_SignMask(PREFIX_PACKED_FLOAT,OPCODE_MOVMSK);
	const SSE_SignMask MOVMSKPD = SSE_SignMask(PREFIX_PACKED_DOUBLE,OPCODE_MOVMSK);
	*/	


namespace X86
{
	//*************************************************************************************
	// Program flow

	extern const CallInstruction CALL;

	extern const ReturnInstruction RET_NEAR;
	extern const ReturnInstruction RET_FAR;

	/**
	 * Jump if CX = 0.
	 */
	extern const CondJumpInstruction JCXZ;

	/**
	 * Jump is ECX = 0.
	 */
	extern const CondJumpInstruction& JECXZ;

	/**
	 * Jump is RCX = 0.
	 */
	extern const CondJumpInstruction& JRCXZ;

	/**
	 * Jump if unsigned a > b
	 */
	extern const CondJumpInstruction JA;

	/**
	 * Jump if not unsigned a <= b
	 */
	extern const CondJumpInstruction& JNBE;

	/**
	 * Jump if unsigned a >= b
	 */
	extern const CondJumpInstruction JAE;

	/**
	 * Jump if not unsigned a < b.
	 */
	extern const CondJumpInstruction& JNB;

	/**
	 * Jump if not carry.
	 */
	extern const CondJumpInstruction& JNC;

	/**
	 * Jump if unsigned a < b.
	 */
	extern const CondJumpInstruction JB;

	/**
	 * Jump if not unsigned a >= b.
	 */
	extern const CondJumpInstruction& JNAE;

	/**
	 * Jump if carry.
	 */
	extern const CondJumpInstruction& JC;

	/**
	 * Jump if unsigned a <= b.
	 */
	extern const CondJumpInstruction JBE;

	/**
	 * Jump if not unsigned a > b.
	 */
	extern const CondJumpInstruction& JNA;

	/**
	 * Jump if a == b
	 */
	extern const CondJumpInstruction JE;

	/**
	 * Jump if zero
	 */
	extern const CondJumpInstruction& JZ;

	/**
	 * Jump if a != b
	 */
	extern const CondJumpInstruction JNE;

	/**
	 * Jump if non-zero
	 */
	extern const CondJumpInstruction& JNZ;
	
	/**
	 * Jump if signed a > b
	 */
	extern const CondJumpInstruction JG;
	extern const CondJumpInstruction& JNLE;

	/**
	 * Jump if signed a >= b
	 */
	extern const CondJumpInstruction JGE;
	extern const CondJumpInstruction& JNL;
	
	/**
	 * Jump if signed a < b
	 */
	extern const CondJumpInstruction JL;
	extern const CondJumpInstruction& JNGE;
	
	/**
	 * Jump if signed a <= b
	 */
	extern const CondJumpInstruction JLE;
	extern const CondJumpInstruction& JNG;

	/**
	 * Jump if signed overflow.
	 */
	extern const CondJumpInstruction JO;

	/**
	 * Jump if not signed overflow.
	 */
	extern const CondJumpInstruction JNO;

	/**
	 * Jump if parity (p=1).
	 */
	extern const CondJumpInstruction JP;

	/**
	 * Jump if parity even (p=1).
	 */
	extern const CondJumpInstruction JPE;

	/**
	 * Jump if not parity (p=0)
	 */
	extern const CondJumpInstruction JNP;

	/**
	 * Jump if parity odd (p=0).
	 */
	extern const CondJumpInstruction JPO;

	/**
	 * Jump if negative.
	 */
	extern const CondJumpInstruction JS;

	/**
	 * Jump if not negative
	 */
	extern const CondJumpInstruction JNS;	
}

#include "x86-alu-cmov.h"

namespace X86
{
	//*************************************************************************************
	// CMOVCC : Conditional move

	extern const ConditionalMove CMOVA;

	extern const ConditionalMove& CMOVNBE;
	
	extern const ConditionalMove CMOVAE;

	extern const ConditionalMove& CMOVNB;

	extern const ConditionalMove& CMOVNC;
	
	extern const ConditionalMove CMOVB;

	extern const ConditionalMove& CMOVNAE;
	
	extern const ConditionalMove& CMOVC;

	extern const ConditionalMove CMOVBE;

	extern const ConditionalMove& CMOVNA;

	extern const ConditionalMove CMOVE;

	extern const ConditionalMove& CMOVZ;

	extern const ConditionalMove CMOVNE;

	extern const ConditionalMove& CMOVNZ;

	extern const ConditionalMove CMOVG;

	extern const ConditionalMove& CMOVNLE;

	extern const ConditionalMove CMOVGE;

	extern const ConditionalMove& CMOVNL;

	extern const ConditionalMove CMOVL;

	extern const ConditionalMove& CMOVNGE;

	extern const ConditionalMove CMOVLE;

	extern const ConditionalMove& CMOVNG;

	extern const ConditionalMove CMOVO;

	extern const ConditionalMove CMOVNO;

	extern const ConditionalMove CMOVP;
	extern const ConditionalMove& CMOVPE;

	extern const ConditionalMove CMOVNP;
	extern const ConditionalMove& CMOVPO;

	extern const ConditionalMove CMOVS;
	extern const ConditionalMove CMOVNS;
}

#include "x86-alu-setcc.h"

namespace X86
{
	//*************************************************************************************
	// SETCC : Set if condition 

	extern const SetCC SETA;
	extern const SetCC& SETNBE;

	extern const SetCC SETAE;
	extern const SetCC& SETNB;
	extern const SetCC& SETNC;
	
	extern const SetCC SETB;
	extern const SetCC& SETC;
	extern const SetCC& SETNAE;

	extern const SetCC SETBE;
	extern const SetCC& SETNA;

	extern const SetCC SETE;
	extern const SetCC& SETZ;
	
	extern const SetCC SETNE;
	extern const SetCC& SETNZ;

	extern const SetCC SETG;
	extern const SetCC& SETNLE;

	extern const SetCC SETGE;
	extern const SetCC& SETNL;

	extern const SetCC SETL;
	extern const SetCC& SETNGE;

	extern const SetCC SETLE;
	extern const SetCC& SETNG;

	extern const SetCC SETNO;

	extern const SetCC SETNP;

	extern const SetCC SETNS;

	extern const SetCC SETO;

	extern const SetCC SETP;

	extern const SetCC SETPE;

	extern const SetCC SETPO;

	extern const SetCC SETS;
}

#include "x86-alu-incr.h"

namespace X86
{
	extern const ALU_Incr INC;
	extern const ALU_Incr DEC;
}

#include "x86-alu-ascii.h"

namespace X86
{
	extern const ALU_Ascii AAD;
	extern const ALU_Ascii AAM;
}

#include "x86-alu-bswap.h"

namespace X86
{
	extern const ALU_ByteSwap BSWAP;
}

#include "x86-fence.h"

namespace X86
{
	extern const FenceOp CLFLUSH;
	
	extern const FenceOp LFENCE;
	extern const FenceOp MFENCE;
	extern const FenceOp SFENCE;

	extern const FenceOp PREFETCHT0;

	extern const FenceOp PREFETCHT1;

	extern const FenceOp PREFETCHT2;

	extern const FenceOp PREFETCHNTA;

	extern const FenceOp PREFETCHW;

	extern const FenceOp SGDT;

	extern const FenceOp SIDT;
}

#include "x86-xsave.h"

namespace X86
{
	//*************************************************************************************
	// Processor state save

	extern const SaveExtState XSAVE;
	extern const SaveExtState XSAVE64;

	extern const SaveExtState XSAVEOPT;
	extern const SaveExtState XSAVEOPT64;

	extern const SaveExtState XRSTOR;
	extern const SaveExtState XRSTOR64;	
}

#include "x86-alu-xchg.h"

namespace X86
{
	extern const Exchange XCHG;
}

namespace X86
{

	//*************************************************************************************
	// ALU instructions

	extern const MoveInstruction MOV;

	extern const AddTypeInstruction ADD;
	extern const AddTypeInstruction OR;
	extern const AddTypeInstruction ADC;
	extern const AddTypeInstruction SBB;
	extern const AddTypeInstruction AND;
	extern const AddTypeInstruction SUB;
	extern const AddTypeInstruction XOR;
	extern const AddTypeInstruction CMP;

	extern const ALU_Shift SAL;
	extern const ALU_Shift SAR;

	extern const ALU_Shift SHL;
	extern const ALU_Shift SHR;

	extern const ALU_Shift RCL;
	extern const ALU_Shift RCR;

	extern const ALU_Shift ROL;
	extern const ALU_Shift ROR;

	extern const ALU_WideShift SHLD;
	extern const ALU_WideShift SHRD;

	extern const ALU_BitTest BT;
	extern const ALU_BitTest BTC;
	extern const ALU_BitTest BTR;
	extern const ALU_BitTest BTS;

	extern const ALU_BitScan BSF;
	extern const ALU_BitScan BSR;

	//*************************************************************************************
	// Long division and multiply

	extern const ALU_Div IDIV;

	extern const ALU_Div DIV;

	extern const ALU_Div MUL;

	//************************************************************************************
	// Two's and one's complements

	extern const ALU_Div NEG;

	extern const ALU_Div NOT;
}

#include "x86-cbw-variant.h"

namespace X86
{
	extern const CBW_Variant CBW;
	extern const CBW_Variant CWDE;
	extern const CBW_Variant CDQE;

	extern const CBW_Variant CWD;
	extern const CBW_Variant CDQ;
	extern const CBW_Variant CQO;

	extern const CBW_Variant IRET;
	extern const CBW_Variant IRETD;
	extern const CBW_Variant IRETQ;

	extern const CBW_Variant POPF;
	extern const CBW_Variant POPFD;
	extern const CBW_Variant POPFQ;

	extern const CBW_Variant PUSHF;
	extern const CBW_Variant PUSHFD;
	extern const CBW_Variant PUSHFQ;

	/**
	 * Pop DI,SI,BP,BX,DX,CX,AX from stack.
	 */
	extern const CBW_Variant POPA;

	/**
	 * Pop EDI,ESI,EBP,EBX,EDX,ECX,EAX from stack.
	 */
	extern const CBW_Variant POPAD;

	/**
	 * Push AX,CX,DX,BX,BP,SI,DI to stack.
	 */
	extern const CBW_Variant PUSHA;

	/**
	 * Push EAX,ECX,EDX,EBX,EBP,ESI,EDI to stack.
	 */
	extern const CBW_Variant PUSHAD;
}

#include "x86-simple-instruction.h"

namespace X86
{
	


	/**
	 * ASCII adjust after addition.
	 */
	extern const SimpleInstruction AAA;

	/**
	 * ASCII adjust AL after subtraction.
	 */
	extern const SimpleInstruction AAS;

	/**
	 * Decimal adjust AL after addition.
	 */
	extern const SimpleInstruction DAA;

	/**
	 * Decimal adjust AL after subtraction.
	 */
	extern const SimpleInstruction DAS;

	/**
	 * Clear carry flag.
	 */
	extern const SimpleInstruction CLC;

	/**
	 * Set carry flag.
	 */
	extern const SimpleInstruction STC;


	/**
	 * Complement carry flag.
	 */
	extern const SimpleInstruction CMC;

	/**
	 * Clear direction flag.
	 */
	extern const SimpleInstruction CLD;

	/**
	 * Set direction flag.
	 */
	extern const SimpleInstruction STD;

	/**
	 * Disable interrupts.
	 */
	extern const SimpleInstruction CLI;

	/**
	 * Enable interrupts.
	 */
	extern const SimpleInstruction STI;

	/**
	 * Clear task-switched flag in CR0.
	 */
	extern const SimpleInstruction CLTS;

	/**
	 * Store register features into EAX,EBX,ECX,EDX.
	 * Input from EAX (and occasionally ECX).
	 */
	extern const SimpleInstruction CPUID;

	/**
	 * Move from MMX mode to X87 FPU mode.
	 */
	extern const SimpleInstruction EMMS;

	/**
	 * Stop execution until interrupt.
	 */
	extern const SimpleInstruction HALT;

	/**
	 * Hint spin-wait loop.
	 */
	extern const SimpleInstruction PAUSE;

	/**
	 * Invalidate internal caches.
	 */
	extern const SimpleInstruction INVD;

	/**
	 * Write caches to memory, then invalidate them.
	 */
	extern const SimpleInstruction WBINDV;

	/**
	 * Load status flags into AH register.
	 */
	extern const SimpleInstruction LAHF;

	/**
	 * Store AH into status flags.
	 */
	extern const SimpleInstruction SAHF;

	/**
	 * Setup monitor for address DS:EAX.
	 */
	extern const SimpleInstruction MONITOR;

	/**
	 * Hint to wait until a monitor event.
	 */
	extern const SimpleInstruction MWAIT;

	/**
	 * Resume from system management mode.
	 */
	extern const SimpleInstruction RSM;

	/**
	 * Fast system call.
	 */
	extern const SimpleInstruction SYSCALL;

	/**
	 * Return from fast system call.
	 */
	extern const SimpleInstruction SYSRET;

	/**
	 * Fast system call.
	 */
	extern const SimpleInstruction SYSENTER;

	/**
	 * Return from fast system call.
	 */
	extern const SimpleInstruction SYSEXIT;

	/**
	 * Raise undefined instruction exception.
	 * Used for software testing.
	 */
	extern const SimpleInstruction UD2;

	/**
	 * Wait until floating point exceptions have been resolved.
	 */
	extern const SimpleInstruction FWAIT;

	/**
	 * Write value in EDX:EAX to model-specific register
	 * selected by ECX.
	 */
	extern const SimpleInstruction WRMSR;

	/**
	 * Read value of a model-specific register selected by ECX
	 * to EDX:EAX.
	 */
	extern const SimpleInstruction RDMSR;

	/**
	 * ECX = Select performance counter to read
	 * EDX:EAX = Output
	 */
	extern const SimpleInstruction RDPMC;

	/**
	 * Read time-stamp counter to EDX:EAX.
	 */
	extern const SimpleInstruction RDTSC;

	/**
	 * EDX:EAX = Timestamp counter
	 * ECX = Processor ID
	 */
	extern const SimpleInstruction RDTSCP;

	/**
	 * Clear zero flag if executing a transaction or
	 * RTM region.
	 */
	extern const SimpleInstruction XTEST;

	/**
	 * Signal transaction end.
	 */
	extern const SimpleInstruction XEND;

	/**
	 * extendedControlRegister[ECX] = EDX:EAX.
	 */
	extern const SimpleInstruction XGETBV;

	/**
	 * EDX:EAX = extendedControlRegister[ECX].
	 */
	extern const SimpleInstruction XSETBV;

	/**
	 * AL = [DS:EBX + unsigned AL].
	 */
	extern const SimpleInstruction XLATB;

	/**
	 * Swap GS register with contents of model specific register 0xc0000102.
	 */
	extern const SimpleInstruction SWAPGS;

	/**
	 * Leave stack frame created by ENTER-instruction.
	 */
	extern const SimpleInstruction LEAVE;

		
};


#endif