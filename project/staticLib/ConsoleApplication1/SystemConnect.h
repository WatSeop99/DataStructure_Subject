#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "Folder.h"

class Folder;

namespace systemfunc
{
	bool CopyDirFromPath(std::string folderName,
		std::string oldPath, std::string newPath);
	bool CopyFileFromPath(std::string fileName, std::string extension,
		std::string oldPath, std::string newPath);
	bool CreateDirFromPath(std::string folderPath);
	bool CreateFileFromPath(std::string name,
		std::string filePath, std::string extension);
	bool DeleteDirFromPath(std::string name, std::string folderPath);
	bool DeleteFileFromPath(std::string name,
		std::string filePath, std::string extension);
	bool IsExist(std::string path);
	bool IsValidName(std::string name);
	bool ReadDirectory(Folder* root);
	void ReadDirAndFile(Folder* root, std::string path);
	void RenameDirectory(std::string oldPath, std::string newPath);
	void RenameFile(std::string oldPath, std::string newPath);
}