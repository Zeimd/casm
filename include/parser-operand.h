/*****************************************************************************
*
* parser-operand.h
*
* By Jari Korkala 5/2014
*
*****************************************************************************/

#ifndef CASM_PARSER_OPERAND_H
#define CASM_PARSER_OPERAND_H

#include <memory>

#include "parser-token.h"

#include "parser-state.h"

namespace Casm
{
	class ParserDatatype
	{
	public:

		enum Category
		{
			unknown = 0 ,

			integer = 1 ,
			floating = 1 << 1 ,
			boolean = 1 << 2 ,

			userdef = 1 << 3 ,

			force_32b = 1 << 30 ,
		};
		
	protected:

		const Ceng::UINT32 sizeBytes;
		const Category category;

	public:

		ParserDatatype(const Ceng::UINT32 sizeBytes,const Category category) :
			sizeBytes(sizeBytes),category(category)
		{
		}
	};

	namespace ParserBasicType
	{
		enum value
		{
			unknown = 0 ,

			int8 = 1 << 1 ,
			int16 = 1 << 2 ,
			int32 = 1 << 3 ,
			int64 = 1 << 4 ,

			uint8 = 1 << 5 ,
			uint16 = 1 << 6 ,
			uint32 = 1 << 7 ,
			uint64 = 1 << 8 ,

			float8 = 1 << 9 ,
			float16 = 1 << 10 ,
			float32 = 1 << 11 ,
			float64 = 1 << 12 ,
			float80 = 1 << 13 ,

			integer = int8 | int16 | int32 | int64 | int8 | int16 | int32 | int64 ,

			floating = float8 | float16 | float32 | float64 | float80 ,

			force_32b = 1 << 30 ,
		};
	}

	class ParserOperand : public ParserToken
	{
	protected:

		const ParserBasicType::value datatype;

		const Ceng::INT32 sizeBytes;

		Ceng::BOOL locked;

		ParserOperand() : ParserToken(),datatype(ParserBasicType::unknown),sizeBytes(0)
		{
			locked = false;
		}

		ParserOperand(const ParserToken::Type type,const ParserBasicType::value datatype,
						const Ceng::UINT32 sizeBytes,const TokenData &data) 
			: ParserToken(type,data),datatype(datatype),sizeBytes(sizeBytes)
		{
			locked = false;
		}

	public:
		virtual ~ParserOperand()
		{
		}

		const Ceng::INT32 SizeBytes() const
		{
			return sizeBytes;
		}

		const ParserBasicType::value Datatype() const
		{
			return datatype;
		}

		const Ceng::BOOL Locked() const
		{
			return locked;
		}

		void Lock()
		{
			locked = true;
		}

		virtual const std::shared_ptr<ParserOperand> SizeCast(ParserState *state,
																std::shared_ptr<ParserOperand> right_this,
																const Ceng::UINT32 newSize)
		{
			return nullptr;
		}

		virtual const std::shared_ptr<ParserOperand> BinaryAdd(ParserState *state,
																std::shared_ptr<ParserOperand> left_this,
																std::shared_ptr<ParserOperand> right)
		{
			return nullptr;
		}
		
		virtual const std::shared_ptr<ParserOperand> BinarySub(ParserState *state,
																std::shared_ptr<ParserOperand> left_this,
																std::shared_ptr<ParserOperand> right)
		{
			return nullptr;
		}

		virtual const std::shared_ptr<ParserOperand> BinaryMul(ParserState *state,
																std::shared_ptr<ParserOperand> left_this,
																std::shared_ptr<ParserOperand> right)
		{
			return nullptr;
		}
		
		virtual const std::shared_ptr<ParserOperand> BinaryDiv(ParserState *state,
																std::shared_ptr<ParserOperand> left_this,
																std::shared_ptr<ParserOperand> right)
		{
			return nullptr;
		}
		
		virtual const std::shared_ptr<ParserOperand> operator *= (const Ceng::INT32 value)
		{
			return nullptr;
		}

		virtual const Ceng::BOOL RangeCheck(const Ceng::INT64 minValue,const Ceng::UINT64 maxValue) const
		{
			return false;
		}

		virtual const Ceng::BOOL RangeCheck(const Ceng::FLOAT64 minValue,const Ceng::FLOAT64 maxValue) const
		{
			return false;
		}

		virtual const Ceng::BOOL UnderflowCheck(const Ceng::FLOAT64 minPosValue) const
		{
			return false;
		}

		virtual const Ceng::BOOL IsValueInt() const
		{
			return false;
		}

		virtual const Ceng::BOOL IsNegative() const
		{
			return false;
		}

		virtual operator const Ceng::FLOAT32() const
		{
			return 0.0f;
		}

		virtual operator const Ceng::UINT64() const
		{
			return 0;
		}

		virtual operator const Ceng::INT64() const
		{
			return 0;
		}
	};
}

#endif