/*****************************************************************************
*
* leaf-vector.h
*
* Created By Jari Korkala 3/9/2014
*
*****************************************************************************/

#ifndef CENG_LEAF_VECTOR_H
#define CENG_LEAF_VECTOR_H

#include <vector>

#include "basic-types.h"
#include "boolean.h"
#include "return-val.h"
#include "aligned-buffer.h"

namespace Ceng
{
	template<class t_ElemType>
	class LeafVector
	{
	protected:

		Ceng::UINT32 leafSize;
		Ceng::UINT32 alignment;

		std::vector<AlignedBuffer<t_ElemType>> leafList;

		Ceng::UINT32 elementCount;

		/**
		 * Where PushBack() adds on last leaf.
		 */
		Ceng::UINT32 backIndex;

		/**
		 * Which leaf contains back-element.
		 */
		Ceng::UINT32 backLeaf;

	public:

		LeafVector();
		~LeafVector();

		LeafVector(const LeafVector &source);
		LeafVector(LeafVector &&source);

		LeafVector(const Ceng::UINT32 leafSize,const Ceng::UINT32 alignment);

		LeafVector& operator = (const LeafVector &source);
		LeafVector& operator = (LeafVector &&source);

		/*
		LeafVector(const Ceng::UINT32 leafSize,const Ceng::UINT32 alignment,
					const Ceng::UINT32 initialElements,
					const t_ElemType &value);
					*/

		void Clear();

		const Ceng::BOOL IsEmpty() const;

		const Ceng::UINT32 Size() const;

		const Ceng::UINT32 Capacity() const;

		const CRESULT Reserve(const Ceng::UINT32 elements);

		const CRESULT Resize(const Ceng::UINT32 elements);

		void ShrinkToFit();

		const CRESULT PushBack(const t_ElemType &source);

		void PopBack();

		t_ElemType& Back();

		const t_ElemType& Back() const;

		t_ElemType& Front();

		const t_ElemType& Front() const;

		t_ElemType& operator[] (const Ceng::UINT32 index);

	protected:

		void CopyPODs(const LeafVector &source);

		const CRESULT AddLeaf();

		void PopLeaf();

		void Compact(const Ceng::UINT32 victimLeafs);

	};

	template<class t_ElemType>
	const CRESULT LeafVector<t_ElemType>::AddLeaf()
	{
		leafList.push_back(AlignedBuffer<t_ElemType>(leafSize,alignment));

		return CE_OK;
	}

	template<class t_ElemType>
	void LeafVector<t_ElemType>::PopLeaf()
	{
		Ceng::UINT32 k;

		for(k=0;k<backIndex;k++)
		{
			leafList[backLeaf][backIndex].~t_ElemType();
		}

		elementCount -= backIndex;

		backIndex = 0;

		if (backLeaf > 0) --backLeaf;

		Compact(2);
	}

	template<class t_ElemType>
	void LeafVector<t_ElemType>::Compact(const Ceng::UINT32 victimLeafs)
	{
		while(backLeaf + 2 < leafList.size())
		{
			leafList.pop_back();
		}
	}

	template<class t_ElemType>
	LeafVector<t_ElemType>::LeafVector() : leafSize(32),alignment(16),backLeaf(0),elementCount(0),
		backIndex(0)
	{
		AddLeaf();
	}

	template<class t_ElemType>
	LeafVector<t_ElemType>::~LeafVector()
	{
	}

	template<class t_ElemType>
	LeafVector<t_ElemType>::LeafVector(const Ceng::UINT32 leafSize,const Ceng::UINT32 alignment) 
		: leafSize(leafSize),alignment(alignment),elementCount(0),backIndex(0),backLeaf(0)
	{
		AddLeaf();
	}

	template<class t_ElemType>
	void LeafVector<t_ElemType>::CopyPODs(const LeafVector &source)
	{
		leafSize = source.leafSize;
		alignment = source.alignment;
		
		elementCount = source.elementCount;
		backIndex = source.backIndex;
		backLeaf = source.backLeaf;
	}

	template<class t_ElemType>
	LeafVector<t_ElemType>::LeafVector(const LeafVector &source)
	{
		CopyPods(source);

		leafList = source.leafList;
	}

	template<class t_ElemType>
	LeafVector<t_ElemType>::LeafVector(LeafVector &&source)
	{
		CopyPODs(source);

		leafList = std::move(source.leafList);
	}

	template<class t_ElemType>
	LeafVector<t_ElemType>& LeafVector<t_ElemType>::operator = (const LeafVector &source)
	{
		if (&source == this) return *this;

		Clear();

		CopyPODs(source);

		leafList = source.leafList;

		return *this;
	}

	template<class t_ElemType>
	LeafVector<t_ElemType>& LeafVector<t_ElemType>::operator = (LeafVector &&source)
	{
		if (&source == this) return *this;

		CopyPODs(source);

		leafList = std::move(source.leafList);

		return *this;
	}

