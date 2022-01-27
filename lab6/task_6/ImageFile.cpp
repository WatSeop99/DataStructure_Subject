#pragma warning(disable : 4996)

#include "ImageFile.h"

ImageFile::~ImageFile() {
	if (m_Graphics) delete m_Graphics;
	if (m_Image) delete m_Image;
	GdiplusShutdown(gdiplusToken);
}

void ImageFile::run(std::string _name) {
	int command;
	while (true) {
		command = getCommand();
		switch (command) {
		case 1:
			drawingImage(_name);
			break;
		case 2:
			return;
		default:
			std::cout << "\t ## INVALID SELECTION ##" << std::endl;
			break;
		}
	}
}

int ImageFile::getCommand() {
	using namespace std;

	int command;
	cout << endl;
	cout << "\t ========= Image File Menu =========" << endl;
	cout << "\t    1.  read image file" << endl;
	cout << "\t    2.  quit" << endl;
	cout << "\t ===================================" << endl;
	cout << "\t Choose : ";
	cin >> command;
	return command;
}

void ImageFile::drawingImage(std::string _name) {
	std::string qCommand;
	// string to wchar* º¯È¯

	_name += ".jpg";
	// null-call to get the size
	size_t needed = ::mbstowcs(NULL, &_name[0], _name.length());

	// allocate
	std::wstring output;
	output.resize(needed);

	// real call
	::mbstowcs(&output[0], &_name[0], _name.length());

	// You asked for a pointer
	const wchar_t* fileName = output.c_str();

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	if (m_Graphics == nullptr) m_Graphics = new Graphics(GetDC(GetConsoleWindow()));
	if (m_Image == nullptr) m_Image = m_Graphics ? new Image(fileName) : nullptr;
	if (m_Image) {
		system("cls");
		m_Graphics->DrawImage(m_Image, 200, 10, m_Image->GetWidth() / 2, m_Image->GetHeight() / 2);
		for (int i = 0; i < 30; i++)
			std::cout << std::endl;
		std::cout << "\t  Press any key if you quit : ";
		std::cin >> qCommand;
	}
	else std::cout << "\t  ## Roading Error ##" << std::endl;
}