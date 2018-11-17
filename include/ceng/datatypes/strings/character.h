/*****************************************************************************
*
* character.h
*
* By Jari Korkala 3/2014
*
*****************************************************************************/

#ifndef CENG_STRING_CHARACTER_H
#define CENG_STRING_CHARACTER_H

#include "../basic-types.h"
#include "../boolean.h"

namespace Ceng
{
	// Windows
	typedef char16_t WCHAR_TYPE;

	// Linux
	//typedef char32_t WCHAR_TYPE;
	
	class Char32
	{
	protected:

		Ceng::UINT32 value;

	public:

		Char32()
		{
			value = 0;
		}

		~Char32()
		{
		}

		Char32(const Ceng::UINT32 value) : value(value)
		{
		}

		Char32(const Char32 &source)
		{
			value = source.value;
		}

		const Ceng::UINT32 Value() const
		{
			return value;
		}

		Char32& operator = (const char32_t source)
		{
			value = source;
			return *this;
		}

		Char32& operator = (const Char32 &source)
		{
			value = source.value;
			return *this;
		}

		const Ceng::BOOL operator == (const Char32 &other) const
		{
			return value == other.value;
		}

		const Ceng::BOOL operator != (const Char32 &other) const
		{
			return value != other.value;
		}

		const Ceng::BOOL operator == (const char32_t other)
		{
			return value == other;
		}

		const Ceng::BOOL operator != (const char32_t other)
		{
			return value != other;
		}
	};

	

	typedef Char32 CHAR32;

	//***********************************************************************************
	// Class CharacterUtf16

	/**
	 * 
	 */
	class CharacterUtf16
	{
	public:

		static const Ceng::UINT32 UNKNOWN_CODE_POINT = 0xFFFD;
		static const Ceng::UINT32 UNICODE_MAX_CODE_POINT = 0x10ffff;

		typedef Ceng::UINT16 DATA_ELEMENT;
		typedef const Ceng::UINT16 CONST_DATA_ELEMENT;

		static const Ceng::INT32 MAX_ENCODING_ELEMENTS = 2;

		CharacterUtf16()
		{
		}

		~CharacterUtf16()
		{
		}

		static const Ceng::INT32 EncodeUTF32(const CHAR32 unicode,DATA_ELEMENT *outputBuffer)
		{
			Ceng::INT32 newBytes=0;

			if (unicode.Value() > UNICODE_MAX_CODE_POINT)
			{
				outputBuffer[0] = UNKNOWN_CODE_POINT;
				return 1;
			}

			if (unicode.Value() < 0x10000)
			{
				outputBuffer[0] = char16_t(unicode.Value());
				newBytes = 1;
			}
			else
			{
				char32_t temp = unicode.Value() - 0x10000;

				outputBuffer[0] = char16_t(temp >> 10) + 0xd800;
				outputBuffer[1] = char16_t(temp & 1023) + 0xdc00;
				newBytes = 2;
			}

			return newBytes;
		}

		static const Ceng::INT32 EncodeUTF32(const CHAR32 unicode, char16_t *outputBuffer)
		{
			Ceng::INT32 newBytes = 0;

			if (unicode.Value() > UNICODE_MAX_CODE_POINT)
			{
				outputBuffer[0] = UNKNOWN_CODE_POINT;
				return 1;
			}

			if (unicode.Value() < 0x10000)
			{
				outputBuffer[0] = char16_t(unicode.Value());
				newBytes = 1;
			}
			else
			{
				char32_t temp = unicode.Value() - 0x10000;

				outputBuffer[0] = char16_t(temp >> 10) + 0xd800;
				outputBuffer[1] = char16_t(temp & 1023) + 0xdc00;
				newBytes = 2;
			}

			return newBytes;
		}

		static const Ceng::INT32 ToWideChar(const DATA_ELEMENT *stringBuffer,char16_t *output)
		{
			return ToUTF16(stringBuffer,output);
		}

		static const Ceng::INT32 ToWideChar(const DATA_ELEMENT *stringBuffer,CHAR32 *output)
		{
			output[0] = ToUTF32(stringBuffer);
			return 1;
		}

