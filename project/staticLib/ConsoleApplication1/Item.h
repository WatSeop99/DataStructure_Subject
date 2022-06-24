#pragma once

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "CompareType.h"

class Item
{
public:
	enum class eItemType
	{
		Directory,
		File,
		None
	};

	Item();

	std::string GenTime() const;
	std::string GetCreationTime() const;
	std::string GetName() const;
	std::string GetPath() const;
	eItemType GetType() const;
	void SetCreationTime(std::string time);
	void SetName(std::string name);
	void SetPath(std::string path);
	void SetType(eItemType type);

	bool operator<(Item& comp);
	bool operator>(Item& comp);
	bool operator==(Item& comp);
	virtual Item& operator=(Item& data);

protected:
	std::string mName;
	std::string mPath;
	std::string mCreationTime;
	std::string mModifiedTime;
	eItemType mType;
	compare::eKeyValue mCompValue;
};