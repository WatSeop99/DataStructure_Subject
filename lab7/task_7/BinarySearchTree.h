#pragma once

#include "DoublyNodeType.h"
#include "Queue.h"
#include "CompareType.h"

template <class Type>
class BinarySearchTree {
public:
	BinarySearchTree() : root(nullptr) { }
	~BinarySearchTree();

	bool isEmpty() const { return root == nullptr; }
	bool isFull() const;
	void makeEmpty() { makeEmptyTree(root); }
	int getLength() { return countNode(root); }
	BinarySearchTree<Type>& operator=(BinarySearchTree<Type>& tree);
	bool addData(Type& data);
	bool removeData(Type& data);
	void retrieveData(Type& data, bool& found) const { retrieveNode(root, data, found); }
	bool get(Type& data);
	Type* getPtr(Type& data);
	void resetTree();
	Type getNextItem(bool& finished);
	void print(std::string type) const { printInOrderTraversal(root, type); }
private:
	NodeType<Type>* root;
	Queue<Type> inQue;
};

template <class Type>
BinarySearchTree<Type>::~BinarySearchTree() {
	if (root) makeEmpty();
	if (~inQue.isEmpty()) inQue.makeEmpty();
}

template <class Type>
bool BinarySearchTree<Type>::isFull() const {
	NodeType<Type>* node;
	try {
		node = new NodeType<Type>;
		delete node;
		return false;
	}
	catch (std::bad_alloc& exception) {
		return true;
	}
}

template <class Type>
BinarySearchTree<Type>& BinarySearchTree<Type>::operator=(BinarySearchTree<Type>& tree) {
	copyTree(root, tree.root);
	return *this;
}

template <class Type>
bool BinarySearchTree<Type>::addData(Type& data) {
	if (isFull() || get(data)) return false;
	insertNode(root, data);
	root = balance(root);
	return true;
}

template <class Type>
bool BinarySearchTree<Type>::removeData(Type& data) {
	if (isEmpty()) return false;
	remove(root, data);
	root = balance(root);
	return true;
}

template <class Type>
bool BinarySearchTree<Type>::get(Type& data) {
	if (isEmpty()) return false;
	bool found = false;
	retrieve(data, found);
	return found;
}

template <class Type>
Type* BinarySearchTree<Type>::getPtr(Type& data) {
	if (isEmpty()) return nullptr;
	NodeType<Type>* node = root;
	CompareType<Type> comparer;
	while (true) {
		if (!node) return nullptr;
		int comp = comparer.compare(data, node->data);
		switch (comp) {
		case -1:
			node = node->left;
			break;
		case 1:
			node = node->right;
			break;
		case 0:
			return &(node->data);
		}
	}
	return nullptr;
}

template <class Type>
void BinarySearchTree<Type>::resetTree() {
	if (!inQue.isEmpty())
		inQue.makeEmpty();
	inOrder(root, inQue);
}

template <class Type>
Type BinarySearchTree<Type>::getNextItem(bool& finished) {
	Type data;
	finished = false;
	inQue.dequeue(data);
	if (inQue.isEmpty()) finished = true;
	return data;
}

// Operation Functions for BST

template <class Type>
void makeEmptyTree(NodeType<Type>*& rootNode) {
	if (rootNode) {
		makeEmptyTree(rootNode->left);
		makeEmptyTree(rootNode->right);
		delete rootNode;
	}
}

template <class Type>
int countNode(NodeType<Type>*& rootNode) {
	if (!rootNode) return 0;
	return countNode(rootNode->right) + countNode(rootNode->left) + 1;
}

template <class Type>
void copyTree(NodeType<Type>*& copy, NodeType<Type>*& original) {
	if (!original) copy = nullptr;
	else {
		copy = new NodeType<Type>;
		copy->data = original->data;
		copyTree(copy->left, original->left);
		copyTree(copy->right, original->right);
	}
}

template <class Type>
void insertNode(NodeType<Type>*& rootNode, Type& data) {
	if (!rootNode) {
		rootNode = new NodeType<Type>;
		rootNode->right = nullptr;
		rootNode->left = nullptr;
		rootNode->data = data;
		return;
	}
	CompareType<Type> comparer;
	int comp = comparer.compare(rootNode->data, data);
	switch (comp) {
	case 1:
		insertNode(rootNode->left, data);
		rootNode->left = balance(rootNode->left);
		break;
	case -1:
		insertNode(rootNode->right, data);
		rootNode->right = balance(rootNode->right);
		break;
	}
}

