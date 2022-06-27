#pragma once

#include "ErrorClass.h"
#include "Iterator.h"
#include "Node.h"

template <typename T1, typename T2>
class Iterator;

template <typename T>
class Stack
{
	friend class Iterator<T, Stack<T>>;

public:
	Stack();
	~Stack();

	int Get(T& outData) const;
	int GetLength() const;
	int GetPtr(T* outData, T& comp) const;
	bool IsEmpty() const;
	bool IsFull() const;
	void MakeEmpty();
	T Pop();
	void Push(T& data);
	T Top() const;

private:
	Node<T>* mFirst;
	Node<T>* mLast;
	Node<T>* mTop;
	int mLength;
};

template <typename T>
Stack<T>::Stack()
{
	mFirst = new Node<T>;
	mLast = new Node<T>;

	mFirst->Left = nullptr;
	mFirst->Right = mLast;

	mLast->Left = mFirst;
	mLast->Right = nullptr;

	mLength = 0;
	mTop = mLast->Left;
}

template <typename T>
Stack<T>::~Stack()
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
int Stack<T>::Get(T& outData) const
{
	if (IsEmpty())
	{
		throw EmptyStack();
		return 0;
	}

	Iterator<T, Stack<T>> iter(*this);
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
int Stack<T>::GetLength() const
{
	return mLength;
}

template <typename T>
int Stack<T>::GetPtr(T* outData, T& comp) const
{
	if (IsEmpty())
	{
		throw EmptyStack();
		return 0;
	}

	Iterator<T, Stack<T>> iter(*this);
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

	return 0;
}

template <typename T>
bool Stack<T>::IsEmpty() const
{
	return mLength == 0;
}

template <typename T>
bool Stack<T>::IsFull() const
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
void Stack<T>::MakeEmpty()
{
	Node<T>* trashNode;
	Iterator<T, Stack<T>> iter(*this);
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


template <typename T>
T Stack<T>::Pop()
{
	if (IsEmpty())
	{
		throw EmptyStack();
		return NULL;
	}

	T popData;
	Node<T>* popNode;

	popNode = mTop;
	popData = popNode->Data;

	mLast->Left = popNode->Left;
	popNode->Left->Right = mLast;
	mTop = mLast->Left;
	delete popNode;
	mLength--;

	return popData;
}

template <typename T>
void Stack<T>::Push(T& data)
{
	if (IsFull())
	{
		throw FullStack();
		return;
	}

	Node<T>* newNode = new Node<T>;
	newNode->Data = data;
	newNode->Left = mLast->Left;
	newNode->Right = mLast;

	mLast->Left->Right = newNode;
	mLast->Left = newNode;
	mLength++;
	mTop = mLast->Left;
}

template <typename T>
T Stack<T>::Top() const
{
	if (IsEmpty())
	{
		throw EmptyStack();
		return NULL;
	}

	return mTop->Data;
}