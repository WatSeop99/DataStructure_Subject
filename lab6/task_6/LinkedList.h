#pragma once

#include "DoublyNodeType.h"
#include "Iterator.h"
#include "CompareType.h"
#include "ErrorClass.h"

template <class Type1, class Type2>
class Iterator;

template <class Type>
class LinkedList {
public:
	LinkedList();
	~LinkedList();

	void makeEmpty();
	bool isFull() const;
	bool isEmpty() const { return length == 0; }
	int getLength() const { return length; }
	LinkedList<Type>& operator=(const LinkedList<Type>& list);
	bool add(Type& data);
	bool remove(Type& data);
	bool replace(Type& data);
	bool get(Type& data) const;
	Type* getPtr(Type& data) const;
	void retrieveAndPrint(std::string key) const;
	void print() const;
protected:
	NodeType<Type>* first;
	NodeType<Type>* last;
	CompareType<Type> comparer;
	int length;
	friend class Iterator<Type, LinkedList<Type>>;
};

template <class Type>
LinkedList<Type>::LinkedList() {
	length = 0;
	first = new NodeType<Type>;
	last = new NodeType<Type>;
	first->prev = nullptr;
	first->next = last;
	last->prev = first;
	last->next = nullptr;
}

template <class Type>
LinkedList<Type>::~LinkedList() {
	if (length) makeEmpty();
	delete first;
	delete last;
	first = last = nullptr;
}

template <class Type>
void LinkedList<Type>::makeEmpty() {
	NodeType<Type>* delNode;
	Iterator<Type, LinkedList<Type>> iter(*this);
	iter.next();
	while (iter.curPointer != last) {
		delNode = iter.curPointer;
		iter.next();
		delete delNode;
	}
	first->next = last;
	last->prev = first;
	length = 0;
}

template <class Type>
bool LinkedList<Type>::isFull() const {
	NodeType<Type>* temp;
	try {
		temp = new NodeType<Type>;
		delete temp;
		return false;
	}
	catch (std::bad_alloc& exception) {
		std::cerr << "\t  ## List is full : " << exception.what() << " ##" << std::endl;
		return true;
	}
}

template <class Type>
LinkedList<Type>& LinkedList<Type>::operator=(const LinkedList<Type>& list) {
	if (length) makeEmpty();
	Type data;
	Iterator<Type, LinkedList<Type>> iter(list);
	iter.next();
	while (iter.curPointer != last) {
		data = iter.curPointer->data;
		add(data);
		iter.next();
	}
	length = list.length;
	return *this;
}

template <class Type>
bool LinkedList<Type>::add(Type& data) {
	if (get(data) || isFull()) return false;
	Iterator<Type, LinkedList<Type>> iter(*this);
	iter.next();
	while (true) {
		if (iter.curPointer == last || comparer.compare(data, iter.curPointer->data) < 0) {
			NodeType<Type>* newNode = new NodeType<Type>;
			newNode->data = data;
			newNode->prev = iter.curPointer->prev;
			newNode->next = iter.curPointer;
			iter.curPointer->prev->next = newNode;
			iter.curPointer->prev = newNode;
			++length;
			return true;
		}
		iter.next();
	}
	return false;
}

template <class Type>
bool LinkedList<Type>::remove(Type& data) {
	if (isEmpty()) return false;
	Iterator<Type, LinkedList<Type>> iter(*this);
	iter.next();
	while (iter.curPointer != last) {
		if (comparer.compare(data, iter.curPointer->data) == 0) {
			NodeType<Type>* delNode = new NodeType<Type>;
			delNode = iter.curPointer;
			iter.next();
			delNode->prev->next = iter.curPointer;
			iter.curPointer->prev = delNode->prev;
			delete delNode;
			--length;
			return true;
		}
		iter.next();
	}
	return false;
}

template <class Type>
bool LinkedList<Type>::replace(Type& data) {
	if (isEmpty()) return false;
	Iterator<Type, LinkedList<Type>> iter(*this);
	iter.next();
	while (iter.curPointer != last) {
		if (comparer.compare(data, iter.curPointer->data) == 0) {
			iter.curPointer->data = data;
			return true;
		}
		iter.next();
	}
	return false;
}

template <class Type>
bool LinkedList<Type>::get(Type& data) const {
	if (isEmpty()) return false;
	Iterator<Type, LinkedList<Type>> iter(*this);
	iter.next();
	while (iter.curPointer != last) {
		if (comparer.compare(iter.curPointer->data, data) == 0) {
			data = iter.curPointer->data;
			return true;
		}
		iter.next();
	}
	return false;
}

template <class Type>
Type* LinkedList<Type>::getPtr(Type& data) const {
	if (isEmpty()) return nullptr;
	Iterator<Type, LinkedList<Type>> iter(*this);
	iter.next();
	while (iter.curPointer != last) {
		if (comparer.compare(data, iter.curPointer->data) == 0)
			return &(iter.curPointer->data);
		iter.next();
	}
	return nullptr;
}

template <class Type>
void LinkedList<Type>::retrieveAndPrint(std::string key) const {
	if (isEmpty()) throw EmptyList();
	bool found = false;
	Iterator<Type, LinkedList<Type>> iter(*this);
	iter.next();
	while (*(iter.curPointer->data).getName().find(key) != std::string::npos) {
		std::cout << "\t      " << iter.curPointer->data << std::endl;
		found = true;
		iter.next();
	}
	if (!found) std::cout << "\t ## NOT FOUND ##" << std::endl;
}

template <class Type>
void LinkedList<Type>::print() const {
	if (isEmpty()) throw EmptyList();
	Iterator<Type, LinkedList<Type>> iter(*this);
	iter.next();
	while (iter.curPointer != last) {
		std::cout << "\t      " << *(iter.curPointer->data) << std::endl;
		iter.next();
	}
}