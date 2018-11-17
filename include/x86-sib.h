/*****************************************************************************
*
* x86-sib.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_SIB_H
#define X86_SIB_H

#include <datatypes/basic-types.h>
#include <datatypes/boolean.h>
#include <datatypes/return-val.h>

#include <vector>

namespace X86
{
	class BuildParams;

	class SIB_Byte
	{
	protected:
		Ceng::UINT8 sib;

		Ceng::BOOL used;

	public:

		enum INDEX_SCALE
		{
			ONE = 0 ,
			TWO = 1 ,
			FOUR = 2 ,
			EIGHT = 8 ,

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