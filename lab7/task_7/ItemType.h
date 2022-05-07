#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

class ItemType {
public:
	ItemType() : name(""), path(""), createTime(""), type("") {
		genCreateTime();
	}

	void setRecordFromKB() {
		std::string input;
		std::cout << "\t Enter Item name : ";
		std::cin >> input;
		name = input;
	}
	void setName(std::string _name) { name = _name; }
	void setPath(std::string _path) { path = _path; }
	void setCreateTime(std::string _time) { createTime = _time; }
	void setType(std::string _type) { type = _type; }
	void genCreateTime() {
		using namespace std;

		time_t curr_time;
		struct tm* curr_tm;
		curr_time = time(NULL);
		curr_tm = localtime(&curr_time);
		string year = to_string(curr_tm->tm_year + 1900) + "년 ";
		string month = to_string(curr_tm->tm_mon + 1) + "월 ";
		string day = to_string(curr_tm->tm_mday) + "일 / ";
		string hour = to_string(curr_tm->tm_hour) + "시 ";
		string minute = to_string(curr_tm->tm_min) + "분 ";
		string second = to_string(curr_tm->tm_sec) + "초 ";
		string curTime = year + month + day + hour + minute + second;
		createTime = curTime;
	}
	std::string getName() const { return name; }
	std::string getPath() const { return path; }
	std::string getCreateTime() const { return createTime; }
	std::string getType() const { return type; }
	virtual ItemType& operator=(ItemType& data) = 0;
	bool operator<(const ItemType& comp) { return name.compare(comp.name) > 0; }
	bool operator>(const ItemType& comp) { return name.compare(comp.name) < 0; }
	bool operator==(const ItemType& comp) { return (name.compare(comp.name) == 0) && (type.compare(comp.type) == 0); }
	friend std::ostream& operator<<(std::ostream& os, const ItemType& data) {
		os << data.name;
		return os;
	}
	virtual void displayInfo() = 0;
protected:
	std::string name;
	std::string path;
	std::string createTime;
	std::string type;
};