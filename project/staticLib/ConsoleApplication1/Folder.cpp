#include "Folder.h"

Folder::Folder()
{
	mType = Item::eItemType::Directory;
	mList = nullptr;
}

Folder::Folder(Item& data)
{
	Folder* input = dynamic_cast<Folder*>(&data);

	mName = input->mName;
	mPath = input->mPath;
	mCreationTime = input->mCreationTime;
	mModifiedTime = GenTime();
	mType = input->mType;

	if (input->mList->GetLength() != 0)
	{
		mList = new BinarySearchTree<Item*>;
		*mList = *(input->mList);
	}
	else
	{
		mList = nullptr;
	}
}

Folder::~Folder()
{
	if (mList != nullptr)
	{
		delete mList;
		mList = nullptr;
	}
}

bool Folder::Add(Item& data, Item::eItemType type)
{
	if (mList == nullptr)
	{
		mList = new BinarySearchTree<Item*>;
	}

	bool success = false;
	switch (type)
	{
	case Item::eItemType::Directory:
	{
		Item* newFolder = new Folder;
		*newFolder = data;

		if (mList->Add(&newFolder))
		{
			if (systemfunc::IsExist(newFolder->GetPath()) == false)
			{
				systemfunc::CreateDirFromPath(newFolder->GetPath());
			}

			success = true;
		}

		delete newFolder;
		break;
	}
	case Item::eItemType::File:
	{
		Item* newFile = new File;
		*newFile = data;

		if (mList->Add(&newFile))
		{
			File* musicFile = dynamic_cast<File*>(newFile);
			if (musicFile->GetContentsType() == Contents::eContentsType::Music)
			{
				std::string filePath;
				std::string configPath;
				int end;

				filePath = musicFile->GetPath();
				end = filePath.find_last_of('.');
				configPath = filePath.substr(0, end) + ".txt";

				std::ofstream outFile(configPath);
				if (outFile.is_open())
				{
					struct Parameter param;
					param.Album = nullptr;
					param.Artist = nullptr;
					param.Event = nullptr;
					param.Lyrics = nullptr;

					musicFile->GetContents(Contents::eContentsType::Music,
						(void*)(&param));
					outFile << param.Artist << '\n';
					outFile << param.Lyrics;
				}
				outFile.close();
			}

			success = true;
		}

		delete newFile;
		break;
	}
	default:
		break;
	}

	return success;
}

bool Folder::Copy(Item* outData, std::string name, Item::eItemType type) const
{
	if (outData != nullptr)
	{
		delete outData;
		outData = nullptr;
	}

	bool success = false;
	switch (type)
	{
	case Item::eItemType::Directory:
	{
		Item* copiedFolder = new Folder;
		copiedFolder->SetName(name);

		if (mList->GetLength() != 0 && mList->Get(copiedFolder))
		{
			outData = new Folder;
			*outData = *copiedFolder;

			success = true;
		}

		delete copiedFolder;
		break;
	}
	case Item::eItemType::File:
	{
		Item* copiedFile = new File;
		copiedFile->SetName(name);

		if (mList->GetLength() != 0 && mList->Get(copiedFile))
		{
			outData = new File;
			*outData = *copiedFile;

			success = true;
		}

		delete copiedFile;
		break;
	}
	default:
		break;
	}

	return success;
}

bool Folder::Delete(Item& data, Item::eItemType type)
{
	bool success = false;
	switch (type)
	{
	case Item::eItemType::Directory:
	{
		Item* trashFolder = new Folder;
		*trashFolder = data;

		if (mList->Remove(trashFolder))
		{
			if (systemfunc::IsExist(trashFolder->GetName()))
			{
				systemfunc::DeleteDirFromPath(trashFolder->GetName(),
					trashFolder->GetPath());
			}
			success = true;
		}

		delete trashFolder;
		break;
	}
	case Item::eItemType::File:
	{
		Item* trashFile = new File;
		*trashFile = data;

		if (mList->Remove(trashFile))
		{
			if (systemfunc::IsExist(trashFile->GetName()))
			{
				File* delFile;
				int end;
				std::string filePath;

				delFile = dynamic_cast<File*>(&data);
				end = delFile->GetPath().find_last_of('.');
				filePath = delFile->GetPath().substr(0, end);

				if (delFile->GetContentsType() == Contents::eContentsType::Image)
				{
					systemfunc::DeleteFileFromPath(delFile->GetName(),
						delFile->GetPath(), "jpg");
					systemfunc::DeleteFileFromPath(delFile->GetName(),
						delFile->GetPath() + ".txt", "txt");
				}
				else if (delFile->GetContentsType() == Contents::eContentsType::Music)
				{
					systemfunc::DeleteFileFromPath(delFile->GetName(),
						delFile->GetPath(), "mp3");
					systemfunc::DeleteFileFromPath(delFile->GetName(),
						delFile->GetPath() + ".txt", "txt");
				}
				
			}

			success = true;
		}

		delete trashFile;
		break;
	}
	default:
		break;
	}

	return success;
}

int Folder::GetLength() const
{
	return mList->GetLength();
}

void Folder::PathUpdate(Folder* folder, std::string path)
{
	for (int i = 0; i < folder->GetLength(); i++)
	{
		Item* item;
		bool found = false;

		folder->mList->ResetTree();
		item = folder->mList->GetNextItem(found);
		if (found)
		{
			Folder* update;

			item->SetPath(path + '\\' + item->GetName());
			update = dynamic_cast<Folder*>(item);
			PathUpdate(update, item->GetPath());
		}
	}
}

