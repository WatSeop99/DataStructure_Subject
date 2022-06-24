#pragma once

template <typename T>
struct Node
{
	T Data;
	Node<T>* Left;
	Node<T>* Right;
};