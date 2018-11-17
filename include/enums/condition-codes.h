/*****************************************************************************
*
* condition-codes.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef CASM_CONDITION_CODES_H
#define CASM_CONDITION_CODES_H

namespace Casm
{
	namespace CONDITION
	{
		enum value
		{
			/**
				* unsigned a > b
				*/
			ABOVE = 1 ,
			NOT_BELOW_EQUAL = 1 ,

			/**
				* carry flag not set.
				*/
			NOT_CARRY = 1 ,


			/**
				* unsigned a >= b
				*/
			ABOVE_EQUAL = 2 ,
			NOT_BELOW = 2 ,

			/**
				* unsigned a < b
				*/
			BELOW = 3 ,
			NOT_ABOVE_EQUAL = 3 ,

			/**
				* carry flag set
				*/
			CARRY = 3 ,

			/**
				* unsigned a <= b
				*/
			BELOW_EQUAL = 4 ,
			NOT_ABOVE = 4 ,

			/**
				* CX-register is zero.
				*/
			CX_ZERO = 7 ,

			/**
				* ECX-register is zero.
				*/
			ECX_ZERO = 7 ,

			/**
				* RCX-register is zero.
				*/
			RCX_ZERO = 7 ,

			/**
				* a == b.
				*/
			EQUAL = 8,

			/**
				* a != b.
				*/
			NOT_EQUAL = 9 ,
			
			/**
				* Signed a > b.
				*/
			GREATER = 10 ,
			NOT_LESS_EQUAL = 10,

			/**
				* Signed a >= b.
				*/
			GREATER_EQUAL = 11 ,
			NOT_LESS = 11 ,

			/**
				* Signed a < b.
				*/
			LESS = 12 ,
			NOT_GREATER_EQUAL = 12 ,

			/**
				* Signed a <= b.
				*/
			LESS_EQUAL = 13 ,
			NOT_GREATER = 13 ,

			/**
				* Parity flag set.
				*/
			PARITY = 14 ,

			/**
				* Comparison result is even.
				*/
			PARITY_IS_EVEN = 14 ,
			
			/**
				* Parity flag not set. 
				*/
			NOT_PARITY = 15 ,

			/**
				* Result is odd.
				*/
			PARITY_IS_ODD = 15 ,

			/**
				* Result is zero.
				*/
			ZERO = 16 ,

			/**
				* Result is non-zero.
				*/
			NOT_ZERO = 17 ,

			/**
				* Signed overflow.
				*/
			OVERFLOW_FLAG = 18 ,

			/**
				* No signed overflow.
				*/
			NOT_OVERFLOW_FLAG = 19,

			/**
				* Result is negative.
				*/
			SIGN = 20 ,

			/**
				* Result is positive.
				*/
			NOT_SIGN = 21 ,
			
			FORCE_32B = 1 << 30 ,

		};
	}
}

#endif