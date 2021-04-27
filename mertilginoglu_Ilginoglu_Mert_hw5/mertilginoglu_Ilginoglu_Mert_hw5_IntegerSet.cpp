#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "mertilginoglu_Ilginoglu_Mert_hw5_IntegerSet.h"
using namespace std;


IntegerSet::IntegerSet() //Default constructor
{
	sizeNum = 0;
	content = NULL;
}

IntegerSet::IntegerSet(int size) //Constructor with int
{
	
	if (size > 0)
	{
		sizeNum = size;
		content = new int[size];
		for (int i = 0; i < size; i++)
		{
			content[i] = i;
		}
	}
	else
	{
		sizeNum = 0;
		content = NULL;
	}
}

IntegerSet::IntegerSet(const IntegerSet & copy) //Deep copy
{
	sizeNum = copy.sizeNum;
	content = new int [sizeNum];

	for(int i = 0; i < sizeNum; i++)
		content[i] = copy.content[i];
}

IntegerSet::~IntegerSet() //Destructor
{
	sizeNum = 0;
	delete [] content;
}

//////// GETTERS ////////

int IntegerSet::getSize() const //Get size
{
	return sizeNum;
}

int* IntegerSet::getContent() const //Get content
{
	int * copyContent = new int[sizeNum];
	for (int i = 0; i < sizeNum; i++)
		copyContent[i] = content[i];
	return copyContent;
}

////////////////////////


//////// MUTATORS ////////

void IntegerSet::setSize(int newSize) //Change size
{
	sizeNum = newSize;
}

void IntegerSet::setContent(int* newContent) //Change content
{
	// delete [] content;
	content = newContent;
}

////////////////////////

bool operator <= (const IntegerSet & lhs, const IntegerSet & rhs) //Subset function
{
	bool isSubset = false;
	int rhsSize = rhs.getSize(), lhsSize = lhs.getSize(), elementsInside = 0;

	//Get the elements inside sets
	int* rhsContent = rhs.getContent(); 
	int* lhsContent = lhs.getContent();
	//Then check how many elements is contained in rhs.
	for (int i = 0; i < lhsSize; i++)
	{
		for (int j = 0; j < rhsSize; j++)
		{
			if (lhsContent[i] == rhsContent[j])
				elementsInside++;
		}
	}

	//If number is equal to lhs size, then it is a subset.
	if (elementsInside == lhsSize)
		isSubset = true;

	delete [] rhsContent;
	delete [] lhsContent;
	return isSubset;
}

bool operator <= (const int & lhs, const IntegerSet & rhs) //Integer containing function
{
	bool contains = false;
	int rhsSize = rhs.getSize();
	int* rhsContent = rhs.getContent();

	//Iterate over all elements inside rhs.
	for (int j = 0; j < rhsSize; j++)
	{
		if (lhs == rhsContent[j])
			contains = true;
	}

	delete [] rhsContent;
	return contains;
}

IntegerSet operator + (const IntegerSet & lhs, const int & rhs) //Integer adding function
{
	IntegerSet final;
	int size;

	bool contains = false;

	int * lhsContent = lhs.getContent();
	int * result;


	for (int i = 0; i < lhs.getSize(); i++) //Iterate over all elements to see if integer is already inside the set.
	{
		if (lhsContent[i] == rhs)
			contains = true;
	}

	if(!contains) //If it is not contained in it, add to set.
	{
		size = lhs.getSize()+1;
		result = new int[lhs.getSize()+1];
		for (int i = 0; i < lhs.getSize(); i++)
			result[i] = lhsContent[i];
		result[lhs.getSize()] = rhs;
	}

	else //If it is contained, do nothing.
	{
		size = lhs.getSize();
		result = lhs.getContent();
	}

	delete [] lhsContent;
	final.setSize(size);
	final.setContent(result);
	return final;
}

IntegerSet operator + (const IntegerSet & lhs, const IntegerSet & rhs) //Adding two sets
{
	IntegerSet final;
	int size, rhsSize = rhs.getSize(), lhsSize = lhs.getSize();

	vector<int> rhsContentVec, resultVec;

	int * lhsContent = lhs.getContent();
	int * rhsContent = rhs.getContent();

	for (int i = 0; i < lhsSize; i++)
		resultVec.push_back(lhsContent[i]);

	for (int i = 0; i < rhsSize; i++)
		rhsContentVec.push_back(rhsContent[i]);
	
	//Compare two vectors, rhsContent and lhsContent.
	for (int i = 0; i < rhsContentVec.size(); i++)
	{
		bool contains = false;
		for (int j = 0; j < resultVec.size(); j++)
		{
			if (rhsContentVec[i] == resultVec[j])
				contains = true;
		}
		if (!contains) //If it is not contained in other set, then add it.
			resultVec.push_back(rhsContentVec[i]);
	}

	delete [] lhsContent;
	delete [] rhsContent;

	int * result = new int[resultVec.size()];

	for (int i = 0; i < resultVec.size(); i++)
		result[i] = resultVec[i];

	final.setSize(resultVec.size());
	final.setContent(result);
	return final;
}

ostream & operator << (ostream & os, const IntegerSet & is) //Cout operator.
{
	int size = is.getSize();
	int * content = is.getContent();

	if (size == 0) //If it is an empty set.
	{
		os << "{ }";
	}
	else
	{
		os << "{";
		for (int i = 0; i < size-1; i++)
			os << content[i] << ", ";
		os << content[size-1] << "}";
	}

	delete [] content;
	return os;
}

IntegerSet operator * (const IntegerSet & lhs, const IntegerSet & rhs) //Union function
{
	IntegerSet final;
	int rhsSize = rhs.getSize(), lhsSize = lhs.getSize();

	vector<int> resultVec; //To store the elements in union

	int * lhsContent = lhs.getContent();
	int * rhsContent = rhs.getContent();

	//Iterate over elements to see if they contain the same element.
	for (int i = 0; i < lhsSize; i++)
	{
		bool contains = false;
		for (int j = 0; j < rhsSize; j++)
		{
			if (lhsContent[i] == rhsContent[j])
				contains = true;
		}
		//If it is contained then push it to the vector.
		if(contains)
			resultVec.push_back(lhsContent[i]);
	}
	delete [] lhsContent;
	delete [] rhsContent;

	int * result = new int[resultVec.size()];
	for (int i = 0; i < resultVec.size(); i++)
		result[i] = resultVec[i];

	final.setSize(resultVec.size());
	final.setContent(result);
	return final;
}

IntegerSet IntegerSet::operator = (const IntegerSet & rhs) //Initialization
{
	int* rhsContent = rhs.getContent();
	if (this != &rhs)	//Prevent self destruct.
	{
		(*this).~IntegerSet();
		sizeNum = rhs.getSize();
		content = new int[rhs.getSize()];
		for (int i = 0; i <= rhs.getSize(); i++)
			content[i] = rhsContent[i];
	}
	delete [] rhsContent;
	return *this;
}

IntegerSet IntegerSet::operator += (const IntegerSet & rhs) //Adding with += operator.
{
	*this = *this + rhs;
	return *this;
}

bool IntegerSet::operator != (const IntegerSet & rhs) //Equal to function
{
	int numElements = 0;
	int * rhsContent = rhs.getContent();
	for (int i = 0; i < rhs.getSize(); i++)
	{
		for (int j = 0; j < sizeNum; j++)
		{
			if (rhsContent[i] == content[j])
				numElements++;
		}
	}

	delete [] rhsContent;
	if (numElements == rhs.getSize() && numElements == sizeNum)
		return false;
	else
		return true;
}
