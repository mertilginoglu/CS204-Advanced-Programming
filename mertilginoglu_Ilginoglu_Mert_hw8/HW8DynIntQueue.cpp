#include <iostream>
#include "HW8DynIntQueue.h"
using namespace std;

//************************************************
// Constructor. Generates an empty queue         *
//************************************************
HW8DynIntQueue::HW8DynIntQueue()
{
	front = NULL;
	rear = NULL;
	currentSize = 0;
}



//************************************************
// Copy Constructor.                             *
//************************************************
HW8DynIntQueue::HW8DynIntQueue(const HW8DynIntQueue& rhs)
{
	front = NULL;
	rear = NULL;
	currentSize = 0;

	if(!rhs.isEmpty())
	{
		currentSize = 0;
		CustomerNode* tmp = rhs.front;
		while (tmp != NULL)
		{
			enqueue(tmp->customerId);
			tmp = tmp->next;
		}
	}
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void HW8DynIntQueue::enqueue(int num)
{
	 if (isEmpty())   //if the queue is empty
	{	//make it the first element
		front = new CustomerNode(num);
		rear = front;
		currentSize++;

	}
	else  //if the queue is not empty
	{	//add it after rear
		rear->next = new CustomerNode(num);
		rear = rear->next;
		currentSize++;

	}

}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void HW8DynIntQueue::dequeue(int & num)
{
	CustomerNode* temp;
	if (isEmpty())
	{
		cout << "Attempting to dequeue on empty queue, exiting program...\n";
		exit(1);
	}
	else //if the queue is not empty
	{	//return front's value, advance front and delete old front
		num = front->customerId;
		temp = front;
		front = front->next;
		delete temp;
		currentSize--;
	}
}

//*********************************************
// Function getCurrentSize returns current    *
// size of the queue.						  *
//*********************************************
int HW8DynIntQueue::getCurrentSize() const
{
	return currentSize;
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool HW8DynIntQueue::isEmpty() const
{
	if (front == NULL)
		return true;
	else
		return false;
}

//*********************************************
// Assignment Operator						  *
//*********************************************
HW8DynIntQueue& HW8DynIntQueue::operator=(const HW8DynIntQueue& rhs)
{
	if (this != &rhs) //self assignment check
	{

		int value;   // Dummy variable for dequeue
		while (!isEmpty())
			dequeue(value); //delete all elements
	
		front = NULL;
		rear = NULL;
		currentSize = 0;
		
		CustomerNode* tmp = rhs.front;
		while (tmp != NULL)
		{
				enqueue(tmp->customerId);
				tmp = tmp->next;
		}

	}
	return *this;
}
//********************************************
// Function clear dequeues all the elements  *
// in the queue.                             *
//********************************************
HW8DynIntQueue::~HW8DynIntQueue()
{
	int value;   // Dummy variable for dequeue

	while (!isEmpty())
		dequeue(value); //delete all elements
}

