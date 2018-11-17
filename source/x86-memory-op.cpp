/*****************************************************************************
*
* x86-memory-operand.cpp
*
* By Jari Korkala 1/2014
*
*****************************************************************************/

#include "../include/x86-memory-op.h"
#include "../include/data-item.h"

#include "../include/x86-regs-alu-adr.h"

#include "../include/build-params.h"
#include "../include/encode-data.h"

using namespace X86;

MemoryOperand::MemoryOperand()
{
	symbol = nullptr;
	
	cpuModes = -1;

	baseReg = -1;
	indexReg = -1;
	indexScale = 0;
			
	displacement = 0;
}

void MemoryOperand::SetCPUmode()
{
	cpuModes = -1;
	if (baseReg > 7 || indexReg > 7)
	{
		usesREX = true;
		cpuModes = CPU_MODE::X64;
	}
}

MemoryOperand::MemoryOperand(std::shared_ptr<Symbol> symbol)
	: Operand(OPERAND_TYPE::MEM,false,symbol->AsData()->elementSize)
{
	this->symbol = symbol;

	baseReg = -1;

	indexReg = -1;
	indexScale = -1;

	displacement = 0;

	SetCPUmode();
}

MemoryOperand::MemoryOperand(const Ceng::INT32 displacement)
	: Operand(OPERAND_TYPE::MEM,false,OPERAND_SIZE::IMPLICIT)
{
	symbol = nullptr;

	baseReg = -1;

	indexReg = -1;
	indexScale = 0;

	this->displacement = displacement;

	SetCPUmode();
}

MemoryOperand::MemoryOperand(const RegisterOperand &base)
	: Operand(OPERAND_TYPE::MEM,false,OPERAND_SIZE::IMPLICIT)
{
	symbol = nullptr;

	baseReg = base.index;

	indexReg = -1;
	indexScale = 0;

	displacement = 0;

	SetCPUmode();
}

MemoryOperand::MemoryOperand(const OPERAND_SIZE::value operandSize,
							 const RegisterOperand &base)
	: Operand(OPERAND_TYPE::MEM,false,operandSize)
{
	symbol = nullptr;

	baseReg = base.index;

	indexReg = -1;
	indexScale = 0;

	displacement = 0;

	SetCPUmode();
}

MemoryOperand::MemoryOperand(const RegisterOperand &base,const Ceng::INT32 displacement)
	: Operand(OPERAND_TYPE::MEM,false,OPERAND_SIZE::IMPLICIT)
{
	symbol = nullptr;

	baseReg = base.index;
	indexReg = -1;
	indexScale = 0;

	this->displacement = displacement;

	SetCPUmode();
}

MemoryOperand::MemoryOperand(const OPERAND_SIZE::value operandSize,
									 const RegisterOperand &base,const Ceng::INT32 displacement)
	: Operand(OPERAND_TYPE::MEM,false,operandSize)
{
	symbol = nullptr;

	baseReg = base.index;
	indexReg = -1;
	indexScale = 0;

	this->displacement = displacement;

	SetCPUmode();
}

MemoryOperand::MemoryOperand(const RegisterOperand &base,const RegisterOperand &indexReg,
									 const Ceng::INT32 indexScale)
	: Operand(OPERAND_TYPE::MEM,false,OPERAND_SIZE::IMPLICIT)
{
	symbol = nullptr;

	baseReg = base.index;
	this->indexReg = indexReg.index;
	this->indexScale = indexScale;

	this->displacement = 0;
	
	SetCPUmode();
}

MemoryOperand::MemoryOperand(const OPERAND_SIZE::value operandSize,
									 const RegisterOperand &base,const RegisterOperand &indexReg,
									 const Ceng::INT32 indexScale)
	: Operand(OPERAND_TYPE::MEM,false,operandSize)
{
	symbol = nullptr;

	baseReg = base.index;
	this->indexReg = indexReg.index;
	this->indexScale = indexScale;

	this->displacement = 0;
	
	SetCPUmode();
}

