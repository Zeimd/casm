/*****************************************************************************
*
* parser-int64.cpp
*
* By Jari Korkala 5/2014
*
*****************************************************************************/

#include "../include/parser-int64.h"
#include "../include/parser-uint64.h"

/*
using namespace Casm;

Literal_Int64::Literal_Int64() : ParserLiteral(8,ParserBasicType::int64,TokenData())
{
	value = 0;
}

Literal_Int64::Literal_Int64(const Ceng::INT64 value,const TokenData &data) 
	: value(value),ParserLiteral(8,ParserBasicType::int64,data)
{
}

Literal_Int64::~Literal_Int64()
{
}

const Ceng::INT64 Literal_Int64::Value() const
{
	return value;
}

void Literal_Int64::ToBuffer(void *destBuffer) const
{
	Ceng::INT64 *ptr = (Ceng::INT64*)destBuffer;

	*ptr = value;
}

const std::shared_ptr<ParserOperand> Literal_Int64::SizeCast(ParserState *state,
															std::shared_ptr<ParserOperand> right_this,
															const Ceng::UINT32 newSize)
{
	if (newSize == 1)
	{
		// return int8
	}
	else if (newSize == 2)
	{
		// return int16
	}
	else if (newSize == 4)
	{
		// return int32
	}
	else if (newSize == 8)
	{
		return right_this;
	}

	return nullptr;
}

const std::shared_ptr<ParserOperand> Literal_Int64::BinaryAdd(ParserState *state,
																std::shared_ptr<ParserOperand> left_this,
																const std::shared_ptr<ParserOperand> right)
{
	if (right->Datatype() & ParserBasicType::floating)
	{
		return right->BinaryAdd(state,right,left_this);
	}

	if (right->Datatype() & ParserBasicType::integer)
	{
		if (right->SizeBytes() > sizeBytes)
		{
			return right->BinaryAdd(state,right,left_this);
		}
	}

	if (value < 0)
	{
		if (right->IsNegative())
		{
			Ceng::INT64 rhs = Ceng::INT64(*right);

			Ceng::INT64 cap = minValue - value;

			if (rhs < cap)
			{
				// negative overflow

				// TODO: Return integer of larger type
				return std::shared_ptr<ParserOperand>(new Literal_Int64(minValue,data));				
			}

			return std::shared_ptr<ParserOperand>(new Literal_Int64(value+rhs,data));
		}
		else
		{
			Ceng::UINT64 rhs = Ceng::UINT64(*right);

			if (rhs < Ceng::UINT64(-value))
			{
				// result is negative

				return std::shared_ptr<ParserOperand>(new Literal_Int64(rhs+value,data));
			}

			Ceng::UINT64 cap = ULLONG_MAX + value;

			if (rhs > cap)
			{
				// positive overflow

				// TODO: Convert to larger integer type

				return std::shared_ptr<ParserOperand>(new Literal_Uint64(ULLONG_MAX,data));
			}
			
			return std::shared_ptr<ParserOperand>(new Literal_Uint64(rhs+value,data));
		}
	}
	else
	{
		if (right->IsNegative())
		{
			return right->BinaryAdd(state,right,left_this);
		}

		Ceng::UINT64 lhs = value;
		Ceng::UINT64 rhs = Ceng::UINT64(*right);

		Ceng::UINT64 cap = ULLONG_MAX - lhs;

		if (rhs > cap)
		{
			// positive overflow

			return std::shared_ptr<ParserOperand>(new Literal_Uint64(ULLONG_MAX,data));
		}

		return std::shared_ptr<ParserOperand>(new Literal_Uint64(lhs+rhs,data));
	}

	return nullptr;
}

const std::shared_ptr<ParserOperand> Literal_Int64::BinarySub(ParserState *state,
																std::shared_ptr<ParserOperand> left_this,
																std::shared_ptr<ParserOperand> right)
{
	return nullptr;
}

const std::shared_ptr<ParserOperand> Literal_Int64::BinaryMul(ParserState *state,
																std::shared_ptr<ParserOperand> left_this,
																std::shared_ptr<ParserOperand> right)
{
	return nullptr;
}

const std::shared_ptr<ParserOperand> Literal_Int64::BinaryDiv(ParserState *state,
																std::shared_ptr<ParserOperand> left_this,
																std::shared_ptr<ParserOperand> right)
{
	return nullptr;
}

const std::shared_ptr<ParserOperand> Literal_Int64::operator *= (const Ceng::INT32 value)
{
	return std::shared_ptr<ParserOperand>( new Literal_Int64(this->value *value,data) );
}

const Ceng::BOOL Literal_Int64::RangeCheck(const Ceng::INT64 minValue,const Ceng::UINT64 maxValue) const
{
	if (value < 0)
	{
		return (value >= minValue);
	}

	if (value >= minValue && Ceng::UINT64(value) <= maxValue)
	{
		return true;
	}

	return false;
}

const Ceng::BOOL Literal_Int64::RangeCheck(const Ceng::FLOAT64 minValue,const Ceng::FLOAT64 maxValue) const
{
	if (value >= minValue && value <= maxValue)
	{
		return true;
	}

	return false;
}

const Ceng::BOOL Literal_Int64::UnderflowCheck(const Ceng::FLOAT64 minPosValue) const
{
	return false;
}

const Ceng::BOOL Literal_Int64::IsValueInt() const
{
	return true;
}

const Ceng::BOOL Literal_Int64::IsNegative() const
{
	return value < 0;
}

Literal_Int64::operator const Ceng::INT64() const
{
	return value;
}

Literal_Int64::operator const Ceng::UINT64() const
{
	return value;
}

Literal_Int64::operator const Ceng::FLOAT32() const
{
	return Ceng::FLOAT32(value);
}

*/