/*****************************************************************************
*
* parser-float.cpp
*
* By Jari Korkala 4/2014
*
*****************************************************************************/

#include "../include/parser-float.h"

#include <math.h>

using namespace Casm;

FloatLiteral::FloatLiteral() : ParserLiteral(4,ParserBasicType::float32,TokenData())
{
	value = 0.0f;
}

FloatLiteral::FloatLiteral(const Ceng::FLOAT32 value,const Casm::TokenData &data) 
	: value(value),ParserLiteral(4,ParserBasicType::float32,data)
{
}

FloatLiteral::~FloatLiteral()
{
}

const Ceng::FLOAT32 FloatLiteral::Value() const
{
	return value;
}

void FloatLiteral::ToBuffer(void *destBuffer) const
{
	Ceng::FLOAT32 *ptr = (Ceng::FLOAT32*)destBuffer;

	*ptr = value;
}

const std::shared_ptr<ParserOperand> FloatLiteral::SizeCast(ParserState *state,
															std::shared_ptr<ParserOperand> right_this,
															const Ceng::UINT32 newSize)
{
	if (newSize == 1)
	{
		// return mini-float
	}
	else if (newSize == 2)
	{
		// return float16
	}
	else if (newSize == 4)
	{
		return right_this;
	}
	else if (newSize == 8)
	{
		// return float64
	}
	else if (newSize == 10)
	{
		// return float80
	}

	return nullptr;
}

const Ceng::UINT32 FloatLiteral::SafetyCheck(const ParserOperand &other) const
{
	Ceng::UINT32 out = 0;

	if (other.Datatype() & ParserBasicType::integer)
	{
		Ceng::BOOL isExact = other.RangeCheck(-maxPosInt,maxPosInt);

		if ( !isExact)
		{
			// warning : conversion x->float : loss of precision
			out |= ParserError::not_exact;
		}
	}
	else if (other.Datatype() & ParserBasicType::floating)
	{
		Ceng::BOOL isUnderflow = other.UnderflowCheck(floatMinPosValue);
		
		if (isUnderflow)
		{
			// error : conversion x->float : loss of precision

			out |= ParserError::underflow;
		}
	}

	Ceng::BOOL overflowTest = other.RangeCheck(-floatMaxPosValue,floatMaxPosValue);

	if ( !overflowTest)
	{
		// error : conversion x->float : doesn't fit to datatype

		out |= ParserError::overflow;
	}

	return out;
}

const std::shared_ptr<ParserOperand> FloatLiteral::BinaryAdd(ParserState *state,
															 std::shared_ptr<ParserOperand> left_this,
															 std::shared_ptr<ParserOperand> right)
{
	if (right->Datatype() == ParserBasicType::float64 ||
		right->Datatype() == ParserBasicType::float80)
	{
		return right->BinaryAdd(state,right,left_this);
	}

	Ceng::UINT32 check = SafetyCheck(*right);

	if ( check & ParserError::error)
	{
		return  std::shared_ptr<ParserOperand>(new FloatLiteral(0.0,data));
	}

	Ceng::FLOAT32 rhs = Ceng::FLOAT32(*right);

	if (value >= 0)
	{
		Ceng::FLOAT32 cap = floatMaxPosValue - value;

		if (rhs > cap)
		{
			// error : operator + : positive overflow
			return  std::shared_ptr<ParserOperand>(new FloatLiteral(0.0,data));
		}
	}
	else if (value < 0)
	{
		Ceng::FLOAT32 cap = -floatMaxPosValue - value;

		if (rhs < cap)
		{
			// error : operator + : negative overflow
			return  std::shared_ptr<ParserOperand>(new FloatLiteral(0.0,data));
		}
	}

	return  std::shared_ptr<ParserOperand>(new FloatLiteral(value + rhs,data));
}

const std::shared_ptr<ParserOperand> FloatLiteral::BinarySub(ParserState *state,
															 std::shared_ptr<ParserOperand> left_this,
															 std::shared_ptr<ParserOperand> right)
{
	/*
	Ceng::UINT32 check = SafetyCheck(*right);

	if ( check & ParserError::error)
	{
		return nullptr;
	}

	Ceng::FLOAT32 rhs = Ceng::FLOAT32(*other);

	if (value >= 0)
	{
		Ceng::FLOAT32 cap = floatMaxPosValue - value;

		if (rhs < -cap)
		{
			// error : operator + : positive overflow
		}
	}
	else if (value < 0)
	{
		Ceng::FLOAT32 cap = -floatMaxPosValue - value;

		if (rhs > -cap)
		{
			// error : operator + : negative overflow
		}
	}

	return new FloatLiteral(value - rhs,data);
	*/

	return nullptr;
}

const std::shared_ptr<ParserOperand> FloatLiteral::BinaryMul(ParserState *state,
															 std::shared_ptr<ParserOperand> left_this,
															 std::shared_ptr<ParserOperand> right)
{
	/*
	Ceng::UINT32 check = SafetyCheck(*other);

	if ( check & ParserError::error)
	{
		return nullptr;
	}

	Ceng::FLOAT32 rhs = Ceng::FLOAT32(*other);

	// Overflow check

	ParserOperand *temp = new FloatLiteral(value * rhs,data);

	return temp;
	*/

	return nullptr;
}

const std::shared_ptr<ParserOperand> FloatLiteral::BinaryDiv(ParserState *state,
															 std::shared_ptr<ParserOperand> left_this,
															 std::shared_ptr<ParserOperand> right) 
{
	/*
	Ceng::UINT32 check = SafetyCheck(*other);

	if ( check & ParserError::error)
	{
		return nullptr;
	}

	Ceng::FLOAT32 rhs = Ceng::FLOAT32(*other);

	if (rhs == 0.0f)
	{
		// Division by zero error

		return nullptr;
	}

	return new FloatLiteral(value / rhs,data);
	*/

	return nullptr;
}

const std::shared_ptr<ParserOperand> FloatLiteral::operator *= (const Ceng::INT32 value) 
{
	return std::shared_ptr<ParserOperand>(new FloatLiteral(this->value *value,data));
}

const Ceng::BOOL FloatLiteral::RangeCheck(const Ceng::INT64 minValue,const Ceng::UINT64 maxValue) const
{
	if (value >= minValue && value <= maxValue)
	{
		return true;
	}

	return false;
}

const Ceng::BOOL FloatLiteral::RangeCheck(const Ceng::FLOAT64 minValue,const Ceng::FLOAT64 maxValue) const
{
	const Ceng::FLOAT64 temp = Ceng::FLOAT64(value);

	if (temp >= minValue && temp <= maxValue)
	{
		return true;
	}

	return false;
}

const Ceng::BOOL FloatLiteral::UnderflowCheck(const Ceng::FLOAT64 minPosValue) const
{
	if (fabs(value) < minPosValue)
	{
		return true;
	}

	return false;
}

const Ceng::BOOL FloatLiteral::IsValueInt() const
{
	return (ceil(value) == value);
}

const Ceng::BOOL FloatLiteral::IsNegative() const
{
	return value < 0.0;
}

FloatLiteral::operator const Ceng::INT64() const
{
	return Ceng::INT64(value);
}

FloatLiteral::operator const Ceng::FLOAT32() const
{
	return value;
}

FloatLiteral::operator const Ceng::UINT64() const
{
	return Ceng::UINT64(value);
}