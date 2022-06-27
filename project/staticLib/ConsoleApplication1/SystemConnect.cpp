#include "SystemConnect.h"

bool systemfunc::CopyDirFromPath(std::string folderName,
	std::string oldPath, std::string newPath)
{
	try
	{
		std::filesystem::copy(oldPath, newPath,
			std::filesystem::copy_options::recursive);
		return true;
	}
	catch (...)
	{
		return false;
	}
}
bool systemfunc::CopyFileFromPath(std::string fileName, std::string extension,
	std::string oldPath, std::string newPath)
{
	try
	{
		std::filesystem::copy_file(oldPath, newPath);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

bool systemfunc::CreateDirFromPath(std::string folderPath)
{
	try
	{
		return std::filesystem::create_directories(folderPath);
	}
	catch (...)
	{
		return false;
	}
}

bool systemfunc::CreateFileFromPath(std::string name,
	std::string filePath, std::string extension)
{
	std::ofstream file;
	file.open(filePath + '\\' + name + "." + extension);

	if (file.fail())
	{
		file.close();
		return false;
	}
	else
	{
		file.close();
		return true;
	}
}

bool systemfunc::DeleteDirFromPath(std::string name, std::string folderPath)
{
	try
	{
		return std::filesystem::remove_all(folderPath);
	}
	catch (...)
	{
		return false;
	}
}

bool systemfunc::DeleteFileFromPath(std::string name,
	std::string filePath, std::string extension)
{
	try
	{
		return std::filesystem::remove_all(filePath);
	}
	catch (...)
	{
		return false;
	}
}

bool systemfunc::IsExist(std::string path)
{
	if (std::filesystem::exists(path))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool systemfunc::IsValidName(std::string name)
{
	if (name.find_first_of("\\/:*?\"<>|,.") == std::string::npos)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool systemfunc::ReadDirectory(Folder* root)
{
	std::string path = root->GetPath();

	try
	{
		ReadDirAndFile(root, path);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

void systemfunc::ReadDirAndFile(Folder* root, std::string path)
{
	for (auto& elem : std::filesystem::directory_iterator(path))
	{
		if (elem.is_directory())
		{
			std::string dirName;
			std::string dirPath;
			Folder* newFolder;
			Item* newItem;

			dirName = elem.path().filename().u8string();
			dirPath = elem.path().u8string();

			newFolder = new Folder;
			newFolder->SetName(dirName);
			newFolder->SetPath(dirPath);
			newItem = dynamic_cast<Item*>(newFolder);
			root->Add(*newItem, Item::eItemType::Directory);

			Item* found = nullptr;
			Folder* temp = root;
			if (root->RetrieveFolder(found, dirName))
			{
				root = dynamic_cast<Folder*>(found);
				ReadDirAndFile(root, root->GetPath());
				root = temp;
			}
			delete newFolder;
		}
		else
		{
			size_t end;
			std::string fileName;
			std::string fileExtention;
			std::string filePath;

			end = elem.path().filename().u8string().find_last_of('.');
			fileName = elem.path().filename().u8string().substr(0, end);
			fileExtention = elem.path().extension().u8string().erase(0, 1);
			filePath = elem.path().u8string();
			
			File* newFile;
			Item* item;
			struct Parameter param;

			newFile = new File;
			item = nullptr;
			param.Album = nullptr;
			param.Artist = nullptr;
			param.Event = nullptr;
			param.Lyrics = nullptr;

			newFile->SetName(fileName);
			newFile->SetPath(filePath);
			if (fileExtention.compare("jpg") == 0 || fileExtention.compare("png") == 0)
			{
				param.Event = new char[root->GetName().length() + 1];
				strcpy_s(param.Event, root->GetName().length() + 1, root->GetName().c_str());
				
				newFile->SetContentsType(Contents::eContentsType::Image);
				newFile->SetContents(Contents::eContentsType::Image, (void*)(&param));
				
				delete param.Event;
			}
			else if (fileExtention.compare("mp3") == 0)
			{
				size_t end2;
				std::string configFile;
				std::ifstream inFile;

				end2 = elem.path().u8string().find_last_of('.');
				configFile = filePath.substr(0, end2) + ".txt";
				inFile.open(configFile);
				newFile->SetContentsType(Contents::eContentsType::Music);

				std::string line;
				std::string lyrics;
				if (inFile.is_open())
				{
					param.Album = new char[root->GetName().length() + 1];
					strcpy_s(param.Album, root->GetName().length() + 1, root->GetName().c_str());

					getline(inFile, line);
					param.Artist = new char[line.length() + 1];
					strcpy_s(param.Artist, line.length() + 1, line.c_str());

					while (getline(inFile, line))
					{
						lyrics += line + '\n';
					}
					param.Lyrics = new char[lyrics.length() + 1];
					strcpy_s(param.Lyrics, lyrics.length() + 1, lyrics.c_str());

					newFile->SetContents(Contents::eContentsType::Music, (void*)(&param));

					delete param.Album;
					delete param.Artist;
					delete param.Lyrics;
				}
			}

			item = dynamic_cast<Item*>(newFile);
			root->Add(*item, Item::eItemType::File);

			delete newFile;
		}
	}
}

void systemfunc::RenameDirectory(std::string oldPath, std::string newPath)
{
	try
	{
		std::filesystem::rename(oldPath, newPath);
	}
	catch (...) { }
}

void systemfunc::RenameFile(std::string oldPath, std::string newPath)
{
	try
	{
		std::filesystem::rename(oldPath, newPath);
	}
	catch (...) { }
}