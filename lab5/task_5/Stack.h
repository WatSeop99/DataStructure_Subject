#pragma once

#include "DoublyNodeType.h"
#include "Iterator.h"
#include "ErrorClass.h"

template <class Type1, class Type2>
class Iterator;

template <class Type>
class Stack {
private:
	NodeType<Type>* m_First;
	NodeType<Type>* m_Last;
	NodeType<Type>* m_Top;
	int m_Length;
	friend class Iterator<Type, Stack<Type>>;
public:
	Stack();
	~Stack();

	bool IsEmpty() const { return m_Length == 0; }
	bool IsFull() const;
	void MakeEmpty();
	bool Get(Type& data);
	Type* GetPtr(Type& data);
	void Print();
	void Push(Type& data);
	void Pop();
	Type Top();
};

template <class Type>
Stack<Type>::Stack() {
	m_First = new NodeType<Type>;
	m_Last = new NodeType<Type>;
	m_First->prev = nullptr;
	m_First->next = m_Last;
	m_Last->prev = m_First;
	m_Last->next = nullptr;
	m_Length = 0;
	m_Top = m_Last->prev;
}

template <class Type>
Stack<Type>::~Stack() {
	if (m_Length != 0) MakeEmpty();
	delete m_First;
	delete m_Last;
	m_First = m_Last = nullptr;
}

template <class Type>
bool Stack<Type>::IsFull() const {
	NodeType<Type>* location;
	try {
		location = new NodeType<Type>;
		delete location;
		return false;
	}
	catch (std::bad_alloc exception) { return true; }
}

template <class Type>
void Stack<Type>::MakeEmpty() {
	NodeType<Type>* temp;
	Iterator<Type, Stack<Type>> iter(*this);
	iter.Next();
	while (iter.m_CurPointer != m_Last) {
		temp = iter.m_CurPointer;
		iter.Next();
		delete temp;
	}
	m_First->next = m_Last;
	m_Last->prev = m_First;
	m_Length = 0;
}

template <class Type>
bool Stack<Type>::Get(Type& data) {
	if (IsEmpty()) throw EmptyStack();
	Iterator<Type, Stack<Type>> iter(*this);
	iter.Next();
	while (iter.m_CurPointer != m_Last) {
		if (*iter.m_CurPointer->data == *data) {
			data = iter.m_CurPointer->data;
			return true;
		}
		iter.Next();
	}
	return false;
}

template <class Type>
Type* Stack<Type>::GetPtr(Type& data) {
	if (IsEmpty()) throw EmptyStack();
	Iterator<Type, Stack<Type>> iter(*this);
	iter.Next();
	while (iter.m_CurPointer != m_Last) {
		if (*iter.m_CurPointer->data == *data) return &(iter.m_CurPointer->data);
		iter.Next();
	}
	return nullptr;
}

template <class Type>
void Stack<Type>::Print() {
	if (IsEmpty()) throw EmptyStack();
	Iterator<Type, Stack<Type>> iter(*this);
	iter.Next();
	while (iter.m_CurPointer != m_Last) {
		std::cout << "\t        " << *(iter.m_CurPointer->data) << std::endl;
		iter.Next();
	}
}

template <class Type>
void Stack<Type>::Push(Type& data) {
	if (IsFull()) throw FullStack();
	NodeType<Type>* newNode = new NodeType<Type>;
	newNode->data = data;
	newNode->prev = m_Last->prev;
	newNode->next = m_Last;
	m_Last->prev->next = newNode;
	m_Last->prev = newNode;
	++m_Length;
	m_Top = m_Last->prev;
}

template <class Type>
void Stack<Type>::Pop() {
	if (IsEmpty()) throw EmptyStack();
	NodeType<Type>* delNode = m_Top;
	m_Last->prev = delNode->prev;
	delNode->prev->next = m_Last;
	m_Top = m_Last->prev;
	delete delNode;
	--m_Length;
}

template <class Type>
Type Stack<Type>::Top() {
	if (IsEmpty()) throw EmptyStack();
	else return m_Top->data;
}