#pragma once

#include <iostream>

#define MAXSIZE 10

template <class Type>
class Queue {
private:
	Type* m_Array;
	int m_Front;
	int m_Rear;
	int maxQue;
public:
	Queue(int maxSize = MAXSIZE) : m_Front(maxSize), m_Rear(maxSize) {
		maxQue = maxSize+1;
		m_Array = new Type[maxQue];
	}
	~Queue() { delete[] m_Array; }

	bool IsFull() const { return (m_Rear+1)%maxQue == m_Front; }
	bool IsEmpty() const { return m_Front == m_Rear; }
	void MakeEmpty();
	bool EnQueue(Type& data);
	bool DeQueue(Type& data);
	void Print() const;
};

template <class Type>
void Queue<Type>::MakeEmpty() {
	m_Front = MAXSIZE-1;
	m_Rear = MAXSIZE-1;
}

template <class Type>
bool Queue<Type>::EnQueue(Type& data) {
	if (IsFull()) return false;
	else {
		m_Rear = (m_Rear+1)%maxQue;
		m_Array[m_Rear] = data;
		return true;
	}
}

template <class Type>
bool Queue<Type>::DeQueue(Type& data) {
	if (IsEmpty()) return false;
	else {
		m_Front = (m_Front+1)%maxQue;
		data = m_Array[m_Front];
		return true;
	}
}

template <class Type>
void Queue<Type>::Print() const {
	if (IsEmpty()) return;
	else {
		int i = m_Rear;
		while (i != m_Front) {
			std::cout << "\t       " << *m_Array[i] << std::endl;
			i = (i-1)%maxQue;
			if (i == -1) i = maxQue-1;
		}
	}
}