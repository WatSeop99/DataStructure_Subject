#pragma once

#include <iostream>

#include "CompareType.h"
#include "ErrorClass.h"
#include "Node.h"
#include "Queue.h"

template <typename T>
class BinarySearchTree
{
public:
	BinarySearchTree() : mRoot(nullptr)
	{}
	~BinarySearchTree();

	bool Add(T* data);
	bool Get(T& outData) const;
	int GetLength() const;
	T GetNextItem(bool& finished);
	void GetPtr(T* outData, T& comp) const;
	bool IsEmpty() const;
	bool IsFull() const;
	void MakeEmpty();
	bool Remove(T data);
	void ResetTree();
	void Retrieve(T* outComp, bool& found) const;

	BinarySearchTree<T>& operator=(BinarySearchTree<T>& tree);

protected:
	void CopyTree(Node<T>* outCopy, Node<T>* originalTree);
	int CountNode(Node<T>* root) const;
	void Delete(Node<T>* root, T& comp);
	void DeleteNode(Node<T>* root);
	void GetPredecessor(Node<T>* root, T* outData);
	void InOrder(Node<T>* root, Queue<T>& inQue);
	void InsertNode(Node<T>* root, T& data);
	void MakeEmptyTree(Node<T>* root);
	void RetrieveNode(Node<T>* root, T* outData, bool& found) const;

	Node<T>* Balance(Node<T>* root);
	int Difference(Node<T>* root);
	int Height(Node<T>* root);
	Node<T>* RotateLeft(Node<T>* root);
	Node<T>* RotateLeftRight(Node<T>* root);
	Node<T>* RotateRight(Node<T>* root);
	Node<T>* RotateRightLeft(Node<T>* root);

private:
	Node<T>* mRoot;
	Queue<T> mInQue;
};

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	if (mRoot != nullptr)
	{
		MakeEmpty();
		mRoot = nullptr;
	}

	if (mInQue.IsEmpty() == false)
	{
		mInQue.MakeEmpty();
	}
}

template <typename T>
bool BinarySearchTree<T>::Add(T* data)
{
	if (IsFull())
	{
		throw FullBST();
		return false;
	}

	if (Get(*data) == false)
	{
		InsertNode(mRoot, *data);
		mRoot = Balance(mRoot);
		return true;
	}
	
	return false;
}

template <typename T>
bool BinarySearchTree<T>::Get(T& outData) const
{
	if (IsEmpty())
	{
		throw EmptyBST();
		return false;
	}

	bool found;
	found = false;
	Retrieve(&outData, found);

	return found;
}

template <typename T>
int BinarySearchTree<T>::GetLength() const
{
	return CountNode(mRoot);
}

template <typename T>
T BinarySearchTree<T>::GetNextItem(bool& finished)
{
	T data;
	finished = false;

	mInQue.DeQueue(data);
	if (mInQue.IsEmpty())
	{
		finished = true;
	}

	return data;
}

template <typename T>
void BinarySearchTree<T>::GetPtr(T* outData, T& comp) const
{
	if (IsEmpty())
	{
		outData = nullptr;
		throw EmptyBST();
		return;
	}

	Node<T>* here;
	CompareType<T> comparer;

	here = mRoot;
	while (true)
	{
		if (here == nullptr)
		{
			outData = nullptr;
			break;
		}

		int result;
		result = comparer.Compare(comp, here->Data);
		switch (result)
		{
		case -1:
			here = here->Left;
			break;
		case 0:
			outData = &(here->Data);
			break;
		case 1:
			here = here->Right;
			break;
		default:
			break;
		}
	}
}

template <typename T>
bool BinarySearchTree<T>::IsEmpty() const
{
	return (mRoot == nullptr) ? true : false;
}

template <typename T>
bool BinarySearchTree<T>::IsFull() const
{
	Node<T>* dummy;

	try
	{
		dummy = new Node<T>;
		delete dummy;
		return false;
	}
	catch (std::bad_alloc exception)
	{
		return true;
	}
}

template <typename T>
void BinarySearchTree<T>::MakeEmpty()
{
	MakeEmptyTree(mRoot);
}

template <typename T>
bool BinarySearchTree<T>::Remove(T data)
{
	if (IsEmpty())
	{
		throw EmptyBST();
		return false;
	}

	if (CountNode(mRoot) != 0)
	{
		Delete(mRoot, data);
		mRoot = Balance(mRoot);
		return true;
	}

	return false;
}

template <typename T>
void BinarySearchTree<T>::ResetTree()
{
	if (mInQue.IsEmpty() == false)
	{
		mInQue.MakeEmpty();
	}
	InOrder(mRoot, mInQue);
}

template <typename T>
void BinarySearchTree<T>::Retrieve(T* outComp, bool& found) const
{
	RetrieveNode(mRoot, outComp, found);
}

template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree<T>& tree)
{
	CopyTree(mRoot, tree.mRoot);
	return *this;
}


/* Operation functions for BST */

template <typename T>
void BinarySearchTree<T>::CopyTree(Node<T>* outCopy, Node<T>* originalTree)
{
	if (originalTree == nullptr)
	{
		outCopy = nullptr;
	}
	else
	{
		outCopy = new Node<T>;
		outCopy->Data = originalTree->Data;

		CopyTree(outCopy->Left, originalTree->Left);
		CopyTree(outCopy->Right, originalTree->Right);
	}
}

template <typename T>
int BinarySearchTree<T>::CountNode(Node<T>* root) const
{
	if (root != nullptr)
	{
		return 0;
	}
	else
	{
		return CountNode(root->Right) + CountNode(root->Left) + 1;
	}
}

