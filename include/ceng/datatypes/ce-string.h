/*****************************************************************************
*
* ce-string.h
*
* By Jari Korkala 10/2013
*
* NOTE: Do not include this file directly. Include "datatypes.h" instead.
*
*****************************************************************************/

#ifndef CENG_STRING_H
#define CENG_STRING_H

#include "strings/character-ref.h"
#include "strings/iterator.h"

#include "basic-types.h"
#include "boolean.h"

#include <algorithm>
#include <utility>
#include <iterator>
#include <vector>

#include <stdio.h>

namespace Ceng
{
	template<class CHARACTER_TYPE>
	class StringConfig
	{
	public:
		typedef CHARACTER_TYPE CHARACTER_TYPE;

		typedef typename CHARACTER_TYPE::DATA_ELEMENT DATA_ELEMENT;

		/**
		 * Iterator for string objects.
		 */
		typedef VaryingIterator<CHARACTER_TYPE,DATA_ELEMENT> ITERATOR_BASE_TYPE;

		typedef VaryingIterator<CHARACTER_TYPE,const DATA_ELEMENT> CONST_ITERATOR_BASE_TYPE;

		/**
		 * Iterator for constant string literals. IE: const char *source.
		 */
		typedef VaryingIterator<CHARACTER_TYPE,DATA_ELEMENT> LITERAL_ITERATOR_BASE_TYPE;
	};

	template<>
	class StringConfig<CharacterUtf32>
	{
	public:

		typedef CharacterUtf32 CHARACTER_TYPE;

		typedef CHARACTER_TYPE::DATA_ELEMENT DATA_ELEMENT;

		/**
		 * Iterator for string objects.
		 */
		typedef FixedLengthIterator<CHARACTER_TYPE,DATA_ELEMENT> ITERATOR_BASE_TYPE;

		typedef FixedLengthIterator<CHARACTER_TYPE,const DATA_ELEMENT> CONST_ITERATOR_BASE_TYPE;

		/**
		 * Iterator for constant string literals. IE: const char *source.
		 */
		typedef VaryingIterator<CHARACTER_TYPE,DATA_ELEMENT> LITERAL_ITERATOR_BASE_TYPE;
	};

	/**
	 * UTF-8 encoding.
	 */
	template<class STRING_CONFIG>
	class BaseString 
	{
	public:

		typedef typename STRING_CONFIG STRING_CONFIG;

		typedef typename STRING_CONFIG::CHARACTER_TYPE CHARACTER_TYPE;

		typedef typename CHARACTER_TYPE::DATA_ELEMENT DATA_ELEMENT;

		typedef typename STRING_CONFIG::ITERATOR_BASE_TYPE ITERATOR_BASE_TYPE;
		typedef typename STRING_CONFIG::CONST_ITERATOR_BASE_TYPE CONST_ITERATOR_BASE_TYPE;
		typedef typename STRING_CONFIG::LITERAL_ITERATOR_BASE_TYPE LITERAL_ITERATOR_BASE_TYPE;

		typedef CharacterRef<CHARACTER_TYPE,DATA_ELEMENT,VectorRef<DATA_ELEMENT>> REF_TYPE;
		typedef CharacterRef<CHARACTER_TYPE,const DATA_ELEMENT,ConstVectorRef<DATA_ELEMENT>> CONST_REF_TYPE;
		
		typedef StringIterator<CHARACTER_TYPE,DATA_ELEMENT,VectorRef<DATA_ELEMENT>,
									ITERATOR_BASE_TYPE> ITERATOR_TYPE;
		
		typedef StringIterator<CHARACTER_TYPE,const DATA_ELEMENT,ConstVectorRef<DATA_ELEMENT>,
									CONST_ITERATOR_BASE_TYPE> CONST_ITERATOR_TYPE;		

		typedef ReverseIterator<ITERATOR_TYPE> REVERSE_ITERATOR_TYPE;
		typedef ReverseIterator<CONST_ITERATOR_TYPE> CONST_REVERSE_ITERATOR_TYPE;

	protected:

		typedef StringIterator<CHARACTER_TYPE,const DATA_ELEMENT,PointerRef<const DATA_ELEMENT>,
									LITERAL_ITERATOR_BASE_TYPE> LITERAL_ITERATOR_TYPE;

		typedef typename StringConfig<CharacterUtf8> CONFIG_UTF8;
		typedef typename StringConfig<CharacterUtf16> CONFIG_UTF16;
		typedef typename StringConfig<CharacterUtf32> CONFIG_UTF32;

		typedef StringIterator<CharacterUtf8,const Ceng::UINT8,PointerRef<const Ceng::UINT8>,
									typename CONFIG_UTF8::LITERAL_ITERATOR_BASE_TYPE> LITERAL_ITERATOR_UTF8;

		typedef StringIterator<CharacterUtf16,const Ceng::UINT16,PointerRef<const Ceng::UINT16>,
									typename CONFIG_UTF16::LITERAL_ITERATOR_BASE_TYPE> LITERAL_ITERATOR_UTF16;

		typedef StringIterator<CharacterUtf32,const Ceng::UINT32,PointerRef<const Ceng::UINT32>,
									typename CONFIG_UTF32::LITERAL_ITERATOR_BASE_TYPE> LITERAL_ITERATOR_UTF32;

		typedef typename StringConfig<WIDE_CHARACTER> CONFIG_WIDE;

		typedef StringIterator<WIDE_CHARACTER,const WCHAR_TYPE,PointerRef<const WCHAR_TYPE>,
									typename CONFIG_WIDE::LITERAL_ITERATOR_BASE_TYPE> LITERAL_ITERATOR_WCHAR;

	protected:

		REF_TYPE charType;

		std::vector<DATA_ELEMENT> rawData;
		/**
		 * Number of characters in the string.
		 */
		Ceng::UINT32 length;

		/*
		 * Index of *rawData* to start next search from.
		 */
		Ceng::UINT32 rawSearchPos;
		
		/*
		 * Index of character to start next search from.
		 */
		Ceng::UINT32 charSearchPos;

	public:

		BaseString();

		~BaseString();

		BaseString(const BaseString &source);

		template<class T>
		BaseString(const T &source);

		template<class OTHER_CONFIG>
		BaseString(const BaseString<OTHER_CONFIG> &source);

		/**
		 * Used to construct substring from existing string.
		 */
		BaseString(const BaseString &source,const Ceng::INT32 rawStart,
					const Ceng::INT32 rawBytes,const Ceng::INT32 length);
		
		/*
		 * Copy a null-terminated string literal. Assume UTF-8 encoding.
		 */
		BaseString(const char *source);

		BaseString(const wchar_t *source);

		static void Swap(BaseString &a,BaseString &b);

		void Swap(BaseString &other);

		void Clear();

		/**
		 * Assignment operator. Implemented as copy and swap.
		 * NOTE: Function parameter must be by value.
		 */
		BaseString& operator = (BaseString source);

		/**
		 * Returns the number of code points in the string.
		 */
		const Ceng::UINT32 Length() const;
		/**
		 * Returns the size of the string buffer in bytes.
		 */
		const Ceng::UINT32 BufferSize() const;

		/**
		 * Returns the maximum number of characters the string can
		 * hold.
		 */
		const Ceng::UINT32 MaxSize() const;

		/**
		 * Returns the maximum number of codepoints that can be stored
		 * with current allocation.
		 */
		const Ceng::UINT32 MaxCapacity() const;

		/**
		 * Returns the minimum number of codepoints that can be stored
		 * with current allocation.
		 */
		const Ceng::UINT32 MinCapacity() const;

		/**
		 * Reserve space for a number of code points. The worst
		 * case size is used when reserving space.
		 */
		void Reserve(const Ceng::UINT32 codepoints);

		/**
		 * Returns a pointer to a null-terminated version of the string.
		 * Pointer could be invalidated at any time.
		 *
		 * NOTE: Exact only for one-byte UTF-8 data.
		 */
		const char* ToCString() const;

