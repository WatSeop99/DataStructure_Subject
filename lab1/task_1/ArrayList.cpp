#include "ArrayList.h"

void ArrayList::MakeEmpty() {
	m_Length = 0;
	m_CurPointer = -1;
}

bool ArrayList::Add(ItemType& data) {
	if (IsFull())
		return false;
	m_Array[m_Length++] = data;
	return true;
}

int ArrayList::GetNextItem(ItemType& data) {
	if (IsEmpty())
		return -1;
	m_CurPointer++;
	if (m_CurPointer >= m_Length)
		return -1;
	data.SetRecord(m_Array[m_CurPointer].GetId(), m_Array[m_CurPointer].GetName(), m_Array[m_CurPointer].GetAddress());
	return m_CurPointer;
}

int ArrayList::Get(ItemType& data) {
	if (IsEmpty())
		return -1;
	for (int i = 0; i < m_Length; ++i) {
		if (m_Array[i].CompareByID(data) == RelationType::EQUAL) {
			data.SetRecord(m_Array[i].GetId(), m_Array[i].GetName(), m_Array[i].GetAddress());
			return i;
		}
	}
	return -1;
}

bool ArrayList::Delete(ItemType& data) {
	int idx = Get(data);
	if (idx != -1) {
		for (int i = idx; i < m_Length - 1; ++i)
			m_Array[i] = m_Array[i + 1];
		m_Length--;
		return true;
	}
	else
		return false;
}

bool ArrayList::RePlace(ItemType& data) {
	int idx = Get(data);
	return idx != -1 ? true : false;
}