		static const Ceng::INT32 ToUTF16(const DATA_ELEMENT *stringBuffer,char16_t *output)
		{
			Ceng::INT32 elements = CalculateSize(stringBuffer);

			Ceng::INT32 k;

			for(k=0;k<elements;k++)
			{
				output[k] = stringBuffer[k];
			}

			return elements;
		}

		static const Ceng::INT32 ToChar(const DATA_ELEMENT *stringBuffer,char *output)
		{
			CHAR32 temp = ToUTF32(stringBuffer);

			if (temp.Value() <= 127)
			{
				return temp.Value();
			}

			return '?';
		}

		static const CHAR32 ToUTF32(const DATA_ELEMENT *stringBuffer)
		{
			if (IsTailSurrogate(stringBuffer[0]))
			{
				return UNKNOWN_CODE_POINT;
			}

			if (IsLeadSurrogate(stringBuffer[0]))
			{
				char32_t high = stringBuffer[0] - 0xd800;

				if (IsTailSurrogate(stringBuffer[1]))
				{
					char32_t low = stringBuffer[1] - 0xdc00;

					return 0x10000 + (high << 10) + low;
				}
				else
				{
					return UNKNOWN_CODE_POINT;
				}
			}

			return stringBuffer[0];
		}

		static const Ceng::BOOL IsLeadSurrogate(const DATA_ELEMENT value)
		{
			if (value >= 0xd800 && value <= 0xdbff)
			{
				return true;
			}

			return false;
		}

		static const Ceng::BOOL IsTailSurrogate(const DATA_ELEMENT value)
		{
			if (value >= 0xdc00 && value <= 0xdfff)
			{
				return true;
			}
			return false;
		}

		static const Ceng::INT32 GetByteCount(const DATA_ELEMENT value)
		{
			if (IsTailSurrogate(value))
			{
				return -1;
			}

			return CalculateSize(&value);
		}


	public:

		/**
		 * Determines the size of current character in elements.
		 */
		static const Ceng::INT32 CalculateSize(const DATA_ELEMENT *startChar)
		{
			if (IsTailSurrogate(startChar[0]))
			{
				return 1;
			}

			if (IsLeadSurrogate(startChar[0]))
			{
				if (IsTailSurrogate(startChar[1]))
				{
					return 2;
				}

				return 1;
			}

			return 1;
		}
	};


	

	//************************************************************************
	// Class CharacterUtf8

	class CharacterUtf8
	{
	public:

		static const Ceng::UINT32 UNKNOWN_CODE_POINT = 0xFFFD;

		static const Ceng::UINT32 LEAD_SURROGATE_START = 0xd800;
		static const Ceng::UINT32 LEAD_SURROGATE_END = 0xdbff;

		static const Ceng::UINT32 TAIL_SURROGATE_START = 0xdc00;
		static const Ceng::UINT32 TAIL_SURROGATE_END = 0xdfff;

		typedef Ceng::UINT8 DATA_ELEMENT;
		typedef const Ceng::UINT8 CONST_DATA_ELEMENT;

		static const Ceng::INT32 MAX_ENCODING_ELEMENTS = 4;

		CharacterUtf8::CharacterUtf8()
		{
		}

		CharacterUtf8::~CharacterUtf8()
		{
		}

		static const Ceng::INT32 EncodeUTF32(const CHAR32 unicode,Ceng::UINT8 *outputBuffer)
		{
			UINT8 newBytes = 0;

			if (unicode.Value() >= LEAD_SURROGATE_START && unicode.Value() <= TAIL_SURROGATE_END)
			{
				return EncodeUTF32(UNKNOWN_CODE_POINT,outputBuffer);
			}

			if (unicode.Value() < 128)
			{
				// Single byte
				outputBuffer[0] = UINT8(unicode.Value());
				newBytes = 1;
			}
			else if (unicode.Value() < 2048)
			{
				// Two bytes
				outputBuffer[0] = 128 + 64 + UINT8(unicode.Value() >> 6);
				outputBuffer[1] = 128 + UINT8(unicode.Value() & 63);

				newBytes = 2;
			}
			else if (unicode.Value() < 65536)
			{
				// Three bytes
				
				outputBuffer[0] = 128 + 64 + 32 + UINT8(unicode.Value() >> 12);
				outputBuffer[1] = 128 + UINT8((unicode.Value() >> 6) & 63);
				outputBuffer[2] = 128 + UINT8(unicode.Value() & 63);

				newBytes = 3;
			}
			else if (unicode.Value() < 0x10FFFF)
			{
				// Four bytes
				
				outputBuffer[0] = 128 + 64 + 32 + 16 + UINT8(unicode.Value() >> 18);
				outputBuffer[1] = 128 + UINT8((unicode.Value() >> 12) & 63);
				outputBuffer[2] = 128 + UINT8((unicode.Value() >> 6) & 63);
				outputBuffer[3] = 128 + UINT8(unicode.Value() & 63);

				newBytes = 4;
			}
			else
			{
				return EncodeUTF32(UNKNOWN_CODE_POINT,outputBuffer);
			}

			return newBytes;
		}

