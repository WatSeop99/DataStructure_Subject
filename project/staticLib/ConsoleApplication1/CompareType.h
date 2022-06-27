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
	CompareType(compare::eSortVer sort = compare::eSortVer::Asending)
		: mSortType(sort)
	{}

	int Compare(T& data1, T& data2) const;
	compare::eSortVer GetSortType() const;
	void SetSortType(compare::eSortVer sort);

private:
	compare::eSortVer mSortType;
};

template <typename T>
int CompareType<T>::Compare(T& data1, T& data2) const
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
compare::eSortVer CompareType<T>::GetSortType() const
{
	return mSortType;
}

template <typename T>
void CompareType<T>::SetSortType(compare::eSortVer sort)
{
	mSortType = sort;
}