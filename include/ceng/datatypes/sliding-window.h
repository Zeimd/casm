/*****************************************************************************
*
* sliding-window.h
*
* Created By Jari Korkala 30/9/2014
*
*****************************************************************************/

#ifndef CENG_SLIDING_WINDOW_H
#define CENG_SLIDING_WINDOW_H

#include "aligned-buffer.h"

#include "return-val.h"

namespace Ceng
{
	template<class t_ElemType>
	class SlidingWindow
	{
	protected:

		AlignedBuffer<t_ElemType> buffer;

		/**
		 * Which buffer index is front of the window.
		 */
		Ceng::UINT32 frontIndex;

		/**
		 * Which input ID is currently front.
		 */
		Ceng::UINT32 frontId;

		Ceng::UINT32 sizePow2;
		Ceng::UINT32 wrapMask;

		SlidingWindow(const Ceng::UINT32 sizePow2,AlignedBuffer<t_ElemType> &buffer);

	public:

		SlidingWindow();
		~SlidingWindow();

		static SlidingWindow Allocate(const Ceng::UINT32 sizePow2,const Ceng::UINT32 alignment);

		
		SlidingWindow(const SlidingWindow &source);
		SlidingWindow(SlidingWindow &&source);

		SlidingWindow& operator = (const SlidingWindow &source);
		SlidingWindow& operator = (SlidingWindow &&source);

		/**
		 * Array access relative to front by index.
		 */
		t_ElemType& operator [] (const Ceng::UINT32 index);

		/**
		 * Array access relative to front by index.
		 */
		const t_ElemType& operator[] (const Ceng::UINT32 index) const;

		/**
		 * Array access relative to index zero.
		 */
		t_ElemType& GetAbsoluteIndex(const Ceng::UINT32 index);

		/**
		 * Access by slot id. 
		 */
		t_ElemType& GetSlot(const Ceng::UINT32 id);

		/**
		 * Access by slot id. 
		 */
		const t_ElemType& GetSlot(const Ceng::UINT32 id) const;

		/**
		 * Access by slot id with range checks.
		 */
		const CRESULT GetSlotSafe(const Ceng::UINT32 id,t_ElemType *out);

		/**
		 * Write to slot if id is valid.
		 */
		const CRESULT WriteSlot(const Ceng::UINT32 id,const t_ElemType &value);

		const Ceng::UINT32 Size() const;

		/**
		 * Slot id of the current first element in the window.
		 */
		const Ceng::UINT32 FrontId() const;

		/**
		 * Checks whether the id falls within current window.
		 */
		const Ceng::BOOL IsValidId(const Ceng::UINT32 id) const;

		/**
		 * Step the window by given amount of slots.
		 */
		void Step(const Ceng::UINT32 amount);

		/**
		 * Returns slot id of given absolute array index.
		 */
		const Ceng::UINT32 IdByIndex(const Ceng::UINT32 index) const;

	protected:

		void Clear();
		void Reset();

		void CopyPODs(const SlidingWindow &source);

		/**
		 * Clear object after getting moved.
		 */
		void ClearAfterMove();

		const CRESULT IdToIndex(const Ceng::UINT32 id,Ceng::UINT32 *out_index);

	};

	template<class t_ElemType>
	SlidingWindow<t_ElemType>::SlidingWindow()
		: frontIndex(0),frontId(0),wrapMask(0),sizePow2(0)
	{
	}

	template<class t_ElemType>
	SlidingWindow<t_ElemType>::SlidingWindow(const Ceng::UINT32 sizePow2,
												AlignedBuffer<t_ElemType> &buffer)
		: frontIndex(0),frontId(0),sizePow2(sizePow2),
		buffer(buffer)
	{
		wrapMask = (1 << sizePow2) - 1;
	}

	template<class t_ElemType>
	SlidingWindow<t_ElemType> SlidingWindow<t_ElemType>::Allocate(const Ceng::UINT32 sizePow2,
																	const Ceng::UINT32 alignment)
	{
		auto buffer = AlignedBuffer<t_ElemType>(1 << sizePow2,alignment);

		Ceng::UINT32 k;

		for(k=0;k<buffer.GetElements();k++)
		{
			new (&buffer[k]) t_ElemType();
		}

		return SlidingWindow(sizePow2,buffer);
	}

	template<class t_ElemType>
	void SlidingWindow<t_ElemType>::CopyPODs(const SlidingWindow &source)
	{
		frontIndex = source.frontIndex;
		frontId = source.frontId;
		wrapMask = source.wrapMask;
		sizePow2 = source.sizePow2;
	}

	template<class t_ElemType>
	SlidingWindow<t_ElemType>::SlidingWindow(const SlidingWindow &source)
	{
		CopyPODs(source);

		buffer = AlignedBuffer<t_ElemType>(source.buffer.GetElements(),
			source.buffer.GetAlignment());

		Ceng::UINT32 k;

		for(k=0;k<buffer.GetElements();k++)
		{
			new (&buffer[k]) t_ElemType(source.buffer[k]);
		}
	}

	template<class t_ElemType>
	void SlidingWindow<t_ElemType>::ClearAfterMove()
	{
		buffer = nullptr;
	}

	template<class t_ElemType>
	SlidingWindow<t_ElemType>::SlidingWindow(SlidingWindow &&source)
	{
		CopyPODs();

		buffer = source.buffer;

		source.ClearAfterMove();
	}

	template<class t_ElemType>
	SlidingWindow<t_ElemType>& SlidingWindow<t_ElemType>::operator=(const SlidingWindow &source)
	{
		if (&source == this)
		{
			return *this;
		}

		CopyPODs();

		buffer = AlignedBuffer<t_ElemType>(source.buffer.GetElements(),
		source.buffer.GetAlignment());

		Ceng::UINT32 k;

		for(k=0;k<buffer.GetElements();k++)
		{
			new (&buffer[k]) t_ElemType(source.buffer[k]);
		}

		return *this;
	}

