#include "Array.h"
#include <iostream>

int* Array::returnArray()
{
	return this->array;
}

void Array::pushFront(int value)
{
	
	int* temp = new int[this->size+1];
	*temp = value;
	for (size_t i = 1;i <=size;i++)
	{
		temp[i] = this->array[i - 1];
	}
	delete[] this->array;
	this->size++;
	this->array = temp;
}

void Array::pushBack(int value)
{
	int* temp = new int[this->size + 1];
	temp[size]=value;
	for (size_t i = 0;i < size;i++)
	{
		temp[i] = this->array[i];
	}
	delete[] this->array;
	this->size++;
	this->array = temp;
}

void Array::push(int value, size_t index)
{
	if (index <= size)
	{
		int* temp = new int[size + 1];
		temp[index] = value;
		for (size_t i = 0;i < index;i++)
		{
			temp[i] = this->array[i];
		}
		for (size_t i = index;i < this->size;i++)
		{
			temp[i + 1] = this->array[i];
		}
		delete[] this->array;
		this->array = temp;
		this->size++;
	}
}

void Array::popFront()
{
	if (size > 0)
	{
		this->size--;
		int* temp = new int[size];
		for (size_t i = 0;i < size;i++)
		{
			temp[i] =this->array[i + 1];
		}
		delete[] this->array;
		this->array = temp;
	}
}

void Array::popBack()
{
	if (size > 0)
	{
		this->size--;
		int* temp = new int[size];
		for (size_t i = 0;i < size; i++)
		{
			temp[i] = this->array[i];
		}
		delete[] this->array;
		this->array = temp;
	}
}

void Array::pop(int index)
{
	if (size > 0||index<size)
	{
		this->size--;
		int* temp = new int[size];
		for (size_t i = 0;i < index;i++)
		{
			temp[i] = this->array[i];
		}
		for (size_t i = index;i < size;i++)
		{
			temp[i] = this->array[i + 1];
		}
		delete[] this->array;
		this->array = temp;
	}
}

void Array::fSwap(int indexa, int indexb)
{
	int temp = this->array[indexa];
	this->array[indexa] = this->array[indexb];
	this->array[indexb] = temp;
}

void Array::swap(int indexA, int indexB)
{
	if (indexA < this->size && indexB <this->size && indexA>=0 && indexB>=0)
	{
		int temp = this->array[indexA];
		this->array[indexA]=this->array[indexB];
		this->array[indexB]=temp;
	}
}

bool Array::search(int number)
{
	for (int i = 0;i < this->size;i++)
	{
		if (this->array[i] == number)
		{
			return true;
		}
	}
	return false;
}
void Array::write(int index,int value)
{
	if (index >= 0 && index < this->size)
	{
		this->array[index] = value;
	}
}

int Array::returnValue(int index)
{
	if(this->size>index) return array[index];
	return 0;
}

void Array::copy(Array* array)
{
	this->erase();
	for (size_t i = 0; i < array->returnSize(); i++)
	{
		this->pushBack(array->returnValue(i));
	}
	this->returnSize();
}

size_t Array::returnSize()
{
	return this->size;
}


void Array::display()
{
	for (size_t i = 0;i <this->size;i++)
	{
		std::cout << this->array[i] << " ";
	}
}

void Array::erase()
{
	if (this->array != nullptr)
	{
		delete[] this->array;
	}
	this->array = nullptr;
	this->size = 0;
}

Array::Array()
{
	this->array = new int[0];
	this->size = 0;
}

Array::~Array()
{
	this->erase();
}