		/**
		 * Returns a pointer to a null-terminated version of a wide string.
		 * Pointer could be invalidated at any time.
		 *
		 * NOTE: Use only for UTF-16 strings.
		 */
		const wchar_t* ToWString() const;

		REF_TYPE operator [] (const Ceng::UINT32 index);

		REF_TYPE CodePointAt(const Ceng::UINT32 index);

		const CONST_REF_TYPE operator [] (const Ceng::UINT32 index) const;

		const CONST_REF_TYPE CodePointAt(const Ceng::UINT32 index) const;

		ITERATOR_TYPE BeginIterator();

		CONST_ITERATOR_TYPE ConstBeginIterator() const;

		ITERATOR_TYPE EndIterator();

		CONST_ITERATOR_TYPE ConstEndIterator() const;

		REVERSE_ITERATOR_TYPE ReverseBeginIterator();

		REVERSE_ITERATOR_TYPE ReverseEndIterator();

		CONST_REVERSE_ITERATOR_TYPE ConstReverseBeginIterator() const;

		CONST_REVERSE_ITERATOR_TYPE ConstReverseEndIterator() const;

		void RemoveLastChar();

		void ResizeRaw(const Ceng::INT32 newIndex,const Ceng::INT32 newRawSize);

		/**
		 * Returns true if the two strings are exactly equal.
		 */
		const Ceng::BOOL operator == (const BaseString &other) const;

		const Ceng::BOOL operator != (const BaseString &other) const;

		template<class T>
		BaseString& operator += (const T *source);

		/**
		 * Appends with a string.
		 */
		BaseString& operator += (const BaseString &other);

		template<class T>
		BaseString& operator += (const T &source);

		/**
		 * Concatenate two strings and store result.
		 */
		const BaseString operator + (const BaseString &other) const;

		template<class T>
		const BaseString operator + (const T *source) const;

		template<class T>
		const BaseString operator + (const T &source) const;

		/**
		 * Insert a string.
		 */
		void Insert(const Ceng::INT32 index,const BaseString &string);

		/**
		 * Insert ASCII string.
		 */
		void Insert(const Ceng::INT32 index,const char *string);

		void Insert(const Ceng::INT32 index,const char16_t *string);

		void Insert(const Ceng::INT32 index,const CHAR32 *string);

		void Insert(const Ceng::INT32 index,const wchar_t *string);

		template<class SOURCE_ITER_TYPE>
		void Insert(const Ceng::INT32 index,SOURCE_ITER_TYPE sourceIter);

		/**
		 * Insert an unicode character.
		 */
		void Insert(const Ceng::INT32 index,const CHAR32 unicode);

		/**
		 * Erase range from position to position+n-1.
		 */
		BaseString& Erase(const Ceng::INT32 position,const Ceng::INT32 n);

		/**
		 * Erase range from startIter to endIter-1.
		 */
		BaseString& Erase(const CONST_ITERATOR_TYPE &startIter,const CONST_ITERATOR_TYPE &endIter);

		void GetIteratorRange(const Ceng::INT32 startIndex,const Ceng::INT32 delta,
								CONST_ITERATOR_TYPE *startIter,CONST_ITERATOR_TYPE *endIter) const;

		const BaseString SubString(const Ceng::INT32 position,const Ceng::INT32 n) const;

		const BaseString SubString(const CONST_ITERATOR_TYPE &startIter,const CONST_ITERATOR_TYPE &endIter) const;

		/**
		 * Returns the index of the first code point that matches given value.
		 */
		const Ceng::INT32 FindFirst(const char ascii,const Ceng::INT32 startIndex) const;

		/**
		 * Returns the index of the first code point that matches given value.
		 */
		const Ceng::INT32 FindFirst(const wchar_t codepoint,const Ceng::INT32 startIndex) const;
		
		const Ceng::INT32 FindFirst(const CHAR32 unicode,const Ceng::INT32 startIndex) const;

		CONST_ITERATOR_TYPE FindFirst(const CHAR32 unicode,CONST_ITERATOR_TYPE seekIterator) const;

		CONST_ITERATOR_TYPE FindFirst(const char *test,CONST_ITERATOR_TYPE seekIterator) const;

		CONST_ITERATOR_TYPE FindFirst(const char *test,CONST_ITERATOR_TYPE startIterator,
										CONST_ITERATOR_TYPE endIterator) const;

		template<class STRING_ITERATOR,class SOURCE_ITERATOR>
		CONST_ITERATOR_TYPE FindFirst(STRING_ITERATOR seekIterator,const STRING_ITERATOR &endIterator,
										const SOURCE_ITERATOR &testIterator) const;		

		/**
		 * Returns constant iterator to first codepoint that matches given value.
		 */
		template<class ITER_TYPE>
		typename ITER_TYPE FindFirst(const CHAR32 unicode,typename ITER_TYPE seekIterator,
									const typename ITER_TYPE &endPoint) const;

		CONST_ITERATOR_TYPE FindLast(const CHAR32 unicode,CONST_ITERATOR_TYPE seekIterator) const;

		CONST_REVERSE_ITERATOR_TYPE FindLast(const CHAR32 unicode,CONST_REVERSE_ITERATOR_TYPE seekIterator) const;

		/**
		 * Returns the first of any codepoint in test string.
		 */
		template<class T>
		const Ceng::INT32 FindFirstOf(const T *test,const Ceng::INT32 startIndex) const;

		CONST_ITERATOR_TYPE FindFirstOf(const char *test,CONST_ITERATOR_TYPE seekIterator) const;

		CONST_ITERATOR_TYPE FindFirstOf(const char *test,CONST_ITERATOR_TYPE startIterator,
										CONST_ITERATOR_TYPE endIterator) const;

		CONST_ITERATOR_TYPE FindFirstOf(const char16_t *test,CONST_ITERATOR_TYPE seekIterator) const;

		CONST_ITERATOR_TYPE FindFirstOf(const CHAR32 *test,CONST_ITERATOR_TYPE seekIterator) const;

		CONST_ITERATOR_TYPE FindFirstOf(const wchar_t *test,CONST_ITERATOR_TYPE seekIterator) const;

		template<class SOURCE_ITER_TYPE>
		CONST_ITERATOR_TYPE FindFirstOf(CONST_ITERATOR_TYPE seekIterator,
											const SOURCE_ITER_TYPE testIter) const;

		template<class SOURCE_ITER_TYPE>
		CONST_ITERATOR_TYPE FindLastOf(CONST_ITERATOR_TYPE seekIterator,
			const SOURCE_ITER_TYPE testIter) const;

		template<class SOURCE_ITER_TYPE>
		CONST_REVERSE_ITERATOR_TYPE FindLastOf(CONST_REVERSE_ITERATOR_TYPE seekIterator,
													const SOURCE_ITER_TYPE testIter) const;

		/**
		 * Returns the first of any codepoint in test string.
		 */
		template<class T>
		const Ceng::INT32 FindLastOf(const T *test,const Ceng::INT32 startIndex) const;

		CONST_REVERSE_ITERATOR_TYPE FindLastOf(const char *test,CONST_REVERSE_ITERATOR_TYPE seekIterator) const;

		CONST_REVERSE_ITERATOR_TYPE FindLastOf(const char16_t *test,CONST_REVERSE_ITERATOR_TYPE seekIterator) const;

		CONST_REVERSE_ITERATOR_TYPE FindFirstOf(const CHAR32 *test,CONST_REVERSE_ITERATOR_TYPE seekIterator) const;

		CONST_REVERSE_ITERATOR_TYPE FindLastOf(const wchar_t *test,CONST_REVERSE_ITERATOR_TYPE seekIterator) const;

		CONST_ITERATOR_TYPE FindLastOf(const char *test, CONST_ITERATOR_TYPE seekIterator) const;

		CONST_ITERATOR_TYPE FindLastOf(const char16_t *test, CONST_ITERATOR_TYPE seekIterator) const;

		CONST_ITERATOR_TYPE FindLastOf(const wchar_t *test, CONST_ITERATOR_TYPE seekIterator) const;

