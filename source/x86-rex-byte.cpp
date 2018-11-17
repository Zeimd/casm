/*****************************************************************************
*
* x86-rex-byte.cpp
*
* By Jari Korkala 5/2014
*
* Moved REX_Byte functions from x86-rex-byte.h
*
*****************************************************************************/

#include "../include/x86-rex-byte.h"

using namespace X86;

REX_Byte::REX_Byte() : rex(0)
{
}

REX_Byte::~REX_Byte()
{
}

void REX_Byte::SetWideSize()
{
	rex |= 1 << 3;
}

const Ceng::CRESULT REX_Byte::SetRegField(const Ceng::INT32 index)
{
	if (index < 0)
	{
		return Ceng::CE_OK;
	}

	if (index > 15)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	rex |= (index >> 3) << 2;

	return Ceng::CE_OK;
}

const Ceng::CRESULT REX_Byte::SetIndexReg(const Ceng::INT32 index)
{
	if (index < 0)
	{
		return Ceng::CE_OK;
	}

	if (index > 15)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	rex |= (index >> 3) << 1;

	return Ceng::CE_OK;
}

const Ceng::CRESULT REX_Byte::SetBaseReg(const Ceng::INT32 index)
{
	if (index < 0)
	{
		return Ceng::CE_OK;
	}

	if (index > 15)
	{
		return Ceng::CE_ERR_INVALID_PARAM;
	}

	rex |= (index >> 3);

	return Ceng::CE_OK;
}

REX_Byte::operator Ceng::UINT8() const
{
	return rex;
}