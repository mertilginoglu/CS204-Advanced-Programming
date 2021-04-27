struct StackNode
{
	int rowValue, colValue;
	StackNode *next;
};

class DynIntStack
{
private:
	StackNode *top;

public:
	DynIntStack(void);
	~DynIntStack(void);
	void push(int, int);
	void pop(int &, int&);
	bool isEmpty(void);
};

//This code were taken from the week 5's lesson codes, "DynIntStack.h".//StackNode was updated and another integer value was added.//Destructor was also added to this file.//Pop and push was updated to have 2 integer values.