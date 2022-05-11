#include "FolderType.h"

FolderType::FolderType()
{
	mName = "";
}

std::string FolderType::GetName() const
{
	return mName;
}

void FolderType::SetName(std::string inName)
{
	mName = inName;
}

void FolderType::SetRecord(std::string inName)
{
	SetName(inName);
}

void FolderType::DisplayNameOnScreen() const
{
	std::cout << "\tName : " << mName << std::endl;
}

void FolderType::DisPlayRecordOnScreen() const
{
	DisplayNameOnScreen();
}

void FolderType::SetNameFromKB()
{
	std::cout << "\t Name : ";
	std::cin >> mName;
}

void FolderType::SetRecordFromKB()
{
	SetNameFromKB();
}
	 
bool FolderType::operator<(FolderType& item) const
{
	return (mName.compare(item.mName) < 0) ? true : false;
}
	 
bool FolderType::operator>(FolderType& item) const
{
	return (mName.compare(item.mName) > 0) ? true : false;
}
	 
bool FolderType::operator==(FolderType& item) const
{
	return (mName.compare(item.mName) == 0) ? true : false;
}
	 
void FolderType::operator<<(FolderType& item) const
{
	item.DisPlayRecordOnScreen();
}