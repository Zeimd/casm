/*****************************************************************************
*
* shader-const.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_SHADER_CONST_H
#define _CENG_SHADER_CONST_H

#include "../datatypes/return-val.h"
#include "../datatypes/boolean.h"

#include "base-interface.h"

namespace Ceng
{
	class ShaderConstant : public BASE_INTERFACE
	{
	protected:
		virtual ~ShaderConstant()
		{
		}
	
	public:
		ShaderConstant()
		{
		}
		
		//virtual const CRESULT GetValue(void *dest)=0;
		//virtual const CRESULT SetValue(void *source)=0;

		virtual const CRESULT SetFloat(const Ceng::FLOAT32 value) = 0;
		virtual const CRESULT SetFloat2(const Ceng::FLOAT32 *values) = 0;
		virtual const CRESULT SetFloat3(const Ceng::FLOAT32 *values) = 0;
		virtual const CRESULT SetFloat4(const Ceng::FLOAT32 *values) = 0;

		virtual const CRESULT SetInt(const Ceng::INT32 value) = 0;
		virtual const CRESULT SetInt2(const Ceng::INT32 *values) = 0;
		virtual const CRESULT SetInt3(const Ceng::INT32 *values) = 0;
		virtual const CRESULT SetInt4(const Ceng::INT32 *values) = 0;

		virtual const CRESULT SetBool(const Ceng::BOOL value) = 0;
		virtual const CRESULT SetBool2(const Ceng::BOOL *values) = 0;
		virtual const CRESULT SetBool3(const Ceng::BOOL *values) = 0;
		virtual const CRESULT SetBool4(const Ceng::BOOL *values) = 0;

		virtual const CRESULT SetMatrix_4x4(const Ceng::FLOAT32 *values,const Ceng::BOOL transpose) = 0;
	};

};

#endif