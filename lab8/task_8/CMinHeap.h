#pragma once

#include "CHeapBase.h"

template <typename T>
class CMinHeap : public CHeapBase<T>
{
public:
	using CHeapBase<T>::mHeap;
	using CHeapBase<T>::mLastNode;
	using CHeapBase<T>::mMaxSize;
	using CHeapBase<T>::Swap;

	CMinHeap(int size);

	virtual void ReheapDown(int iparent, int ibottom);
	virtual void ReheapUp(int iroot, int ibottom);
	virtual void Delete(T& item, bool& found, int iparent);
	virtual void Retrieve(T& item, bool& found, int iparent) const;
};

template <typename T>
CMinHeap<T>::CMinHeap(int size)
{
	mMaxSize = size;
	mHeap = new T[mMaxSize];
}

template <typename T>
void CMinHeap<T>::ReheapDown(int iparent, int ibottom)
{
	int maxChild;
	int leftChild;
	int rightChild;

	leftChild = iparent * 2 + 1;
	rightChild = iparent * 2 + 2;

	if (leftChild <= ibottom)
	{
		if (leftChild == ibottom)
		{
			maxChild = leftChild;
		}
		else
		{
			if (mHeap[leftChild] > mHeap[rightChild])
			{
				maxChild = rightChild;
			}
			else
			{
				maxChild = leftChild;
			}

			if (mHeap[iparent] > mHeap[maxChild])
			{
				Swap(iparent, maxChild);
				ReheapDown(maxChild, ibottom);
			}
		}
	}
}

template <typename T>
void CMinHeap<T>::ReheapUp(int iroot, int ibottom)
{
	int iparent;

	if (ibottom > iroot)
	{
		iparent = (ibottom - 1) / 2;
		if (mHeap[iparent] > mHeap[ibottom])
		{
			Swap(iparent, ibottom);
			ReheapUp(iroot, iparent);
		}
	}
}

template <typename T>
void CMinHeap<T>::Delete(T& item, bool& found, int iparent)
{
	int leftChild;
	int rightChild;

	leftChild = iparent * 2 + 1;
	rightChild = iparent * 2 + 2;

	if (mHeap[iparent] == item)
	{
		mHeap[iparent] = mHeap[mLastNode - 1];
		ReheapDown(iparent, mLastNode - 2);
		found = true;
	}

	if (leftChild < mLastNode && found == false)
	{
		Delete(item, found, leftChild);
	}
	if (rightChild < mLastNode && found == false)
	{
		Delete(item, found, rightChild);
	}
}

template <typename T>
void CMinHeap<T>::Retrieve(T& item, bool& found, int iparent) const
{
	int leftChild;
	int rightChild;

	leftChild = iparent * 2 + 1;
	rightChild = iparent * 2 + 2;

	if (mHeap[iparent] == item)
	{
		item = mHeap[iparent];
		found = true;
	}

	if (leftChild < mLastNode && found == false)
	{
		Retrieve(item, found, leftChild);
	}
	if (rightChild < mLastNode && found == false)
	{
		Retrieve(item, found, rightChild);
	}
}