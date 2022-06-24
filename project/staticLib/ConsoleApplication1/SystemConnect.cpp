#include "SystemConnect.h"

bool system::CopyDirFromPath(std::string folderName,
	std::string oldPath, std::string newPath)
{
	try
	{
		std::filesystem::copy(oldPath, newPath,
			std::filesystem::recursive);
		return true;
	}
	catch (...)
	{
		return false;
	}
}
bool system::CopyFileFromPath(std::string fileName, std::string extension,
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

bool system::CreateDirFromPath(std::string folderPath)
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

bool system::CreateFileFromPath(std::string name,
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

bool system::DeleteDirFromPath(std::string name, std::string folderPath)
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

bool system::DeleteFileFromPath(std::string name,
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

bool system::IsExist(std::string path)
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

bool system::IsValidName(std::string name)
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

bool system::ReadDirectory(Folder* root)
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

void system::ReadDirAndFile(Folder* root, std::string path)
{
	for (auto& elem : std::filesystem::directory_iterator(path))
	{
		if (elem.is_directory())
		{
			std::string dirName;
			std::string dirPath;

			dirName = elem.path().filename().u8string();
			dirPath = elem.path().u8string();

			Folder* inputDir = new Folder;

		}
	}
}

void system::RenameDirectory(std::string oldPath, std::string newPath);
void system::RenameFile(std::string oldPath, std::string newPath);