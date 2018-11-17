/*****************************************************************************
*
* x86-rex-byte.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_REX_BYTE_H
#define X86_REX_BYTE_H

#include <datatypes/basic-types.h>
#include <datatypes/return-val.h>

namespace X86
{
	class REX_Byte
	{
	protected:
		Ceng::UINT8 rex;

	public:
		REX_Byte();
		~REX_Byte();

		void SetWideSize();

		const Ceng::CRESULT SetRegField(const Ceng::INT32 index);

		const Ceng::CRESULT SetIndexReg(const Ceng::INT32 index);

		const Ceng::CRESULT SetBaseReg(const Ceng::INT32 index);

		operator Ceng::UINT8() const;
	};
}

#endif