		static const Ceng::INT32 ToWideChar(const Ceng::UINT8 *stringBuffer,CHAR32 *output)
		{
			output[0] = ToUTF32(stringBuffer);

			return 1;
		}

		static const Ceng::INT32 ToWideChar(const Ceng::UINT8 *stringBuffer,char16_t *output)
		{
			return ToUTF16(stringBuffer,output);
		}

		static const char ToChar(const Ceng::UINT8 *stringBuffer,char *output)
		{
			Ceng::INT32 bytes = CalculateSize(stringBuffer);

			Ceng::INT32 k;

			for(k=0;k<bytes;k++)
			{
				output[k] = stringBuffer[k];
			}

			return char(bytes);
		}
		
		static const char32_t ToUTF32(const Ceng::UINT8 *stringBuffer)
		{
			if (stringBuffer == nullptr)
			{
				return '\0';
			}

			// Possible byte formats

			// 0xxx xxxx : 1-byte character
			// 110x xxxx : 2-byte character start
			// 1110 xxxx : 3-byte character start
			// 1111 0xxx : 4-byte character start

			// 10xx xxxx : continuation byte

			// Catch one-byte characters
			if ( stringBuffer[0] < 128)
			{
				return stringBuffer[0];
			}
			
			// Catch illegal starting bytes
			if ( stringBuffer[0] > 247)
			{
				return UNKNOWN_CODE_POINT;
			}

			if ( IsContinuationByte( stringBuffer[0] ) )
			{
				return UNKNOWN_CODE_POINT;
			}

			// At this point possible bytes are of the form:
			// 110x xxxx
			// 1110 xxxx
			// 1111 0xxx

			UINT32 extraBytes = GetByteCount( stringBuffer[0] ) - 1;

			if (extraBytes > 3)
			{
				return UNKNOWN_CODE_POINT;
			}

			UINT8 startMask = (1 << (6-extraBytes)) - 1;
			
			UINT32 shiftCount = 6*extraBytes;
	
			char32_t temp = UINT32( stringBuffer[0] & startMask) << shiftCount;

			UINT32 k=0;

			do
			{
				k++;

				// NOTE: also catches null-terminator
				if ( !IsContinuationByte( stringBuffer[k]) )
				{
					return UNKNOWN_CODE_POINT;
				}

				shiftCount -= 6;

				temp += UINT32( stringBuffer[k] & 63) << shiftCount;

			} while(k < extraBytes);

			// Check that code point is below currently defined
			// upper bound
			if (temp > 0x10FFFF)
			{
				return UNKNOWN_CODE_POINT;
			}

			return temp;
		}

		static const Ceng::BOOL IsContinuationByte(const UINT8 value)
		{
			// Continuation byte has format 10xxxxxx
			return ( ( value & (128 | 64) ) == 128 );
		}


	public:
	
		/*
		* Returns the number of bytes in the character that
		* starts from given byte.
		*
		* NOTE: Returns -1 if value is a continuation byte.
		*/
		static const INT32 GetByteCount(const UINT8 value)
		{
			//UINT32 bytes = 0; 

			//UINT8 mask = 128;

			if ( (value & 128) == 0)
			{
				return 1;
			}

			if ( (value & (128 | 64)) == 128)
			{
				//  Continuation byte
				return -1;
			}

			if ( (value & (128 | 64 | 32)) == (128 | 64))
			{
				return 2;
			}

			if ( (value & (128 | 64 | 32 | 16)) == (128 | 64 | 32))
			{
				return 3;
			}

			if ( (value & (128 | 64 | 32 | 16 | 8)) == (128 | 64 | 32 | 16))
			{
				return 4;
			}

			/*
			if ( (value & (128 | 64 | 32 | 16 | 8 | 4)) == (128 | 64 | 32 | 16 | 8))
			{
				return 5;
			}

			if ( (value & (128 | 64 | 32 | 16 | 8 | 4 | 2)) == (128 | 64 | 32 | 16 | 8 | 4))
			{
				return 6;
			}
			*/

			return 1;
		}

