/*****************************************************************************
*
* test-type.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_TEST_TYPE_H
#define _CENG_TEST_TYPE_H

namespace Ceng
{
	namespace TEST_TYPE
	{
		enum value
		{
			LESS = 1 ,
			LESS_EQ = 2 ,

			EQUAL = 3 ,
			NOT_EQUAL = 4 ,

			ABOVE = 5 ,
			ABOVE_EQ = 6 ,
			
			ALWAYS_PASS = 7 ,
			NEVER_PASS = 8 ,

			FORCE32B = 1 << 30 ,
		};
	};
};

#endif