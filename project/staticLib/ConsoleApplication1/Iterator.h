#pragma once

#include "Node.h"
#include "Queue.h"
#include "Stack.h"

template <typename T>
class Queue;

template <typename T>
class Stack;

template <typename T1, typename T2>
class Iterator
{
	friend class Queue<T1>;
	friend class Stack<T1>;

public:
	Iterator(const T2& list)
		: mList(list),
		mCurPointer(list.mFirst)
	{}

	void Back();
	bool BackNotNull() const;
	T1 First();
	Node<T1> GetCurrentNode() const;
	void Next();
	bool NextNotNull() const;
	bool NotNull() const;

protected:
	const T2& mList;
	Node<T1>* mCurPointer;
};

template <typename T1, typename T2>
void Iterator<T1, T2>::Back()
{
	if (BackNotNull())
	{
		mCurPointer = mCurPointer->Left;
	}
}

template <typename T1, typename T2>
bool Iterator<T1, T2>::BackNotNull() const
{
	return (mCurPointer->Left != nullptr);
}

template <typename T1, typename T2>
T1 Iterator<T1, T2>::First()
{
	mCurPointer = mList.mFirst;
	return mCurPointer->Data;
}

template <typename T1, typename T2>
Node<T1> Iterator<T1, T2>::GetCurrentNode() const
{
	if (NotNull())
	{
		return *mCurPointer;
	}

	return nullptr;
}

template <typename T1, typename T2>
void Iterator<T1, T2>::Next()
{
	if (NextNotNull())
	{
		mCurPointer = mCurPointer->Right;
	}
}

template <typename T1, typename T2>
bool Iterator<T1, T2>::NextNotNull() const
{
	return (mCurPointer->Right != nullptr);
}

template <typename T1, typename T2>
bool Iterator<T1, T2>::NotNull() const
{
	return (mCurPointer != nullptr);
}