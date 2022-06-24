#pragma once

#include <cstring>

#include "Contents.h"
#include "Item.h"

struct Parameter
{
	char* Album;
	char* Artist;
	char* Event;
	char* Lyrics;
};

class File : public Item
{
public:
	File(Contents::eContentsType type = Contents::eContentsType::None);
	File(Item& data);
	~File();

	void GetContents(Contents::eContentsType type, void* param) const;
	Contents::eContentsType GetContentsType() const;
	void SetContents(Contents::eContentsType type, void* param);
	void SetContentsType(Contents::eContentsType type);

	Item& operator=(Item& data);

private:
	Contents* mContents;
	Contents::eContentsType mContentsType;
};