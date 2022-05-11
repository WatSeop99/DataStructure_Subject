#pragma once

#include <iostream>
#include <string>

class FolderType
{
public:
	FolderType();

	std::string GetName() const;
	void SetName(std::string inName);
	void SetRecord(std::string inName);
	void DisplayNameOnScreen() const;
	void DisPlayRecordOnScreen() const;
	void SetNameFromKB();
	void SetRecordFromKB();
	bool operator<(FolderType& item) const;
	bool operator>(FolderType& item) const;
	bool operator==(FolderType& item) const;
	void operator<<(FolderType& item) const;

private:
	std::string mName;
};