template <class Type>
void getPredecessor(NodeType<Type>* rootNode, Type& data) {
	while (rootNode->right)
		rootNode = rootNode->right;
	data = rootNode->data;
}

template <class Type>
void removeNode(NodeType<Type>*& rootNode) {
	NodeType<Type>* delNode = rootNode;
	if (!rootNode->left) {
		rootNode = rootNode->right;
		delete delNode;
	}
	else if (!rootNode->right) {
		rootNode = rootNode->left;
		delete delNode;
	}
	else {
		Type tempData;
		getPredecessor(rootNode->left, tempData);
		rootNode->data = tempData;
		remove(rootNode->left, tempData);
	}
}

template <class Type>
void remove(NodeType<Type>*& rootNode, Type& data) {
	CompareType<Type> comparer;
	int comp = comparer.compare(data, rootNode->data);
	switch (comp) {
	case -1:
		remove(rootNode->left, data);
		break;
	case 1:
		remove(rootNode->right, data);
		break;
	case 0:
		removeNode(rootNode);
		break;
	}
}

template <class Type>
void inOrder(NodeType<Type>* rootNode, Queue<Type>& que) {
	if (rootNode) {
		inOrder(rootNode->left, que);
		que.enqueue(rootNode->data);
		inOrder(rootNode->right, que);
	}
}

template <class Type>
void retrieveNode(NodeType<Type>* rootNode, Type& data, bool& found) {
	if (!rootNode) {
		found = false;
		return;
	}
	CompareType<Type> comparer;
	int comp = comparer.compare(data, rootNode->data);
	switch (comp) {
	case -1:
		retrieveNode(rootNode->left, data, found);
		break;
	case 1:
		retrieveNode(rootNode->right, data, found);
		break;
	case 0:
		data = rootNode->data;
		found = true;
		break;
	}
}

template <class Type>
void printInOrderTraversal(NodeType<Type>* rootNode, std::string type) {
	if (rootNode) {
		printInOrderTraversal(rootNode->left, type);
		if ((*rootNode->data).getType().compare(type) == 0)
			cout << "\t        " << *rootNode->data << endl;
		printInOrderTraversal(rootNode->right, type);
	}
}

// Balancing Functions

template <class Type>
int difference(NodeType<Type>* rootNode) {
	if (!rootNode) return 0;
	return height(rootNode->left) - height(rootNode->right);
}

template <class Type>
int height(NodeType<Type>* rootNode) {
	if (!rootNode) return 0;
	int heightLeft = height(rootNode->left), heightRight = height(rootNode->right);
	if (heightLeft > heightRight)
		return heightLeft + 1;
	else
		return heightRight + 1;
}

template <class Type>
NodeType<Type>* balance(NodeType<Type>* rootNode) {
	int balanceFactor = difference(rootNode);
	if (balanceFactor > 1) {
		if (difference(rootNode->left) > 1) return rotateRight(rootNode);
		return rotateLeftRight(rootNode);
	}
	else if (balanceFactor < -1) {
		if (difference(rootNode->right) < 0) return rotateLeft(rootNode);
		return rotateRightLeft(rootNode);
	}
	return rootNode;
}

template <class Type>
NodeType<Type>* rotateRight(NodeType<Type>* rootNode) {
	NodeType<Type>* temp1 = rootNode->left;
	NodeType<Type>* temp2 = temp1->right;
	temp1->right = rootNode;
	rootNode->left = temp2;
	return temp1;
}

template <class Type>
NodeType<Type>* rotateLeft(NodeType<Type>* rootNode) {
	NodeType<Type>* temp1 = rootNode->right;
	NodeType<Type>* temp2 = temp1->left;
	temp1->left = rootNode;
	rootNode->right = temp2;
	return temp1;
}

template <class Type>
NodeType<Type>* rotateRightLeft(NodeType<Type>* rootNode) {
	NodeType<Type>* temp = rootNode->right;
	rootNode->right = rotateRight(temp);
	return rotateLeft(rootNode);
}

template <class Type>
NodeType<Type>* rotateLeftRight(NodeType<Type>* rootNode) {
	NodeType<Type>* temp = rootNode->left;
	rootNode->left = rotateLeft(temp);
	return rotateRight(rootNode);
}