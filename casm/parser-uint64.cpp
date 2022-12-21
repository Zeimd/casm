/*****************************************************************************
*
* parser-uint64.cpp
*
* By Jari Korkala 4/2014
*
*****************************************************************************/

#include "parser-uint64.h"
#include "parser-int64.h"

/*

using namespace Casm;

Literal_Uint64::Literal_Uint64() : ParserLiteral(8,ParserBasicType::uint64,TokenData())
{
	value = 0;
}

Literal_Uint64::Literal_Uint64(const Ceng::UINT64 value,const TokenData &data) 
	: value(value),ParserLiteral(8,ParserBasicType::uint64,data)
{
}

Literal_Uint64::Literal_Uint64(const Ceng::UINT64 value,const X86::OPERAND_SIZE::value opSize,const TokenData &data)
	: value(value),ParserLiteral(8,ParserBasicType::uint64,opSize,data)
{
}


Literal_Uint64::~Literal_Uint64()
{
}

const Ceng::UINT64 Literal_Uint64::Value() const
{
	return value;
}

void Literal_Uint64::ToBuffer(void *destBuffer) const
{
	Ceng::UINT64 *ptr = (Ceng::UINT64*)destBuffer;

	*ptr = value;
}

const std::shared_ptr<ParserOperand> Literal_Uint64::SizeCast(ParserState *state,
															std::shared_ptr<ParserOperand> right_this,
															const Ceng::UINT32 newSize)
{
	Ceng::UINT64 max=0;

	if (newSize == 1)
	{
		max = UCHAR_MAX;
	}
	else if (newSize == 2)
	{
		max = USHRT_MAX;
	}
	else if (newSize == 4)
	{
		max = ULONG_MAX;
	}
	else if (newSize == 8)
	{
		return std::shared_ptr<ParserOperand>(new Literal_Uint64(value,X86::OPERAND_SIZE::QWORD,data));
	}
	else
	{
		return nullptr;
	}

	Ceng::UINT64 out;

	if (value > max)
	{
		// overflow
		out = max;
	}
	else
	{
		out = value;
	}

	return std::shared_ptr<ParserOperand>( new Literal_Uint64(out,X86::OPERAND_SIZE::DWORD,data) );

}

const std::shared_ptr<ParserOperand> Literal_Uint64::BinaryAdd(ParserState *state,
																std::shared_ptr<ParserOperand> left_this,
																std::shared_ptr<ParserOperand> right)
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

	if (right->IsNegative())
	{
		Ceng::INT64 rhs = Ceng::INT64(*right);

		if (Ceng::UINT64(-rhs) > value)
		{
			// left+right < 0

			return std::shared_ptr<ParserOperand>(new Literal_Int64( -Ceng::INT64(-rhs - value),data));
		}
		else
		{
			return std::shared_ptr<ParserOperand>(new Literal_Uint64(value+rhs,data));
		}
	}
	else
	{
		Ceng::UINT64 rhs = Ceng::UINT64(*right);

		if (rhs > (maxValue - value) )
		{
			// Error : operator + : overflow
			
			// TODO: Increased precision integers

			return std::shared_ptr<ParserOperand>(new Literal_Uint64(0,data));
		}
		else
		{
			return std::shared_ptr<ParserOperand>(new Literal_Uint64(value+rhs,data));
		}
	}

	return nullptr;
}

const std::shared_ptr<ParserOperand> Literal_Uint64::BinarySub(ParserState *state,
																std::shared_ptr<ParserOperand> left_this,
																std::shared_ptr<ParserOperand> right)
{
	return nullptr;
}

const std::shared_ptr<ParserOperand> Literal_Uint64::BinaryMul(ParserState *state,
																std::shared_ptr<ParserOperand> left_this,
																std::shared_ptr<ParserOperand> right) 
{
	return nullptr;
}

const std::shared_ptr<ParserOperand> Literal_Uint64::BinaryDiv(ParserState *state,
																std::shared_ptr<ParserOperand> left_this,
																std::shared_ptr<ParserOperand> right)
{
	return nullptr;
}

const std::shared_ptr<ParserOperand> Literal_Uint64::operator *= (const Ceng::INT32 value)
{
	if (value >= 0)
	{
		return std::shared_ptr<ParserOperand>(new Literal_Uint64(this->value *value,data));
	}

	if (this->value < Literal_Int64::maxValue)
	{
		return std::shared_ptr<ParserOperand>(new Literal_Int64( Ceng::INT64(this->value)*value,data));
	}

	return nullptr;
}


const Ceng::BOOL Literal_Uint64::RangeCheck(const Ceng::INT64 minValue,const Ceng::UINT64 maxValue) const
{
	if (minValue < 0)
	{
		return value <= maxValue;
	}

	if (value >= Ceng::UINT64(minValue) && value <= maxValue)
	{
		return true;
	}

	return false;
}

const Ceng::BOOL Literal_Uint64::RangeCheck(const Ceng::FLOAT64 minValue,const Ceng::FLOAT64 maxValue) const
{
	if (value >= minValue && value <= maxValue)
	{
		return true;
	}

	return false;
}

const Ceng::BOOL Literal_Uint64::UnderflowCheck(const Ceng::FLOAT64 minPosValue) const
{
	return false;
}

const Ceng::BOOL Literal_Uint64::IsValueInt() const
{
	return true;
}

const Ceng::BOOL Literal_Uint64::IsNegative() const
{
	return false;
}

Literal_Uint64::operator const Ceng::INT64() const
{
	return value;
}

Literal_Uint64::operator const Ceng::UINT64() const
{
	return value;
}

Literal_Uint64::operator const Ceng::FLOAT32() const
{
	return Ceng::FLOAT32(value);
}

*/