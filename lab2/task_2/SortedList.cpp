#pragma once

#include "SortedList.h"

SortedList::~SortedList() {
	MakeEmpty();
	delete[] m_Array;
}

void SortedList::MakeEmpty() {
	m_Length = 0;
	m_CurPointer = -1;
}

bool SortedList::Add(FolderType& data) {
	if (m_Size == 0) {
		m_Size = 10;
		m_Array = new FolderType[m_Size];
	}
	if (IsFull()) {
		FolderType* tempArr = new FolderType[2*m_Size];
		m_Size *= 2;
		for (int i = 0; i < m_Length; ++i)
			tempArr[i] = m_Array[i];
		delete[] m_Array;
		m_Array = tempArr;
	}
	if (m_Length == 0)
		m_Array[m_Length++] = data;
	else {
		bool moreToSearch = false;
		for (int i = m_Length-1; i > 0; --i) {
			if (data > m_Array[i]) {
				m_Array[i+1] = data;
				moreToSearch = true;
				break;
			}
			m_Array[i+1] = m_Array[i];
		}
		if (!moreToSearch) m_Array[0] = data;
		++m_Length;
	}
	return true;
}

int SortedList::GetNextItem(FolderType& data) {
	if (IsEmpty()) return -1;
	m_CurPointer++;
	if (m_CurPointer >= m_Length) return -1;
	data = m_Array[m_CurPointer];
	return m_CurPointer;
}

FolderType* SortedList::GetNextItemPtr() {
	m_CurPointer++;
	return m_CurPointer < m_Length ? &m_Array[m_CurPointer] : nullptr;
}

int SortedList::Get(FolderType& data) {
	int idx = GetByBinarySearch(data);
	return idx != -1 ? idx : -1;
}

bool SortedList::Delete(FolderType& data) {
	int idx = GetByBinarySearch(data);
	if (idx != -1) {
		for (int i = idx+1; i < m_Length; ++i)
			m_Array[i-1] = m_Array[i];
		--m_Length;
		return true;
	}
	else return false;
}

bool SortedList::Replace(FolderType& data) {
	int idx = GetByBinarySearch(data);
	if (idx != -1) {
		m_Array[idx] = data;
		return true;
	}
	else return false;
}

int SortedList::GetByBinarySearch(FolderType& data) {
	int begin = 0, end = m_Length-1;
	while (begin <= end) {
		int mid = (begin+end)/2;
		if (data < m_Array[mid]) end = mid-1;
		else if (data > m_Array[mid]) begin = mid+1;
		else {
			data = m_Array[mid];
			return mid;
		}
	}
	return -1;
}

void SortedList::operator=(const SortedList& list) {
	if (m_Array) delete[] m_Array;
	m_Array = new FolderType[list.m_Length];
	m_Size = list.m_Size;
	m_Length = list.m_Length;
	for (int i = 0; i < m_Length; ++i)
		m_Array[i] = list.m_Array[i];
}