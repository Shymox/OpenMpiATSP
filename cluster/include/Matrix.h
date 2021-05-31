
#include <string>
#include "List.h"
#include "Array.h"
#include <stddef.h>

class Matrix
{
private:
	int size;
	size_t number;
	size_t start;
	int optimum;
	List* answers;
	Array* array;
	Array* sequence;

public:
	int** matrix;

	void bruteForce(int last);

	void displayAnsBF();

	void push(int value, size_t start, size_t end);

	void setOptimum(long optimum);

	int getOptimum();

	void init(int size);

	void erase();

	int countPermLeft();

	int getValue(size_t start, size_t end);

	void generatePerm(int size);

	int returnSize();

	void display();

	int* returnSequence();

	int answer();
	
	void reset();

	Matrix();

	~Matrix();

};

