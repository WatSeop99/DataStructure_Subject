#pragma once

#include <iostream>
#include <exception>
#include <string>

class EmptyList : public std::exception {
private:
	std::string message;
public:
	EmptyList() : message("\t  ## List is Empty ##\n") { }
	virtual const char* what() const throw() { return message.c_str(); }
};

class FullList : public std::exception {
private:
	std::string message;
public:
	FullList() : message("\t  ## List is Full ##\n") { }
	virtual const char* what() const throw() { return message.c_str(); }
};

class EmptyQueue : public std::exception {
private:
	std::string message;
public:
	EmptyQueue() : message("\t  ## Queue is Empty ##\n") { }
	virtual const char* what() const throw() { return message.c_str(); }
};

class FullQueue : public std::exception {
private:
	std::string message;
public:
	FullQueue() : message("\t  ## Queue is Full ##\n") { }
	virtual const char* what() const throw() { return message.c_str(); }
};

class EmptyStack : public std::exception {
private:
	std::string message;
public:
	EmptyStack() : message("\t  ## Stack is Empty ##\n") { }
	virtual const char* what() const throw() { return message.c_str(); }
};

class FullStack : public std::exception {
private:
	std::string message;
public:
	FullStack() : message("\t  ## Stack is Full ##\n") { }
	virtual const char* what() const throw() { return message.c_str(); }
};