		template<class STRING_ITER_TYPE,class SOURCE_ITER_TYPE>
		STRING_ITER_TYPE FindFirstOf(STRING_ITER_TYPE seekIterator,
											const SOURCE_ITER_TYPE testIter,
											const STRING_ITER_TYPE &endPoint) const;

		/**
		 * Returns the first of any codepoint in test string.
		 */
		template<class T>
		const Ceng::INT32 FindFirstNotOf(const T *test,const Ceng::INT32 startIndex) const;

		CONST_ITERATOR_TYPE FindFirstNotOf(const char *test,CONST_ITERATOR_TYPE seekIterator) const;

		CONST_ITERATOR_TYPE FindFirstNotOf(const char16_t *test,CONST_ITERATOR_TYPE seekIterator) const;

		CONST_ITERATOR_TYPE FindFirstNotOf(const CHAR32 *test,CONST_ITERATOR_TYPE seekIterator) const;

		CONST_ITERATOR_TYPE FindFirstNotOf(const wchar_t *test,CONST_ITERATOR_TYPE seekIterator) const;

		template<class SOURCE_ITER_TYPE>
		CONST_ITERATOR_TYPE FindFirstNotOf(CONST_ITERATOR_TYPE stringIterator,
												SOURCE_ITER_TYPE patternIterator) const;

		template<class STRING_ITER,class SOURCE_ITER_TYPE>
		STRING_ITER FindFirstNotOf(STRING_ITER stringIterator,
											const SOURCE_ITER_TYPE patternIterator,
											const STRING_ITER &endPoint) const;

		/**
		 * Returns the first of any codepoint in test string.
		 */
		template<class T>
		const Ceng::INT32 FindLastNotOf(const T *test,const Ceng::INT32 startIndex) const;

		CONST_REVERSE_ITERATOR_TYPE FindLastNotOf(const char *test,CONST_REVERSE_ITERATOR_TYPE seekIterator) const;

		CONST_REVERSE_ITERATOR_TYPE FindLastNotOf(const char16_t *test,CONST_REVERSE_ITERATOR_TYPE seekIterator) const;

		CONST_REVERSE_ITERATOR_TYPE FindLastNotOf(const CHAR32 *test,CONST_REVERSE_ITERATOR_TYPE seekIterator) const;

		CONST_REVERSE_ITERATOR_TYPE FindLastNotOf(const wchar_t *test,CONST_REVERSE_ITERATOR_TYPE seekIterator) const;

		template<class SOURCE_ITER_TYPE>
		CONST_REVERSE_ITERATOR_TYPE FindLastNotOf(CONST_REVERSE_ITERATOR_TYPE stringIterator,
												SOURCE_ITER_TYPE patternIterator) const;
		/**
		 * Returns iterator to first codepoint that matches given value.
		 */
		ITERATOR_TYPE FindFirstEdit(const CHAR32 unicode,ITERATOR_TYPE seekIterator);

		template<class OTHER_CONFIG>
		void Append(const BaseString<OTHER_CONFIG> &source);

		/**
		 * Append single unicode codepoint.
		 */
		void Append(const Ceng::CHAR32 unicode);

		/**
		 * Append one-byte UTF-8 code point.
		 */
		void Append(const char source);

		/**
		 * Append one-word UTF-16 code point.
		 */
		void Append(const wchar_t source);

		void Append(const char16_t source);

		void Append(const std::string &source);

		void Append(const std::wstring &source);

		/**
		 * Append UTF-8 literal.
		 */
		void Append(const char *source);

		void Append(const char16_t *source);

		void Append(const CHAR32 *source);

		void Append(const wchar_t *source);

		void Append(const Ceng::FLOAT32 value);

		void Append(const Ceng::FLOAT64 value);

		void Append(const Ceng::INT32 value);

		void Append(const Ceng::UINT32 value);

	protected:

		void ChainedAppend(const CHAR32 unicode);

		const CONST_REF_TYPE ConstCharacter(const Ceng::UINT32 index) const;
		
		REF_TYPE CharacterRef(const Ceng::UINT32 index);
	};

	template<class STRING_CONFIG>
	BaseString<STRING_CONFIG>::BaseString()
	{
		rawData.push_back('\0');

		length = 0;
			
		rawSearchPos = 0;
		charSearchPos = 0;
	}

	template<class STRING_CONFIG>
	BaseString<STRING_CONFIG>::~BaseString()
	{
	}

	template<class STRING_CONFIG>
	BaseString<STRING_CONFIG>::BaseString(const BaseString &source)
	{
		rawData = std::vector<DATA_ELEMENT>(source.rawData);

		length = source.length;

		rawSearchPos = source.rawSearchPos;
		charSearchPos = source.charSearchPos;
	}

	template<class STRING_CONFIG>
	template<class T>
	BaseString<STRING_CONFIG>::BaseString(const T &source)
	{
		length = 0;

		rawData.push_back('\0');

		Append(source);
	}

	template<class STRING_CONFIG>
	template<class OTHER_CONFIG>
	BaseString<STRING_CONFIG>::BaseString(const BaseString<OTHER_CONFIG> &source)
	{
		length = 0;

		rawData.push_back('\0');

		Append(source);
	}


	template<class STRING_CONFIG>
	BaseString<STRING_CONFIG>::BaseString(const BaseString &source,const Ceng::INT32 rawStart,
											const Ceng::INT32 rawBytes,const Ceng::INT32 length)
	{
		this->length = length;

		Ceng::INT32 k;

		for(k=0;k<rawBytes;k++)
		{
			rawData.push_back(source.rawData[rawStart+k]);
		}

		rawData.push_back('\0');
	}
		
	template<class STRING_CONFIG>
	BaseString<STRING_CONFIG>::BaseString(const char *source)
	{
		length = 0;

		if (source == NULL)
		{	
			return;
		}

		rawData.push_back('\0');

		Append(source);
	}