MemoryOperand::MemoryOperand(const OPERAND_SIZE::value operandSize,
									 const RegisterOperand *base,const RegisterOperand *indexReg,
									 const Ceng::INT32 indexScale,const Ceng::INT32 displacement)
	: Operand(OPERAND_TYPE::MEM,false,operandSize)
{
	symbol = nullptr;

	baseReg = -1;
	if (base != nullptr)
	{
		baseReg = base->index;
	}

	this->indexReg = -1;
	this->indexScale = 0;

	if (indexReg != nullptr)
	{
		this->indexReg = indexReg->index;
		this->indexScale = indexScale;
	}	

	this->displacement = displacement;
	
	SetCPUmode();
}

const Ceng::CRESULT MemoryOperand::EncodeAsOperand(BuildParams *params,EncodeData *encodeData,
												   const Ceng::UINT32 operandIndex) const
{
	if (encodeData->operandPlace[operandIndex] == OPERAND_PLACE::NOT_USED)
	{
		return Ceng::CE_OK;
	}

	// Error conditions

	if (indexReg == X86::RIP.index)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	// Check if sib-byte is present

	Ceng::BOOL useSib = false;

	if (indexReg != -1)
	{
		// Use of index register always requires SIB-byte
		useSib = true;
	}

	if ( (baseReg & 7) == ESP.index) 
	{
		// Use of ESP or R12 as base register
		useSib = true;
	}

	if (params->mode->cpuMode == CPU_MODE::X64)
	{
		// Using bare disp32 in 64-bit mode
		
		if (baseReg == -1 && indexReg == -1)
		{
			useSib = true;
		}
	}
	else
	{
		// RIP-based addressing only available in x64

		if (baseReg == X86::RIP.index)
		{
			return Ceng::CE_ERR_INVALID_PARAM;
		}
	}

	if (useSib == false)
	{
		if (baseReg == X86::RIP.index)
		{	
			// RIP + disp32

			encodeData->modRM.SetBaseField(5); 

			encodeData->hasDisplacement = true;
			encodeData->dispEncoding = OPERAND_SIZE::DWORD;		
		}

		if (baseReg == -1)
		{
			// pure disp32

			encodeData->modRM.SetBaseField(5); 
			
			encodeData->hasDisplacement = true;
			encodeData->dispEncoding = OPERAND_SIZE::DWORD;
		}
		else
		{
			// Base register

			encodeData->modRM.SetBaseField(baseReg);

			encodeData->rex.SetBaseReg(baseReg);
			encodeData->vex.SetBaseReg(baseReg);

			if (displacement == 0)
			{
				// EBP or R13 as base register 
				if ( (baseReg & 7) == EBP.index)
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
		if (baseReg == X86::RIP.index)
		{
			return Ceng::CE_ERR_INVALID_PARAM;
		}

		// has sib-byte
		encodeData->modRM.UseSIB(); 

		if (indexReg == -1)
		{
			encodeData->sib.NoIndexReg();
		}
		else
		{
			// ESP cannot be used as index register
		
			// EXCEPTION: R12 can be used even though (R12.index & 7) == ESP.index

			if (indexReg == ESP.index)
			{
				return Ceng::CE_ERR_INVALID_PARAM;
			}

			encodeData->sib.SetIndexField(indexReg);

			encodeData->rex.SetIndexReg(indexReg);
			encodeData->vex.SetIndexReg(indexReg);

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

		if (baseReg == -1 || (baseReg & 7) == X86::EBP.index)
		{
			encodeData->sib.NoBaseReg();
		}
		else
		{
			encodeData->sib.SetBaseField(baseReg);			
			encodeData->rex.SetBaseReg(baseReg);
			encodeData->vex.SetBaseReg(baseReg);
		}

		if (displacement == 0)
		{
			if ( (baseReg & 7) == X86::EBP.index)
			{
				// has disp8
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

	encodeData->displacement = displacement;

	/*
	if (memoryOp->symbol != nullptr)
	{
		REFERENCE_TYPE::value refType = REFERENCE_TYPE::ADDRESS;

		if (params->mode->cpuMode == CPU_MODE::X64)
		{
			refType = REFERENCE_TYPE::IP_RELATIVE;
		}

		SymbolRef *temp = new SymbolRef(memoryOp->symbol,params->out_dispOffset,
											params->out_dispSize,refType);

		params->codeElement->references.push_back(temp);
		params->memRef = temp;
	}
	*/

	return Ceng::CE_OK;
}