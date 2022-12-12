/*****************************************************************************
*
* x86-fence.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-fence.h"

#include "../include/enums/x86-param-list.h"

#include "../include/encode-data.h"

#include "../include/x86-memory-op.h"

using namespace X86;

FenceOp::FenceOp(const Ceng::UINT8 opcode,const Ceng::UINT8 option,
				 const Ceng::UINT32 paramLists)
	: opcode(opcode),option(option),paramLists(paramLists)
{
}

FenceOp::~FenceOp()
{
}

const Ceng::CRESULT FenceOp::SelectOpcode(BuildParams *params,EncodeData *encodeData) const
{
	if (paramLists != 0)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
	encodeData->opcode = opcode;

	// Mark the parameter as register, because it is a different
	// instruction if a memory operand is used.
	encodeData->modRM.SetBasetype(ModRM_Byte::REGISTER);

	encodeData->modRM.SetRegField(option);

	return Ceng::CE_OK;
}

const Ceng::CRESULT FenceOp::SelectOpcode(BuildParams *params,
										  EncodeData *encodeData,const Operand *operand) const
{
	if ( !(paramLists & PARAM_LIST::MEM) )
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (operand->IsMemoryOperand())
	{
		return Select_M(params,encodeData,static_cast<const MemoryOperand*>(operand));
	}

	return Ceng::CE_ERR_INVALID_PARAM;
}

const Ceng::CRESULT FenceOp::Select_M(BuildParams *params,EncodeData *encodeData,
									  const MemoryOperand *operand) const
{
	encodeData->escapeCode = OPCODE_ESCAPE::BYTE_0F;
	encodeData->opcode = opcode;

	encodeData->modRM.SetRegField(option);

	encodeData->operandPlace[0] = OPERAND_PLACE::RM_FIELD;

	return Ceng::CE_OK;
}