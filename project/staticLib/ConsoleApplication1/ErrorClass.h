#pragma once

#include <exception>
#include <iostream>
#include <string>

class EmptyQueue : public std::exception
{
public:
	EmptyQueue() : mMessage("\t ## Queue is empty. ##")
	{
	}

	virtual const char* what() const throw()
	{
		return mMessage.c_str();
	}

private:
	std::string mMessage;
};

class FullQueue : public std::exception
{
public:
	FullQueue() : mMessage("\t ## Queue is full. ##")
	{
	}

	virtual const char* what() const throw()
	{
		return mMessage.c_str();
	}

private:
	std::string mMessage;
};

class EmptyStack : public std::exception
{
public:
	EmptyStack() : mMessage("\t ## Stack is full. ##")
	{
	}

	virtual const char* what() const throw()
	{
		return mMessage.c_str();
	}

private:
	std::string mMessage;
};

class FullStack : public std::exception
{
public:
	FullStack() : mMessage("\t ## Stack is full. ##")
	{
	}

	virtual const char* what() const throw()
	{
		return mMessage.c_str();
	}

private:
	std::string mMessage;
};

class EmptyBST : public std::exception
{
public:
	EmptyBST() : mMessage("\t ## BST is empty. ##")
	{

	}

	virtual const char* what() const throw()
	{
		return mMessage.c_str();
	}

private:
	std::string mMessage;
};

class FullBST : public std::exception
{
public:
	FullBST() : mMessage("\t ## BST is full. ##")
	{

	}

	virtual const char* what() const throw()
	{
		return mMessage.c_str();
	}

private:
	std::string mMessage;
};