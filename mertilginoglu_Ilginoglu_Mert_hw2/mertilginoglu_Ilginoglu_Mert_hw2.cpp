#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip> 

using namespace std;

struct node
{
	int month, year;
	vector<string> cards;
	node* next;

	//default constructor
	node::node ()
	{}

	//constructor
	node::node (int i, int j, node *n)
		:month(i), year(j), next(n)
	{}	
};
/* Begin: code taken from linkedList.cpp */

//Updated SearchList according to search of month and year in the linked list.
bool SearchList(node *head, int searchMonth, int searchYear)
{
	while (head != NULL)
	{
		if(head->month == searchMonth && head->year == searchYear) //If the node with the given month and year is found
			return true;			
		head = head->next;
	}
	//If the code proceeds from here, it means that the whole list is traversed 
	//and a node with month == searchMonth and year == searchYear could not be found. 
	return false;
}

//In order to avoid memory leak.
void ClearList(node *head)
{
	node *ptr;
	while(head!=NULL)
	{
		ptr=head;
		head=head->next;
		delete ptr;
	}
}

/* End: code taken from linkedList.cpp */

//This function was taken from lecture slides and was updated to make sure that it is ordered in terms of date.
node * AddInOrder(node * head, int monthGiven, int yearGiven, string cardID)
// pre: list is sorted
// post: add newkey to list, keep list sorted, return head of new list
{
   node *  ptr = head;   // loop variable
   // if new node should be first, handle this case and return  
   // in this case, we return address of new node since it is new head  
    if (head == NULL || yearGiven < head->year) //If list is empty or given year is smaller than head's year, then put in  front of head.        
    {   
		node * temp = new node;  //node to be inserted 
		temp->month = monthGiven;
		temp->year = yearGiven; 
		temp->cards.push_back(cardID);
		temp->next = head;
		return temp;
    }
	else if (monthGiven < head->month && yearGiven == head->year) //If years are same but given month is smaller than head's month. We'll also put the node in front of head.
	{
		node * temp = new node;  //node to be inserted 
		temp->month = monthGiven;
		temp->year = yearGiven; 
		temp->cards.push_back(cardID);
		temp->next = head;
		return temp;
	}
	//We'll pass to next node if given date is bigger than the following node.
    while (ptr->next != NULL && ((ptr->next->year < yearGiven) || (ptr->next->year == yearGiven && ptr->next->month < monthGiven))) 
    {   
		ptr = ptr->next;
    }
	//We are now sure that given date is smaller than next node, with the above while command.
    //now insert new node with newkey after where ptr points to.
	node * temp = new node;  //node to be inserted 
	temp->month = monthGiven;
	temp->year = yearGiven;
	temp->cards.push_back(cardID);
	temp->next = ptr->next;
	ptr->next = temp;
	return head;
}

//To print whole list, which is the first option of menu.
void printList(node * head)
{
	if(head == NULL) //If head is null, it means that there is nothing in the list.
	{
		cout << endl << "List is empty!" << endl;
		return;
	}
	while(head != NULL) //If head is not pointing to null, then list is not empty and we can print them.
	{
		cout << "Expiration Date: " << head->month << " " << head->year << endl;
		for(int i = 0; i < head->cards.size(); i++)
		{
			cout << i+1 << ") " << head->cards[i] << endl;
		}
		cout << "-------------------" << endl << endl;
		head = head->next;
	}
}

//If date is found in the list, then this function adds that card ID to the cards vector of the struct.
void addToList(node* head, int month, int year, string cardID)
{
	node * ptr = head;
	while(ptr->month != month || ptr->year != year) //Search until date is found.
	{
		ptr = ptr->next;
	}
	ptr->cards.push_back(cardID); //Add to the list after finding it.
}

//Checks whether given card ID is correct.
bool validInput(string element)
{
	int counter = 0; //To get the digit size.
	for(int i = 0; i < element.size(); i++)
	{
		if(element.at(i) > '9' || element.at(i) < '0') //If it contains some character other than numbers.
			return false;
		counter++;
	}
	if(counter == 16) //If it contains less digits than 16.
		return true;
	else
		return false;
}

//To check if date is correct
bool validMonthYear(string month, string year)
{
	bool monthTrue = true, yearTrue = true;
	for(int i = 0; i < month.size() && monthTrue; i++) //Makes sure it's all numbers.
	{
		if(month.at(i) > '9' || month.at(i) < '0')
			monthTrue = false;
	}

	for(int i = 0; i < year.size() && yearTrue; i++) //Makes sure it's all numbers.
	{
		if(year.at(i) > '9' || year.at(i) < '0')
			yearTrue = false;
	}

	if(!monthTrue || !yearTrue) //If year or month is wrong then return false.
		return false;
	else
	{
		if(stoi(month) > 12 || stoi(month) < 1) //Checks the month value. If it is smaller than 1 or bigger than 12, it returns false.
			return false;
		else
			return true;
	}
}

