/*****************************************************************************
*
* code-generator.cpp
*
* By Jari Korkala 1/2014
*
******************************************************************************/

#include "../include/code-generator.h"

using namespace X86;

Ceng::CRESULT CodeGenerator::Create(const AssemblerState &state,CodeGenerator **output)
{
	CodeGenerator *temp;

	temp = new CodeGenerator();

	memcpy(&temp->state,&state,sizeof(AssemblerState));

	*output = temp;

	return Ceng::CE_OK;
}

CodeGenerator::~CodeGenerator()
{
}

Ceng::CRESULT CodeGenerator::GenerateCode(Program **output)
{
	Ceng::UINT8 *execPage = NULL;

	execPage = (Ceng::UINT8*)VirtualAlloc(NULL,4096,MEM_COMMIT | MEM_RESERVE,PAGE_EXECUTE_READWRITE);

	if (execPage == NULL)
	{
		return Ceng::CE_ERR_OUT_OF_MEMORY;
	}

	Ceng::INT32 k;

	for(k=0;k<codeBuffer.size();k++)
	{
		execPage[k] = codeBuffer[k];
	}

	Program *temp = Program::Create(execPage,4096);

	*output = temp;

	return Ceng::CE_OK;
}

Ceng::CRESULT CodeGenerator::EncodeOneForm(const OneForm &instruction,const Operand &operand)
{
	return instruction.Encode(codeBuffer,&operand);
}

Ceng::CRESULT CodeGenerator::EncodeTwoForm(const TwoForm &instruction,
										   const Operand &dest,
										   const Operand &source)
{
	return instruction.Encode(codeBuffer,&dest,&source);
}
								

Ceng::CRESULT CodeGenerator::AppendCode(const Ceng::UINT8 *bytes,const Ceng::UINT32 length)
{
	Ceng::INT32 k;

	for(k=0;k<length;k++)
	{
		codeBuffer.push_back(bytes[k]);
	}

	return Ceng::CE_OK;
}

Ceng::CRESULT CodeGenerator::X86_POP(const RegisterOperand &dest)
{
	Ceng::UINT32 length = 0;
	Ceng::UINT8 line[16];

	line[0] = 0x58 + dest.index;
	length = 1;

	AppendCode(line,length);

	return Ceng::CE_OK;
}

Ceng::CRESULT CodeGenerator::X86_PUSH(const RegisterOperand &source)
{
	UINT32 length = 0;
	UINT8 line[16];

	line[0] = 0x50 + source.index;
	length = 1;

	AppendCode(line,length);

	return Ceng::CE_OK;
}

Ceng::CRESULT CodeGenerator::X86_PUSH(const MemoryOperand &source)
{
	UINT32 length = 0;
	UINT8 line[16];

	line[0] = 0xff;
	length = 1;

	length += EncodeOperands_RegMem(&line[length],6,source);

	AppendCode(line,length);

	return Ceng::CE_OK;
}

//*****************************************************************************************************


Ceng::CRESULT CodeGenerator::SSE_TWO_FORM(const SSE_MoveInstruction &instruction,
										  const SSE_RegisterOperand &dest,const SSE_RegisterOperand &source)
{
	Ceng::UINT32 length = 0;
	Ceng::UINT8 line[16];

	if (instruction.prefixByte)
	{
		line[length] = instruction.prefixByte;
		length++;
	}

	// REX prefix if required

	line[length] = 0x0f;
	line[length+1] = instruction.opcodeToREG;

	length += 2;

	length += EncodeOperands_RegReg(&line[length],
										dest.index,
										source.index);

	AppendCode(line,length);

	return Ceng::CE_OK;

}

Ceng::CRESULT CodeGenerator::SSE_TWO_FORM(const SSE_MoveInstruction &instruction,
										  const MemoryOperand &dest,const SSE_RegisterOperand &source)
{
	Ceng::UINT32 length = 0;
	Ceng::UINT8 line[16];

	if (instruction.prefixByte)
	{
		line[length] = instruction.prefixByte;
		length++;
	}

	// REX prefix if required

	line[length] = 0x0f;
	line[length+1] = instruction.opcodeToMEM;

	length += 2;

	length += EncodeOperands_RegMem(&line[length],
										source.index,
										dest);

	AppendCode(line,length);

	return Ceng::CE_OK;
}

Ceng::CRESULT CodeGenerator::SSE_TWO_FORM(const SSE_MoveInstruction &instruction,
										  const SSE_RegisterOperand &dest,const MemoryOperand &source)
{
	Ceng::UINT32 length = 0;
	Ceng::UINT8 line[16];

	if (instruction.prefixByte)
	{
		line[length] = instruction.prefixByte;
		length++;
	}

	// REX prefix if required

	line[length] = 0x0f;
	line[length+1] = instruction.opcodeToREG;

	length += 2;

	length += EncodeOperands_RegMem(&line[length],
										dest.index,
										source);

	AppendCode(line,length);

	return Ceng::CE_OK;
}

