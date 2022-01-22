#pragma warning(disable : 4996)

#include "ImageFile.h"

ImageFile::~ImageFile() {
	if (m_Graphics != nullptr) delete m_Graphics;
	if (m_Image != nullptr) delete m_Image;
	GdiplusShutdown(gdiplusToken);
}

void ImageFile::Run(std::string name) {
	int command;
	while (true) {
		command = GetCommand();
		switch (command) {
		case 1:
			DrawingImage(name);
			break;
		case 2:
			return;
		default:
			std::cout << "\t ## Illegal selection... ##" << std::endl;
			break;
		}
	}
}

int ImageFile::GetCommand() {
	using namespace std;

	int command;
	cout << endl;
	cout << "\t  ==========================" << endl;
	cout << "\t  || Image 파일 작업 메뉴 ||" << endl;
	cout << "\t  ===========================================================================" << endl;
	cout << "\t     1.  Image 읽어오기" << endl;
	cout << "\t     2.  Image 파일 종료" << endl;
	cout << "\t  ===========================================================================" << endl;
	cout << "\t   작업 선택 : ";
	cin >> command;
	return command;
}

void ImageFile::DrawingImage(std::string name) {
	std::string qCommand;
	// string to wchar* 변환

	name += ".jpg";
	// null-call to get the size
	size_t needed = ::mbstowcs(NULL, &name[0], name.length());

	// allocate
	std::wstring output;
	output.resize(needed);

	// real call
	::mbstowcs(&output[0], &name[0], name.length());

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
		std::cout << "\t  종료 하려면 아무키나 누르시오 : ";
		std::cin >> qCommand;
	}
	else std::cout << "\t  ## Roading Error ##" << std::endl;
}