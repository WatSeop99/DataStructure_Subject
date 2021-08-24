#pragma once

#include <iostream>

template <class Type>
struct NodeType {
	Type data;
	NodeType* next;
};

template <class Type>
class LinkedList {
private:
	NodeType<Type>* m_List;
	NodeType<Type>* m_CurPointer;
	int m_Length;
public:
	LinkedList();
	~LinkedList();

	bool IsFull();
	void MakeEmpty();
	void ResetList() { m_CurPointer = nullptr; }
	int GetLegnth() const { return m_Length; }
	void GetNextItem(Type& data);
	bool Get(Type& data);
	Type* GetPtr(Type& data);
	bool Add(Type& data);
	bool Delete(Type& data);
	bool Replace(Type& data);
	LinkedList<Type> operator=(const LinkedList<Type>& data)
};

template <class Type>
LinkedList<Type>::LinkedList() {
	m_Length = 0;
	m_List = nullptr;
	m_CurPointer = nullptr;
}

template <class Type>
LinkedList<Type>::~LinkedList() {
	NodeType<Type>* temp;
	while (m_List != nullptr) {
		temp = m_List;
		m_List = m_List->next;
		delete temp;
	}
}

template <class Type>
bool LinkedList<Type>::IsFull() {
	NodeType<Type>* location;
	try {
		location = new NodeType<Type>;
		delete location;
		return false;
	}
	catch (bad_alloc exception) { return true; }
}

template <class Type>
void LinkedList<Type>::MakeEmpty() {
	NodeType<Type>* temp;
	while (m_List != nullptr) {
		temp = m_List;
		m_List = m_List->next;
		delete temp;
	}
	m_Length = 0;
}

template <class Type>
void LinkedList<Type>::GetNextItem(Type& data) {
	if (m_CurPointer == nullptr) m_CurPointer = m_List;
	else {
		data = m_CurPointer->data;
		m_CurPointer = m_CurPointer->next;
	}
}

template <class Type>
bool LinkedList<Type>::Get(Type& data) {
	bool moreToSearch;
	NodeType<Type>* location;
	location = m_List;
	moreToSearch = (location != nullptr);
	while (moreToSearch) {
		if (data == location->data) {
			data = location->data;
			return true;
		}
		else {
			location = location->next;
			moreToSearch = (location != nullptr);
		}
	}
	return false;
}

template <class Type>
Type* LinkedList<Type>::GetPtr(Type& data) {
	bool moreToSearch;
	NodeType<Type>* location;
	location = m_List;
	moreToSearch = (location != nullptr);
	while (moreToSearch) {
		if (data == location->data) return &(location->data);
		else {
			location = location->next;
			moreToSearch = (location != nullptr);
		}
	}
	return nullptr;
}

template <class Type>
bool LinkedList<Type>::Add(Type& data) {
	if (Get(data)) return false;
	NodeType<Type> *newNode, *preLoc, *location;
	bool moreToSearch;
	location = m_List;
	preLoc = nullptr;
	moreToSearch = (location != nullptr);
	while (moreToSearch) {
		if (location->data < data) {
			preLoc = location;
			location = location->next;
			moreToSearch = (location != nullptr);
		}
		else moreToSearch = false;
	}
	newNode = new NodeType<Type>;
	newNode->data = data;
	if (preLoc == nullptr) {
		newNode->next = m_List;
		m_List = newNode;
	}
	else {
		newNode->next = location;
		preLoc->next = newNode;
	}
	++m_Length;
	return true;
}

template <class Type>
bool LinkedList<Type>::Delete(Type& data) {
	NodeType<Type>* location = m_List;
	NodeType<Type>* tempLocation = nullptr
	if (data == m_List->data) {
		tempLocation = location;
		m_List = m_List->next;
	}
	else {
		while (data != (location->next)->data)
			location = location->next;
		tempLocation = location->next;
		location->next = (location->next)->next;
	}
	if (tempLocation != nullptr) {
		delete tempLocation;
		--m_Length;
		return true;
	}
	else return false;
}

template <class Type>
bool LinkedList<Type>::Replace(Type& data) {
	bool moreToSearch;
	NodeType<Type>* location;
	location = m_List;
	moreToSearch = (location != nullptr);
	while (moreToSearch) {
		if (data == location->data) {
			location->data = data;
			return true;
		}
		else {
			location = location->next;
			moreToSearch = (location != nullptr);
		}
	}
	return false;
}

template <class Type>
LinkedList<Type> LinkedList<Type>::operator=(const LinkedList<Type>& data) {
	Type tempData;
	data.ResetList();
	data.GetNextItem(tempData);
	while (data.m_CurPointer != nullptr) {
		Add(tempData);
		data.GetNextItem(tempData);
	}
	return *this;
}