	template<class STRING_CONFIG>
	BaseString<STRING_CONFIG>::BaseString(const wchar_t *source)
	{
		length = 0;

		if (source == nullptr)
		{
			return;
		}

		rawData.push_back('\0');

		Append(source);			
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Swap(BaseString &a,BaseString &b)
	{
		std::swap(a.length,b.length);
		std::swap(a.charSearchPos,b.charSearchPos);
		std::swap(a.rawSearchPos,b.rawSearchPos);
			
		a.rawData.swap(b.rawData);
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Swap(BaseString &other)
	{
		Swap(*this,other);
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Clear()
	{
		rawData.clear();

		rawData.push_back('\0');

		length = 0;
		rawSearchPos = 0;
		charSearchPos = 0;
	}

	template<class STRING_CONFIG>
	BaseString<STRING_CONFIG>& BaseString<STRING_CONFIG>::operator = (BaseString source)
	{
		Swap(*this,source);

		return *this;
	}

	template<class STRING_CONFIG>
	const Ceng::UINT32 BaseString<STRING_CONFIG>::Length() const
	{
		return length;
	}

	template<class STRING_CONFIG>
	const Ceng::UINT32 BaseString<STRING_CONFIG>::BufferSize() const
	{
		return rawData.size()-1;
	}

	template<class STRING_CONFIG>
	const Ceng::UINT32 BaseString<STRING_CONFIG>::MaxSize() const
	{
		return rawData.max_size() / typename CHARACTER_TYPE::MAX_ENCODING_BYTES;
		return 0;
	}

	template<class STRING_CONFIG>
	const Ceng::UINT32 BaseString<STRING_CONFIG>::MaxCapacity() const
	{
		return rawData.capacity()-1;
	}

	template<class STRING_CONFIG>
	const Ceng::UINT32 BaseString<STRING_CONFIG>::MinCapacity() const
	{
		return (rawData.capacity()-1) / typename CHARACTER_TYPE::MAX_ENCODING_BYTES;
	}
	
	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Reserve(const Ceng::UINT32 codepoints)
	{
		Ceng::UINT32 newCapacity = codepoints * typename CHARACTER_TYPE::MAX_ENCODING_BYTES;

		if (newCapacity > rawData.capacity())
		{
			rawData.reserve(newCapacity);
		}
	}

	template<class STRING_CONFIG>
	const char* BaseString<STRING_CONFIG>::ToCString() const
	{
		return (const char*)&rawData[0];
	}

	template<class STRING_CONFIG>
	const wchar_t* BaseString<STRING_CONFIG>::ToWString() const
	{
		return (const wchar_t*)&rawData[0];
	}


	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::REF_TYPE BaseString<STRING_CONFIG>::
		operator [] (const Ceng::UINT32 index)
	{
		return CharacterRef(index);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::REF_TYPE 
		BaseString<STRING_CONFIG>::CodePointAt(const Ceng::UINT32 index)
	{
		if (index < length)
		{
			return CharacterRef(index);
		}

		return REF_TYPE();
	}

	template<class STRING_CONFIG>
	const typename BaseString<STRING_CONFIG>::CONST_REF_TYPE 
		BaseString<STRING_CONFIG>::operator [] (const Ceng::UINT32 index) const
	{
		return ConstCharacter(index);
	}

	template<class STRING_CONFIG>
	const typename BaseString<STRING_CONFIG>::CONST_REF_TYPE 
		BaseString<STRING_CONFIG>::CodePointAt(const Ceng::UINT32 index) const
	{
		if (index < length)
		{
			return ConstCharacter(index);
		}

		return CONST_REF_TYPE();
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::ITERATOR_TYPE BaseString<STRING_CONFIG>::BeginIterator()
	{
		return ITERATOR_TYPE(VectorRef<DATA_ELEMENT>(&rawData));
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE BaseString<STRING_CONFIG>::ConstBeginIterator() const
	{
		return CONST_ITERATOR_TYPE(ConstVectorRef<DATA_ELEMENT>(&rawData));
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::ITERATOR_TYPE BaseString<STRING_CONFIG>::EndIterator()
	{
		return ITERATOR_TYPE(VectorRef<DATA_ELEMENT>(&rawData),length,rawData.size()-1);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE BaseString<STRING_CONFIG>::ConstEndIterator() const
	{
		return CONST_ITERATOR_TYPE(&rawData,length,rawData.size()-1);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::REVERSE_ITERATOR_TYPE BaseString<STRING_CONFIG>::ReverseBeginIterator()
	{
		ITERATOR_TYPE temp(VectorRef<DATA_ELEMENT>(&rawData),length,rawData.size()-1);

		// Step back to the last character in the string
		--temp;

		return ReverseIterator<ITERATOR_TYPE>(temp);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::REVERSE_ITERATOR_TYPE BaseString<STRING_CONFIG>::ReverseEndIterator()
	{
		ITERATOR_TYPE temp(VectorRef<DATA_ELEMENT>(&rawData),-1,-1);

		return ReverseIterator<ITERATOR_TYPE>(temp);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_REVERSE_ITERATOR_TYPE 
		BaseString<STRING_CONFIG>::ConstReverseBeginIterator() const
	{
		CONST_ITERATOR_TYPE temp(ConstVectorRef<DATA_ELEMENT>(&rawData),length,rawData.size()-1);

		// Step back to the first element of last character in the string
		--temp;

		return ReverseIterator<CONST_ITERATOR_TYPE>(temp);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_REVERSE_ITERATOR_TYPE 
		BaseString<STRING_CONFIG>::ConstReverseEndIterator() const
	{
		CONST_ITERATOR_TYPE temp(ConstVectorRef<DATA_ELEMENT>(&rawData),-1,-1);

		return ReverseIterator<CONST_ITERATOR_TYPE>(temp);
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::RemoveLastChar()
	{
		ITERATOR_TYPE iter = EndIterator();

		--iter;

		ResizeRaw(length-1,iter.RawPosition());
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::ResizeRaw(const Ceng::INT32 newIndex,const Ceng::INT32 newRawSize)
	{
		length = newIndex;

		rawData.resize(newRawSize);

		rawData.push_back('\0');
	}

	template<class STRING_CONFIG>
	const Ceng::BOOL BaseString<STRING_CONFIG>::operator == (const BaseString &other) const
	{
		if (length != other.length) return false;

		auto test = std::mismatch(rawData.begin(),rawData.end(),other.rawData.begin());

		if (test.first == rawData.end())
		{
			return true;
		}
		return false;
	}

	template<class STRING_CONFIG>
	const Ceng::BOOL BaseString<STRING_CONFIG>::operator != (const BaseString &other) const
	{
		return !(*this == other);
	}

	template<class STRING_CONFIG>
	template<class T>
	BaseString<STRING_CONFIG>& BaseString<STRING_CONFIG>::operator += (const T *source)
	{
		Append(source);

		return *this;
	}

	template<class STRING_CONFIG>
	BaseString<STRING_CONFIG>& BaseString<STRING_CONFIG>::operator += (const BaseString &other)
	{
		rawData.pop_back();

		std::copy(other.rawData.begin(),other.rawData.end()-1,std::back_inserter(rawData));

		length += other.length;

		rawData.push_back('\0');

		return *this;
	}

	template<class STRING_CONFIG>
	template<class T>
	BaseString<STRING_CONFIG>& BaseString<STRING_CONFIG>::operator += (const T &source)
	{
		Append(source);

		return *this;
	}

	template<class STRING_CONFIG>
	const BaseString<STRING_CONFIG> BaseString<STRING_CONFIG>::operator + (const BaseString &other) const
	{
		BaseString temp(*this);

		temp += other;

		return temp;
	}

	template<class STRING_CONFIG>
	template<class T>
	const BaseString<STRING_CONFIG> BaseString<STRING_CONFIG>::operator + (const T *source) const
	{
		BaseString temp(*this);

		temp += source;

		return temp;
	}

	template<class STRING_CONFIG>
	template<class T>
	const BaseString<STRING_CONFIG> BaseString<STRING_CONFIG>::operator + (const T &source) const
	{
		BaseString temp(*this);

		temp += source;

		return temp;
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Insert(const Ceng::INT32 index,const BaseString &string)
	{
		rawData.insert(rawData.begin()+index,string.rawData.size()-1,0);

		std::copy(string.rawData.begin(),string.rawData.end()-1,rawData.begin()+index);

		length += string.length;
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Insert(const Ceng::INT32 index,const char *string)
	{
		LITERAL_ITERATOR_UTF8 sourceIter(reinterpret_cast<const Ceng::UINT8*>(string));

		return Insert(index,sourceIter);
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Insert(const Ceng::INT32 index,const char16_t *string)
	{
		LITERAL_ITERATOR_UTF16 sourceIter(reinterpret_cast<const char16_t*>(string));

		return Insert(index,sourceIter);
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Insert(const Ceng::INT32 index,const CHAR32 *string)
	{
		LITERAL_ITERATOR_UTF32 sourceIter(reinterpret_cast<const CHAR32*>(string));

		return Insert(index,sourceIter);
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Insert(const Ceng::INT32 index,const wchar_t *string)
	{
		LITERAL_ITERATOR_WCHAR sourceIter(reinterpret_cast<const Ceng::WCHAR_TYPE*>(string));

		return Insert(index,sourceIter);
	}

	template<class STRING_CONFIG>
	template<class SOURCE_ITER_TYPE>
	void BaseString<STRING_CONFIG>::Insert(const Ceng::INT32 index,SOURCE_ITER_TYPE sourceIter)
	{
		CHAR32 temp;

		UINT32 k = 0;

		// NOTE: Do this instead of direct copy to replace all
		//       illegal sequences with the unknown symbol.

		do
		{
			temp = *sourceIter;

			if (temp == '\0')
			{
				break;
			}

			Insert(index+k,temp);

			k++;

			++sourceIter;
		} while(1);
	}
		


	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Insert(const Ceng::INT32 index,const CHAR32 unicode)
	{
		DATA_ELEMENT encoding[typename CHARACTER_TYPE::MAX_ENCODING_ELEMENTS];
		UINT32 bytes;

		bytes = typename CHARACTER_TYPE::EncodeUTF32(unicode,encoding);

		UINT32 k;

		rawData.insert(rawData.begin()+index,bytes,0);

		// TODO: Need insert iterator

		for(k=0;k<bytes;k++)
		{
			rawData[index+k] = encoding[k];
		}

		length++;
	}

	template<class STRING_CONFIG>
	BaseString<STRING_CONFIG>& BaseString<STRING_CONFIG>::Erase(const Ceng::INT32 position,const Ceng::INT32 n)
	{					
		CONST_ITERATOR_TYPE startIter,endIter;

		GetIteratorRange(position,n,&startIter,&endIter);

		return Erase(startIter,endIter);
	}

	template<class STRING_CONFIG>
	BaseString<STRING_CONFIG>& BaseString<STRING_CONFIG>::
		Erase(const CONST_ITERATOR_TYPE &startIter,const CONST_ITERATOR_TYPE &endIter)
	{
		if (startIter >= endIter)
		{
			return *this;
		}

		if (startIter == ConstEndIterator())
		{
			return *this;
		}
			
		rawData.erase(rawData.begin()+startIter.RawPosition(),rawData.begin()+endIter.RawPosition());

		length -= endIter.Index()-startIter.Index();

		return *this;
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::GetIteratorRange(const Ceng::INT32 startIndex,const Ceng::INT32 delta,
							CONST_ITERATOR_TYPE *startIter,CONST_ITERATOR_TYPE *endIter) const
	{
		*startIter = ConstBeginIterator();

		*startIter += startIndex;

		if (*startIter == ConstEndIterator())
		{
			*endIter = ConstEndIterator();
			return;
		}

		*endIter = *startIter;

		*endIter += delta;

		return;
	}

	template<class STRING_CONFIG>
	const BaseString<STRING_CONFIG> BaseString<STRING_CONFIG>::
		SubString(const Ceng::INT32 position,const Ceng::INT32 n) const
	{
		CONST_ITERATOR_TYPE startIter,endIter;

		GetIteratorRange(position,n,&startIter,&endIter);

		return SubString(startIter,endIter);
	}

	template<class STRING_CONFIG>
	const BaseString<STRING_CONFIG> BaseString<STRING_CONFIG>::
		SubString(const CONST_ITERATOR_TYPE &startIter,const CONST_ITERATOR_TYPE &endIter) const
	{
		if (startIter >= endIter)
		{
			return BaseString();
		}

		if (startIter == ConstEndIterator())
		{
			return BaseString();
		}

		Ceng::UINT32 endOffset = endIter.RawPosition();
		Ceng::UINT32 endIndex = endIter.Index();

		return BaseString(*this,startIter.RawPosition(),endOffset-startIter.RawPosition(),endIndex-startIter.Index());
	}
	
	template<class STRING_CONFIG>
	const Ceng::INT32 BaseString<STRING_CONFIG>::FindFirst(const char ascii,const Ceng::INT32 startIndex) const
	{
		CHAR32 match = ascii;

		if (ascii < 0)
		{
			return -1;
		}

		return FindFirst(match,startIndex);			
	}

	template<class STRING_CONFIG>
	const Ceng::INT32 BaseString<STRING_CONFIG>::FindFirst(const wchar_t codepoint,const Ceng::INT32 startIndex) const
	{
		return FindFirst( (CHAR32)codepoint,startIndex);			
	}
		
	template<class STRING_CONFIG>
	const Ceng::INT32 BaseString<STRING_CONFIG>::FindFirst(const CHAR32 unicode,const Ceng::INT32 startIndex) const
	{
		CONST_ITERATOR_TYPE temp;

		temp = FindFirst(unicode,ConstBeginIterator()+startIndex);

		if (temp == ConstEndIterator())
		{
			return -1;
		}

		return temp.Index();
	}	

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE 
		BaseString<STRING_CONFIG>::FindFirst(const CHAR32 unicode,CONST_ITERATOR_TYPE seekIterator) const
	{
		return FindFirst(unicode,seekIterator,ConstEndIterator());
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE 
		BaseString<STRING_CONFIG>::FindFirst(const char *test,CONST_ITERATOR_TYPE seekIterator) const
	{
		LITERAL_ITERATOR_UTF8 testIter(PointerRef<const Ceng::UINT8>(reinterpret_cast<const Ceng::UINT8*>(test)));

		return FindFirst(seekIterator,ConstEndIterator(),testIter);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE 
		BaseString<STRING_CONFIG>::FindFirst(const char *test,CONST_ITERATOR_TYPE startIterator,
									CONST_ITERATOR_TYPE endIterator) const
	{
		LITERAL_ITERATOR_UTF8 testIter(PointerRef<const Ceng::UINT8>(reinterpret_cast<const Ceng::UINT8*>(test)));

		return FindFirst(startIterator,endIterator,testIter);
	}

	template<class STRING_CONFIG>
	template<class STRING_ITERATOR,class SOURCE_ITERATOR>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE BaseString<STRING_CONFIG>::
		FindFirst(STRING_ITERATOR seekIterator,const STRING_ITERATOR &endIterator,
									const SOURCE_ITERATOR &testIterator) const
	{
		CHAR32 a,b;

		STRING_ITERATOR start;

		do
		{
			SOURCE_ITERATOR workIter = testIterator;

			start = seekIterator;

			while(*workIter != '\0')
			{
				if (seekIterator == endIterator)
				{
					return ConstEndIterator();
				}

				a = *workIter;
				b = *seekIterator;

				++workIter;
				++seekIterator;

				if (a != b)
				{
					break;
				}

				if (*workIter == '\0')
				{
					return start;
				}					
			}

		} while(1);

		return ConstEndIterator();
	}
								

	template<class STRING_CONFIG>
	template<class ITER_TYPE>
	ITER_TYPE BaseString<STRING_CONFIG>::
		FindFirst(const CHAR32 unicode,ITER_TYPE seekIterator,const ITER_TYPE &endPoint) const
	{
		CHAR32 temp;

		do
		{
			if (seekIterator == endPoint)
			{
				return endPoint;
			}

			temp = *seekIterator;

			if (temp == unicode)
			{
				return seekIterator;
			}

			++seekIterator;

		} while(1);

		return endPoint;
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE 
		BaseString<STRING_CONFIG>::
		FindLast(const CHAR32 unicode,CONST_ITERATOR_TYPE seekIterator) const
	{
		return FindFirst(unicode, ConstReverseBeginIterator(),
			CONST_REVERSE_ITERATOR_TYPE(seekIterator)).Iterator();
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_REVERSE_ITERATOR_TYPE 
		BaseString<STRING_CONFIG>::
		FindLast(const CHAR32 unicode,CONST_REVERSE_ITERATOR_TYPE seekIterator) const
	{
		return FindFirst(unicode,seekIterator,ConstReverseEndIterator());
	}

	template<class STRING_CONFIG>
	template<class T>
	const Ceng::INT32 BaseString<STRING_CONFIG>::
		FindFirstOf(const T *test,const Ceng::INT32 startIndex) const
	{
		CONST_ITERATOR_TYPE result;

		result = FindFirstOf(test,ConstBeginIterator() + startIndex);

		if (result == ConstEndIterator())
		{
			return -1;
		}

		return result.Index();
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE 
		BaseString<STRING_CONFIG>::
		FindFirstOf(const char *test,CONST_ITERATOR_TYPE seekIterator) const
	{
		LITERAL_ITERATOR_UTF8 testIter(PointerRef<const Ceng::UINT8>(reinterpret_cast<const Ceng::UINT8*>(test)));

		return FindFirstOf(seekIterator,testIter);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE 
		BaseString<STRING_CONFIG>::
		FindFirstOf(const char *test,CONST_ITERATOR_TYPE startIterator,
									CONST_ITERATOR_TYPE endIterator) const
	{
		LITERAL_ITERATOR_UTF8 testIter(PointerRef<const Ceng::UINT8>(reinterpret_cast<const Ceng::UINT8*>(test)));

		return FindFirstOf(startIterator,testIter,endIterator);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE 
		BaseString<STRING_CONFIG>::
		FindFirstOf(const char16_t *test,CONST_ITERATOR_TYPE seekIterator) const
	{
		LITERAL_ITERATOR_UTF16 testIter(PointerRef<const Ceng::UINT16>(reinterpret_cast<const Ceng::UINT16*>(test)));

		return FindFirstOf(seekIterator,testIter);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE BaseString<STRING_CONFIG>::
		FindFirstOf(const CHAR32 *test,CONST_ITERATOR_TYPE seekIterator) const
	{
		LITERAL_ITERATOR_UTF32 testIter(PointerRef<const Ceng::UINT32>(reinterpret_cast<const Ceng::UINT32*>(test)));

		return FindFirstOf(seekIterator,testIter);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE BaseString<STRING_CONFIG>::
		FindFirstOf(const wchar_t *test,CONST_ITERATOR_TYPE seekIterator) const
	{
		LITERAL_ITERATOR_WCHAR testIter(PointerRef<const Ceng::WCHAR_TYPE>(reinterpret_cast<const Ceng::WCHAR_TYPE*>(test)));

		return FindFirstOf(seekIterator,testIter);
	}

	template<class STRING_CONFIG>
	template<class SOURCE_ITER_TYPE>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE BaseString<STRING_CONFIG>::
		FindFirstOf(CONST_ITERATOR_TYPE seekIterator,const SOURCE_ITER_TYPE testIter) const
	{
		return FindFirstOf(seekIterator,testIter,ConstEndIterator());
	}

	template<class STRING_CONFIG>
	template<class SOURCE_ITER_TYPE>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE BaseString<STRING_CONFIG>::
		FindLastOf(CONST_ITERATOR_TYPE seekIterator, const SOURCE_ITER_TYPE testIter) const
	{
		return FindFirstOf(ConstReverseBeginIterator(), testIter,CONST_REVERSE_ITERATOR_TYPE(seekIterator)
			).Iterator();

		//return FindFirstOf(seekIterator, testIter, ConstReverseEndIterator());
	}

	template<class STRING_CONFIG>
	template<class SOURCE_ITER_TYPE>
	typename BaseString<STRING_CONFIG>::CONST_REVERSE_ITERATOR_TYPE BaseString<STRING_CONFIG>::
		FindLastOf(CONST_REVERSE_ITERATOR_TYPE seekIterator,const SOURCE_ITER_TYPE testIter) const
	{
		return FindFirstOf(seekIterator,testIter,ConstReverseEndIterator());
	}

	template<class STRING_CONFIG>
	template<class T>
	const Ceng::INT32 BaseString<STRING_CONFIG>::FindLastOf(const T *test,const Ceng::INT32 startIndex) const
	{
		CONST_REVERSE_ITERATOR_TYPE result;

		result = FindLastOf(test,ConstReverseBeginIterator() + (length-startIndex-1));

		if (result == ConstReverseEndIterator())
		{
			return -1;
		}

		return result.Iterator().Index();
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE
		BaseString<STRING_CONFIG>::
		FindLastOf(const char *test, CONST_ITERATOR_TYPE seekIterator) const
	{
		LITERAL_ITERATOR_UTF8 testIter(PointerRef<const Ceng::UINT8>(reinterpret_cast<const Ceng::UINT8*>(test)));

		return FindLastOf(seekIterator, testIter);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_REVERSE_ITERATOR_TYPE 
		BaseString<STRING_CONFIG>::
		FindLastOf(const char *test,CONST_REVERSE_ITERATOR_TYPE seekIterator) const
	{
		LITERAL_ITERATOR_UTF8 testIter(PointerRef<const Ceng::UINT8>(reinterpret_cast<const Ceng::UINT8*>(test)));

		return FindLastOf(seekIterator,testIter);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE
		BaseString<STRING_CONFIG>::
		FindLastOf(const char16_t *test, CONST_ITERATOR_TYPE seekIterator) const
	{
		LITERAL_ITERATOR_UTF16 testIter(PointerRef<const Ceng::UINT16>(reinterpret_cast<const Ceng::UINT16*>(test)));

		return FindLastOf(seekIterator, testIter);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_REVERSE_ITERATOR_TYPE 
		BaseString<STRING_CONFIG>::
		FindLastOf(const char16_t *test,CONST_REVERSE_ITERATOR_TYPE seekIterator) const
	{
		LITERAL_ITERATOR_UTF16 testIter(PointerRef<const Ceng::UINT16>(reinterpret_cast<const Ceng::UINT16*>(test)));

		return FindLastOf(seekIterator,testIter);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_REVERSE_ITERATOR_TYPE 
		BaseString<STRING_CONFIG>::
		FindFirstOf(const CHAR32 *test,CONST_REVERSE_ITERATOR_TYPE seekIterator) const
	{
		LITERAL_ITERATOR_UTF32 testIter(PointerRef<const Ceng::UINT32>(reinterpret_cast<const Ceng::UINT32*>(test)));

		return FindFirstOf(seekIterator, testIter,ConstReverseEndIterator());

		//return FindLastOf(seekIterator,testIter);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE
		BaseString<STRING_CONFIG>::
		FindLastOf(const wchar_t *test, CONST_ITERATOR_TYPE seekIterator) const
	{
		LITERAL_ITERATOR_WCHAR testIter(PointerRef<const Ceng::WCHAR_TYPE>(reinterpret_cast<const Ceng::WCHAR_TYPE*>(test)));

		return FindLastOf(seekIterator, testIter);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_REVERSE_ITERATOR_TYPE 
		BaseString<STRING_CONFIG>::
		FindLastOf(const wchar_t *test,CONST_REVERSE_ITERATOR_TYPE seekIterator) const
	{
		LITERAL_ITERATOR_WCHAR testIter(PointerRef<const Ceng::WCHAR_TYPE>(reinterpret_cast<const Ceng::WCHAR_TYPE*>(test)));

		return FindLastOf(seekIterator,testIter);
	}

	template<class STRING_CONFIG>
	template<class STRING_ITER_TYPE,class SOURCE_ITER_TYPE>
	typename STRING_ITER_TYPE BaseString<STRING_CONFIG>::
		FindFirstOf(STRING_ITER_TYPE seekIterator,const SOURCE_ITER_TYPE testIter,
										const STRING_ITER_TYPE &endPoint) const
	{
		CHAR32 temp,pattern;

		if (seekIterator == endPoint)
		{
			return seekIterator;
		}

		do
		{
			temp = *seekIterator;

			SOURCE_ITER_TYPE matchIter(testIter);

			do
			{
				pattern = *matchIter;

				if (pattern == '\0') break;

				if (temp == pattern)
				{
					return seekIterator;
				}

				++matchIter;

			} while(1);

			++seekIterator;

		} while(seekIterator != endPoint);

		return seekIterator;
	}

	template<class STRING_CONFIG>
	template<class T>
	const Ceng::INT32 BaseString<STRING_CONFIG>::
		FindFirstNotOf(const T *test,const Ceng::INT32 startIndex) const
	{
		CONST_ITERATOR_TYPE result;

		result = FindFirstNotOf(test,ConstBeginIterator() + startIndex);

		if (result == ConstEndIterator())
		{
			return -1;
		}

		return result.Index();
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE BaseString<STRING_CONFIG>::
		FindFirstNotOf(const char *test,CONST_ITERATOR_TYPE seekIterator) const
	{
		LITERAL_ITERATOR_UTF8 testIter(PointerRef<const Ceng::UINT8>(reinterpret_cast<const Ceng::UINT8*>(test)));

		return FindFirstNotOf(seekIterator,testIter);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE BaseString<STRING_CONFIG>::
		FindFirstNotOf(const char16_t *test,CONST_ITERATOR_TYPE seekIterator) const
	{
		LITERAL_ITERATOR_UTF16 testIter(PointerRef<const Ceng::UINT16>(reinterpret_cast<const Ceng::UINT16*>(test)));

		return FindFirstNotOf(seekIterator,testIter);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE BaseString<STRING_CONFIG>::
		FindFirstNotOf(const CHAR32 *test,CONST_ITERATOR_TYPE seekIterator) const
	{
		LITERAL_ITERATOR_UTF32 testIter(PointerRef<const Ceng::UINT32>(reinterpret_cast<const Ceng::UINT32*>(test)));

		return FindFirstNotOf(seekIterator,testIter);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE BaseString<STRING_CONFIG>::
		FindFirstNotOf(const wchar_t *test,CONST_ITERATOR_TYPE seekIterator) const
	{
		LITERAL_ITERATOR_WCHAR testIter(PointerRef<const Ceng::WCHAR_TYPE>(reinterpret_cast<const Ceng::WCHAR_TYPE*>(test)));

		return FindFirstNotOf(seekIterator,testIter);
	}

	template<class STRING_CONFIG>
	template<class SOURCE_ITER_TYPE>
	typename BaseString<STRING_CONFIG>::CONST_ITERATOR_TYPE BaseString<STRING_CONFIG>::
		FindFirstNotOf(CONST_ITERATOR_TYPE stringIterator,
											SOURCE_ITER_TYPE patternIterator) const
	{
		return FindFirstNotOf(stringIterator,patternIterator,ConstEndIterator());
	}

	template<class STRING_CONFIG>
	template<class STRING_ITER,class SOURCE_ITER_TYPE>
	typename STRING_ITER BaseString<STRING_CONFIG>::
		FindFirstNotOf(STRING_ITER stringIterator,const SOURCE_ITER_TYPE patternIterator,
										const STRING_ITER &endPoint) const
	{
		CHAR32 temp,pattern;

		if (stringIterator == endPoint)
		{
			return stringIterator;
		}

		do
		{
			temp = *stringIterator;

			SOURCE_ITER_TYPE matchIter(patternIterator);

			do
			{
				pattern = *matchIter;

				if (pattern == '\0')
				{
					return stringIterator;
				}

				if (pattern == temp) break;

				++matchIter;

			} while(1);

			++stringIterator;

		} while(stringIterator != endPoint);

		return stringIterator;
	}

	template<class STRING_CONFIG>
	template<class T>
	const Ceng::INT32 BaseString<STRING_CONFIG>::FindLastNotOf(const T *test,const Ceng::INT32 startIndex) const
	{
		CONST_REVERSE_ITERATOR_TYPE result;

		Ceng::INT32 delta = length-startIndex-1;

		if (delta < 0) delta = 0;

		CONST_REVERSE_ITERATOR_TYPE start = ConstReverseBeginIterator();

		CONST_REVERSE_ITERATOR_TYPE temp = start + delta;

		result = FindLastNotOf(test,temp);

		if (result == ConstReverseEndIterator())
		{
			return -1;
		}

		return result.Iterator().Index();
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_REVERSE_ITERATOR_TYPE BaseString<STRING_CONFIG>::
		FindLastNotOf(const char *test,CONST_REVERSE_ITERATOR_TYPE seekIterator) const
	{
		LITERAL_ITERATOR_UTF8 testIter(PointerRef<const Ceng::UINT8>(reinterpret_cast<const Ceng::UINT8*>(test)));

		return FindLastNotOf(seekIterator,testIter);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_REVERSE_ITERATOR_TYPE BaseString<STRING_CONFIG>::
		FindLastNotOf(const char16_t *test,CONST_REVERSE_ITERATOR_TYPE seekIterator) const
	{
		LITERAL_ITERATOR_UTF16 testIter(PointerRef<const Ceng::UINT16>(reinterpret_cast<const Ceng::UINT16*>(test)));

		return FindLastNotOf(seekIterator,testIter);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_REVERSE_ITERATOR_TYPE BaseString<STRING_CONFIG>::
		FindLastNotOf(const CHAR32 *test,CONST_REVERSE_ITERATOR_TYPE seekIterator) const
	{
		LITERAL_ITERATOR_UTF32 testIter(PointerRef<const Ceng::UINT32>(reinterpret_cast<const Ceng::UINT32*>(test)));

		return FindLastNotOf(seekIterator,testIter);
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::CONST_REVERSE_ITERATOR_TYPE BaseString<STRING_CONFIG>::
		FindLastNotOf(const wchar_t *test,CONST_REVERSE_ITERATOR_TYPE seekIterator) const
	{
		LITERAL_ITERATOR_WCHAR testIter(PointerRef<const Ceng::WCHAR_TYPE>(reinterpret_cast<const Ceng::WCHAR_TYPE*>(test)));

		return FindLastNotOf(seekIterator,testIter);
	}

	template<class STRING_CONFIG>
	template<class SOURCE_ITER_TYPE>
	typename BaseString<STRING_CONFIG>::CONST_REVERSE_ITERATOR_TYPE BaseString<STRING_CONFIG>::
		FindLastNotOf(CONST_REVERSE_ITERATOR_TYPE stringIterator,
											SOURCE_ITER_TYPE patternIterator) const
	{
		return FindFirstNotOf(stringIterator,patternIterator,ConstReverseEndIterator());
	}

	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::ITERATOR_TYPE 
		BaseString<STRING_CONFIG>::FindFirstEdit(const CHAR32 unicode,ITERATOR_TYPE seekIterator)
	{
		CHAR32 temp;

		do
		{
			temp = *seekIterator;

			if (temp == '\0')
			{
				return EndIterator();
			}

			if (temp == unicode)
			{
				return seekIterator;
			}

			++seekIterator;

		} while(1);

		return EndIterator();
	}

	template<class STRING_CONFIG>
	template<class OTHER_CONFIG>
	void BaseString<STRING_CONFIG>::Append(const BaseString<OTHER_CONFIG> &source)
	{
		auto iter = source.ConstBeginIterator();

		rawData.pop_back();

		while (iter != source.ConstEndIterator())
		{
			ChainedAppend(*iter);

			++iter;
		}

		rawData.push_back('\0');
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Append(const Ceng::CHAR32 unicode)
	{
		DATA_ELEMENT encoding[typename CHARACTER_TYPE::MAX_ENCODING_ELEMENTS];
		INT32 bytes;

		bytes = typename CHARACTER_TYPE::EncodeUTF32(unicode,encoding);

		INT32 k;

		rawData.pop_back();

		// TODO: Need insert iterator

		for(k=0;k<bytes;k++)
		{
			rawData.push_back(encoding[k]);
		}

		length++;

		rawData.push_back('\0');
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Append(const char source)
	{
		Append( CHAR32(source));
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Append(const wchar_t source)
	{
		Append( CHAR32(source));
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Append(const char16_t source)
	{
		Append( CHAR32(source));
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Append(const std::string &source)
	{
		Append(source.c_str());
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Append(const std::wstring &source)
	{
		Append(source.c_str());
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Append(const char *source)
	{
		LITERAL_ITERATOR_UTF8 sourceIter(PointerRef<const Ceng::UINT8>(reinterpret_cast<const Ceng::UINT8*>(source)));

		CHAR32 temp;

		UINT32 characters = 0;

		// NOTE: Do this instead of direct copy to replace all
		//       illegal sequences with the unknown symbol.

		rawData.pop_back();

		do
		{
			temp = *sourceIter;

			if (temp == '\0')
			{
				break;
			}

			ChainedAppend(temp);
			characters++;

			++sourceIter;
		} while(1);

		length += characters;

		rawData.push_back('\0');
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Append(const char16_t *source)
	{
		LITERAL_ITERATOR_UTF16 sourceIter(PointerRef<const Ceng::UINT16>(reinterpret_cast<const Ceng::UINT16*>(source)));

		CHAR32 temp;

		UINT32 characters = 0;

		// NOTE: Do this instead of direct copy to replace all
		//       illegal sequences with the unknown symbol.

		rawData.pop_back();

		do
		{
			temp = *sourceIter;

			if (temp == '\0')
			{
				break;
			}

			ChainedAppend(temp);
			characters++;

			++sourceIter;
		} while(1);

		length += characters;

		rawData.push_back('\0');
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Append(const CHAR32 *source)
	{
		LITERAL_ITERATOR_UTF32 sourceIter(PointerRef<const Ceng::UINT32>(reinterpret_cast<const Ceng::UINT32*>(source)));

		CHAR32 temp;

		UINT32 characters = 0;

		// NOTE: Do this instead of direct copy to replace all
		//       illegal sequences with the unknown symbol.

		rawData.pop_back();

		do
		{
			temp = *sourceIter;

			if (temp == '\0')
			{
				break;
			}

			ChainedAppend(temp);
			characters++;

			++sourceIter;
		} while(1);

		length += characters;

		rawData.push_back('\0');
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Append(const wchar_t *source)
	{
		// NOTE: Windows only.

		Append( reinterpret_cast<const WCHAR_TYPE*>(source) );
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Append(const Ceng::FLOAT32 value)
	{
		char digits[64];

		sprintf_s(digits,"%f",value);

		Append(digits);
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Append(const Ceng::FLOAT64 value)
	{
		char digits[64];

		sprintf_s(digits,"%lf",value);

		Append(digits);
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Append(const Ceng::INT32 value)
	{
		char digits[16];

		sprintf_s(digits,"%i",value);

		Append(digits);
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::Append(const Ceng::UINT32 value)
	{
		char digits[16];

		sprintf_s(digits,"%u",value);

		Append(digits);
	}

	template<class STRING_CONFIG>
	void BaseString<STRING_CONFIG>::ChainedAppend(const CHAR32 unicode)
	{
		DATA_ELEMENT encoding[typename CHARACTER_TYPE::MAX_ENCODING_ELEMENTS];
		UINT32 bytes;

		bytes = CHARACTER_TYPE::EncodeUTF32(unicode,encoding);

		UINT32 k;

		for(k=0;k<bytes;k++)
		{
			rawData.push_back(encoding[k]);
		}
	}

	template<class STRING_CONFIG>
	const typename BaseString<STRING_CONFIG>::CONST_REF_TYPE 
		BaseString<STRING_CONFIG>::ConstCharacter(const Ceng::UINT32 index) const
	{
		CONST_ITERATOR_TYPE sourceIter(ConstBeginIterator());

		sourceIter += index;

		return *sourceIter;
	}
		
	template<class STRING_CONFIG>
	typename BaseString<STRING_CONFIG>::REF_TYPE 
		BaseString<STRING_CONFIG>::CharacterRef(const Ceng::UINT32 index)
	{
		ITERATOR_TYPE sourceIter(BeginIterator());

		sourceIter += index;

		return *sourceIter;
	}

	//******************************************************************************
	// Default string classes

	typedef BaseString<StringConfig<CharacterUtf8>> StringUtf8;
	typedef BaseString<StringConfig<CharacterUtf16>> StringUtf16;
	typedef BaseString<StringConfig<CharacterUtf32>> StringUtf32;

	typedef Ceng::StringUtf8 String;

	/*
	typedef BaseString<CharacterUtf8> StringUTF8;
	typedef BaseString<CharacterUtf16> StringUTF16;
	typedef BaseString<CharacterUtf32> StringUTF32;
	*/
};

#include <iostream>

namespace std
{
	template<class CHARACTER_TYPE>
	ostream& operator << (ostream &stream, const Ceng::BaseString<CHARACTER_TYPE> &source)
	{
		typename Ceng::BaseString<CHARACTER_TYPE>::CONST_ITERATOR_TYPE iter(source.ConstBeginIterator());

		while (iter != source.ConstEndIterator())
		{
			stream << *iter;

			++iter;
		}

		return stream;
	}

	template<class CHARACTER_TYPE>
	wostream& operator << (wostream &stream, const Ceng::BaseString<CHARACTER_TYPE> &source)
	{
		typename Ceng::BaseString<CHARACTER_TYPE>::CONST_ITERATOR_TYPE iter(source.ConstBeginIterator());

		while (iter != source.ConstEndIterator())
		{
			stream << *iter;

			++iter;
		}

		return stream;
	}
}

//#include "../../MurmurHash3.h"

#if defined(_MSC_VER) && (_MSC_VER < 1600)

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;

// Other compilers

#else	// defined(_MSC_VER)

#include <stdint.h>

#endif // !defined(_MSC_VER)

#if defined(_MSC_VER)

#define FORCE_INLINE	__forceinline

#include <stdlib.h>

#define ROTL32(x,y)	_rotl(x,y)
#define ROTL64(x,y)	_rotl64(x,y)

#define BIG_CONSTANT(x) (x)

// Other compilers

#else	// defined(_MSC_VER)

#define	FORCE_INLINE inline __attribute__((always_inline))

inline uint32_t rotl32(uint32_t x, int8_t r)
{
	return (x << r) | (x >> (32 - r));
}

inline uint64_t rotl64(uint64_t x, int8_t r)
{
	return (x << r) | (x >> (64 - r));
}

#define	ROTL32(x,y)	rotl32(x,y)
#define ROTL64(x,y)	rotl64(x,y)

#define BIG_CONSTANT(x) (x##LLU)

#endif // !defined(_MSC_VER)

FORCE_INLINE uint32_t getblock32(const uint32_t * p, int i)
{
	return p[i];
}

FORCE_INLINE uint64_t getblock64(const uint64_t * p, int i)
{
	return p[i];
}

//-----------------------------------------------------------------------------
// Finalization mix - force all bits of a hash block to avalanche

FORCE_INLINE uint32_t fmix32(uint32_t h)
{
	h ^= h >> 16;
	h *= 0x85ebca6b;
	h ^= h >> 13;
	h *= 0xc2b2ae35;
	h ^= h >> 16;

	return h;
}

inline void MurmurHash3_x86_32(const void * key, int len,
	uint32_t seed, void * out)
{
	const uint8_t * data = (const uint8_t*)key;
	const int nblocks = len / 4;

	uint32_t h1 = seed;

	const uint32_t c1 = 0xcc9e2d51;
	const uint32_t c2 = 0x1b873593;

	//----------
	// body

	const uint32_t * blocks = (const uint32_t *)(data + nblocks * 4);

	for (int i = -nblocks; i; i++)
	{
		uint32_t k1 = getblock32(blocks, i);

		k1 *= c1;
		k1 = ROTL32(k1, 15);
		k1 *= c2;

		h1 ^= k1;
		h1 = ROTL32(h1, 13);
		h1 = h1 * 5 + 0xe6546b64;
	}

	//----------
	// tail

	const uint8_t * tail = (const uint8_t*)(data + nblocks * 4);

	uint32_t k1 = 0;

	switch (len & 3)
	{
	case 3: k1 ^= tail[2] << 16;
	case 2: k1 ^= tail[1] << 8;
	case 1: k1 ^= tail[0];
		k1 *= c1; k1 = ROTL32(k1, 15); k1 *= c2; h1 ^= k1;
	};

	//----------
	// finalization

	h1 ^= len;

	h1 = fmix32(h1);

	*(uint32_t*)out = h1;
}


namespace std
{
	template<>
	struct hash<Ceng::StringUtf8>
	{
		std::size_t operator() (const Ceng::StringUtf8 &param) const
		{
			const unsigned int seed = 0xB0F57EE3;

			std::size_t result;

			MurmurHash3_x86_32(param.ToCString(), param.BufferSize(), seed, &result);

			return result;
		}
	};

	template<>
	struct hash<Ceng::StringUtf16>
	{
		std::size_t operator() (const Ceng::StringUtf16 &param) const
		{
			const unsigned int seed = 0xB0F57EE3;

			std::size_t result;

			MurmurHash3_x86_32(param.ToWString(), 2*param.BufferSize(), seed, &result);

			return result;
		}
	};

	template<>
	struct hash<Ceng::StringUtf32>
	{
		std::size_t operator() (const Ceng::StringUtf32 &param) const
		{
			const unsigned int seed = 0xB0F57EE3;

			std::size_t result;

			MurmurHash3_x86_32(param.ToWString(), 4 * param.BufferSize(), seed, &result);

			return result;
		}
	};

}

#endif