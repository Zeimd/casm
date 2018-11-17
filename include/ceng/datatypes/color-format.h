/*****************************************************************************
*
* color-format.h
*
* By Jari Korkala 10/2012
*
*****************************************************************************/

#ifndef _CONCEPT2_COLOR_FORMAT_H
#define _CONCEPT2_COLOR_FORMAT_H

#include "basic-types.h"

//****************************************************************************
// Color data abstraction

namespace Ceng
{
	/**
	* A color container that stores each component
	* in 0.16 fixed point.
	*/
	
	class CE_Color
	{
	public:
		UINT16 blue;
		UINT16 green;
		UINT16 red;
		UINT16 alpha;

		CE_Color() {}
		~CE_Color() {}

		/** 
		* Create a color with input values between 0-255. 
		*/
		CE_Color(UINT8 r,UINT8 g,UINT8 b,UINT8 a = 255);
	
		/** 
		* Create a color with input values between 0-65535. 
		*/
		CE_Color(UINT16 r,UINT16 g,UINT16 b,UINT16 a = 65535);
	
		/**
		* Create a color with input values between 0.0-1.0. 
		*/
		CE_Color(FLOAT32 r,FLOAT32 g,FLOAT32 b,FLOAT32 a = FLOAT32(1.0));
			
		/**
		* Extract a color from A8-R8-G8-B8 or A2-R10-G10-B10 format. 
		*/
		CE_Color(UINT32 input,bool color10 = false);
	
		/**
		 * Extract a color from R5-G6-B5 or A1-R5-G5-B5 format. 
		 */
		CE_Color(UINT16 input,bool green5 = false);
	
		const UINT16 ExtractColor16(bool green5 = false) const;
		const UINT32 ExtractColor32(bool color10 = false) const;
		const UINT64 ExtractCE_Color() const;

		const void ExtractFloatColor(FLOAT32 *color) const;
	};

	inline CE_Color::CE_Color(UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		blue = UINT16(b) << 8;
		green = UINT16(g) << 8;
		red = UINT16(r) << 8;
		alpha = UINT16(a) << 8;
	}
	
	inline CE_Color::CE_Color(UINT16 r, UINT16 g, UINT16 b, UINT16 a)
	{
		blue = b;
		green = g;
		red = r;
		alpha = a;
	}

	inline CE_Color::CE_Color(FLOAT32 r, FLOAT32 g, FLOAT32 b, FLOAT32 a)
	{
		if (r < 0)
		{
			r = FLOAT32(0.0);
		}
		else if (r > FLOAT32(1.0))
		{
			r = FLOAT32(1.0);
		}

		if (g < 0)
		{
			g = FLOAT32(0.0);
		}
		else if (g > FLOAT32(1.0))
		{
			g = FLOAT32(1.0);
		}

		if (b < 0)
		{
			b = FLOAT32(0.0);
		}
		else if (b > FLOAT32(1.0))
		{
			b = FLOAT32(1.0);
		}

		if (a < 0)
		{
			a = FLOAT32(0.0);
		}
		else if (a > FLOAT32(1.0))
		{
			a = FLOAT32(1.0);
		}

		red = UINT16(FLOAT32(65535.0)*r);
		green = UINT16(FLOAT32(65535.0)*g);
		blue = UINT16(FLOAT32(65535.0)*b);
		alpha = UINT16(FLOAT32(65535.0)*a);
	}

	inline CE_Color::CE_Color(UINT16 input,bool green5)
	{
		if (green5 == false)
		{
			blue = (input & 31) << 11;
			green = ((input >> 5) & 63) << 10;
			red = ((input >> 11) & 31) << 11;
			alpha = 0;
		}
		else
		{
			blue = (input & 31) << 11;
			green = ((input >> 5) & 31) << 11;
			red = ((input >> 10) & 31) << 11;
			alpha = (input >> 15) << 15;
		}
	}
	
	inline CE_Color::CE_Color(UINT32 input,bool color10)
	{
		if (color10 == false)
		{
			blue = (input & 255) << 8;
			green = ((input >> 8) & 255) << 8;
			red = ((input >> 16) & 255) << 8;
			alpha = (input >> 24) << 8;
		}
		else
		{
			blue = (input & 1023) << 6;
			green = ((input >> 10) & 1023) << 6;
			red = ((input >> 20) & 1023) << 6;
			alpha = (input >> 30) << 14;
		}
	}
	
	inline const UINT16 CE_Color::ExtractColor16(bool green5) const
	{
		UINT16 color = 0;
		
		if (green5 == false)
		{
			color += blue >> 11;
			color += (green >> 10) << 5;
			color += (red >> 11) << 11;
		}
		else
		{
			color += blue >> 11;
			color += (green >> 11) << 5;
			color += (red >> 11) << 10;
			color += (alpha >> 15) << 15;
		}
		
		return color;
	}
	
	inline const UINT32 CE_Color::ExtractColor32(bool color10) const
	{
		UINT32 color = 0;
		
		if (color10 == false)
		{
			color += UINT32(blue) >> 8;
			color += UINT32(green >> 8) << 8;
			color += UINT32(red >> 8) << 16;
			color += UINT32(alpha >> 8) << 24;
		}
		else
		{
			color += UINT32(blue) >> 6;
			color += UINT32(green >> 6) << 10;
			color += UINT32(red >> 6) << 20;
			color += UINT32(alpha >> 14) << 30;
		}
		
		return color;
	}
	
	inline const UINT64 CE_Color::ExtractCE_Color() const
	{
		UINT64 color = 0;
		
		color += blue;
		color += UINT32(green) << 16;
		color += UINT64(red) << 32;
		color += UINT64(alpha) << 48;
		
		return color;
	}
	
	const FLOAT32 CE_COLOR_SCALE = FLOAT32(1.0 / 65535.0);
	
	inline const void CE_Color::ExtractFloatColor(FLOAT32 *color) const
	{
		color[0] = FLOAT32(blue)*CE_COLOR_SCALE;
		color[1] = FLOAT32(green)*CE_COLOR_SCALE;
		color[2] = FLOAT32(red)*CE_COLOR_SCALE;
		color[3] = FLOAT32(alpha)*CE_COLOR_SCALE;
	}

} // Namespace Ceng

#endif