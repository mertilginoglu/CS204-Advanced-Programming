#include <iostream>
#include <string>
#include "mertilginoglu_Ilginoglu_Mert_hw3_cardList.h"
using namespace std;

CardList::CardList()
{
	head = NULL;
	tail = NULL;
}

void CardList::insertCard (string creditCardNo, int month, int year)
{
	if (head == NULL) //Empty list.
	{
		creditCardNode * cardPtr = new creditCardNode(creditCardNo, NULL);
		expirationNode * ptrNew = new expirationNode(month, year, cardPtr, NULL, NULL);
		head = ptrNew;
		tail = head;
		cout << creditCardNo << " " << month << " " << year << ": added to a new expiration date node" << endl;
	}
	else if (year < head->year || (month < head->month && year == head->year)) //Not empty list. Inserting into beginning.
	{
		creditCardNode * cardPtr = new creditCardNode(creditCardNo, NULL);
		expirationNode * ptrNew = new expirationNode(month, year, cardPtr, head, NULL);
		head->prev = ptrNew;
		head = ptrNew;
		cout << creditCardNo << " " << month << " " << year << ": added to a new expiration date node" << endl;
	}
	else //Not empty list, insert into middle or last.
	{
		expirationNode * ptr = head;

		while((ptr != tail && year > ptr->next->year) || (ptr != tail && year == ptr->next->year && month > ptr->next->month))
			ptr = ptr->next;
		//If year and month already exists in the list. It might either be equal to current pointer or pointers next node.
		if((year == ptr->year && month == ptr->month) || (ptr->next != NULL && ptr->next->year == year && ptr->next->month == month)) 
		{
			bool foundInList = false, equalToCurrent;
			creditCardNode * cardPtrSearch; //Pointer to search credit card in list. Used for iterating over list.
			creditCardNode * cardPtr; //This will be used when inserting other node.
			if((year == ptr->year && month == ptr->month)) //It is equal to pointer
			{
				equalToCurrent = true;
				cardPtrSearch = ptr->cHead; 
				cardPtr = ptr->cHead;
			}
			else //It is equal to pointer's next
			{
				equalToCurrent = false;
				cardPtrSearch = ptr->next->cHead; 
				cardPtr = ptr->next->cHead;
			}

			if(creditCardNo == cardPtr->creditCardNo)
				foundInList = true;

			while(cardPtrSearch != NULL && !foundInList) //Searching for the given credit card in the list. If it exists, make foundInList true. Might turn this into function.
			{
				if (cardPtrSearch->creditCardNo == creditCardNo)
					foundInList = true;
				cardPtrSearch = cardPtrSearch->next;
			}
			if(!foundInList) //If given card is not in the list.
			{
				if(cardPtr->creditCardNo > creditCardNo)
				{
					creditCardNode * newNode = new creditCardNode(creditCardNo, NULL);
					if(equalToCurrent)
					{
						newNode->next = ptr->cHead;
						ptr->cHead = newNode;
					}
					else
					{
						newNode->next = ptr->next->cHead;
						ptr->next->cHead = newNode;
					}
					cout << creditCardNo << " " << month << " " << year << ": inserted to an existing expiration date node" << endl;
				}
				else
				{
					creditCardNode * newNode = new creditCardNode(creditCardNo, NULL);
					while(cardPtr->next != NULL && cardPtr->next->creditCardNo < creditCardNo)
						cardPtr = cardPtr->next;

					newNode->next = cardPtr->next;
					cardPtr->next = newNode;
					
					cout << creditCardNo << " " << month << " " << year << ": inserted to an existing expiration date node" << endl;
				}
			}
			else
			{
				cout << creditCardNo << " " << month << " " << year << ": this card was already inserted" << endl;
			}

		}
		else //If date doesn't exist in the list, create a new node.
		{
			creditCardNode * cardPtr = new creditCardNode(creditCardNo, NULL);
			expirationNode * ptrNew = new expirationNode(month, year, cardPtr, NULL, NULL);
			ptrNew->next = ptr->next;
			ptrNew->prev = ptr;
			if(ptrNew->next != NULL)
				ptrNew->next->prev = ptrNew;
			ptr->next = ptrNew;
			if(ptr == tail)
				tail = ptrNew;
			cout << creditCardNo << " " << month << " " << year << ": added to a new expiration date node" << endl;
		}
	}
}

