#pragma once

#include "DoublyNodeType.h"
#include "Iterator.h"
#include "ErrorClass.h"

template <class Type1, class Type2>
class Iterator;

template <class Type>
class Queue {
private:
	NodeType<Type>* m_First;
	NodeType<Type>* m_Last;
	int m_Length;
	friend class Iterator<Type, Queue<Type>>;
public:
	Queue();
	~Queue();

	bool IsEmpty() const { return m_Length == 0; }
	bool IsFull() const;
	void MakeEmpty();
	bool Get(Type& data);
	void Get(Type& data, Type& comp);
	Type* GetPtr(Type& data);
	void EnQueue(Type& data);
	void DeQueue(Type& data);
	void Print();
};

template <class Type>
Queue<Type>::Queue() {
	m_First = new NodeType<Type>;
	m_Last = new NodeType<Type>;
	m_First->prev = nullptr;
	m_First->next = m_Last;
	m_Last->prev = m_First;
	m_Last->next = nullptr;
	m_Length = 0;
}

template <class Type>
Queue<Type>::~Queue() {
	if (m_Length != 0) MakeEmpty();
	delete m_First;
	delete m_Last;
	m_First = m_Last = nullptr;
}

template <class Type>
bool Queue<Type>::IsFull() const {
	NodeType<Type>* location;
	try {
		location = new NodeType<Type>;
		delete location;
		return false;
	}
	catch (std::bad_alloc exception) { return true; }
}

template <class Type>
void Queue<Type>::MakeEmpty() {
	NodeType<Type>* temp;
	Iterator<Type, Queue<Type>> iter(*this);
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
bool Queue<Type>::Get(Type& data) {
	Iterator<Type, Queue<Type>> iter(*this);
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
void Queue<Type>::Get(Type& data, Type& comp) {
	Iterator<Type, Queue<Type>> iter(*this);
	iter.Next();
	while (iter.m_CurPointer != m_Last) {
		if (*iter.m_CurPointer->data == *comp) {
			data = iter.m_CurPointer->data;
			return;
		}
		iter.Next();
	}
	data = nullptr;
}

template <class Type>
Type* Queue<Type>::GetPtr(Type& data) {
	Iterator<Type, Queue<Type>> iter(*this);
	iter.Next();
	while (iter.m_CurPointer != m_Last) {
		if (*iter.m_CurPointer->data == data) return &(iter.m_CurPointer->data);
		iter.Next();
	}
	return nullptr;
}

template <class Type>
void Queue<Type>::EnQueue(Type& data) {
	if (IsFull()) throw FullQueue();
	NodeType<Type>* newNode = new NodeType<Type>;
	newNode->data = data;
	newNode->prev = m_Last->prev;
	newNode->next = m_Last;
	m_Last->prev->next = newNode;
	m_Last->prev = newNode;
	++m_Length;
}

template <class Type>
void Queue<Type>::DeQueue(Type& data) {
	if (IsEmpty()) throw EmptyQueue();
	NodeType<Type>* delNode;
	delNode = m_First->next;
	data = delNode->data;
	m_First->next = delNode->next;
	delNode->next->prev = m_First;
	delete delNode;
	--m_Length;
}

template <class Type>
void Queue<Type>::Print() {
	if (IsEmpty()) throw EmptyQueue();
	Iterator<Type, Queue<Type>> iter(*this);
	iter.m_CurPointer = m_Last;
	iter.Back();
	while (iter.m_CurPointer != m_First) {
		std::cout << "\t        " << *(iter.m_CurPointer->data) << std::endl;
		iter.Back();
	}
}