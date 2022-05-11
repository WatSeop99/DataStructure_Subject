#pragma once

#include "FolderType.h"

template <typename T>
class CHeapBase
{
public:
	CHeapBase();
	virtual ~CHeapBase();

	bool IsEmpty() const;
	bool IsFull() const;
	int GetLength() const;
	void MakeEmpty();
	void Swap(int iparent, int ibottom);
	virtual int Add(T& item);
	virtual int Delete(T& item);
	virtual T Dequeue();
	virtual void RetrieveItem(T& item, bool& found);
	virtual void PrintHeap() const;

	virtual void ReheapDown(int iparent, int ibottom) = 0;
	virtual void ReheapUp(int irrot, int ibottom) = 0;
	virtual void Delete(T& item, bool& found, int iparent) = 0;
	virtual void Retrieve(T& item, bool& found, int iparent) const = 0;

protected:
	T* mHeap;
	int mLastNode;
	int mMaxSize;
};


template <typename T>
CHeapBase<T>::CHeapBase()
{
	mLastNode = 0;
}

template <typename T>
CHeapBase<T>::~CHeapBase()
{
	MakeEmpty();
}

template <typename T>
bool CHeapBase<T>::IsEmpty() const
{
	if (mLastNode == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <typename T>
bool CHeapBase<T>::IsFull() const
{
	if (mLastNode == mMaxSize)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <typename T>
int CHeapBase<T>::GetLength() const
{
	return mLastNode;
}

template <typename T>
void CHeapBase<T>::MakeEmpty()
{
	delete[] mHeap;
}

template <typename T>
void CHeapBase<T>::Swap(int iparent, int ibottom)
{
	T temp = mHeap[iparent];
	mHeap[iparent] = mHeap[ibottom];
	mHeap[ibottom] = temp;
}

template <typename T>
int CHeapBase<T>::Add(T& item)
{
	mHeap[mLastNode] = item;
	ReheapUp(0, mLastNode);
	mLastNode++;

	return 1;
}

template <typename T>
int CHeapBase<T>::Delete(T& item)
{
	bool found = false;

	Delete(item, found, 0);
	if (found)
	{
		mLastNode--;
	}
	else
		return 0;

	return 1;
}

template <typename T>
T CHeapBase<T>::Dequeue()
{
	T item = mHeap[0];

	Delete(item);

	return item;
}

template <typename T>
void CHeapBase<T>::RetrieveItem(T& item, bool& found)
{
	Retrieve(item, found, 0);
}

template <typename T>
void CHeapBase<T>::PrintHeap() const
{
	T item;

	for (int i = 0; i < mLastNode; i++)
	{
		item << mHeap[i];
	}
}