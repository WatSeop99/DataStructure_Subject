#pragma once

#include <iostream>
#define MAXSIZE 10

class FullQueue {
public:
	void Print() { std::cout << "\t Queue is Full!" << std::endl; }
};

class EmptyQueue {
public:
	void Print() { std::cout << "\t Queue is Empty" << std::endl; }
};

template <class Type>
class Queue {
private:
	Type* m_Array;
	int m_Front;
	int m_Rear;
public:
	Queue() : m_Front(0), m_Rear(MAXSIZE-1) {
		m_Array = nullptr;
	}
	~Queue() { if (m_Array) delete[] m_Array; }

	bool IsFull();
	bool IsEmpty();
	void MakeEmpty();
	void EnQueue(Type& data);
	void DeQueue(Type& data);
	void Print();
	Type Front() const { return IsEmpty() ? m_Array[0] : NULL; }
};

template <class Type>
bool Queue<Type>::IsFull() {
	
}