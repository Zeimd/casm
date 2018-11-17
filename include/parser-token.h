/*****************************************************************************
*
* parser-token.h
*
* By Jari Korkala 4/2014
*
*****************************************************************************/

#ifndef CASM_PARSER_TOKEN_H
#define CASM_PARSER_TOKEN_H

#include <datatypes/basic-types.h>

#include <list>

#include "symbol.h"

namespace Casm
{
	namespace ParserError
	{
		enum value
		{
			ok = 0 ,

			/**
			 * Absolute value is larger than datatype can
			 * represent.
			 */
			overflow = 1 ,

			/**
			 * Absolute value is smaller than datatype can
			 * represent.
			 */
			underflow = 1 << 1 ,

			/**
			 * When converting integer to float, if the integer cannot be represented
			 * exactly.
			 */
			not_exact = 1 << 2 ,

			/**
			 * When assigning negative value to unsigned integer or (inf,nan) to
			 * an integer type.
			 */
			not_representable = 1 << 3 ,

			/**
			 * Symbol not defined by this point in code.
			 */
			unknown_symbol = 1 << 4 ,

			/**
			 * Keyword not allowed here.
			 */
			illegal = 1 << 5 ,

			not_available = 1 << 6 ,

			/**
			 * Missing brackets, illegal operator chain, etc.
			 */
			syntax_error = 1 << 7 ,

			div_by_zero = 1 << 8 ,

			error = overflow | not_representable | illegal | div_by_zero,

			warning = not_exact | underflow ,

			force_32b = 1 << 30 ,

		};
	}

	struct TokenData
	{
		Ceng::INT32 line;
		Ceng::INT32 start;
		Ceng::INT32 end;

		Ceng::UINT32 errors;
	};

	class ParserState;

	class ParserToken
	{
	public:

		enum Type
		{
			unknown = 0 ,

			/**
			 * Token is an operator.
			 */
			op = 1 ,

			/**
			 * Token is a literal constant.
			 */
			literal_value = 1 << 1 ,
			
			datatype = 1 << 2 ,

			variable = 1 << 3 ,

			registerOp = 1 << 4 ,

			memoryOp = 1 << 5 ,

			instruction = 1 << 6 ,

			data_def = 1 << 7 ,

			separator = 1 << 8 ,

			name = 1 << 9 ,
			
			group = 1 << 29 ,
		
			force_32b = 1 << 30 ,
		};

	protected:

		ParserToken() : tokenType(unknown),data(TokenData())
		{
		}

		const Type tokenType;

		const TokenData data;

	public:

		ParserToken(const Type tokenType,const TokenData &data) : 
			tokenType(tokenType),data(data)
		{
		}	

		virtual ~ParserToken()
		{
		}

		const Type TokenType() const
		{
			return tokenType;
		}

		/**
		 * Executed after token type deduction during lexographic
		 * analyzer phase.
		 */
		virtual void LexographAction(ParserState *state)
		{
		}

		virtual const char* TypeString() const
		{
			return "ParserToken";
		}
	};

	
}

#endif