void CardList::displayListChronological()
{
	expirationNode * ptr = head;
	//List is empty
	if(head == NULL)
	{
		cout << "\nList is empty!" << endl;
	}
	else
	{
		while(ptr != NULL)
		{
			int count = 1; //To show the ranking numbers of the credit cards.
			cout << "Expiration Date: " << ptr->month << " " << ptr->year << endl;
			creditCardNode * cardShowPtr = ptr->cHead;
			while(cardShowPtr != NULL)
			{
				cout << count << ") " << cardShowPtr->creditCardNo << endl;
				count++;
				cardShowPtr = cardShowPtr->next;
			}
			cout << "-------------------" << endl;
			ptr = ptr->next;
		}
	}
}

void CardList::displayListReverseChronological()
{
	expirationNode * ptr = tail;
	//List is empty
	if(tail == NULL)
	{
		cout << "\nList is empty!" << endl;
	}
	else
	{
		while(ptr != NULL)
		{
			int count = 1; //To show the ranking numbers of the credit cards.
			cout << "Expiration Date: " << ptr->month << " " << ptr->year << endl;
			creditCardNode * cardShowPtr = ptr->cHead;
			while(cardShowPtr != NULL)
			{
				cout << count << ") " << cardShowPtr->creditCardNo << endl;
				count++;
				cardShowPtr = cardShowPtr->next;
			}
			cout << "-------------------" << endl;
			ptr = ptr->prev;
		}
	}
}

void CardList::cardSearch(string creditCardNo)
{
	bool found = false;
	expirationNode * ptr = head;
	//List is empty

	/*
	if(head == NULL)
	{
		cout << "List is empty" << endl;
	}
	*/

	while(ptr != NULL)
	{
		creditCardNode * cardShowPtr = ptr->cHead;
		while(cardShowPtr != NULL)
		{
			if (cardShowPtr->creditCardNo == creditCardNo)
			{
				found = true;
				cout << "There exists a credit card given number " << creditCardNo << " with expiration date: " << ptr->month << " " << ptr->year << endl;
			}
			cardShowPtr = cardShowPtr->next;
		}
		ptr = ptr->next;
	}

	if(!found)
		cout << "\nThere is no credit card with given credit card number: " << creditCardNo << endl;
}

void CardList::bulkDelete(int month, int year)
{
	expirationNode * ptr;
	while(head != NULL &&  ((year >= head->year) || (year == head->year && month >= head->month)))
	{
		int count = 1; //To show the card number count.
		ptr = head;
		creditCardNode * cardPtr;
		cout << "Node with expiration date " << ptr->month << " " << ptr->year << " and the following credit cards have been deleted!" << endl;
		while (head->cHead != NULL) //Delete the card list in order to avoid memory leak.
		{
			cardPtr = head->cHead;
			cout << count << ") " << cardPtr->creditCardNo << endl;
			head->cHead = head->cHead->next;
			delete cardPtr;
			count++;
		}
		if (head == tail) //If we are in the last node.
		{
			delete head;
			head = NULL;
			tail = NULL;
		}
		else //Change prev in order to have not bugs.
		{
		head = head->next;
		delete ptr;
		head->prev = NULL;
		}
	}
}

void CardList::deleteAll()
{
	expirationNode * ptr;
	while(head != NULL)
	{
		ptr = head;
		creditCardNode * cardPtr;
		while (head->cHead != NULL)
		{
			cardPtr = head->cHead; //Delete the card list also.
			head->cHead = head->cHead->next;
			delete cardPtr;
		}
		head = head->next;
		delete ptr;

		if(head != NULL)
			head->prev = NULL;
	}

}