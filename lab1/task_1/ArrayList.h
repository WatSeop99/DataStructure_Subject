#pragma once

#include "ItemType.h"

#define MAXSIZE 10

class ArrayList {
private:
	ItemType m_Array[MAXSIZE];
	int m_Length;
	int m_CurPointer;
public:
	ArrayList() : m_Length(0), m_CurPointer(-1)
	{ }
	~ArrayList() { MakeEmpty(); }

	void MakeEmpty();
	int GetLength() { return m_Length; }
	bool IsFull() { return MAXSIZE == m_Length ? true : false; }
	bool IsEmpty() { return m_Length == 0 ? true : false; }
	bool Add(ItemType& data);
	void ResetList() { m_CurPointer = -1; }
	int GetNextItem(ItemType& data);
	int Get(ItemType& data);
	bool Delete(ItemType& data);
	bool RePlace(ItemType& data);
};