#pragma once

template <class Type>
struct NodeType {
	Type data;
	NodeType* prev;
	NodeType* next;
};