#pragma once

#include <iostream>
#include <string>
#include "DoublyNodeType.h"
#include "Iterator.h"

template <class Type>
class LinkedList {
private:
	NodeType<Type>* m_First;
	NodeType<Type>* m_Last;
	int m_Length;
	friend class Iterator<Type, LinkedList<Type>>;
public:
	LinkedList();
	~LinkedList();

	void MakeEmpty();
	bool IsFull();
	bool IsEmpty() const { return m_Legnth == 0; }
	int GetLength() const { return m_Legnth; }
	LinkedList<Type>& operator=(const LinkedList<Type>& list);
	bool Add(Type& data);
	bool Delete(Type& data);
	bool Replace(Type& data);
	bool Get(Type& data);
	Type* GetPtr(Type& data);
	void RetrieveAndPrint(std::string key);
	void Print() const;
};

template <class Type>
LinkedList<Type>::LinkedList() {
	m_Length = 0;
	m_First = new NodeType<Type>;
	m_Last = new NodeType<Type>;
	m_First->prev = nullptr;
	m_First->next = m_Last;
	m_Last->prev = m_First;
	m_Last->next = nullptr;
}

template <class Type>
LinkedList<Type>::~LinkedList() {
	if (m_Length != 0) MakeEmpty();
	delete m_First;
	delete m_Last;
}

template <class Type>
void LinkedList<Type>::MakeEmpty() {
	NodeType<Type>* temp;
	Iterator<Type, LinkedList<Type>> iter(*this);
	iter.Next();
	while (iter.m_CurPoineter != m_Last) {
		temp = iter.m_CurPointer;
		iter.Next();
		delete temp;
	}
	m_First->next = m_Last;
	m_Last->prev = m_First;
	m_Length = 0;
}

template <class Type>
bool LinkedList<Type>::IsFull() {
	NodeType<Type>* temp;
	try {
		temp = new NodeType<Type>;
		delete temp;
		return false;
	}
	catch (std::bad_alloc& exception) {
		std::cerr << "\t  ## List°¡ °¡µæÂü : " << exception.what() << " ##" << std::endl;
		return true;
	}
}

template <class Type>
LinkedList<Type>& LinkedList<Type>::operator=(const LinkedList<Type>& list) {
	if (m_Length != 0) MakeEmpty();
	Type data;
	Iterator<Type, LinkedList<Type>> iter(list);
	iter.Next();
	while (iter.m_CurPointer != list.m_Last) {
		data = iter.m_CurPointer->data;
		Add(data);
		iter.Next();
	}
	m_Length = list.m_Length;
	m_First = m_Last = nullptr;
	return *this;
}

template <class Type>
bool LinkedList<Type>::Add(Type& data) {
	if (Get(data) || IsFull()) return false;
	Iterator<Type, LinkedList<Type>> iter(*this);
	iter.Next();
	while (true) {
		if (data > iter.m_CurPointer || iter.m_CurPointer == m_Last) {
			NodeType<Type>* newNode = new NodeType<Type>;
			newNode->data = data;
			newNode->prev = iter.m_CurPointer->prev;
			newNode->next = iter.m_CurPointer;
			iter.m_CurPointer->prev->next = newNode;
			iter.m_CurPointer->prev = newNode;
			++m_Length;
			return true;
		}
		iter.Next();
	}
	return false;
}

template <class Type>
bool LinkedList<Type>::Delete(Type& data) {
	if (IsEmpty()) return false;
	Iterator<Type, LinkedList<Type>> iter(*this);
	iter.Next();
	while (iter.m_CurPointer != m_Last) {
		if (iter.m_CurPointer->data == data) {
			NodeType<Type> delNode = iter.m_CurPointer;
			iter.Next();
			delNode->prev->next = iter.m_CurPointer;
			iter.m_CurPointer->prev = delNode->prev;
			delete delNode;
			--m_Length;
			return true;
		}
		iter.Next();
	}
	return false;
}

bool Replace(Type& data);
bool Get(Type& data);
Type* GetPtr(Type& data);
void RetrieveAndPrint(std::string key);
void Print() const;