//*****************************************************************************************************

Ceng::CRESULT CodeGenerator::SSE_TWO_FORM(const SSE_MathInstruction &instruction,
									const SSE_RegisterOperand &dest,const SSE_RegisterOperand &source)
{
	UINT32 length = 0;
	UINT8 line[16];

	if (instruction.prefixByte != 0)
	{
		line[length] = instruction.prefixByte;
		length++;
	}

	// REX prefix if required

	line[length] = 0x0f;
	line[length+1] = instruction.opcode;

	length += 2;

	length += EncodeOperands_RegReg(&line[length],dest.index,source.index);

	AppendCode(line,length);

	return Ceng::CE_OK;
}

Ceng::CRESULT CodeGenerator::SSE_TWO_FORM(const SSE_MathInstruction &instruction,
										  const SSE_RegisterOperand &dest,const MemoryOperand &source)
{
	Ceng::UINT32 length = 0;
	Ceng::UINT8 line[16];

	if (instruction.prefixByte != 0)
	{
		line[length] = instruction.prefixByte;
		length++;
	}

	// REX prefix if required

	line[length] = 0x0f;
	line[length+1] = instruction.opcode;

	length += 2;

	length += EncodeOperands_RegMem(&line[length],dest.index,source);

	AppendCode(line,length);

	return Ceng::CE_OK;
}

//**********************************************************************
const Ceng::INT32 CodeGenerator::EncodeOperands_RegReg(Ceng::UINT8 *destBuffer,
													   const Ceng::INT32 destReg,
													   const Ceng::INT32 sourceReg)
{
	Ceng::UINT8 modRM = 0;
	Ceng::UINT8 sib = 0;

	modRM += 3 << 6; // Source is register

	modRM += (destReg & 7) << 3; // Destination register

	modRM += (sourceReg & 7); // Source register

	destBuffer[0] = modRM;
	return 1;
}

const Ceng::INT32 CodeGenerator::EncodeOperands_RegMem(Ceng::UINT8 *destBuffer,const Ceng::INT32 registerOp,
													   const MemoryOperand &memoryOp)
{
	Ceng::UINT8 modRM = 0;
	Ceng::UINT8 sib = 0;

	// Set register operand
	modRM += (registerOp & 7) << 3;

	// Check if sib-byte is present

	Ceng::BOOL useSib = false;

	if (memoryOp.indexReg != -1 || memoryOp.baseReg == X86::ESP.index
		|| (memoryOp.baseReg == X86::EBP.index && memoryOp.displacement == 0))
	{
		useSib = true;
	}

	Ceng::INT32 dispBytes = 0;

	if (useSib == false)
	{
		if (memoryOp.baseReg == -1)
		{
			modRM += 5; // pure disp32
			dispBytes = 4;
		}
		else
		{
			modRM += memoryOp.baseReg;

			if (memoryOp.displacement == 0)
			{
			}
			else if (memoryOp.displacement >= -128 && memoryOp.displacement <= 127)
			{
				modRM += 1 << 6; // has disp8
				dispBytes = 1;
			}
			else
			{
				modRM += 2 << 6; // has disp32
				dispBytes = 4;
			}		
		}
	}
	else
	{
		modRM += 4; // has sib-byte

		if (memoryOp.indexReg == -1)
		{
			sib += 4 << 3; // no index register
		}
		else
		{
			sib += memoryOp.indexReg << 3;
			sib += memoryOp.indexScale << 6;
		}

		if (memoryOp.baseReg == -1 || memoryOp.baseReg == X86::EBP.index)
		{
			sib += 5;
		}
		else
		{
			sib += memoryOp.baseReg;
		}

		if (memoryOp.displacement == 0)
		{
			if (memoryOp.baseReg == X86::EBP.index)
			{
				modRM += 1 << 6; // has disp8
				dispBytes = 1;
			}
		}
		else if (memoryOp.displacement >= -128 && memoryOp.displacement <= 127)
		{
			modRM += 1 << 6; // has disp8
			dispBytes = 1;
		}
		else
		{
			modRM += 2 << 6; // has disp32
			dispBytes = 4;
		}		
	}

	destBuffer[0] = modRM;

	Ceng::INT32 length = 1;

	if (useSib == true)
	{
		destBuffer[length] = sib;
		length++;
	}

	if (dispBytes == 1)
	{
		destBuffer[length] = Ceng::INT8(memoryOp.displacement);
		length++;
	}
	else if (dispBytes == 4)
	{
		Ceng::INT32 *dword = (Ceng::INT32*)&destBuffer[length];

		*dword = memoryOp.displacement;
		length += 4;
	}

	return length;
}