#include "FileType.h"

FileType::FileType(ItemType& data) {
	FileType* tempPtr = dynamic_cast<FileType*> (&data);
	name = tempPtr->name;
	path = tempPtr->path;
	createTime = tempPtr->createTime;
	type = "file";
	contentsType = tempPtr->contentsType;
	switch (contentsType) {
	case 0:
		contents = new TextFile;
		break;
	case 1:
		contents = new ImageFile;
		break;
	case 2:
		contents = new MusicFile;
		break;
	}
}

void FileType::setContentsType(int type) {
	contentsType = type;
	if (contents) delete contents;
	switch (contentsType) {
	case 0:
		contents = new TextFile;
		break;
	case 1:
		contents = new ImageFile;
		break;
	case 2:
		contents = new MusicFile;
		break;
	}
}

ItemType& FileType::operator=(ItemType& data) {
	FileType* tempPtr = dynamic_cast<FileType*> (&data);
	name = tempPtr->name;
	path = tempPtr->path;
	createTime = tempPtr->createTime;
	type = "file";
	contentsType = tempPtr->contentsType;
	if (contents) delete contents;
	switch (contentsType) {
	case 0:
		contents = new TextFile;
		contents = tempPtr->contents;
		break;
	case 1:
		contents = new ImageFile;
		contents = tempPtr->contents;
		break;
	case 2:
		contents = new MusicFile;
		contents = tempPtr->contents;
		break;
	}
	return *this;
}

void FileType::run() {
	system("color CF");
	contents->run(this->name);
}

void FileType::displayInfo() {
	using namespace std;

	cout << endl;
	cout << "\t ======= Current File Info =======" << endl;
	cout << "\t    file name : " << name << endl;
	cout << "\t    file path : " << path << endl;
	cout << "\t    created time : " << createTime << endl;
	cout << "\t =================================" << endl << endl;
}