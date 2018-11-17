/*****************************************************************************
*
* x86-vex-prefix.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-vex-prefix.h"
#include "../include/build-params.h"

using namespace X86;

VEX_Prefix::VEX_Prefix()
{
	bytes = 0;
}

VEX_Prefix::VEX_Prefix(const VEX_BYTES bytes)
{	
	SetBytes(bytes);
}

void VEX_Prefix::SetBytes(const VEX_BYTES bytes)
{
	// Assume two-byte form

	vex[0] = THREE_BYTE_HEADER;

	// NOTE: REX.R , REX.X , REX.B are stored in one's complement
	//       and will be set if unused
	vex[1] = 7 << 5;

	// NOTE: VEX.vvvv is stored in one's complement 
	//       and will be set if unused
	vex[2] = 15 << 3;

	
	if (bytes == 2)
	{
		vex[0] = TWO_BYTE_HEADER;

		// NOTE: REX.R , VEX.vvvv are stored in one's complement 
		//       and will be set if unused
		vex[1] = 31 << 3;

		escapeCode = OPCODE_ESCAPE::BYTE_0F;
	}

	this->bytes = bytes;
}

void VEX_Prefix::Promote()
{
	vex[0] = THREE_BYTE_HEADER;

	vex[2] = vex[1] & 63;

	vex[1] = vex[1] & 128;

	bytes = 3;

	// Not encoded in 2-byte version, but can
	// have a value
	SetEscapeCode(escapeCode);
}

const Ceng::CRESULT VEX_Prefix::SetVectorSize(const VECTOR_SIZE size)
{
	if (bytes == 2)
	{
		vex[1] |= size << 2;
	}
	else
	{
		vex[2] |= size << 2;
	}

	return Ceng::CE_OK;
}

const Ceng::CRESULT VEX_Prefix::SetPrefixCode(const PREFIX_BYTE::value prefixCode)
{
	Ceng::UINT8 temp = 0;

	switch(prefixCode)
	{
	case PREFIX_BYTE::BYTE_66:
		temp = 1;
		break;
	case PREFIX_BYTE::BYTE_F3:
		temp = 2;
		break;
	case PREFIX_BYTE::BYTE_F2:			
		temp = 3;
		break;
	default:
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (bytes == 2)
	{
		vex[1] |= temp;
	}
	else if (bytes == 3)
	{
		vex[2] |= temp;
	}

	return Ceng::CE_OK;
}

const Ceng::CRESULT VEX_Prefix::SetEscapeCode(const OPCODE_ESCAPE::value escapeCode)
{
	this->escapeCode = escapeCode;

	if (bytes == 2)
	{
		if (escapeCode == OPCODE_ESCAPE::BYTE_0F)
		{
			return Ceng::CE_OK;
		}

		Promote();
	}

	switch(escapeCode)
	{
	case OPCODE_ESCAPE::BYTE_0F:
		vex[1] |= 1;
		break;
	case OPCODE_ESCAPE::BYTES_0F_38:
		vex[1] |= 2;
		break;
	case OPCODE_ESCAPE::BYTES_0F_3A:
		vex[1] |= 3;
		break;
	default:
		return Ceng::CE_ERR_INVALID_PARAM;
	}
	
	return Ceng::CE_OK;
}

const Ceng::CRESULT VEX_Prefix::Set_VVVV(const Ceng::INT32 index)
{
	if (index < 0)
	{
		return Ceng::CE_OK;
	}

	if (index > 15)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	// Write value

	Ceng::INT32 write = (index ^ -1) & 15; // Flip bits

	if (bytes == 2)
	{
		vex[1] &= ~(15 << 3); // Clear vvvv bits
		vex[1] |= write << 3;
	}
	else if (bytes == 3)
	{
		vex[2] &= ~(15 << 3); // Clear vvvv bits
		vex[2] |= write << 3;
	}

	return Ceng::CE_OK;
}

const Ceng::CRESULT VEX_Prefix::SetWideSize()
{
	if (bytes < 3)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	vex[2] |= (1 << 7); // Clear W-bit

	return Ceng::CE_OK;
}

const Ceng::CRESULT VEX_Prefix::SetRegField(const Ceng::INT32 index)
{
	if (index < 0)
	{
		return Ceng::CE_OK;
	}

	if (index > 15)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	Ceng::INT32 write = (index >> 3) ^ 1;
	
	vex[1] &= ~(1 << 7);
	vex[1] |= write << 7;
	
	return Ceng::CE_OK;
}

const Ceng::CRESULT VEX_Prefix::SetIndexReg(const Ceng::INT32 index)
{
	if (index < 0)
	{
		return Ceng::CE_OK;
	}

	if (index > 15)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (bytes == 2)
	{
		Promote();
	}

	Ceng::INT32 write = (index >> 3) ^ 1;

	if (bytes == 2)
	{
		// Promote to 3 byte form if REX.X is needed
		if (write == 0)
		{
			Promote();
		}
	}	
	
	vex[1] &= ~(1 << 6);
	vex[1] |= write << 6;

	return Ceng::CE_OK;
}

const Ceng::CRESULT VEX_Prefix::SetBaseReg(const Ceng::INT32 index)
{
	if (index < 0)
	{
		return Ceng::CE_OK;
	}

	if (index > 15)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	Ceng::INT32 write = (index >> 3) ^ 1;

	if (bytes == 2)
	{
		// Promote to 3 byte form if REX.B is needed
		if (write == 0)
		{
			Promote();
		}
	}	
	
	vex[1] &= ~(1 << 5);
	vex[1] |= write << 5;

	return Ceng::CE_OK;
}



const Ceng::CRESULT VEX_Prefix::Encode(BuildParams *params,std::vector<Ceng::UINT8> &destBuffer) const
{
	Ceng::UINT32 k;

	for(k=0;k<bytes;k++)
	{
		destBuffer.push_back(vex[k]);
	}

	return Ceng::CE_OK;
}