#pragma once

#include "LinkedList.h"

template <class Type>
class LinkedList2 : public LinkedList<Type> {
public:
	using LinkedList<Type>::first;
	using LinkedList<Type>::last;
	using LinkedList<Type>::length;
	using LinkedList<Type>::makeEmpty();

	LinkedList2();
	~LinkedList2();

	void retrAndPrint(std::string type, std::string keyword);
	void print(std::string type);
};

template <class Type>
LinkedList2<Type>::LinkedList2() {
	length = 0;
	first = new NodeType<Type>;
	last = new NodeType<Type>;
	first->prev = nullptr;
	first->next = last;
	last->prev = first;
	last->next = nullptr;
}

template <class Type>
LinkedList2<Type>::~LinkedList2() {
	if (length) makeEmpty();
	delete first;
	delete last;
	first = last = nullptr;
}

template <class Type>
void LinkedList2<Type>::retrAndPrint(std::string type, std::string keyword) {
	if (LinkedList<Type>::isEmpty()) throw EmptyList();
	int count = 0;
	Iterator<Type, LinkedList2<Type>> iter(*this);
	iter.next();
	while (iter.curPointer != last) {
		if ((*iter.getCurrentNode().data).getType().compare(type) == 0) {// try optimize plz
			if ((*iter.getCurrentNode().data).getName().find(keyword) != std::string::npos) {
				std::cout << "\t      " << iter.getCurrentNode().data << std::endl;
				++count;
			}
		}
		iter.next();
	}
	if (!count) std::cout << "t ## NOT FOUND ##" << std::endl;
}

template <class Type>
void LinkedList2<Type>::print(std::string type) {
	if (LinkedList<Type>::isEmpty()) throw EmptyList();
	Iterator<Type, LinkedList2<Type>> iter(*this);
	iter.next();
	while (iter.curPointer != last) {
		if ((**iter.getCurrentNode().data).getType().compare(type) == 0) // try optimize plz
			std::cout << "\t      " << iter.getCurrentNode().data << std::endl;
		iter.next();
	}
}