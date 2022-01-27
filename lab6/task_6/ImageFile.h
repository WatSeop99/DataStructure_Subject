#pragma once

#include <Windows.h>
#include <gdiplus.h>
#include <wchar.h>
#include "ContentsType.h"
using namespace Gdiplus;

#pragma comment(lib, "Gdiplus.lib")

class ImageFile : public ContentsType {
public:
	ImageFile() : gdiplusToken(NULL), m_Graphics(nullptr), m_Image(nullptr) { }
	~ImageFile();

	void run(std::string _name);
	int getCommand();
	void drawingImage(std::string _name);
private:
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Graphics* m_Graphics;
	Image* m_Image;
};