	template<class t_ElemType>
	const Ceng::BOOL LeafVector<t_ElemType>::IsEmpty() const
	{
		return (elementCount == 0);
	}

	template<class t_ElemType>
	const Ceng::UINT32 LeafVector<t_ElemType>::Size() const
	{
		return elementCount;
	}

	template<class t_ElemType>
	const Ceng::UINT32 LeafVector<t_ElemType>::Capacity() const
	{
		return leafSize*leafList.size();
	}

	template<class t_ElemType>
	const CRESULT LeafVector<t_ElemType>::Reserve(const Ceng::UINT32 elements)
	{
		Ceng::UINT32 newLeafs = elements / leafSize;
		Ceng::UINT32 remainder = elements % leafSize;

		if (remainder) ++newLeafs;

		if (newLeafs >= leafList.size()) return CE_OK;

		newLeafs -= leafList.size();

		CRESULT cresult;
		Ceng::UINT32 k;

		for(k=0;k<newLeafs;k++)
		{
			cresult = AddLeaf();

			if (cresult != CE_OK) return cresult;
		}

		return CE_OK;
	}

	template<class t_ElemType>
	const CRESULT LeafVector<t_ElemType>::Resize(const Ceng::UINT32 elements)
	{
		Ceng::UINT32 newLeafs = elements / leafSize;
		Ceng::UINT32 remainder = elements % leafSize;

		Ceng::UINT32 paddedLeafs = newLeafs;

		if (remainder) ++paddedLeafs;

		Ceng::UINT32 k;

		if (paddedLeafs > leafList.size())
		{
			paddedLeafs -= leafList.size();

			for(k=0;k<paddedLeafs;k++)
			{
				AddLeaf();
			}

			while(elementCount < elements)
			{
				PushBack(t_ElemType());
			}
		}
		else
		{
			while(backLeaf > paddedLeafs)
			{
				PopLeaf();
			}

			while(backIndex > remainder)
			{
				PopBack();
			}
		}

		elementCount = elements;
		backLeaf = newLeafs;
		backIndex = remainder;

		return CE_OK;
	}

	template<class t_ElemType>
	void LeafVector<t_ElemType>::ShrinkToFit()
	{
		Compact(0);
	}

	template<class t_ElemType>
	void LeafVector<t_ElemType>::Clear()
	{
		Ceng::UINT32 k,j;

		for(k=0;k<backLeaf;k++)
		{
			for(j=0;j<leafSize;j++)
			{
				leafList[k][j].~t_ElemType();
			}
		}

		for(k=0;k<backIndex;k++)
		{
			leafList[backLeaf][k].~t_ElemType();
		}

		backLeaf = 0;
		backIndex = 0;
		elementCount = 0;

		Compact(2);
	}


	template<class t_ElemType>
	const CRESULT LeafVector<t_ElemType>::PushBack(const t_ElemType &source)
	{
		new (&leafList[backLeaf][backIndex]) t_ElemType(source);

		++elementCount;
		++backIndex;

		if (backIndex == leafSize)
		{
			leafList.push_back(AlignedBuffer<t_ElemType>(leafSize,alignment));

			++backLeaf;

			backIndex = 0;
		}

		return CE_OK;
	}

	template<class t_ElemType>
	void LeafVector<t_ElemType>::PopBack()
	{
		if (elementCount == 0) return;

		if (backIndex == 0)
		{
			if (backLeaf > 0)
			{
				--backLeaf;

				Compact(2);

				backIndex = leafSize;
			}
		}

		--backIndex;
		--elementCount;
	}

	template<class t_ElemType>
	t_ElemType& LeafVector<t_ElemType>::Back()
	{
		if (elementCount == 0) return leafList[0][0];

		if (backIndex == 0)
		{
			return leafList[backLeaf-1][leafSize-1];
		}

		return leafList[backLeaf][backIndex-1];
	}

	template<class t_ElemType>
	const t_ElemType& LeafVector<t_ElemType>::Back() const
	{
		if (elementCount == 0) return leafList[0][0];

		if (backIndex == 0)
		{
			return leafList[backLeaf-1][leafSize-1];
		}

		return leafList[backLeaf][backIndex-1];
	}

	template<class t_ElemType>
	t_ElemType& LeafVector<t_ElemType>::Front()
	{
		return leafList[0][0];
	}

	template<class t_ElemType>
	const t_ElemType& LeafVector<t_ElemType>::Front() const
	{
		return leafList[0][0];
	}

	template<class t_ElemType>
	t_ElemType& LeafVector<t_ElemType>::operator[] (const Ceng::UINT32 index)
	{
		if (elementCount == 0) return leafList[0][0];

		Ceng::UINT32 leaf = index / leafSize;
		Ceng::UINT32 localIndex = index % leafSize;

		return leafList[leaf][localIndex];
	}
}

#endif