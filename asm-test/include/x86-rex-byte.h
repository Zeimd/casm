/*****************************************************************************
*
* x86-rex-byte.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_REX_BYTE_H
#define X86_REX_BYTE_H

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/return-val.h>

namespace X86
{
	class REX_Byte
	{
	protected:
		// REX byte. Encoding:
		// 7:4 - 0100b
		// 3 - W : If set, operand size is 64 bits
		// 2 - R : Extension to Mod/RM reg field
		// 1 - X : Extension to SIB index field
		// 0 - B : Extension to Mod/RM r/m field, SIB base field, or Opcode reg field
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