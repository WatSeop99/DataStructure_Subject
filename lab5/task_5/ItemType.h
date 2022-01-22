#pragma once

#include <iostream>
#include <string>

class ItemType {
public:
	virtual void Run(std::string _name) = 0;
};