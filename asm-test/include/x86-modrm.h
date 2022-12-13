/*****************************************************************************
*
* x86-modrm.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_MODRM_H
#define X86_MODRM_H

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/boolean.h>
#include <ceng/datatypes/return-val.h>

#include <vector>

namespace X86
{
	class BuildParams;

	class ModRM_Byte
	{
	protected:

		// Mod/RM encoding:
		// 7:6 - mod
		// 5:3 - reg
		// 2:0 - r/m
		Ceng::UINT8 modRM;

		Ceng::BOOL used;

	public:

		// Allowed Mod field values
		enum RM_TYPE
		{
			// addressing mode [reg]
			BASE = 0 ,

			// addressing mode [reg+disp8]
			BASE_DISP8 = 1 ,

			// addressing mode [reg+disp32]
			BASE_DISP32 = 2 ,

			// Register operand, no memory access
			REGISTER = 3 ,

			// Unused. Forces enum storage type to int32
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