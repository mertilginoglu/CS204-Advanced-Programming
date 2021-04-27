#include <iostream>
#include "mertilginoglu_Ilginoglu_Mert_hw3_cardList.h"
#include <fstream>
#include <sstream>

using namespace std;

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

void printMenu()
{
	cout << endl;
	cout << "1) Upload Card(s) from a File" << endl;
	cout << "2) Display List Chronological" << endl;
	cout << "3) Display List Reverse Chronological" << endl;
	cout << "4) Card Search" << endl;
	cout << "5) Bulk Delete" << endl;
	cout << "6) Exit" << endl;
	cout << "Please choose option from the menu: ";
}

int main()
{
	CardList list; //Construct CardList object.
	bool programEnd = false; //To make program finish.

	while(!programEnd)
	{
		string option;
		printMenu();
		cin >> option;

		if (option == "1")
		{
			string TextFile, line, cardID;
			int cardMonth, cardYear;
			ifstream InputText;

			cout << "Please enter file name: "; 
			cin >> TextFile;
			InputText.open(TextFile.c_str()); //Try to open the file.
			if (InputText.fail()) //If file can't be opened, say couldn't finnd the file.
			{
				cout << "Could not find a file named " << TextFile << endl;
			}
			else
			{
				while(!InputText.eof()) //Get input until end of the file.
				{
					while(getline(InputText, line))
					{
						istringstream ssLine(line);
						ssLine >> cardID >> cardMonth >> cardYear;
						list.insertCard(cardID, cardMonth, cardYear);
					}
				}
			}
		}

		else if (option == "2") //Display list chronological.
		{
			list.displayListChronological();
		}

		else if (option == "3") //Display list reverse
		{
			list.displayListReverseChronological();
		}
		
		else if (option == "4") //Card search
		{
			string searchCardNo;
			cout << "Please enter the credit card number: ";
			cin >> searchCardNo;
			if (!validInput(searchCardNo))
			{
				cout << "Invalid format!" << endl;
			}
			else
			{
				list.cardSearch(searchCardNo);
			}
		}

		else if (option == "5") //Deleting upto one date.
		{
			string month, year;
			cout << "Please enter month and year: ";
			cin >> month >> year;
			if(!validMonthYear(month, year))
			{
				cout << "Invalid format!" << endl;
			}
			else
			{
				list.bulkDelete(stoi(month), stoi(year));
			}
		}

		else if (option == "6") //Exit
		{
			cout << "Terminating!!!";
			programEnd = true;
		}

		else
		{
			cout << "Invalid operation!" << endl;
		}
	
	}
	list.deleteAll(); //In order to avoid memory leak.
	return 0;
}