#pragma once

#include <string>

template <class Type>
class CompareType {
public:
	CompareType(std::string key = "name") { keyValue = key; }

	void setKey(std::string key) { keyValue = key; }
	std::string getKey() const { return keyValue; }
	int compare(Type& data1, Type& data2) const;
private:
	std::string keyValue;
};

template <class Type>
int CompareType<Type>::compare(Type& data1, Type& data2) const {
	if (keyValue.compare("name") == 0) {
		if (*data1 < *data2) return -1;
		else if (*data1 == *data2) return 0;
	}
	return 1;