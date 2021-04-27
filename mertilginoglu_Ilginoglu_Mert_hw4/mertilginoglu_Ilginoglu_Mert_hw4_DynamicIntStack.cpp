//This code was taken from week 5's lesson code, "DynIntStack.cpp".
//Push and pop was updated according to having 2 integer variables as parameters.
//Destructor was also added.


#include <iostream>
#include "mertilginoglu_Ilginoglu_Mert_hw4_DynamicIntStack.h"
using namespace std;

//************************************************
// Constructor to generate an empty stack.       *
//************************************************
DynIntStack::DynIntStack()
{
	top = NULL; 
}

DynIntStack::~DynIntStack()
{
	StackNode *temp;
	while(top != NULL)
	{
		temp = top->next;
		delete top;
		top = temp;
	}
}

//************************************************
// Member function push pushes the argument onto *
// the stack.                                    *
//************************************************
void DynIntStack::push(int rowNumber, int colNumber)
{
	StackNode *newNode;

	// Allocate a new node & store Num
	newNode = new StackNode;
	newNode->rowValue = rowNumber;
	newNode->colValue = colNumber;

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
}

//****************************************************
// Member function pop pops the value at the top     *
// of the stack off, and copies it into the variable *
// passed as an argument.                            *
//****************************************************
void DynIntStack::pop(int &rowNumber, int &colNumber)
{
	StackNode *temp;

	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else	// pop value off top of stack
	{
		rowNumber = top->rowValue;
		colNumber = top->colValue;
		temp = top->next;
		delete top;
		top = temp;
		/*
		if(top != NULL)
		{
		rowNumber = top->rowValue;
		colNumber = top->colValue;
		}
		*/
	}
}

//****************************************************
// Member funciton isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************
bool DynIntStack::isEmpty(void)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}

