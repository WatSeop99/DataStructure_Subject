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
public:
	Iterator(const Type2& listData) : list(listData), curPointer(listData.first) { }

	bool notNull() { return curPointer != nullptr; }
	bool nextNotNull() { return curPointer->next != nullptr; }
	bool backNotNull() { return curPointer->prev != nullptr; }
	Type1 first();
	void next() { if (nextNotNull()) curPointer = curPointer->next; }
	void back() { if (backNotNull()) curPointer = curPointer->prev; }
	NodeType<Type1> getCurrentNode() { if (notNull()) return *curPointer; }
protected:
	const Type2& list;
	NodeType<Type1>* curPointer;
	friend class LinkedList<Type1>;
	friend class Queue<Type1>;
	friend class Stack<Type1>;
};

template <class Type1, class Type2>
Type1 Iterator<Type1, Type2>::first() {
	curPointer = list.first;
	return curPointer->data;
}