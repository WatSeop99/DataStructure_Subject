#pragma once

#include <iostream>

#define MAXSIZE 10

template <class Type>
class Stack {
private:
	Type* m_Array;
	int m_Top;
public:
	Stack() {
		m_Array = new Type[MAXSIZE];
		m_Top = -1;
	}
	~Stack() { delete[] m_Array; }

	void MakeEmpty() { m_Top = -1; }
	bool IsFull() const { return m_Top == MAXSIZE-1; }
	bool IsEmpty() const { return m_Top == -1; }
	bool Push(Type& data);
	bool Pop();
	Type Top() { return IsEmpty() ? NULL : m_Array[m_Top]; }
};

template <class Type>
bool Stack<Type>::Push(Type& data) {
	if (IsFull()) return false;
	else {
		m_Top++;
		m_Array[m_Top] = data;
		return true;
	}
}

template <class Type>
bool Stack<Type>::Pop() {
	if (IsEmpty()) return false;
	else {
		--m_Top;
		return true;
	}
}