	template<class t_ElemType>
	SlidingWindow<t_ElemType>& SlidingWindow<t_ElemType>::operator=(SlidingWindow &&source)
	{
		if (&source == this)
		{
			return *this;
		}

		CopyPODs();

		buffer = source.buffer;

		source.ClearAfterMove();

		return *this;
	}

	template<class t_ElemType>
	SlidingWindow<t_ElemType>::~SlidingWindow()
	{
		Clear();
	}

	template<class t_ElemType>
	void SlidingWindow<t_ElemType>::Clear()
	{
		if (buffer != nullptr)
		{
			Ceng::UINT32 k;

			for(k=0;k<buffer.GetElements();k++)
			{
				buffer[k].~t_ElemType();
			}
		}

		frontIndex = 0;
		frontId = 0;
	}

	template<class t_ElemType>
	void SlidingWindow<t_ElemType>::Reset()
	{
		if (buffer != nullptr)
		{
			Ceng::UINT32 k;

			for(k=0;k<buffer.Size();k++)
			{
				new (&buffer[k]) t_ElemType();
			}
		}

		frontIndex = 0;
		frontId = 0;
	}

	template<class t_ElemType>
	const Ceng::UINT32 SlidingWindow<t_ElemType>::Size() const
	{
		return buffer.GetElements();
	}

	template<class t_ElemType>
	const Ceng::UINT32 SlidingWindow<t_ElemType>::FrontId() const
	{
		return frontId;
	}

	template<class t_ElemType>
	const Ceng::BOOL SlidingWindow<t_ElemType>::IsValidId(const Ceng::UINT32 id) const
	{
		Ceng::UINT32 index;

		CRESULT cresult = IdToIndex(id,&index);

		if (cresult != CE_OK) return false;
		return true;
	}

	template<class t_ElemType>
	void SlidingWindow<t_ElemType>::Step(const Ceng::UINT32 amount)
	{
		Ceng::UINT32 k;
		
		for(k=0;k<amount;k++)
		{
			buffer[frontIndex] = t_ElemType();
			
			++frontIndex;
			frontIndex = frontIndex & wrapMask;

			++frontId;
		}
	}

	template<class t_ElemType>
	t_ElemType& SlidingWindow<t_ElemType>::operator [] (const Ceng::UINT32 index)
	{
		Ceng::UINT32 k = (frontIndex + index) & wrapMask;

		return buffer[k];
	}

	template<class t_ElemType>
	const t_ElemType& SlidingWindow<t_ElemType>::operator [] (const Ceng::UINT32 index) const
	{
		Ceng::UINT32 k = (frontIndex + index) & wrapMask;

		return buffer[k];
	}

	template<class t_ElemType>
	t_ElemType& SlidingWindow<t_ElemType>::GetAbsoluteIndex(const Ceng::UINT32 index)
	{
		return buffer[index];
	}


	template<class t_ElemType>
	const CRESULT SlidingWindow<t_ElemType>::IdToIndex(const Ceng::UINT32 id,Ceng::UINT32 *out_index)
	{
		Ceng::UINT32 delta=0;

		if (id < frontId)
		{
			if (frontId + buffer.GetElements() < frontId)
			{
				// Slot id counter wraps during current window

				delta = (-1 - frontId) + id;
			}
			else
			{
				return CE_ERR_INVALID_PARAM;
			}
		}
		else
		{
			if (id >= frontId + buffer.GetElements())
			{
				return CE_ERR_INVALID_PARAM;
			}

			delta = id - frontId;
		}

		*out_index = (frontIndex + delta) & wrapMask;

		return CE_OK;
	}

	template<class t_ElemType>
	const CRESULT SlidingWindow<t_ElemType>::WriteSlot(const Ceng::UINT32 id,const t_ElemType &value)
	{
		Ceng::UINT32 index=0;

		CRESULT cresult = IdToIndex(id,&index);

		if (cresult != CE_OK) return cresult;

		buffer[index] = value;

		return CE_OK;
	}

	template<class t_ElemType>
	const Ceng::UINT32 SlidingWindow<t_ElemType>::IdByIndex(const Ceng::UINT32 index) const
	{
		Ceng::UINT32 delta;

		if (index < frontIndex)
		{
			delta = (buffer.GetElements()-frontIndex)+index;
		}
		else
		{
			delta = index - frontIndex;
		}

		return frontId + delta;
	}


	template<class t_ElemType>
	const CRESULT SlidingWindow<t_ElemType>::GetSlotSafe(const Ceng::UINT32 id,t_ElemType *out)
	{
		Ceng::UINT32 index=0;

		CRESULT cresult = IdToIndex(id,&index);

		if (cresult != CE_OK) return cresult;

		*out = buffer[index];			

		return CE_OK;
	}

	template<class t_ElemType>
	t_ElemType& SlidingWindow<t_ElemType>::GetSlot(const Ceng::UINT32 id)
	{
		Ceng::UINT32 index=0;

		CRESULT cresult = IdToIndex(id,&index);

		if (cresult != CE_OK) return t_ElemType();

		return &buffer[index];			
	}

	template<class t_ElemType>
	const t_ElemType& SlidingWindow<t_ElemType>::GetSlot(const Ceng::UINT32 id) const
	{
		Ceng::UINT32 index=0;

		CRESULT cresult = IdToIndex(id,&index);

		if (cresult != CE_OK) return t_ElemType();

		return &buffer[index];			
	}

}

#endif