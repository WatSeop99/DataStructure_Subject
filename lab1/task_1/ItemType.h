#pragma once

#include <iostream>
#include <fstream>
#include <string>

enum class RelationType { LESS = 1, GREATER = 2, EQUAL = 3 };

class ItemType {
private:
	int m_Id;
	std::string m_sName;
	std::string m_sAddress;
public:
	ItemType(int id = 0, std::string name = "\0", std::string ad = "\0") : m_Id(id), m_sName(name), m_sAddress(ad)
	{ }
	~ItemType() { }

	int GetId() { return m_Id; }
	std::string GetName() { return m_sName; }
	std::string GetAddress() { return m_sAddress; }
	void SetId(int id) { m_Id = id; }
	void SetName(std::string name) { m_sName = name; }
	void SetAddress(std::string address) { m_sAddress = address; }
	void SetRecord(int id, std::string name, std::string address);
	void DisplayIdOnScreen() { std::cout << "\tID   : " << m_Id << std::endl; }
	void DisplayNameOnScreen() { std::cout << "\tName   : " << m_sName << std::endl; }
	void DisplayAddressOnScreen() { std::cout << "\tName   : " << m_sAddress << std::endl; }
	void DisplayRecordOnScreen();
	void SetIdFromKB();
	void SetNameFromKB();
	void SetAddressFromKB();
	void SetRecordFromKB();
	bool ReadDataFromFile(std::ifstream& fin);
	bool WriteDataToFile(std::ofstream& fout);
	RelationType CompareByID(const ItemType& data);
};