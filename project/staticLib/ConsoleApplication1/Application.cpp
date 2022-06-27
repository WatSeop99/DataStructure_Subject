#include "Application.h"

Application::Application()
{
	mRoot.SetName("root");
	mRoot.SetPath(".\\root");
	mCurFolder = &mRoot;
}

Application::~Application()
{
	mCurFolder = nullptr;
}

bool Application::AddItemFromWindow(const char* name, Item::eItemType type, void* param)
{
	Item* item;
	bool success = false;

	switch (type)
	{
	case Item::eItemType::Directory:
	{
		item = new Folder;
		item->SetName(name);
		item->SetPath(mCurFolder->GetPath() + '\\' + name);

		if (mCurFolder->Add(*item, type))
		{
			success = true;
		}
		delete item;
		break;
	}
	case Item::eItemType::File:
	{
		item = new File;
		item->SetName(name);

		File* newFile = dynamic_cast<File*>(item);
		if (((struct Parameter*)param)->Artist != nullptr)
		{
			item->SetPath(mCurFolder->GetPath() + '\\' + name + ".mp3");
			newFile->SetContentsType(Contents::eContentsType::Music);
			newFile->SetContents(Contents::eContentsType::Music, param);
		}
		else
		{
			item->SetPath(mCurFolder->GetPath() + '\\' + name + ".jpg");
			newFile->SetContentsType(Contents::eContentsType::Image);
			newFile->SetContents(Contents::eContentsType::Image, param);
		}

		if (mCurFolder->Add(*item, type))
		{
			success = true;
		}
		delete item;
		break;
	}
	default:
		break;
	}

	return success;
}

bool Application::ChangeFolNameFromWindow(const char* oldName, const char* newName)
{
	Item** data;
	Item* comp;
	std::string oldPath;
	std::string newPath;
	bool success;

	data = nullptr;
	comp = new Folder;
	comp->SetName(oldName);
	success = false;

	if (mRoot.RetrieveAll(*data, *comp))
	{
		int end;
		oldPath = (**data).GetPath();
		end = oldPath.find_last_of('\\');

		newPath = oldPath.substr(0, end) + newName;
		(**data).SetName(newName);
		systemfunc::RenameDirectory(oldPath, newPath);
		success = true;
	}

	delete comp;
	return success;
}

bool Application::ChangeFilNameFromWindow(const char* oldName, const char* newName)
{
	Item** data;
	Item* comp;
	std::string oldPath;
	std::string newPath;
	bool success;

	data = nullptr;
	comp = new File;
	comp->SetName(oldName);
	success = false;

	if (mRoot.RetrieveAll(*data, *comp))
	{
		int end;
		oldPath = (**data).GetPath();
		end = oldPath.find_last_of('\\');

		newPath = oldPath.substr(0, end) + newName;
		(**data).SetName(newName);
		systemfunc::RenameDirectory(oldPath, newPath);
		success = true;
	}

	delete comp;
	return success;
}

bool Application::DeleteItemFromWindow(const char* name, Item::eItemType type)
{
	Item** data;
	Item* comp;
	Folder* temp;
	bool success = false;

	switch (type)
	{
	case Item::eItemType::Directory:
		data = nullptr;
		comp = new Folder;
		temp = mCurFolder;
		comp->SetName(name);
		comp->SetType(Item::eItemType::Directory);
		mCurFolder = &mRoot;

		if (mCurFolder->RetrieveAll(*data, *comp))
		{
			mCurFolder = temp;
			if (mCurFolder->Delete(**data, Item::eItemType::Directory))
			{
				success = true;
			}
		}

		delete comp;
		break;
	case Item::eItemType::File:
		data = nullptr;
		comp = new File;
		temp = mCurFolder;
		comp->SetName(name);
		comp->SetType(Item::eItemType::File);
		mCurFolder = &mRoot;

		if (mCurFolder->RetrieveAll(*data, *comp))
		{
			mCurFolder = temp;
			if (mCurFolder->Delete(**data, Item::eItemType::File))
			{
				success = true;
			}
		}

		delete comp;
		break;
	default:
		break;
	}

	return success;
}

Folder* Application::GetCurFolder()
{
	return mCurFolder;
}

bool Application::OpencurFolderFromWindow(const char* name)
{
	Item** data;
	Item* comp;
	bool success;

	data = nullptr;
	comp = new Folder;
	success = false;
	comp->SetName(name);
	comp->SetType(Item::eItemType::Directory);

	if (mRoot.RetrieveAll(*data, *comp))
	{
		mCurFolder = dynamic_cast<Folder*>(*data);
		success = true;
	}

	delete comp;
	return success;
}

File* Application::RetrieveFileFromWindow(const char* name)
{
	Item** data;
	Item* comp;
	File* returnPtr;

	data = nullptr;
	comp = new File;
	returnPtr = nullptr;
	comp->SetName(name);
	comp->SetType(Item::eItemType::File);

	if (mCurFolder->RetrieveAll(*data, *comp))
	{
		returnPtr = dynamic_cast<File*>(*data);
	}

	delete comp;
	return returnPtr;
}

Folder* Application::RetrieveFolderFromWindow(const char* name)
{
	Item** data;
	Item* comp;
	Folder* returnPtr;

	data = nullptr;
	comp = new Folder;
	returnPtr = nullptr;
	comp->SetName(name);
	comp->SetType(Item::eItemType::Directory);

	if (mCurFolder->RetrieveAll(*data, *comp))
	{
		returnPtr = dynamic_cast<Folder*>(*data);
	}

	delete comp;
	return returnPtr;
}