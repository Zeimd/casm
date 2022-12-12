/*****************************************************************************
*
* x86-opcodes-alu.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-opcodes-alu.h"


#include "../include/enums/x86-param-list.h"

namespace X86
{
	//*************************************************************************************
	// Program flow

	const CallInstruction CALL = CallInstruction();

	const ReturnInstruction RET_NEAR = ReturnInstruction(0xc3,0xc2);
	const ReturnInstruction RET_FAR = ReturnInstruction(0xcb,0xca);

	const CondJumpInstruction JCXZ = CondJumpInstruction(0xe3,0x00);
	const CondJumpInstruction& JECXZ = JCXZ;
	const CondJumpInstruction& JRCXZ = JCXZ;

	const CondJumpInstruction JA = CondJumpInstruction(0x77,0x87);
	const CondJumpInstruction& JNBE = JA;

	const CondJumpInstruction JAE = CondJumpInstruction(0x73,0x83);
	const CondJumpInstruction& JNB = JAE;
	const CondJumpInstruction& JNC = JAE;

	const CondJumpInstruction JB = CondJumpInstruction(0x72,0x82);
	const CondJumpInstruction& JNAE = JB;
	const CondJumpInstruction& JC = JC;

	const CondJumpInstruction JBE = CondJumpInstruction(0x76,0x86);
	const CondJumpInstruction& JNA = JBE;

	const CondJumpInstruction JE = CondJumpInstruction(0x74,0x84);
	const CondJumpInstruction& JZ = JE;

	const CondJumpInstruction JNE = CondJumpInstruction(0x75,0x85);
	const CondJumpInstruction& JNZ = JNE;

	const CondJumpInstruction JG = CondJumpInstruction(0x7f,0x8f);
	const CondJumpInstruction& JNLE = JG;

	const CondJumpInstruction JGE = CondJumpInstruction(0x7d,0x8d);
	const CondJumpInstruction& JNL = JGE;

	const CondJumpInstruction JL = CondJumpInstruction(0x7c,0x8c);
	const CondJumpInstruction& JNGE = JL;

	const CondJumpInstruction JLE = CondJumpInstruction(0x7e,0x8e);
	const CondJumpInstruction& JNG = JLE;

	const CondJumpInstruction JO = CondJumpInstruction(0x70,0x80);
	const CondJumpInstruction JNO = CondJumpInstruction(0x71,0x81);
	const CondJumpInstruction JP = CondJumpInstruction(0x7a,0x8a);
	const CondJumpInstruction JPE = CondJumpInstruction(0x7a,0x8a);
	const CondJumpInstruction JNP = CondJumpInstruction(0x7b,0x8b);
	const CondJumpInstruction JPO = CondJumpInstruction(0x7b,0x8b);
	const CondJumpInstruction JS = CondJumpInstruction(0x78,0x88);
	const CondJumpInstruction JNS = CondJumpInstruction(0x79,0x89);	

	//*************************************************************************************
	// SETCC : Set if condition 

	const SetCC SETA = SetCC(0x97);
	const SetCC& SETNBE = SETA;
	const SetCC SETAE = SetCC(0x93);
	const SetCC& SETNB = SETAE;
	const SetCC& SETNC = SETNC;	
	const SetCC SETB = SetCC(0x92);
	const SetCC& SETC = SETB;
	const SetCC& SETNAE = SETB;
	const SetCC SETBE = SetCC(0x96);
	const SetCC& SETNA = SETBE;
	const SetCC SETE = SetCC(0x94);
	const SetCC& SETZ = SETE;	
	const SetCC SETNE = SetCC(0x95);
	const SetCC& SETNZ = SETNE;
	const SetCC SETG = SetCC(0x9f);
	const SetCC& SETNLE = SETG;
	const SetCC SETGE = SetCC(0x9d);
	const SetCC& SETNL = SETGE;
	const SetCC SETL = SetCC(0x9c);
	const SetCC& SETNGE = SETNGE;
	const SetCC SETLE = SetCC(0x9e);
	const SetCC& SETNG = SETLE;
	const SetCC SETNO = SetCC(0x91);
	const SetCC SETNP = SetCC(0x9b);
	const SetCC SETNS = SetCC(0x99);
	const SetCC SETO = SetCC(0x90);
	const SetCC	SETP = SetCC(0x9a);
	const SetCC SETPE = SetCC(0x9a);
	const SetCC SETPO = SetCC(0x9b);
	const SetCC SETS = SetCC(0x98);

	//*************************************************************************************
	// CMOVCC : Conditional move

	const ConditionalMove CMOVA = ConditionalMove(0x47);

	const ConditionalMove& CMOVNBE = CMOVA;
	
	const ConditionalMove CMOVAE = ConditionalMove(0x43);

	const ConditionalMove& CMOVNB = CMOVAE;

	const ConditionalMove& CMOVNC = CMOVAE;
	
	const ConditionalMove CMOVB = ConditionalMove(0x42);

	const ConditionalMove& CMOVNAE = CMOVB;
	
	const ConditionalMove& CMOVC = CMOVB;

	const ConditionalMove CMOVBE = ConditionalMove(0x46);

	const ConditionalMove& CMOVNA = CMOVBE;

	const ConditionalMove CMOVE = ConditionalMove(0x44);

	const ConditionalMove& CMOVZ = CMOVE;

	const ConditionalMove CMOVNE = ConditionalMove(0x45);

	const ConditionalMove& CMOVNZ = CMOVNE;

	const ConditionalMove CMOVG = ConditionalMove(0x4f);

	const ConditionalMove& CMOVNLE = CMOVG;

	const ConditionalMove CMOVGE = ConditionalMove(0x4d);

	const ConditionalMove& CMOVNL = CMOVGE;

	const ConditionalMove CMOVL = ConditionalMove(0x4c);

	const ConditionalMove& CMOVNGE = CMOVL;

	const ConditionalMove CMOVLE = ConditionalMove(0x4e);

	const ConditionalMove& CMOVNG = CMOVLE;

	const ConditionalMove CMOVO = ConditionalMove(0x40);

	const ConditionalMove CMOVNO = ConditionalMove(0x41);

	const ConditionalMove CMOVP = ConditionalMove(0x4a);
	const ConditionalMove& CMOVPE = CMOVP;

	const ConditionalMove CMOVNP = ConditionalMove(0x4b);
	const ConditionalMove& CMOVPO = CMOVNP;

	const ConditionalMove CMOVS = ConditionalMove(0x48);
	const ConditionalMove CMOVNS = ConditionalMove(0x49);

	//*************************************************************************************
	// Memory control

	const FenceOp CLFLUSH = FenceOp(0xae,7,PARAM_LIST::MEM);
	
	const FenceOp LFENCE = FenceOp(0xae,5,0);
	const FenceOp MFENCE = FenceOp(0xae,6,0);
	const FenceOp SFENCE = FenceOp(0xae,7,0);

	const FenceOp PREFETCHT0 = FenceOp(0x18,1,PARAM_LIST::MEM);

	const FenceOp PREFETCHT1 = FenceOp(0x18,2,PARAM_LIST::MEM);

	const FenceOp PREFETCHT2 = FenceOp(0x18,3,PARAM_LIST::MEM);

	const FenceOp PREFETCHNTA = FenceOp(0x18,0,PARAM_LIST::MEM);

	const FenceOp PREFETCHW = FenceOp(0x0d,1,PARAM_LIST::MEM);

	const FenceOp SGDT = FenceOp(0x01,0,PARAM_LIST::MEM);

	const FenceOp SIDT = FenceOp(0x01,1,PARAM_LIST::MEM);

	//*************************************************************************************
	// Processor state save

	const SaveExtState XSAVE = SaveExtState(4,false);
	const SaveExtState XSAVE64 = SaveExtState(4,true);

	const SaveExtState XSAVEOPT = SaveExtState(6,false);
	const SaveExtState XSAVEOPT64 = SaveExtState(6,true);

	const SaveExtState XRSTOR = SaveExtState(5,false);
	const SaveExtState XRSTOR64 = SaveExtState(5,true);
	
	//*************************************************************************************
	// ALU instructions

	const Exchange XCHG = Exchange();

	const ALU_ByteSwap BSWAP = ALU_ByteSwap();

	const ALU_Ascii AAD = ALU_Ascii(0xd5);
	const ALU_Ascii AAM = ALU_Ascii(0xd4);

	const ALU_Incr INC = ALU_Incr(0x40,0);
	const ALU_Incr DEC = ALU_Incr(0x48,1);	

	const MoveInstruction MOV = MoveInstruction();

	const AddTypeInstruction ADD = AddTypeInstruction(0x01,0x03,0x00,0x02,0x04,0x05,0);
	const AddTypeInstruction OR = AddTypeInstruction(0x09,0x0b,0x08,0x0a,0x0c,0x0d,1);
	const AddTypeInstruction ADC = AddTypeInstruction(0x11,0x13,0x10,0x12,0x14,0x15,2);
	const AddTypeInstruction SBB = AddTypeInstruction(0x19,0x1b,0x18,0x1a,0x1c,0x1d,3);
	const AddTypeInstruction AND = AddTypeInstruction(0x21,0x23,0x20,0x22,0x24,0x25,4);
	const AddTypeInstruction SUB = AddTypeInstruction(0x29,0x2b,0x28,0x2a,0x2c,0x2d,5);
	const AddTypeInstruction XOR = AddTypeInstruction(0x31,0x33,0x30,0x32,0x34,0x35,6);
	const AddTypeInstruction CMP = AddTypeInstruction(0x39,0x3b,0x38,0x3a,0x3c,0x3d,7);

	const ALU_Shift SAL = ALU_Shift(4);
	const ALU_Shift SAR = ALU_Shift(7);

	const ALU_Shift SHL = ALU_Shift(4);
	const ALU_Shift SHR = ALU_Shift(5);

	const ALU_Shift RCL = ALU_Shift(2);
	const ALU_Shift RCR = ALU_Shift(3);

	const ALU_Shift ROL = ALU_Shift(0);
	const ALU_Shift ROR = ALU_Shift(1);

	const ALU_WideShift SHLD = ALU_WideShift(0xa4,0xa5);
	const ALU_WideShift SHRD = ALU_WideShift(0xac,0xad);

	const ALU_BitTest BT = ALU_BitTest(0xa3,4);
	const ALU_BitTest BTC = ALU_BitTest(0xbb,7);
	const ALU_BitTest BTR = ALU_BitTest(0xb3,6);
	const ALU_BitTest BTS = ALU_BitTest(0xab,5);

	const ALU_BitScan BSF = ALU_BitScan(0xbc);
	const ALU_BitScan BSR = ALU_BitScan(0xbd);

	const CBW_Variant CBW = CBW_Variant(0x98,OPERAND_SIZE::WORD);
	const CBW_Variant CWDE = CBW_Variant(0x98,OPERAND_SIZE::DWORD);
	const CBW_Variant CDQE = CBW_Variant(0x98,OPERAND_SIZE::QWORD);

	const CBW_Variant CWD = CBW_Variant(0x99,OPERAND_SIZE::WORD);
	const CBW_Variant CDQ = CBW_Variant(0x99,OPERAND_SIZE::DWORD);
	const CBW_Variant CQO = CBW_Variant(0x99,OPERAND_SIZE::QWORD);

	const CBW_Variant IRET = CBW_Variant(0xcf,OPERAND_SIZE::WORD);
	const CBW_Variant IRETD = CBW_Variant(0xcf,OPERAND_SIZE::DWORD);
	const CBW_Variant IRETQ = CBW_Variant(0xcf,OPERAND_SIZE::QWORD);

	const CBW_Variant POPF = CBW_Variant(0x9d,OPERAND_SIZE::WORD);
	const CBW_Variant POPFD = CBW_Variant(0x9d,OPERAND_SIZE::DWORD);
	const CBW_Variant POPFQ = CBW_Variant(0x9d,OPERAND_SIZE::QWORD);

	const CBW_Variant PUSHF = CBW_Variant(0x9c,OPERAND_SIZE::WORD);
	const CBW_Variant PUSHFD = CBW_Variant(0x9c,OPERAND_SIZE::DWORD);
	const CBW_Variant PUSHFQ = CBW_Variant(0x9c,OPERAND_SIZE::QWORD);

	const CBW_Variant POPA = CBW_Variant(0x61,OPERAND_SIZE::WORD);

	const CBW_Variant POPAD = CBW_Variant(0x61,OPERAND_SIZE::DWORD);

	const CBW_Variant PUSHA = CBW_Variant(0x60,OPERAND_SIZE::WORD);

	const CBW_Variant PUSHAD = CBW_Variant(0x60,OPERAND_SIZE::DWORD);

	//*************************************************************************************
	// Long division and multiply

	extern const ALU_Div IDIV = ALU_Div(7);

	extern const ALU_Div DIV = ALU_Div(6);

	extern const ALU_Div MUL = ALU_Div(4);

	//************************************************************************************
	// Two's and one's complements

	extern const ALU_Div NEG = ALU_Div(3);

	extern const ALU_Div NOT = ALU_Div(2);

	//************************************************************************************
	// Simple instructions (no explicit operands)

	const SimpleInstruction AAA = SimpleInstruction(0x37);

	const SimpleInstruction AAS = SimpleInstruction(0x3f);

	const SimpleInstruction DAA = SimpleInstruction(0x27);

	const SimpleInstruction DAS = SimpleInstruction(0x2f);

	const SimpleInstruction CLC = SimpleInstruction(0xf8);

	const SimpleInstruction STC = SimpleInstruction(0xf9);

	const SimpleInstruction CMC = SimpleInstruction(0xf5);

	const SimpleInstruction CLD = SimpleInstruction(0xfc);

	const SimpleInstruction STD = SimpleInstruction(0xfd);

	const SimpleInstruction CLI = SimpleInstruction(0xfa);

	const SimpleInstruction STI = SimpleInstruction(0xfb);

	const SimpleInstruction CLTS = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTE_0F,0x06);

	const SimpleInstruction CPUID = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTE_0F,0xa2);

	const SimpleInstruction EMMS = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTE_0F,0x77);

	const SimpleInstruction HALT = SimpleInstruction(0xf4);

	const SimpleInstruction PAUSE = SimpleInstruction(PREFIX_BYTE::BYTE_F3,OPCODE_ESCAPE::NONE,0x90);

	const SimpleInstruction INVD = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTE_0F,0x08);

	const SimpleInstruction WBINDV = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTE_0F,0x09);

	const SimpleInstruction LAHF = SimpleInstruction(0x9f);

	const SimpleInstruction SAHF = SimpleInstruction(0x9e);

	const SimpleInstruction MONITOR = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTES_0F_01,0xc8);

	const SimpleInstruction MWAIT = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTES_0F_01,0xc9);

	const SimpleInstruction RSM = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTE_0F,0xaa);

	const SimpleInstruction SYSCALL = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTE_0F,0x05);

	const SimpleInstruction SYSRET = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTE_0F,0x07);

	const SimpleInstruction SYSENTER = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTE_0F,0x34);

	const SimpleInstruction SYSEXIT = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTE_0F,0x35);

	const SimpleInstruction UD2 = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTE_0F,0x0b);

	const SimpleInstruction FWAIT = SimpleInstruction(0x9b);

	const SimpleInstruction WRMSR = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTE_0F,0x30);

	const SimpleInstruction RDMSR = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTE_0F,0x32);

	const SimpleInstruction RDPMC = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTE_0F,0x33);

	const SimpleInstruction RDTSC = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTE_0F,0x31);

	const SimpleInstruction RDTSCP = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTES_0F_01,0xf9);

	const SimpleInstruction XTEST = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTES_0F_01,0xd6);

	const SimpleInstruction XEND = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTES_0F_01,0xd5);

	const SimpleInstruction XGETBV = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTES_0F_01,0xd0);

	const SimpleInstruction XSETBV = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTES_0F_01,0xd1);

	const SimpleInstruction XLATB = SimpleInstruction(0xd7);

	const SimpleInstruction SWAPGS = SimpleInstruction(PREFIX_BYTE::NONE,OPCODE_ESCAPE::BYTES_0F_01,0xf8);

	const SimpleInstruction LEAVE = SimpleInstruction(0xc9);


}
