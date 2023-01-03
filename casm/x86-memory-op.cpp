/*****************************************************************************
*
* x86-memory-operand.cpp
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#include "x86-memory-op.h"
#include "data-item.h"

#include "x86-regs-alu-adr.h"

#include "build-params.h"
#include "encode-data.h"

#include "symbol-ref.h"

#include "section.h"

#include "code-label.h"

using namespace X86;

MemoryOperand::MemoryOperand() :
	symbol(nullptr), cpuModes(-1), baseReg(nullptr), indexReg(nullptr),
	indexScale(0), displacement(0)
{
	
}

void MemoryOperand::SetCPUmode()
{
	cpuModes = -1;

	Ceng::BOOL expand = false;

	if ( (baseReg != nullptr && baseReg->index > 7)
		|| (indexReg != nullptr && indexReg->index > 7) )
	{
		usesREX = true;
		cpuModes = CPU_MODE::X64;
	}
}

MemoryOperand::MemoryOperand(std::shared_ptr<Casm::CodeLabel>& symbol)
	: Operand(OPERAND_TYPE::MEM,false,X86::OPERAND_SIZE::IMPLICIT),
	symbol(symbol),baseReg(nullptr), indexReg(nullptr), displacement(0),
	indexScale(0)
{
	SetCPUmode();
}

MemoryOperand::MemoryOperand(const Ceng::INT32 displacement)
	: Operand(OPERAND_TYPE::MEM,false,OPERAND_SIZE::IMPLICIT),
	symbol(nullptr), baseReg(nullptr), indexReg(nullptr), indexScale(0),
	displacement(displacement)
{
	SetCPUmode();
}

MemoryOperand::MemoryOperand(const RegisterOperand &base)
	: Operand(OPERAND_TYPE::MEM,false,OPERAND_SIZE::IMPLICIT),
	symbol(nullptr), baseReg(&base), indexReg(nullptr), indexScale(0),
	displacement(0)
{
	SetCPUmode();
}

MemoryOperand::MemoryOperand(const OPERAND_SIZE::value operandSize,
							 const RegisterOperand &base)
	: Operand(OPERAND_TYPE::MEM,false,operandSize),
	symbol(nullptr), baseReg(&base), indexReg(nullptr), indexScale(0),
	displacement(0)
{
	SetCPUmode();
}

MemoryOperand::MemoryOperand(const RegisterOperand &base,const Ceng::INT32 displacement)
	: Operand(OPERAND_TYPE::MEM,false,OPERAND_SIZE::IMPLICIT),
	symbol(nullptr), baseReg(&base), indexReg(nullptr), indexScale(0), 
	displacement(displacement)
{
	SetCPUmode();
}

MemoryOperand::MemoryOperand(const OPERAND_SIZE::value operandSize,
									 const RegisterOperand &base,const Ceng::INT32 displacement)
	: Operand(OPERAND_TYPE::MEM,false,operandSize),
	symbol(nullptr), baseReg(&base), indexReg(nullptr), indexScale(0),
	displacement(displacement)
{
	SetCPUmode();
}

MemoryOperand::MemoryOperand(const RegisterOperand &base,const RegisterOperand &indexReg,
									 const Ceng::INT32 indexScale)
	: Operand(OPERAND_TYPE::MEM,false,OPERAND_SIZE::IMPLICIT),
	symbol(nullptr), baseReg(&base), indexReg(&indexReg), indexScale(indexScale),
	displacement(displacement)
{
	SetCPUmode();
}

MemoryOperand::MemoryOperand(const OPERAND_SIZE::value operandSize,
									 const RegisterOperand &base,const RegisterOperand &indexReg,
									 const Ceng::INT32 indexScale)
	: Operand(OPERAND_TYPE::MEM,false,operandSize),
	symbol(nullptr), baseReg(&base), indexReg(&indexReg), indexScale(indexScale),
	displacement(0)
{	
	SetCPUmode();
}

MemoryOperand::MemoryOperand(const OPERAND_SIZE::value operandSize,
									 const RegisterOperand& base,const RegisterOperand& indexReg,
									 const Ceng::INT32 indexScale,const Ceng::INT32 displacement)
	: Operand(OPERAND_TYPE::MEM,false,operandSize),
	symbol(nullptr), baseReg(&base), indexReg(&indexReg), indexScale(indexScale),
	displacement(displacement)
{	
	SetCPUmode();
}

Ceng::String MemoryOperand::ToString() const
{
	Ceng::String temp = "[";

	Ceng::BOOL prevOp = false;

	if (baseReg != nullptr)
	{
		temp += baseReg->name;
		prevOp = true;
	}

	if (indexReg != nullptr)
	{
		if (prevOp)
		{
			temp += " + ";
		}

		temp += indexReg->name;

		prevOp = true;
	}

	if (displacement == 0 && symbol != nullptr)
	{
		if (prevOp)
		{
			temp += " + ";
		}

		temp += symbol->Name();
	}
	else if (displacement != 0)
	{
		temp += " ";

		if (displacement > 0)
		{
			temp += "+ ";
		}

		temp += displacement;
	}

	temp += "]";

	return temp;
}


const Ceng::CRESULT MemoryOperand::EncodeAsOperand(BuildParams *params,EncodeData *encodeData,
												   const Ceng::UINT32 operandIndex) const
{
	if (encodeData->operandPlace[operandIndex] == OperandPlace::unused)
	{
		return Ceng::CE_OK;
	}

	// Error conditions

	if (indexReg != nullptr && (indexReg->index == X86::RIP.index))
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	// Check if sib-byte is present

	Ceng::BOOL useSib = false;

	if (indexReg != nullptr)
	{
		// Use of index register always requires SIB-byte
		useSib = true;
	}

	if (baseReg != nullptr)
	{
		if ((baseReg->index & 7) == ESP.index)
		{
			// Use of ESP or R12 as base register
			useSib = true;
		}
	}

	if (params->mode->cpuMode == CPU_MODE::X64)
	{
		// Using bare disp32 in 64-bit mode
		
		if (baseReg == nullptr && indexReg == nullptr)
		{
			useSib = true;
		}
	}
	else
	{
		// RIP-based addressing only available in x64

		if (baseReg != nullptr && baseReg->index == X86::RIP.index)
		{
			return Ceng::CE_ERR_INVALID_PARAM;
		}
	}

	if (useSib == false)
	{
		if (baseReg == nullptr)
		{
			// pure disp32

			encodeData->modRM.SetBaseField(5);

			encodeData->hasDisplacement = true;
			encodeData->dispEncoding = OPERAND_SIZE::DWORD;
		}
		else if (baseReg->index == X86::RIP.index)
		{	
			// RIP + disp32

			encodeData->modRM.SetBaseField(5); 

			encodeData->hasDisplacement = true;
			encodeData->dispEncoding = OPERAND_SIZE::DWORD;		
		}
		else
		{
			// Base register

			encodeData->modRM.SetBaseField(baseReg->index);

			encodeData->rex.SetBaseReg(baseReg->index);
			encodeData->vex.SetBaseReg(baseReg->index);

			if (displacement == 0)
			{
				// EBP or R13 as base register 
				if ( (baseReg->index & 7) == EBP.index)
				{
					// must encode as disp8 = 0

					encodeData->modRM.SetBasetype(ModRM_Byte::BASE_DISP8);

					encodeData->hasDisplacement = true;
					encodeData->dispEncoding = OPERAND_SIZE::BYTE;
				}
			}
			else if (displacement >= -128 && displacement <= 127)
			{
				// has disp8
				
				encodeData->modRM.SetBasetype(ModRM_Byte::BASE_DISP8);

				encodeData->hasDisplacement = true;
				encodeData->dispEncoding = OPERAND_SIZE::BYTE;
			}
			else
			{
				// has disp32

				encodeData->modRM.SetBasetype(ModRM_Byte::BASE_DISP32);

				encodeData->hasDisplacement = true;
				encodeData->dispEncoding = OPERAND_SIZE::DWORD;
			}		
		}
	}
	else
	{
		if (baseReg != nullptr && baseReg->index == X86::RIP.index)
		{
			return Ceng::CE_ERR_INVALID_PARAM;
		}

		// has sib-byte
		encodeData->modRM.UseSIB(); 

		if (indexReg == nullptr)
		{
			encodeData->sib.NoIndexReg();
		}
		else
		{
			// ESP cannot be used as index register
		
			// EXCEPTION: R12 can be used even though (R12.index & 7) == ESP.index

			if (indexReg->index == ESP.index)
			{
				return Ceng::CE_ERR_INVALID_PARAM;
			}

			encodeData->sib.SetIndexField(indexReg->index);

			encodeData->rex.SetIndexReg(indexReg->index);
			encodeData->vex.SetIndexReg(indexReg->index);

			SIB_Byte::INDEX_SCALE scaleValue;

			switch(indexScale)
			{
			case 1:
				scaleValue = SIB_Byte::ONE;
				break;
			case 2:
				scaleValue = SIB_Byte::TWO;
				break;
			case 4:
				scaleValue = SIB_Byte::FOUR;
				break;
			case 8:
				scaleValue = SIB_Byte::EIGHT;
				break;
			default:
				return Ceng::CE_ERR_INVALID_PARAM;
			}

			encodeData->sib.SetIndexScale(scaleValue);
		}

		if (baseReg == nullptr || (baseReg->index & 7) == X86::EBP.index)
		{
			encodeData->sib.NoBaseReg();
		}
		else
		{
			encodeData->sib.SetBaseField(baseReg->index);			
			encodeData->rex.SetBaseReg(baseReg->index);
			encodeData->vex.SetBaseReg(baseReg->index);
		}

		if (displacement == 0)
		{
			if (baseReg != nullptr)
			{
				if ((baseReg->index & 7) == X86::EBP.index)
				{
					// has disp8
					encodeData->modRM.SetBasetype(ModRM_Byte::BASE_DISP8);

					encodeData->hasDisplacement = true;
					encodeData->dispEncoding = OPERAND_SIZE::BYTE;
				}
			}			
		}
		else if (displacement >= -128 && displacement <= 127)
		{
			// has disp8
			encodeData->modRM.SetBasetype(ModRM_Byte::BASE_DISP8);

			encodeData->hasDisplacement = true;
			encodeData->dispEncoding = OPERAND_SIZE::BYTE;
		}
		else
		{
			// has disp32
			encodeData->modRM.SetBasetype(ModRM_Byte::BASE_DISP32);

			encodeData->hasDisplacement = true;
			encodeData->dispEncoding = OPERAND_SIZE::DWORD;
		}		
	}

	encodeData->displacement = displacement;

	if (symbol != nullptr)
	{
		Casm::REFERENCE_TYPE::value refType = Casm::REFERENCE_TYPE::ADDRESS;

		/*
		if (params->mode->cpuMode == CPU_MODE::X64)
		{
			refType = Casm::REFERENCE_TYPE::IP_RELATIVE;
		}
		*/

		std::shared_ptr<Casm::SymbolRef> temp =
			std::make_shared<Casm::SymbolRef>(symbol, params->out_dispOffset,
				params->out_dispSize, refType);

		params->section->AddSymbolRef(temp);
		params->memRef = temp;
	}

	return Ceng::CE_OK;
}