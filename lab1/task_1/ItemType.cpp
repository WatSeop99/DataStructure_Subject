#include "ItemType.h"

void ItemType::SetRecord(int id, std::string name, std::string address) {
	SetId(id);
	SetName(name);
	SetAddress(address);
}

void ItemType::DisplayRecordOnScreen() {
	DisplayIdOnScreen();
	DisplayNameOnScreen();
	DisplayAddressOnScreen();
}

void ItemType::SetIdFromKB() {
	std::cout << "\tID : ";
	std::cin >> m_Id;
}

void ItemType::SetNameFromKB() {
	std::cout << "\tName : ";
	std::cin >> m_sName;
}

void ItemType::SetAddressFromKB() {
	std::cout << "\tAddress : ";
	std::cin >> m_sAddress;
}

void ItemType::SetRecordFromKB() {
	SetIdFromKB();
	SetNameFromKB();
	SetAddressFromKB();
}

bool ItemType::ReadDataFromFile(std::ifstream& fin) {
	fin >> m_Id >> m_sName >> m_sAddress;
	if (fin.fail())
		return false;
	fin.clear();
	return true;
}

bool ItemType::WriteDataToFile(std::ofstream& fout) {
	fout << m_Id << ' ' << m_sName << ' ' << m_sAddress << std::endl;
	return true;
}

RelationType ItemType::CompareByID(const ItemType& data) {
	if (m_Id > data.m_Id)
		return RelationType::GREATER;
	else if (m_Id < data.m_Id)
		return RelationType::LESS;
	else
		return RelationType::EQUAL;
}