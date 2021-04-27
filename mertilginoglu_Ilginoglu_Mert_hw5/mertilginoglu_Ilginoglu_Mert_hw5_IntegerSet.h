#ifndef _MERTILGINOGLU_ILGINOGLU_MERT_HW5_INTEGERSET_H
#define _MERTILGINOGLU_ILGINOGLU_MERT_HW5_INTEGERSET_H

#include <iostream>
using namespace std;

class IntegerSet
{
	public:
		IntegerSet();
		IntegerSet(int size);
		IntegerSet (const IntegerSet & copy);
		~IntegerSet();

		
		IntegerSet operator = (const IntegerSet & rhs);
		IntegerSet operator += (const IntegerSet & rhs);
		bool operator != (const IntegerSet & rhs);

		//Getters and mutators
		int getSize() const;
		int* getContent() const;
		void setSize(int newSize);
		void setContent(int* newContent);

	private:
		int sizeNum;
		int *content;

};

//Free functions
ostream & operator << (ostream & os, const IntegerSet & is);
bool operator <= (const IntegerSet & lhs, const IntegerSet & rhs);
bool operator <= (const int & lhs, const IntegerSet & rhs);
IntegerSet operator + (const IntegerSet & lhs, const int & rhs);
IntegerSet operator + (const IntegerSet & lhs, const IntegerSet & rhs);
IntegerSet operator * (const IntegerSet & lhs, const IntegerSet & rhs);

#endif