/*****************************************************************************
*
* x86-sib.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_SIB_H
#define X86_SIB_H

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/boolean.h>
#include <ceng/datatypes/return-val.h>

#include <vector>

namespace X86
{
	class BuildParams;

	class SIB_Byte
	{
	protected:

		// SIB byte. Encoding:
		// 7:6 - index scale
		// 5:3 - index register
		// 2:0 - base register
		Ceng::UINT8 sib;

		Ceng::BOOL used;

	public:

		// Allowed multipliers for [reg*scale] type
		// memory access
		enum INDEX_SCALE
		{
			ONE = 0 ,
			TWO = 1 ,
			FOUR = 2 ,
			EIGHT = 8 ,

			// Unused. Forces enumeration storage to int32.
			FORCE_32B = 1 << 30 ,
		};

		SIB_Byte();
		~SIB_Byte();

		const Ceng::CRESULT SetBaseField(const Ceng::INT32 value);

		const Ceng::CRESULT SetIndexField(const Ceng::INT32 value);

		void NoBaseReg();
		void NoIndexReg();

		const Ceng::CRESULT SetIndexScale(const INDEX_SCALE value);

		const Ceng::BOOL IsPresent() const;

		const Ceng::CRESULT Encode(BuildParams *params,std::vector<Ceng::UINT8> &destBuffer) const;
	};
}

#endif