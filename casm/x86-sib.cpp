/*****************************************************************************
*
* x86-sib.cpp
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#include "../include/x86-sib.h"

using namespace X86;

SIB_Byte::SIB_Byte() : sib(0),used(false)
{
}

SIB_Byte::~SIB_Byte()
{
}

void SIB_Byte::NoBaseReg()
{
	sib |= 5;
}

void SIB_Byte::NoIndexReg()
{
	sib |= 4 << 3;
}

const Ceng::CRESULT SIB_Byte::SetBaseField(const Ceng::INT32 value)
{
	if (value < 0)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}
	else
	{
		sib |= value & 7;
	}

	used = true;

	return Ceng::CE_OK;
}

const Ceng::CRESULT SIB_Byte::SetIndexField(const Ceng::INT32 value)
{
	if (value == 4)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	if (value < 0)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}
	else
	{
		sib |= (value & 7) << 3;
	}

	used = true;

	return Ceng::CE_OK;
}

const Ceng::CRESULT SIB_Byte::SetIndexScale(const INDEX_SCALE value)
{
	if (value == FORCE_32B)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	sib |= value << 6;

	used = true;

	return Ceng::CE_OK;
}

const Ceng::CRESULT SIB_Byte::Encode(BuildParams *params,std::vector<Ceng::UINT8> &destBuffer) const
{
	if (used)
	{
		destBuffer.push_back(sib);
	}

	return Ceng::CE_OK;
}