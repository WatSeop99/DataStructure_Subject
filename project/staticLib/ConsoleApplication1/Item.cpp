#include "Item.h"

Item::Item()
	: mName("untitled"),
	mPath(""),
	mType(eItemType::Directory),
	mCompValue(compare::eKeyValue::Name)
{
	mCreationTime = GenTime();
	mModifiedTime = mCreationTime;
}

std::string Item::GenTime() const
{
	std::time_t curTime;
	struct tm* curTm;

	curTime = time(nullptr);
	curTm = localtime(&curTime);

	std::string year = std::to_string(curTm->tm_year + 1900) + "년 ";
	std::string month = std::to_string(curTm->tm_mon + 1) + "월 ";
	std::string day = std::to_string(curTm->tm_mday) + "일 / ";
	std::string hour = std::to_string(curTm->tm_hour) + "시 ";
	std::string minute = std::to_string(curTm->tm_min) + "분 ";
	std::string second = std::to_string(curTm->tm_sec) + "초 ";
	std::string time = year + month + day + hour + minute + second;

	return time;
}

std::string Item::GetCreationTime() const
{
	return mCreationTime;
}

std::string Item::GetName() const
{
	return mName;
}

std::string Item::GetPath() const
{
	return mPath;
}

Item::eItemType Item::GetType() const
{
	return mType;
}

void Item::SetCreationTime(std::string time)
{
	mCreationTime = time;
}

void Item::SetName(std::string name)
{
	mName = name;
}

void Item::SetPath(std::string path)
{
	mPath = path;
}

void Item::SetType(Item::eItemType type)
{
	mType = type;
}

bool Item::operator<(Item& comp)
{
	switch (mCompValue)
	{
	case compare::eKeyValue::Name:
		return mName.compare(comp.mName) < 0;
	case compare::eKeyValue::Type:
		return mType < comp.mType;
	case compare::eKeyValue::CreationTime:
		return mCreationTime < comp.mCreationTime;
	case compare::eKeyValue::ModifiedTime:
		return mModifiedTime < comp.mModifiedTime;
	default:
		return false;
	}
}

bool Item::operator>(Item& comp)
{
	switch (mCompValue)
	{
	case compare::eKeyValue::Name:
		return mName.compare(comp.mName) > 0;
	case compare::eKeyValue::Type:
		return mType > comp.mType;
	case compare::eKeyValue::CreationTime:
		return mCreationTime > comp.mCreationTime;
	case compare::eKeyValue::ModifiedTime:
		return mModifiedTime > comp.mModifiedTime;
	default:
		return false;
	}
}

bool Item::operator==(Item& comp)
{
	switch (mCompValue)
	{
	case compare::eKeyValue::Name:
		return mName.compare(comp.mName) == 0;
	case compare::eKeyValue::Type:
		return mType == comp.mType;
	case compare::eKeyValue::CreationTime:
		return mCreationTime == comp.mCreationTime;
	case compare::eKeyValue::ModifiedTime:
		return mModifiedTime == comp.mModifiedTime;
	default:
		return false;
	}
}

Item& Item::operator=(Item& data)
{
	mName = data.mName;
	mType = data.mType;
	mCreationTime = data.mCreationTime;
	mModifiedTime = GenTime();
	mCompValue = compare::eKeyValue::Name;

	return *this;
}