#pragma once
#include <stddef.h>

class Array
{
private:
	int* array;
	size_t size;
public:
	int* returnArray();

	void pushFront(int value);

	void pushBack(int value);

	void push(int value, size_t index);

	void popFront();

	void popBack();

	void pop(int index);

	void fSwap(int indexa, int indexb);

	void swap(int indexa, int indexb);

	bool search(int number);

	void write(int index, int value);

	int returnValue(int index);

	void copy(Array* array);

	size_t returnSize();

	void display();

	void erase();

	Array();

	~Array();

};

