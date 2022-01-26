#pragma once

#include "ItemType.h"
#include "ContentsType.h"
#include "TextFile.h"
#include "ImageFile.h"
#include "MusicFile.h"

class FileType : public ItemType {
public:
	FileType(int _contentsType = 0) : contents(nullptr), contentsType(_contentsType) { type = "file"; }
	FileType(ItemType& data);
	~FileType() { if (contents) delete contents; }

	void setContentsType(int type);
	int getCongtentsType() const { return constentsType; }
	ItemType& operator=(ItemType& data);
	void run();
	void displayInfo();
private:
	ContenteType* contents;
	int contentsType;
};