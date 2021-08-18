#pragma once

#include "FolderType.h"

class FolderType;

class SortedList {
private:
	FolderType* m_Array;
	int m_Size;
	int m_Length;
	int m_CurPointer;
public:
	SortedList() : m_Size(0), m_Length(0), m_CurPointer(-1) { m_Array = nullptr; }
	~SortedList();

	void MakeEmpty();
	int GetLength() { return m_Length; }
	bool IsFull() { return m_Size == m_Length ? true : false; }
	bool IsEmpty() { return m_Length == 0 ? true : false; }
	bool Add(FolderType& data);
	void ResetList() { m_CurPointer = -1; }
	int GetNextItem(FolderType& data);
	FolderType* GetNextItemPtr();
	int Get(FolderType& data);
	bool Delete(FolderType& data);
	bool Replace(FolderType& data);
	int GetByBinarySearch(FolderType& data);
	void operator=(const SortedList& list);
};