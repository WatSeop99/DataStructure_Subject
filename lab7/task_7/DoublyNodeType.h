#pragma once

template <class Type>
struct NodeType {
	Type data;
	NodeType* left;
	NodeType* right;
};