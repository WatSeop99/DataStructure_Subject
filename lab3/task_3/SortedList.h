#pragma once

template <class Type>
class SortedList {
private:
	Type* m_Array;
	int m_Size;
	int m_Length;
	int m_CurPointer;
public:
	SortedList() : m_Size(0), m_Length(0), m_CurPointer(-1) { m_Array = nullptr; }
	~SortedList();

	void MakeEmpty();
	int GetLength() const { return m_Length; }
	bool IsFull() const { return m_Size == m_Length; }
	bool IsEmpty() const { return m_Length == 0; }
	bool Add(Type& data);
	void ResetList() { m_CurPointer = -1; }
	int GetNextItem(Type& data);
	Type* GetNextItemPtr();
	int Get(Type& data);
	bool Delete(Type& data);
	bool Replace(Type& data);
	int GetByBinarySearch(Type& data);
	SortedList<Type>& operator=(const SortedList<Type>& list);
};

template <class Type>
SortedList<Type>::~SortedList() {
	MakeEmpty();
	if (m_Array) delete[] m_Array;
}

template <class Type>
void SortedList<Type>::MakeEmpty() {
	m_Length = 0;
	m_CurPointer = -1;
}

template <class Type>
bool SortedList<Type>::Add(Type& data) {
	if (m_Size == 0) {
		m_Size = 10;
		m_Array = new Type[m_Size];
	}
	if (IsFull()) {
		m_Size *= 2;
		Type* tempArr = new Type[m_Size];
		for (int i = 0; i < m_Length; ++i)
			tempArr[i] = m_Array[i];
		delete[] m_Array;
		m_Array = tempArr;
	}
	if (m_Length == 0) m_Array[m_Length++] = data;
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

template <class Type>
int SortedList<Type>::GetNextItem(Type& data) {
	if (IsEmpty()) return -1;
	if (m_CurPointer+1 >= m_Length) return -1;
	data = m_Array[++m_CurPointer];
	return m_CurPointer;
}

template <class Type>
Type* SortedList<Type>::GetNextItemPtr() {
	++m_CurPointer;
	return m_CurPointer < m_Length ? &m_Array[m_CurPointer] : nullptr;
}

template <class Type>
int SortedList<Type>::Get(Type& data) {
	int idx = GetByBinarySearch(data);
	return idx != -1 ? idx : -1;
}

template <class Type>
bool SortedList<Type>::Delete(Type& data) {
	int idx = GetByBinarySearch(data);
	if (idx != -1) {
		for (int i = idx + 1; i < m_Length; ++i)
			m_Array[i-1] = m_Array[i];
		--m_Length;
		return true;
	}
	return false;
}

template <class Type>
bool SortedList<Type>::Replace(Type& data) {
	int idx = GetByBinarySearch(data);
	if (idx != -1) {
		m_Array[idx] = data;
		return true;
	}
	return false;
}

template <class Type>
int SortedList<Type>::GetByBinarySearch(Type& data) {
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

template <class Type>
SortedList<Type>& SortedList<Type>::operator=(const SortedList<Type>& list) {
	if (m_Array) delete[] m_Array;
	m_Array = new Type[list.m_Length];
	m_Size = list.m_Size;
	m_Length = list.m_Length;
	for (int i = 0; i < m_Length; ++i)
		m_Array[i] = list.m_Array[i];
	return *this;
}