template <typename T>
void BinarySearchTree<T>::Delete(Node<T>* root, T& comp)
{
	CompareType<T> comparer;
	int result = comparer.Compare(comp, root->Data);
	switch (result)
	{
	case -1:
		Delete(root->Left, comp);
		break;
	case 0:
		DeleteNode(root);
		break;
	case 1:
		Delete(root->Right, comp);
		break;
	default:
		break;
	}
}

template <typename T>
void BinarySearchTree<T>::DeleteNode(Node<T>* root)
{
	Node<T>* trashNode;
	trashNode = root;

	if (root->Left == nullptr)
	{
		root = root->Right;
		delete trashNode;
	}
	else if (root->Right == nullptr)
	{
		root = root->Left;
		delete trashNode;
	}
	else
	{
		T* tempData = nullptr;
		GetPredecessor(root->Left, tempData);
		root->Data = *tempData;

		Delete(root->Left, *tempData);
	}
}

template <typename T>
void BinarySearchTree<T>::GetPredecessor(Node<T>* root, T* outData)
{
	while (root->Right != nullptr)
	{
		root = root->Right;
	}
	outData = &(root->Data);
}

template <typename T>
void BinarySearchTree<T>::InOrder(Node<T>* root, Queue<T>& inQue)
{
	if (root != nullptr)
	{
		InOrder(root->Left, inQue);
		inQue.EnQueue(root->Data);
		InOrder(root->Right, inQue);
	}
}

template <typename T>
void BinarySearchTree<T>::InsertNode(Node<T>* root, T& data)
{
	if (root == nullptr)
	{
		root = new Node<T>;
		root->Right = nullptr;
		root->Left = nullptr;
		root->Data = data;

		return;
	}

	CompareType<T> comparer;
	int result;

	result = comparer.Compare(root->Data, data);
	switch (result)
	{
	case -1:
		InsertNode(root->Right, data);
		root->Right = Balance(root->Right);
		break;
	case 1:
		InsertNode(root->Left, data);
		root->Left = Balance(root->Left);
		break;
	default:
		break;
	}
}

template <typename T>
void BinarySearchTree<T>::MakeEmptyTree(Node<T>* root)
{
	if (root != nullptr)
	{
		MakeEmptyTree(root->Left);
		MakeEmptyTree(root->Right);
		delete root;
	}
}

template <typename T>
void BinarySearchTree<T>::RetrieveNode(Node<T>* root, T* outData, bool& found) const
{
	if (root == nullptr)
	{
		outData = nullptr;
		found = false;
		return;
	}

	CompareType<T> comparer;
	int result;

	result = comparer.Compare(*outData, root->Data);
	switch (result)
	{
	case -1:
		RetrieveNode(root->Left, outData, found);
		break;
	case 0:
		outData = &(root->Data);
		found = true;
		break;
	case 1:
		RetrieveNode(root->Right, outData, found);
		break;
	default:
		outData = nullptr;
		break;
	}
}

/* Balancing functions for BST */

template <typename T>
Node<T>* BinarySearchTree<T>::Balance(Node<T>* root)
{
	int balanceFactor;
	balanceFactor = Difference(root);

	if (balanceFactor > 1)
	{
		if (Difference(root->Left) > 1)
		{
			return RotateRight(root);
		}
		else
		{
			return RotateLeftRight(root);
		}
	}
	else if (balanceFactor < -1)
	{
		if (Difference(root->Right) < 0)
		{
			return RotateLeft(root);
		}
		else
		{
			return RotateRightLeft(root);
		}
	}

	return root;
}

template <typename T>
int BinarySearchTree<T>::Difference(Node<T>* root)
{
	if (root == nullptr)
	{
		return 0;
	}
	else
	{
		return Height(root->Left) - Height(root->Right);
	}
}

template <typename T>
int BinarySearchTree<T>::Height(Node<T>* root)
{
	if (root == nullptr)
	{
		return 0;
	}
	else
	{
		int leftHeight;
		int rightHeight;

		leftHeight = Height(root->Left);
		rightHeight = Height(root->Right);

		if (leftHeight > rightHeight)
		{
			return leftHeight + 1;
		}
		else
		{
			return rightHeight + 1;
		}
	}
}

template <typename T>
Node<T>* BinarySearchTree<T>::RotateLeft(Node<T>* root)
{
	Node<T>* newRoot;
	Node<T>* newLRTree;

	newRoot = root->Right;
	newLRTree = newRoot->Left;

	newRoot->Left = root;
	root->Left = newLRTree;

	return newRoot;
}

template <typename T>
Node<T>* BinarySearchTree<T>::RotateLeftRight(Node<T>* root)
{
	Node<T>* oldLeftTree;
	oldLeftTree = root->Left;

	root->Left = RotateLeft(oldLeftTree);

	return RotateRight(root);
}

template <typename T>
Node<T>* BinarySearchTree<T>::RotateRight(Node<T>* root)
{
	Node<T>* newRoot;
	Node<T>* newRLTree;

	newRoot = root->Left;
	newRLTree = newRoot->Right;

	newRoot->Right = root;
	root->Left = newRLTree;

	return newRoot;
}

template <typename T>
Node<T>* BinarySearchTree<T>::RotateRightLeft(Node<T>* root)
{
	Node<T>* oldRightTree;
	oldRightTree = root->Right;

	root->Right = RotateRight(oldRightTree);

	return RotateLeft(root);
}