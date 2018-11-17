/*****************************************************************************
*
* string-manipulator.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef CENG_STRING_MANIPULATOR_H
#define CENG_STRING_MANIPULATOR_H

#include "ce-string.h"

namespace Ceng
{
	class StringManipulator
	{
	public:

		template<class STRING_TYPE,class CHAR_TYPE>
		static const STRING_TYPE Strip(const STRING_TYPE &source,const CHAR_TYPE code)
		{
			return Strip(source,(char32_t)code,
								source.ConstBeginIterator(),
								source.ConstEndIterator());
		}

		template<class STRING_TYPE>
		static const STRING_TYPE Strip(const STRING_TYPE &source,const char32_t unicode,
											const Ceng::INT32 startIndex,const Ceng::INT32 n)
		{
			if (n <= 0)
			{
				return source;
			}

			typename STRING_TYPE::CONST_ITERATOR_TYPE start,end;

			start = source.ConstBeginIterator() + startIndex;

			end = start + n;

			return Strip(source,unicode,start,end);			
		}

		template<class STRING_TYPE>
		static const STRING_TYPE Strip(const STRING_TYPE &source,const char32_t unicode,
											const typename STRING_TYPE::CONST_ITERATOR_TYPE &start,
											const typename STRING_TYPE::CONST_ITERATOR_TYPE &end)
		{
			char32_t stripList[2] = {unicode,'\0'};

			return Strip(source,stripList,start,end);
		}

		template<class STRING_TYPE,class STRIP_TYPE>
		static const STRING_TYPE Strip(const STRING_TYPE &source,const STRIP_TYPE *stripList)
		{
			return Strip(source,stripList,source.ConstBeginIterator()
								,source.ConstEndIterator());
		}

		template<class STRING_TYPE,class STRIP_TYPE>
		static const STRING_TYPE Strip(const STRING_TYPE &source,const STRIP_TYPE *stripList,
										const Ceng::INT32 startIndex,const Ceng::INT32 n)
		{
			if (n <= 0)
			{
				return source;
			}

			typename STRING_TYPE::CONST_ITERATOR_TYPE start,end;

			start = source.ConstBeginIterator() + startIndex;
			end = start + n;

			return Strip(source,stripList,start,end);
		}

		template<class STRING_TYPE,class STRIP_TYPE>
		static const STRING_TYPE Strip(const STRING_TYPE &source,const STRIP_TYPE *stripList,
											const typename STRING_TYPE::CONST_ITERATOR_TYPE &start,
											const typename STRING_TYPE::CONST_ITERATOR_TYPE &end)
		{
			if (end <= start)
			{
				return source;
			}

			if (start == source.ConstEndIterator())
			{
				return source;
			}

			typename STRING_TYPE::CONST_ITERATOR_TYPE work(source.ConstBeginIterator());

			STRING_TYPE output;

			while(work != start)
			{
				output += CHAR32(*work);
				++work;
			}

			typename STRING_TYPE::CONST_ITERATOR_TYPE spanStart,spanEnd;

			do
			{
				spanStart = source.FindFirstNotOf(stripList,work);

				if (spanStart > end)
				{
					spanStart = end;
				}

				spanEnd = source.FindFirstOf(stripList,spanStart+1);

				if (spanEnd > end)
				{
					spanEnd = end;
				}

				output += source.SubString(spanStart,spanEnd);

				work = spanEnd;

			} while (work < end);

			while(work != source.ConstEndIterator())
			{
				output += CHAR32(*work);
				++work;
			}

			return output;
		}

		template<class STRING_TYPE,class STRIP_TYPE>
		static const STRING_TYPE StripRepeatsOf(const STRING_TYPE &source,const STRIP_TYPE *stripList)
		{
			return StripRepeatsOf(source,stripList,
										source.ConstBeginIterator(),
										source.ConstEndIterator());
		}

		template<class STRING_TYPE,class STRIP_TYPE>
		static const STRING_TYPE StripRepeatsOf(const STRING_TYPE &source,const STRIP_TYPE *stripList,
													const Ceng::INT32 startIndex,const Ceng::INT32 n)
		{
			if (n <= 0)
			{
				return source;
			}

			typename STRING_TYPE::CONST_ITERATOR_TYPE start,end;

			start = source.ConstBeginIterator() + startIndex;
			end = start + n;

			return StripRepeatsOf(source,stripList,start,end);
		}

		/**
		 * If a sequence of a strip codepoint appears, remove all but one
		 * of them.
		 */
		template<class STRING_TYPE,class STRIP_TYPE>
		static const STRING_TYPE StripRepeatsOf(const STRING_TYPE &source,const STRIP_TYPE *stripList,
													const typename STRING_TYPE::CONST_ITERATOR_TYPE &start,
													const typename STRING_TYPE::CONST_ITERATOR_TYPE &end)
		{
			if (end <= start)
			{
				return source;
			}

			if (start == source.ConstEndIterator())
			{
				return source;
			}
			
			typename STRING_TYPE::CONST_ITERATOR_TYPE work(source.ConstBeginIterator());

			STRING_TYPE output;

			while(work != start)
			{
				output += CHAR32(*work);
				++work;
			}

			typename STRING_TYPE::CONST_ITERATOR_TYPE spanStart,spanEnd;

			Char32 currentList[2] = {0,0};

			do
			{
				spanStart = work;

				spanEnd = source.FindFirstOf(stripList,spanStart);

				if (spanEnd > end)
				{
					spanEnd = end;
				}

				output += source.SubString(spanStart,spanEnd+1);

				currentList[0] = *spanEnd;

				spanStart = source.FindFirstNotOf(currentList,spanEnd+1);

				if (spanStart > end)
				{
					spanStart = end;
				}

				work = spanStart;

			} while (work < end);

			while(work != source.ConstEndIterator())
			{
				output += CHAR32(*work);
				++work;
			}

			return output;

		}

		/**
		 * Replace any codepoints in the strip list with a codepoint.
		 */
		template<class STRING_TYPE,class STRIP_TYPE>
		static const STRING_TYPE ReplaceWith(const STRING_TYPE &source,const STRIP_TYPE *list,const char32_t replace,
												const typename STRING_TYPE::CONST_ITERATOR_TYPE &start,
												const typename STRING_TYPE::CONST_ITERATOR_TYPE &end)
		{
			if (end <= start)
			{
				return source;
			}

			if (start == source.ConstEndIterator())
			{
				return source;
			}
			
			typename STRING_TYPE::CONST_ITERATOR_TYPE work(source.ConstBeginIterator());

			STRING_TYPE output;

			while(work != start)
			{
				output += CHAR32(*work);
				++work;
			}


			typename STRING_TYPE::CONST_ITERATOR_TYPE spanStart,spanEnd;

			do
			{
				spanStart = source.FindFirstNotOf(list,work);

				if (spanStart > end)
				{
					spanStart = end;
				}

				spanEnd = source.FindFirstOf(list,spanStart+1);

				if (spanEnd > end)
				{
					spanEnd = end;
				}

				while(work < spanStart)
				{
					output += CHAR32(replace);
					++work;
				}

				output += source.SubString(spanStart,spanEnd);

				work = spanEnd;				

			} while (work < end);

			while(work != source.ConstEndIterator())
			{
				output += CHAR32(*work);
				++work;
			}

			return output;
		}

		template<class STRING_TYPE,class STRIP_TYPE>
		static const STRING_TYPE ReplaceWith(const STRING_TYPE &source,const STRIP_TYPE *list,const char32_t replace)
		{
			return ReplaceWith(source,list,replace,
									source.ConstBeginIterator(),
									source.ConstEndIterator());
		}

		template<class STRING_TYPE,class STRIP_TYPE>
		static const STRING_TYPE ReplaceWith(const STRING_TYPE &source,const STRIP_TYPE *list,const char32_t replace,
												const Ceng::INT32 startIndex,const Ceng::INT32 n)
		{
			if (n <= 0)
			{
				return source;
			}

			typename STRING_TYPE::CONST_ITERATOR_TYPE start,end;

			start = source.ConstBeginIterator() + startIndex;
			end = start + n;

			return ReplaceWith(source,list,replace,start,end);
		}


		template<class STRING_TYPE,class STRIP_TYPE>
		static const STRING_TYPE LeftStrip(const STRING_TYPE &source,const STRIP_TYPE *stripList)
		{
			typename STRING_TYPE::CONST_ITERATOR_TYPE start;

			start = typename source.FindFirstNotOf(stripList,source.ConstBeginIterator());

			return source.SubString(start,source.ConstEndIterator());
		}

		template<class STRING_TYPE,class STRIP_TYPE>
		static const STRING_TYPE RightStrip(const STRING_TYPE &source,const STRIP_TYPE *stripList)
		{
			typename STRING_TYPE::CONST_REVERSE_ITERATOR_TYPE end;

			end = typename source.FindLastNotOf(stripList,source.ConstReverseBeginIterator());

			return source.SubString(source.ConstBeginIterator(),end.Iterator()+1);
		}
	};
}

#endif