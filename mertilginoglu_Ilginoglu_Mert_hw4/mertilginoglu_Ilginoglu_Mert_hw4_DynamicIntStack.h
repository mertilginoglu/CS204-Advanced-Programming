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

//This code were taken from the week 5's lesson codes, "DynIntStack.h".