bool Folder::Paste(Item* data, Item::eItemType select)
{
	if (mList == nullptr)
	{
		mList = new BinarySearchTree<Item*>;
	}

	int i = 0;
	bool success = false;

	switch (select)
	{
	case Item::eItemType::Directory:
	{
		Item* overlapFolder;

		overlapFolder = new Folder;
		overlapFolder->SetName(data->GetName());

		while (mList->Get(overlapFolder))
		{
			i++;
			overlapFolder->SetName(data->GetName() + '(' + std::to_string(i) + ')');
		}
		data->SetName(overlapFolder->GetName());
		delete overlapFolder;

		Folder* newFolder;
		std::string oldPath = data->GetPath();

		newFolder = dynamic_cast<Folder*>(data);

		if (mList->Add(&data))
		{
			if (std::filesystem::exists(GetPath() + '\\' + newFolder->GetName()) == false)
			{
				systemfunc::CopyDirFromPath(newFolder->GetName(), oldPath,
					GetPath() + '\\' + data->GetName());
			}
			PathUpdate(newFolder, GetPath() + '\\' + data->GetName());
			success = true;
		}
		break;
	}
	case Item::eItemType::File:
	{
		Item* overlapFile;

		overlapFile = new File;
		overlapFile->SetName(data->GetName());

		while (mList->Get(overlapFile))
		{
			i++;
			overlapFile->SetName(data->GetName() + '(' + std::to_string(i) + ')');
		}
		data->SetName(overlapFile->GetName());
		data->SetPath(GetPath());
		delete overlapFile;

		File* newFile = dynamic_cast<File*>(data);
		if (mList->Add(&data))
		{
			switch (newFile->GetContentsType())
			{
			case Contents::eContentsType::Image:
				systemfunc::CopyFileFromPath(newFile->GetName(),
					"jpg", newFile->GetPath(), GetPath());
				break;
			case Contents::eContentsType::Music:
				systemfunc::CopyFileFromPath(newFile->GetPath(),
					"mp3", newFile->GetPath(), GetPath());
				break;
			default:
				break;
			}

			success = true;
		}
		break;
	}
	default:
		break;
	}

	return success;
}

bool Folder::RetrieveAll(Item* outData, Item& comp)
{
	if (mList == nullptr || mList->GetLength() == 0)
	{
		outData = nullptr;
		return false;
	}

	bool success = false;
	switch (comp.GetType())
	{
	case Item::eItemType::Directory:
		mList->ResetTree();
		for (int i = 0; i < mList->GetLength(); i++)
		{
			Item* item;
			Folder* childFolder;

			item = mList->GetNextItem(success);
			if (item->GetType() == Item::eItemType::Directory)
			{
				CompareType<Item*> comparer;
				Item* compPtr = &comp;

				childFolder = dynamic_cast<Folder*>(item);
				if (comparer.Compare(item, compPtr) == 0)
				{
					outData = item;
					success = true;
					break;
				}
				if (childFolder->RetrieveAll(outData, comp))
				{
					success = true;
					break;
				}
			}
		}
		break;
	case Item::eItemType::File:
		mList->ResetTree();
		for (int i = 0; i < mList->GetLength(); i++)
		{
			Item* item;
			Folder* childFolder;

			item = mList->GetNextItem(success);
			if (item->GetType() == Item::eItemType::File)
			{
				CompareType<Item*> comparer;
				Item* compPtr = &comp;

				if (comparer.Compare(item, compPtr) == 0)
				{
					outData = item;
					success = true;
					break;
				}
			}
			else
			{
				childFolder = dynamic_cast<Folder*>(item);
				if (childFolder->RetrieveAll(outData, comp))
				{
					success = true;
					break;
				}
			}
		}
		break;
	default:
		break;
	}

	return success;
}

bool Folder::RetrieveFile(Item* outData, std::string name)
{
	if (mList == nullptr)
	{
		return false;
	}

	Item* found;
	bool success;

	found = new File;
	success = false;
	found->SetType(Item::eItemType::File);
	found->SetName(name);

	mList->GetPtr(&outData, found);
	if (outData != nullptr)
	{
		success = true;
	}
	delete found;

	return success;
}

bool Folder::RetrieveFolder(Item* outData, std::string name)
{
	if (mList == nullptr)
	{
		return false;
	}

	Item* found;
	bool success;

	found = new Folder;
	success = false;
	found->SetType(Item::eItemType::Directory);
	found->SetName(name);

	mList->GetPtr(&outData, found);
	if (outData != nullptr)
	{
		success = true;
	}
	delete found;

	return success;
}

Item& Folder::operator=(Item& data)
{
	Folder* input = dynamic_cast<Folder*>(&data);

	mName = input->mName;
	mPath = input->mPath;
	mCreationTime = input->mCreationTime;
	mModifiedTime = GenTime();
	mType = input->mType;

	if (input->GetLength() != 0)
	{
		if (mList == nullptr)
		{
			mList = new BinarySearchTree<Item*>;
		}
		else
		{
			delete mList;
			mList = new BinarySearchTree<Item*>;
		}

		*mList = *(input->mList);
	}
	else
	{
		mList = nullptr;
	}

	return *this;
}