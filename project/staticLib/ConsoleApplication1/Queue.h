#pragma once

#include "ErrorClass.h"
#include "Iterator.h"
#include "Node.h"

template <typename T1, typename T2>
class Iterator;

template <typename T>
class Queue
{
	friend class Iterator<T, Queue<T>>;

public:
	Queue();
	~Queue();

	void DeQueue(T& data);
	void EnQueue(T& data);
	int Get(T& outData) const;
	int GetLength() const;
	int GetPtr(T* outData, T& comp) const;
	bool IsEmpty() const;
	bool IsFull() const;
	void MakeEmpty();

private:
	Node<T>* mFirst;
	Node<T>* mLast;
	int mLength;
};

template <typename T>
Queue<T>::Queue()
{
	mFirst = new Node<T>;
	mLast = new Node<T>;

	mFirst->Left = nullptr;
	mFirst->Right = mLast;

	mLast->Left = mFirst;
	mLast->Right = nullptr;

	mLength = 0;
}

template <typename T>
Queue<T>::~Queue()
{
	if (mLength != 0)
	{
		MakeEmpty();
	}

	delete mFirst;
	delete mLast;
	mFirst = nullptr;
	mLast = nullptr;
}

template <typename T>
void Queue<T>::DeQueue(T& data)
{
	if (IsEmpty())
	{
		throw EmptyQueue();
		return;
	}
	
	Node<T>* dequeNode;
	dequeNode = mFirst->Right;
	data = dequeNode->Data;

	mFirst->Right = dequeNode->Right;
	dequeNode->Right->Left = mFirst;
	delete dequeNode;
	mLength--;
}

template <typename T>
void Queue<T>::EnQueue(T& data)
{
	if (IsFull())
	{
		throw FullQueue();
		return;
	}
	
	Iterator<T, Queue<T>> iter(*this);
	iter.Next();

	while (iter.mCurPointer != mLast)
	{
		if (data == iter.mCurPointer->Data)
		{
			Node<T>* overlap;
			overlap = iter.mCurPointer;

			iter.Next();
			overlap->Left->Right = iter.mCurPointer;
			iter.mCurPointer->Left = overlap->Left;

			overlap->Left = mLast->Left;
			overlap->Right = mLast;
			mLast->Left->Right = overlap;
			mLast->Left = overlap;

			return;
		}

		iter.Next();
	}


	Node<T>* newNode = new Node<T>;
	newNode->Data = data;
	newNode->Left = mLast->Left;
	newNode->Right = mLast;

	mLast->Left->Right = newNode;
	mLast->Left = newNode;
	mLength++;
}

template <typename T>
int Queue<T>::Get(T& outData) const
{
	if (IsEmpty())
	{
		throw EmptyQueue();
		return 0;
	}

	Iterator<T, Queue<T>> iter(*this);
	iter.Next();

	while (iter.mCurPointer != mLast)
	{
		if (iter.mCurPointer->Data == outData)
		{
			outData = iter.mCurPointer->Data;
			return 1;
		}

		iter.Next();
	}

	return 0;
}

template <typename T>
int Queue<T>::GetLength() const
{
	return mLength;
}

template <typename T>
int Queue<T>::GetPtr(T* outData, T& comp) const
{
	if (IsEmpty())
	{
		throw EmptyQueue();
		return 0;
	}

	Iterator<T, Queue<T>> iter(*this);
	iter.Next();

	while (iter.mCurPointer != mLast)
	{
		if (iter.mCurPointer->Data == comp)
		{
			outData = &(iter.mCurPointer->Data);
			return 1;
		}

		iter.Next();
	}

	outData = nullptr;
	return 0;
}

template <typename T>
bool Queue<T>::IsEmpty() const
{
	return mLength == 0;
}

template <typename T>
bool Queue<T>::IsFull() const
{
	Node<T>* emptyNode;

	try
	{
		emptyNode = new Node<T>;
		delete emptyNode;
		return false;
	}
	catch (std::bad_alloc exception)
	{
		return true;
	}
}

template <typename T>
void Queue<T>::MakeEmpty()
{
	Node<T>* trashNode;
	Iterator<T, Queue<T>> iter(*this);
	iter.Next();

	while (iter.mCurPointer != mLast)
	{
		trashNode = iter.mCurPointer;
		iter.Next();
		delete trashNode;
	}

	mFirst->Right = mLast;
	mLast->Left = mFirst;
	mLength = 0;
}