//Searches for unique card ID. If it is found, then shows the information. If it is not in the list, then it says id wasn't found.
void printCard(string cardNumber, node * head)
{
	node * ptr = head;
	while (ptr != NULL)
	{
		for(int i = 0; i < ptr->cards.size(); i++) //Iterates over all of the elements in tha node's cards vector.
		{
			if(ptr->cards[i] == cardNumber) //If ID is found.
			{
				cout << "There exists a credit card given number " << cardNumber << " with expiration date: " << ptr->month << " " << ptr->year << endl;
				return;
			}
		}
		ptr = ptr->next; //If ID is not found, then go for the next node.
	}
	cout << "There is no credit card with given credit card number: " << cardNumber << endl;
	return;
}

//Taken from lecture slides and updated according to year and month.
node * deleteNode(node * head, int month, int year)
{
	if(head == NULL)
	{
		cout << "There is no node with expiration date " << month << " " << year << " nothing deleted!" << endl;
		return head;
	}
	if(head->month == month && head->year == year)
	{
		cout << "Node with expiration date " << month << " " << year << " and the following credit cards have been deleted!" << endl;
		for(int i = 0; i < head->cards.size(); i++)
		{
			cout << i+1 << ")" << head->cards[i] << endl;
		}
		node * toBeDeleted = head;
		head = head->next;
		delete toBeDeleted;
		return head;
	}
	node * ptr = head;                                                                                                                 //First part is to make sure that program doesn't give error due to
	while((ptr != NULL) && (ptr->next != NULL) && (ptr->next->next != NULL) && (ptr->next->month != month || ptr->next->year != year)) //trying to print values in NULL node. Other part is to iterate until we find the date.
	{
		ptr = ptr->next;
	}
	if (ptr->next != NULL) //To make sure not to give error.
	{
		node * nextNode = ptr->next;
		if(nextNode->month == month && nextNode->year == year) //If date is found.
		{
			cout << "Node with expiration date " << month << " " << year << " and the following credit cards have been deleted!" << endl;
			for(int i = 0; i < nextNode->cards.size(); i++)
			{
				cout << i+1 << ")" << nextNode->cards[i] << endl;
			}
			ptr->next = nextNode->next;
			delete nextNode;
			return head;
		}
	}
	cout <<"There is no node with expiration date " <<month << " " << year <<", nothing deleted!" << endl; //If date is not found.
	return head;
}


int main()
{
	node * linkList = NULL; //Initialize it to NULL first.
	string TextFile, line, cardID;
	int cardMonth, cardYear;
	ifstream InputText;

	cout << "Please enter file name: "; 
	cin >> TextFile;
	InputText.open(TextFile.c_str()); //Try to open the file.
	while (InputText.fail()) //If file can't be opened, ask again.
	{
		cout << "Cannot find a file named " << TextFile << endl;
		cout << "Please enter file name: "; 
		cin >> TextFile;
		InputText.open(TextFile.c_str());
	}
	
	while(!InputText.eof()) //Get input until end of the file.
	{
		while(getline(InputText, line))
		{
			istringstream ssLine(line);
			ssLine >> cardID >> cardMonth >> cardYear;
			if(!SearchList(linkList, cardMonth, cardYear)) //If date is not found in the list.
			{
				linkList = AddInOrder(linkList, cardMonth, cardYear, cardID); //Add the node with that year.
				cout << "New node is created with expiration date: " << cardMonth << " " << cardYear << endl;
			}
			else
			{
				addToList(linkList, cardMonth, cardYear, cardID); //If date is found in the list, then add the card ID to that node's card vector.
				cout << "Node with expiration date " << cardMonth << " " << cardYear << " already exists." << endl;
			}
			cout << "Credit card " << cardID << " added to node " << cardMonth << " " << cardYear << endl;
			cout << "***************" << endl;
		}
	}
	while(true)
	{
		string option;
		cout << endl << "1)Display List" << endl;
		cout << "2)Card Search via Credit Number" << endl;
		cout << "3)Delete Card with respect to Expiration Date" << endl;
		cout << "4)Exit" << endl << endl;
		cout << "Please choose option from the menu: ";
		cin >> option; //Get options from user.
		if(option == "1") //Display list
			printList(linkList);
		else if(option == "2") //Card search.
		{
			string cardSearch;
			cout << "Please enter the credit card number: ";
			cin >> cardSearch;
			while (!validInput(cardSearch)) //If input is not correct, ask again.
			{
				cout << "Invalid format!" << endl;
				cout << "Please enter the credit card number: ";
				cin >> cardSearch;
			}
			printCard(cardSearch, linkList); //When Input is correct, search for the card in the list.
		}
		else if(option == "3") //Delete cards
		{
			string deleteMonth, deleteYear;
			cout << "Please enter month and year:";
			cin >> deleteMonth >> deleteYear;
			while (!validMonthYear(deleteMonth, deleteYear)) //Make sure we get correct date else ask again.
			{
				cout << "Invalid Date!" << endl;
				cout << "Please enter month and year:";
				cin >> deleteMonth >> deleteYear;
			}
			linkList = deleteNode(linkList, stoi(deleteMonth), stoi(deleteYear)); //Delete with respect to date.
		}
		else if(option == "4") //Terminate
		{
			cout << "Terminating!!!";
			break;
		}
		else
		{
			cout << "Wrong option. Please choose an option from menu again.";
		}

	}
	ClearList(linkList); //Clear to avoid memory leak.
	return 0;
}