		/**
		 * Determines the size of current character in bytes.
		 */
		static const Ceng::INT32 CalculateSize(const Ceng::UINT8 *startChar)
		{
			// Don't step if at the end of the string literal
			if (startChar[0] == '\0')
			{
				return 0;
			}

			// Genuine single byte character
			if (startChar[0] < 128)
			{
				return 1;
			}

			// Unexpected continuation byte counts as one character
			if (IsContinuationByte(startChar[0]))
			{
				return 1;
			}

			UINT32 step = GetByteCount(startChar[0]);

			if (step > 3)
			{
				return 1;
			}

			UINT32 k = 1;

			// Check that byte is followed by enough continuation bytes
			for( k = 1 ; k < step ; k++)
			{
				if ( !IsContinuationByte(startChar[k]) )
				{
					break;
				}
			}

			return k;
		}

		static const Ceng::INT32 ToUTF16(const Ceng::UINT8 *stringBuffer,char16_t *output)
		{
			char32_t unicode = ToUTF32(stringBuffer);

			return CharacterUtf16::EncodeUTF32(unicode,output);
		}

	};

	//**********************************************************************************
	// Class CharacterUtf32

	class CharacterUtf32
	{
	public:
		static const Ceng::UINT32 UNKNOWN_CODE_POINT = 0xFFFD;
		static const Ceng::UINT32 UNICODE_MAX_CODE_POINT = 0x10ffff;

		typedef Ceng::UINT32 DATA_ELEMENT;
		typedef const Ceng::UINT32 CONST_DATA_ELEMENT;

		static const Ceng::INT32 MAX_ENCODING_ELEMENTS = 1;

		CharacterUtf32()
		{
		}

		~CharacterUtf32()
		{
		}

		/**
		 * Determines the size of current character in elements.
		 */
		static const Ceng::INT32 CalculateSize(const DATA_ELEMENT *startChar)
		{
			return 1;
		}

		static const Ceng::INT32 GetByteCount(const DATA_ELEMENT value)
		{
			return 1;
		}

		static const Ceng::INT32 EncodeUTF32(const CHAR32 unicode,DATA_ELEMENT *outputBuffer)
		{
			outputBuffer[0] = unicode.Value();

			if (unicode.Value() > UNICODE_MAX_CODE_POINT)
			{
				outputBuffer[0] = UNKNOWN_CODE_POINT;
			}

			return 1;
		}

		static const Ceng::INT32 ToWideChar(const DATA_ELEMENT *stringBuffer,CHAR32 *output)
		{
			output[0] = stringBuffer[0];
			return 1;
		}

		static const Ceng::INT32 ToWideChar(const DATA_ELEMENT *stringBuffer,char16_t *output)
		{
			return ToUTF16(stringBuffer,output);
		}

		static const Ceng::INT32 ToChar(const DATA_ELEMENT *stringBuffer,char *output)
		{
			char32_t temp = ToUTF32(stringBuffer);

			if (temp <= 127)
			{
				return temp;
			}

			return '?';
		}

		static const char32_t ToUTF32(const DATA_ELEMENT *stringBuffer)
		{
			return stringBuffer[0];
		}

		static const Ceng::INT32 ToUTF16(const Ceng::UINT32 *stringBuffer,char16_t *output)
		{
			char32_t unicode = ToUTF32(stringBuffer);

			return CharacterUtf16::EncodeUTF32(unicode,output);
		}
	};

	

	//********************************************************************************************
	// Platform-specific - part 2

	// Windows
	typedef CharacterUtf16 WIDE_CHARACTER;

	// Linux (maybe)
	// typedef CharacterUtf32 WIDE_CHARACTER;
}

#endif