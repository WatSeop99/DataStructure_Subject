#pragma once

#include "LinkedList.h"
#include "Queue.h"
#include "Stack.h"

template <class Type>
class LinkedList;

template <class Type>
class Queue;

template <class Type>
class Stack;

template <class Type1, class Type2>
class Iterator {
private:
	const Type2& m_List;
	NodeType<Type1>* m_CurPointer;
	friend class LinkedList<Type1>;
	friend class Queue<Type1>;
	friend class Stack<Type1>;
public:
	Iterator(const Type2& list) : m_List(list), m_CurPointer(list.m_First) { }

	bool NotNull() { return m_CurPointer != nullptr; }
	bool NextNotNull() { return m_CurPointer->next != nullptr; }
	bool BackNotNull() { return m_CurPointer->prev != nullptr; }
	Type1 First();
	void Next() { if (NextNotNull()) m_CurPointer = m_CurPointer->next; }
	void Back() { if (BackNotNull()) m_CurPointer = m_CurPointer->prev; }
	NodeType<Type1> GetCurrentNode() { if (NotNull()) return *m_CurPointer; }
};

template <class Type1, class Type2>
Type1 Iterator<Type1, Type2>::First() {
	m_CurPointer = m_List.m_First;
	return m_CurPointer->data;
}