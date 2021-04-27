#ifndef HW8DynIntQueue_H
#define HW8DynIntQueue_H

struct CustomerNode
{
	int customerId;
	CustomerNode* next;
	CustomerNode(int num, CustomerNode* ptr = NULL)
	{
		customerId = num;
		next = ptr;
	}
};

class HW8DynIntQueue
{
private:
	// These track the front and rear of the queue.
	CustomerNode* front;
	CustomerNode* rear;
	int currentSize; // maxsize kalkacak
public:
	// Constructor.
	HW8DynIntQueue();
	HW8DynIntQueue(const HW8DynIntQueue& rhs);
	// Member functions.
	int getCurrentSize() const;
	HW8DynIntQueue& operator=(const HW8DynIntQueue& rhs);
	void enqueue(int id);
	void dequeue(int& id);
	bool isEmpty() const;
	//Destructor
	~HW8DynIntQueue();
};
#endif