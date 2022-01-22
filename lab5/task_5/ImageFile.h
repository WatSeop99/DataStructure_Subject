#pragma once

#include <Windows.h>
#include <gdiplus.h>
#include <wchar.h>
#include "ItemType.h"
using namespace Gdiplus;

#pragma comment(lib, "Gdiplus.lib")

class ImageFile : public ItemType {
private:
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Graphics* m_Graphics;
	Image* m_Image;
public:
	ImageFile() : gdiplusToken(NULL), m_Graphics(nullptr), m_Image(nullptr) { }
	~ImageFile();

	void Run(std::string name);
	int GetCommand();
	void DrawingImage(std::string name);
};