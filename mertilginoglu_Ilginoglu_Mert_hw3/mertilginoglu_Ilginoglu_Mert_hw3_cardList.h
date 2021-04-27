#ifndef _CARDLIST_H
#define _CARDLIST_H
#include <string>
using namespace std;

struct creditCardNode { 
	string creditCardNo; 
	creditCardNode * next; 

	creditCardNode::creditCardNode()
	{}

	creditCardNode::creditCardNode(string ccNo, creditCardNode * right)
		: creditCardNo(ccNo),  next(right)
	{}

};

struct expirationNode { 
	int month, year; 
	creditCardNode * cHead; 
	expirationNode * next; 
	expirationNode * prev;

	expirationNode::expirationNode()
	{}

	expirationNode::expirationNode(int m, int y, creditCardNode * head, expirationNode * right, expirationNode * left)
		: month(m), year(y), cHead(head), next(right), prev(left)
	{}

};


class CardList { 
public: 
	CardList(); //default constructor that creates an empty list 
	void insertCard (string creditCardNo, int month, int year); //inserts a new card to the structure in sorted fashion 
	void displayListChronological (); //displays entire structure in chronological order 
	void displayListReverseChronological (); //displays entire structure in reverse chronological order 
	void cardSearch (string creditCardNo); //displays all of the occurrences of the given card number 
	void bulkDelete (int month, int year); //deletes all nodes up to and including given expiration date 
	void deleteAll (); //deletes the entire structure 

private: 
		expirationNode * head; 
		expirationNode * tail;
// any helper functions you see necessary
};

#endif