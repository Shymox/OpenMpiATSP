#pragma once
#include <string>
#include <stddef.h>

struct ListElem
{
	int node;
	ListElem*prev, *next;
};
class List
{
private:
	int size;
	ListElem* head, * tail;
	void popElem(ListElem* elem);

public:
	void random(int size);

	void load(std::string name);

	void pushFront(int node);

	void pushBack(int node);

	void push(int node, size_t index);

	void popFront();

	void popBack();

	void pop(int index);

	void popNumber(int number);

	bool search(int number);

	bool isEmpty();

	int returnFNode();

	int returnNode(int i);

	int returnSize();

	int returnLNode();

	ListElem* returnHead();

	void display();

	void display2();

	void erase();

	List();

	~List();

};

