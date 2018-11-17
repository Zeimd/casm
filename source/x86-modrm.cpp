/*****************************************************************************
*
* x86-modrm.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-modrm.h"

#include "../include/build-params.h"

using namespace X86;

ModRM_Byte::ModRM_Byte() : modRM(0),used(false)
{
}

ModRM_Byte::~ModRM_Byte()
{
}


void ModRM_Byte::UseSIB()
{
	modRM |= 4;
}

const Ceng::CRESULT ModRM_Byte::SetRegField(const Ceng::INT32 value)
{
	if (value < 0)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	modRM |= (value & 7) << 3;

	used = true;

	return Ceng::CE_OK;
}

const Ceng::CRESULT ModRM_Byte::SetBaseField(const Ceng::INT32 value)
{
	if (value < 0)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	modRM |= (value & 7);

	used = true;

	return Ceng::CE_OK;
}

const Ceng::CRESULT ModRM_Byte::SetBasetype(const RM_TYPE value)
{
	if (value == RM_TYPE::FORCE_32B)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	modRM |= value << 6;

	used = true;

	return Ceng::CE_OK;
}

const Ceng::BOOL ModRM_Byte::IsPresent() const
{
	return used;
}

const Ceng::CRESULT ModRM_Byte::Encode(BuildParams *params,std::vector<Ceng::UINT8> &destBuffer) const
{
	if (used)
	{
		destBuffer.push_back(modRM);
	}

	return Ceng::CE_OK;
}