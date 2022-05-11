#include "Application.h"

Application::Application()
{
	mCurCommand = 0;
}

Application::~Application()
{

}

void Application::Run()
{
	WhatHeap();

	while (true)
	{
		mCurCommand = GetCommand();

		switch (mCurCommand)
		{
		case 1:
			AddItem();
			break;
		case 2:
			DeleteItem();
			break;
		case 3:
			DequeueItem();
			break;
		case 4:
			DisplayItem();
			break;
		case 5:
			SearchItem();
			break;
		case 0:
			return;
		default:
			std::cout << "\t Illegal sellection... \n";
			break;
		}
	}
}

void Application::WhatHeap()
{
	int command;

	std::cout << std::endl << std::endl;
	std::cout << "\t---Id -- Command ----- " << std::endl;
	std::cout << "\t   1 : Max Heap" << std::endl;
	std::cout << "\t   2 : Min Heap" << std::endl;
	std::cout << "\t   0 : Quit" << std::endl;
	
	std::cout << std::endl << "\t Choose a Command -->";
	std::cin >> command;
	std::cout << std::endl;

	switch (command)
	{
	case 1:
		mList = new CMaxHeap<FolderType>(10);
		break;
	case 2:
		mList = new CMinHeap<FolderType>(10);
		break;
	case 0:
		return;
	default:
		std::cout << "\t Illegal sellection... \n";
		break;
	}
}
int Application::GetCommand() const
{
	int command;

	std::cout << std::endl << std::endl;
	std::cout << "\t---ID -- Command ----- " << std::endl;
	std::cout << "\t   1 : Add folder" << std::endl;
	std::cout << "\t   2 : Delete folder" << std::endl;
	std::cout << "\t   3 : Dequeue folder" << std::endl;
	std::cout << "\t   4 : Display folder" << std::endl;
	std::cout << "\t   5 : Search folder" << std::endl;
	std::cout << "\t   0 : Quit " << std::endl;

	std::cout << std::endl << "\t Choose a Command--> ";
	std::cin >> command;
	std::cout << std::endl;

	return command;
}

int Application::AddItem()
{
	FolderType item;
	item.SetRecordFromKB();

	if (mList->IsFull() == false)
	{
		mList->Add(item);
		return 1;
	}
	else
	{
		std::cout << "\t Empty!!!" << std::endl;
		return 0;
	}
}

int Application::DeleteItem()
{
	if (mList->IsEmpty() == false)
	{
		FolderType item;
		item.SetNameFromKB();

		if (mList->Delete(item) == false)
		{
			std::cout << "\n\t No Data" << std::endl;
		}

		return 1;
	}
	else
	{
		std::cout << "\t Empty!!!" << std::endl;
		return 0;
	}
}

int Application::DequeueItem()
{
	if (mList->IsEmpty() == false)
	{
		mList->Dequeue();
		return 1;
	}
	else
	{
		std::cout << "\t Empty!!!" << std::endl;
		return 0;
	}
}

void Application::DisplayItem() const
{
	if (mList->IsEmpty() == false)
	{
		mList->PrintHeap();
	}
	else
	{
		std::cout << "\t Empty!!!" << std::endl;
	}
}

int Application::SearchItem()
{
	FolderType item;
	bool found = false;

	if (mList->IsEmpty() == false)
	{
		item.SetNameFromKB();
		mList->RetrieveItem(item, found);

		if (found)
		{
			std::cout << "\n\t Found!!!" << std::endl;
			item.DisPlayRecordOnScreen();
		}
		else
		{
			std::cout << "\n\t No Data" << std::endl;
		}
		
		return 1;
	}
	else
	{
		std::cout << "\t Empty!!!" << std::endl;
		return 0;
	}
}