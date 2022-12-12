/******************************************************************************
*
* parser-float.h
*
* By Jari Korkala 5/2014
*
******************************************************************************/

#ifndef CASM_PARSER_FLOAT_H
#define CASM_PARSER_FLOAT_H

/*
#include "parser-literal.h"

#include <float.h>

namespace Casm
{
	// Maximum absolute value that is representable. Overflow if
	// not possible.
	const Ceng::FLOAT32 floatMaxPosValue = FLT_MAX;

	// Minimum absolute value that is representable. Underflow
    // if not possible.
	const Ceng::FLOAT32 floatMinPosValue = FLT_MIN;

	class FloatLiteral : public ParserLiteral
	{
	protected:
		Ceng::FLOAT32 value;

	public:

		// All signed integers up to this value can be represented
		// exactly.
		// NOTE: Warning if not possible.
		static const Ceng::INT64 maxPosInt = (1 << 24);


		FloatLiteral();
		FloatLiteral(const Ceng::FLOAT32 value,const TokenData &data);

		virtual ~FloatLiteral();

		const Ceng::FLOAT32 Value() const;

		virtual void ToBuffer(void *destBuffer) const override;

	
		virtual const std::shared_ptr<ParserOperand> BinaryAdd(ParserState *state,
																std::shared_ptr<ParserOperand> left_this,
																std::shared_ptr<ParserOperand> right) override;

		virtual const std::shared_ptr<ParserOperand> BinarySub(ParserState *state,
																std::shared_ptr<ParserOperand> left_this,
																std::shared_ptr<ParserOperand> right) override;


		virtual const std::shared_ptr<ParserOperand> BinaryMul(ParserState *state,
																std::shared_ptr<ParserOperand> left_this,
																std::shared_ptr<ParserOperand> right) override;
		
		
		virtual const std::shared_ptr<ParserOperand> BinaryDiv(ParserState *state,
																std::shared_ptr<ParserOperand> left_this,
																std::shared_ptr<ParserOperand> right) override;
	
		virtual const std::shared_ptr<ParserOperand> operator *= (const Ceng::INT32 value) override;

		virtual const Ceng::BOOL RangeCheck(const Ceng::INT64 minValue,const Ceng::UINT64 maxValue) const override;
		virtual const Ceng::BOOL RangeCheck(const Ceng::FLOAT64 minValue,const Ceng::FLOAT64 maxValue) const override;

		virtual const Ceng::BOOL UnderflowCheck(const Ceng::FLOAT64 minPosValue) const override;

		const Ceng::BOOL IsValueInt() const override;

		const Ceng::BOOL IsNegative() const override;

		virtual operator const Ceng::FLOAT32() const override;
		virtual operator const Ceng::UINT64() const override;
		virtual operator const Ceng::INT64() const override;

		virtual const std::shared_ptr<ParserOperand> SizeCast(ParserState *state,
																std::shared_ptr<ParserOperand> right_this,
																const Ceng::UINT32 newSize) override;

	protected:

		const Ceng::UINT32 SafetyCheck(const ParserOperand &other) const;
	};

}
*/

#endif