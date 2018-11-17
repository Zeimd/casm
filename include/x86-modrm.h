/*****************************************************************************
*
* x86-modrm.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_MODRM_H
#define X86_MODRM_H

#include <datatypes/basic-types.h>
#include <datatypes/boolean.h>
#include <datatypes/return-val.h>

#include <vector>

namespace X86
{
	class BuildParams;

	class ModRM_Byte
	{
	protected:
		Ceng::UINT8 modRM;

		Ceng::BOOL used;

	public:

		enum RM_TYPE
		{
			BASE = 0 ,
			BASE_DISP8 = 1 ,
			BASE_DISP32 = 2 ,
			REGISTER = 3 ,

			FORCE_32B = 1 << 30 ,

		};

		ModRM_Byte();

		~ModRM_Byte();

		void UseSIB();

		const Ceng::CRESULT SetRegField(const Ceng::INT32 value);

		const Ceng::CRESULT SetBaseField(const Ceng::INT32 value);

		const Ceng::CRESULT SetBasetype(const RM_TYPE value);

		const Ceng::BOOL IsPresent() const;

		const Ceng::CRESULT Encode(BuildParams *params,std::vector<Ceng::UINT8> &destBuffer) const;
	};
}

#endif