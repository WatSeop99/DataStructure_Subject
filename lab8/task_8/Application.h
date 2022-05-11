#pragma once

#include <iostream>
#include <string>

#include "CHeapBase.h"
#include "CMaxHeap.h"
#include "CMinHeap.h"
#include "FolderType.h"

class Application
{
public:
	Application();
	~Application();

	void Run();
	void WhatHeap();
	int GetCommand() const;
	int AddItem();
	int DeleteItem();
	int DequeueItem();
	void DisplayItem() const;
	int SearchItem();

private:
	CHeapBase<FolderType>* mList;
	int mCurCommand;
};