#pragma once

#include "DoublyNodeType.h"
#include "Iterator.h"
#include "ErrorClass.h"

template <class Type1, class Type2>
class Iterator;

template <class Type>
class Stack {
public:
	Stack();
	~Stack();

	bool isEmpty() const { return length == 0; }
	bool isFull() const;
	void makeEmpty();
	bool get(Type& data);
	Type* getPtr(Type& data);
	void print();
	void push(Type& data);
	void pop();
	Type getTop();
private:
	NodeType<Type>* first;
	NodeType<Type>* last;
	NodeType<Type>* top;
	int length;
	friend class Iterator<Type, Stack<Type>>;
};

template <class Type>
Stack<Type>::Stack() {
	length = 0;
	first = new NodeType<Type>;
	last = new NodeType<Type>;
	first->prev = nullptr;
	first->next = last;
	last->prev = first;
	last->next = nullptr;
}

template <class Type>
Stack<Type>::~Stack() {
	if (length) makeEmpty();
	delete first;
	delete last;
	first = last = nullptr;
}

template <class Type>
bool Stack<Type>::isFull() const {
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
void Stack<Type>::makeEmpty() {
	NodeType<Type>* delNode;
	Iterator<Type, Stack<Type>> iter(*this);
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
bool Stack<Type>::get(Type& data) {
	if (isEmpty()) throw EmptyStack();
	Iterator<Type, Stack<Type>> iter(*this);
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
Type* Stack<Type>::getPtr(Type& data) {
	if(isEmpty()) throw EmptyStack();
	Iterator<Type, Stack<Type>> iter(*this);
	iter.next();
	while (iter.curPointer != last) {
		if (*iter.curPointer->data == *data) return &(iter.curPointer->data);
		iter.next();
	}
	return nullptr;
}

template <class Type>
void Stack<Type>::print() {
	if (isEmpty()) throw EmptyStack();
	Iterator<Type, Stack<Type>> iter(*this);
	iter.next();
	while (iter.curPointer != last) {
		std::cout << "\t        " << *(iter.curPointer->data) << std::endl;
		iter.next();
	}
}

template <class Type>
void Stack<Type>::push(Type& data) {
	if (isFull()) throw FullStack();
	NodeType<Type>* newNode = new NodeType<Type>;
	newNode->data = data;
	newNode->prev = last->prev;
	newNode->next = last;
	last->prev->next = newNode;
	last->prev = newNode;
	++length;
	top = last->prev;
}

template <class Type>
void Stack<Type>::pop() {
	if (isEmpty()) throw EmptyStack();
	NodeType<Type>* delNode = top;
	last->prev = delNode->prev;
	delNode->prev->next = last;
	top = last->prev;
	delete delNode;
	--length;
}

template <class Type>
Type Stack<Type>::getTop() {
	if (isEmpty()) throw EmptyStack();
	return top->data;
}