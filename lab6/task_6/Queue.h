#pragma once

#include "DoublyNodeType.h"
#include "Iterator.h"
#include "ErrorClass.h"

template <class Type1, class Type2>
class Iterator;

template <class Type>
class Queue {
public:
	Queue();
	~Queue();

	bool isEmpty() const { return length == 0; }
	bool isFull() const;
	void makeEmpty();
	bool get(Type& data);
	void get(Type& data, Type& comp);
	Type* getPtr(Type& data);
	void enqueue(Type& data);
	void dequeue(Type& data);
	void print(std::string type);
private:
	NodeType<Type>* first;
	NodeType<Type>* last;
	int length;
	friend class Iterator<Type, Queue<Type>>;
};

template <class Type>
Queue<Type>::Queue() {
	length = 0;
	first = new NodeType<Type>;
	last = new NodeType<Type>;
	first->prev = nullptr;
	first->next = last;
	last->prev = first;
	last->next = nullptr;
}

template <class Type>
Queue<Type>::~Queue() {
	if (length) makeEmpty();
	delete first;
	delete last;
	first = last = nullptr;
}

template <class Type>
bool Queue<Type>::isFull() const {
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
void Queue<Type>::makeEmpty() {
	NodeType<Type>* delNode;
	Iterator<Type, Queue<Type>> iter(*this);
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
bool Queue<Type>::get(Type& data) {
	if (isEmpty()) return false;
	Iterator<Type, Queue<Type>> iter(*this);
	iter.next();
	while (iter.curPointer != last) {
		if (*iter.curPointer->data == *data) {
			data = iter.curPointer->data;
			return true;
		}
		iter.next();
	}
	return false;
}

template <class Type>
void Queue<Type>::get(Type& data, Type& comp) {
	if (isEmpty()) {
		data = nullptr;
		return;
	}
	Iterator<Type, Queue<Type>> iter(*this);
	iter.next();
	while (iter.curPointer != last) {
		if (*iter.curPointer->data == *comp) {
			data = iter.curPointer->data;
			return;
		}
		iter.next();
	}
	data = nullptr;
}

template <class Type>
Type* Queue<Type>::getPtr(Type& data) {
	if (isEmpty()) throw EmptyQueue();
	Iterator<Type, Queue<Type>> iter(*this);
	iter.next();
	while (iter.curPointer != last) {
		if (*iter.curPointer->data == *data) return &(iter.curPointer->data);
		iter.next();
	}
	return nullptr;
}

template <class Type>
void Queue<Type>::enqueue(Type& data) {
	if (isFull()) {
		throw FullQueue();
		return;
	}
	NodeType<Type>* newNode = new NodeType<Type>;
	newNode->data = data;
	newNode->prev = last->prev;
	newNode->next = last;
	last->prev->next = newNode;
	last->prev = newNode;
	++length;
}

template <class Type>
void Queue<Type>::dequeue(Type& data) {
	if (isEmpty()) {
		throw EmptyQueue();
		return;
	}
	NodeType<Type>* delNode;
	delNode = first->next;
	data = delNode->data;
	first->next = delNode->next;
	delNode->next->prev = first;
	delete delNode;
	--length;
}

template <class Type>
void Queue<Type>::print(std::string type) {
	if (isEmpty()) throw EmptyQueue();
	Iterator<Type, Queue<Type>> iter(*this);
	iter.curPointer = last;
	iter.back();
	while (iter.curPointer != first) {
		if ((*iter.curPointer->data).getType().compare(type) == 0)
			std::cout << "\t      " << *(iter.curPointer->data) << std::endl;
		iter.next();
	}
}