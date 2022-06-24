#pragma once

#include <iostream>
#include <string>

const int INF = 987654321;

namespace compare
{
	enum class eKeyValue
	{
		Name,
		Type,
		CreationTime,
		ModifiedTime
	};

	enum class eSortVer
	{
		Asending,
		Desending
	};
};

template <typename T>
class CompareType
{
public:
	CompareType(compare::eKeyValue key = compare::eKeyValue::Name,
		compare::eSortVer sort = compare::eSortVer::Asending)
		:mKey(key),
		mSortType(sort)
	{}

	int Compare(const T& data1, const T& data2) const;
	compare::eKeyValue GetKey() const;
	void SetKey(compare::eKeyValue key);

private:
	compare::eSortVer mSortType;
};

template <typename T>
int CompareType<T>::Compare(const T& data1, const T& data2) const
{
	switch (mSortType)
	{
	case compare::eSortVer::Asending:
		if (*data1 < *data2)
		{
			return -1;
		}
		else if (*data1 == *data2)
		{
			return 0;
		}
		else
		{
			return 1;
		}
		break;
	case compare::eSortVer::Desending:
		if (*data1 > *data2)
		{
			return -1;
		}
		else if (*data1 == *data2)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	default:
		break;
	}
	

	return INF;
}

template <typename T>
compare::eKeyValue CompareType<T>::GetKey() const
{
	return mKey;
}

template <typename T>
void CompareType<T>::SetKey(compare::eKeyValue key)
{
	mKey = key;
}