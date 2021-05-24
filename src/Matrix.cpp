#include "Matrix.h"
#include <iostream>
#include <curses.h>
#include <time.h>
#include <fstream>
#include <limits.h>

void Matrix::bruteForce(int last)
{
	this->array->fSwap(this->array->returnSize()-1,last);
	//this->array->display();
	generatePerm(this->array->returnSize()-1);
	//this->displayAnsBF();
}
void Matrix::displayAnsBF()
{
	for (int i = this->answers->returnSize() - 2; i >=0 ; i--)
	{
		int j = this->answers->returnNode(i);
		std::cout << j << "(" << 100 * static_cast<float>(j) / this->optimum << "%)\n";
	}
	std::cout << "0 ";
	this->sequence->display();
	std::cout << "\n";
}

//dodanie krawedzi do macierz
void Matrix::push(int value,size_t start,size_t end)
{
 		this->matrix[end][start] = value;
		this->number++;
}
void Matrix::setOptimum(long optimum)
{
	this->optimum = optimum;
}
int Matrix::getOptimum()
{
	return this->optimum;
}
//inicjalizacja macierzy o podanej liczbie wierzcho�k�w
void Matrix::init(int size)
{
	this->erase();
	this->sequence = new Array();
	this->array = new Array();
	this->answers = new List();
	this->answers->pushFront(INT_MAX);
	this->size = size;
	for (int i = 1; i < this->size; i++)
	{
		array->pushBack(i);
	}
	this->matrix = new int* [this->size];
	for (size_t i = 0;i < this->size;i++)
	{
		this->matrix[i] = new int[this->size];
		for (size_t j = 0;j < this->size;j++)
		{
			this->matrix[i][j]=0;
		}
	}
}
//wymazanie zawarto�ci macierzy
void Matrix::erase()
{
	if (this->matrix != nullptr)
	{
		for (size_t i = 0;i < this->size;i++)
		{
			delete[] this->matrix[i];
		}
		delete[] this->matrix;
	}
	if (this->sequence != nullptr)
	{
		delete this->sequence;
	}
	if (this->array != nullptr)
	{
		delete this->array;
	}
	if (this->answers != nullptr)
	{
		delete this->answers;
	}
	this->sequence = nullptr;
	this->array = nullptr;
	this->answers = nullptr;
	this->matrix = nullptr;
	this->size = 0;
	this->start = 0;
	this->number = 0;
}


int Matrix::countPermLeft()
{
	int count = 0;
	count += this->matrix[0][this->array->returnValue(0)];
	for (int i = 1; i < this->array->returnSize(); i++)
	{
		count += this->matrix[this->array->returnValue(i-1)][this->array->returnValue(i)];
	}
	count += this->matrix[this->array->returnValue(this->array->returnSize() - 1)][0];
	return count;
}
int Matrix::getValue(size_t start, size_t end)
{
	if (start >= 0 && start < this->size && end >= 0 && end < this->size)
		return this->matrix[end][start];
	return 0;
}
void Matrix::generatePerm(int size)
{
	if (size == 1)
	{
		int j = this->countPermLeft();
		if (j < this->answers->returnFNode())
		{
			this->answers->pushFront(j);
			this->sequence->copy(this->array);
		}
		return;
	}

		for (int i=0;i<size;i++)
		{
			generatePerm(size - 1);
			if (size % 2)
			{
				this->array->fSwap(i, size - 1);
			}
			else
			{
				this->array->fSwap(0, size - 1);
			}
		}
}

int Matrix::returnSize()
{
	return this->size;
}
//wy�wietlenie zawarto�ci macierzy
void Matrix::display()
{
	if (this->matrix!=nullptr)
	{
		for (size_t i = 0; i < this->size; i++)
		{
			for (size_t j = 0; j < this->size; j++)
			{
				std::cout << matrix[j][i] << " ";
			}
			std::cout << "\n";
		}
	}
	std::cout << "Optimum: " << optimum << "\n";
}

int* Matrix::returnSequence()
{
	return this->sequence->returnArray();
}

int Matrix::answer()
{
	return this->answers->returnNode(0);
}

void Matrix::reset()
{
	if (this->sequence != nullptr)
	{
		delete this->sequence;
	}
	if (this->array != nullptr)
	{
		delete this->array;
	}
	if (this->answers != nullptr)
	{
		delete this->answers;
	}
	this->sequence = new Array();
	this->array = new Array();
	this->answers = new List();
	this->answers->pushFront(INT_MAX);
	for (int i = 1; i < this->size; i++)
	{
		array->pushBack(i);
	}
}



//konstruktor Matrix
Matrix::Matrix()
{
	this->sequence = nullptr;
	this->array = nullptr;
	this->answers = nullptr;
	this->matrix = nullptr;
	this->size = 0;
	this->start = 0;
	this->number = 0;
	this->optimum = INT_MAX;
	
}
//destruktor Matrix
Matrix::~Matrix()
{
	this->erase();
}
