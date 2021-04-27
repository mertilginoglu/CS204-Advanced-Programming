#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip> 
#include "mertilginoglu_Ilginoglu_Mert_hw4_DynamicIntStack.h"

using namespace std;

bool validInput(string element) //To check if row and column is in correct format.
{
	for(int i = 0; i < element.size(); i++)
	{
		if (element.at(i) > '9' || element.at(i) < '0') //If it contains some character other than numbers.
			return false;
	}
	if(stoi(element) < 3) //If it is smaller than 3.
		return false;
	else
		return true;
}

bool validStartCoor(string rowCoor, string colCoor, int rowValue, int colValue) //To check if starting points are in correct format.
{
	for(int i = 0; i < rowCoor.size(); i++)
	{
		if (rowCoor.at(i) > '9' || rowCoor.at(i) < '0') //If it contains some character other than numbers.
			return false;
	}

	for(int j = 0; j < colCoor.size(); j++)
	{
		if (colCoor.at(j) > '9' || colCoor.at(j) < '0') //If it contains some character other than numbers.
			return false;
	}

	if(stoi(rowCoor) <= 0 || stoi(rowCoor) >= rowValue) //If the value is in borders or lower/higher than it
		return false;
	if(stoi(colCoor) <= 0 || stoi(colCoor) >= colValue)
		return false;

	return true;
}

int main()
{
	bool ToShow;
	string strNumRow, strNumCol, strStartRow, strStartCol;
	cout << "Enter the number of rows: ";
	cin >> strNumRow;
	while (!validInput(strNumRow)) //If row is below 3 or alphabetic.
	{
		cout << strNumRow << " is not valid! \nEnter the number of rows: ";
		cin >> strNumRow;
	}
	cout << "Enter the number of columns: ";
	cin >> strNumCol;
	while (!validInput(strNumCol)) //If column is below 3 or alphabetic.
	{
		cout << strNumCol << " is not valid! \nEnter the number of columns: ";
		cin >> strNumCol;
	}

	int NumRow = stoi(strNumRow), NumCol = stoi(strNumCol), rowcount = 0;
	char** dmatrix = new char*[NumRow]; //2D Matrix initialization

	for(int i = 0; i < NumRow; i++)
	{
		dmatrix[i] = new char[NumCol];
	}

	string MatText, line;
	ifstream InputMat;
	cout << "Please enter file name: "; 
	cin >> MatText;
	InputMat.open(MatText.c_str()); //Try to open the file.
	while (InputMat.fail()) //If file can't be opened, ask again.
	{
		cout << "Cannot open a file named " << MatText << endl;
		cout << "Please enter file name: "; 
		cin >> MatText;
		InputMat.open(MatText.c_str());
	}

	cout << "Enter the starting point: ";
	cin >> strStartRow >> strStartCol;
	while(!validStartCoor(strStartRow, strStartCol, NumRow, NumCol)) //If invalid, ask again.
	{
		cout << "Invalid coordinate!" << endl;
		cout << "Enter the starting point: ";
		cin >> strStartRow >> strStartCol;
	}

	while(!validStartCoor(strStartRow, strStartCol, NumRow, NumCol)) //If invalid, ask again.
	{
		cout << "Invalid coordinate!" << endl;
		cout << "Enter the starting point: ";
		cin >> strStartRow >> strStartCol;
	}
	int startRow = stoi(strStartRow), startCol = stoi(strStartCol); //Change the starting values which taken as strings to integers.
	while(!InputMat.eof()) //Storing the file in a 2D matrix
	{
		int columncount = 0; //To store the which column are we in.
		char element;
		
		while(InputMat.get(element))
		{
			if (element == 'X') //If element is 'X'
			{
				dmatrix[rowcount][columncount] = 'X';
				columncount++;
			}
			else if (element == ' ') //If element is blank
			{
				dmatrix[rowcount][columncount] = ' ';
				columncount++;
			}
			else //If element isn't equal to blank or 'x', then it means a new row. So increase row.
			{
				columncount = 0;
				rowcount++;
			}
		}
	}

	if(dmatrix[startRow][startCol] == 'X') //If starting point contains 'X'
	{
		cout << "Starting point is already occupied." << endl;
		cout << "Terminating..";
		ToShow = false;
	}
	else
	{
		bool moveLeft = false, moveRight = false, moveTop = false, moveBelow = false;
		ToShow = true;
		char fillingChar;
		cout << "Enter the filling char: ";
		cin >> fillingChar;
		while(fillingChar == 'X' || fillingChar == 'x')
		{
			cout << "Filling char is not valid!" << endl;
			cout << "Enter the filling char: ";
			cin >> fillingChar;
		}
		int currentRow = startRow, currentCol = startCol;
		DynIntStack stack;
		dmatrix[startRow][startCol] = fillingChar;

		//These will help us to add neighbor cells to the stack after we are finished with our starting point.
		if(dmatrix[startRow+1][startCol] == ' ') 
			moveBelow = true;
		if(dmatrix[startRow-1][startCol] == ' ')
			moveTop = true;
		if(dmatrix[startRow][startCol+1] == ' ')
			moveRight = true;
		if(dmatrix[startRow][startCol-1] == ' ')
			moveLeft = true;

		if(moveLeft || moveRight || moveTop || moveBelow)
			stack.push(startRow, startCol);
		else //If there are no neighbors.
			dmatrix[startRow][startCol] = fillingChar;


		while(!stack.isEmpty())
		{
			if(dmatrix[currentRow+1][currentCol] == ' ') //Look if below is empty.
			{
				dmatrix[currentRow+1][currentCol] = fillingChar;
				currentRow = currentRow + 1;
				stack.push(currentRow, currentCol); //Then push it to the stack.
			}
			else if(dmatrix[currentRow-1][currentCol] == ' ') //Look if above is empty.
			{
				dmatrix[currentRow-1][currentCol] = fillingChar;
				currentRow = currentRow - 1;
				stack.push(currentRow, currentCol); //Then push it to the stack.
			}
			else if(dmatrix[currentRow][currentCol+1] == ' ')  //Look if right is empty.
			{
				dmatrix[currentRow][currentCol+1] = fillingChar;
				currentCol = currentCol + 1;
				stack.push(currentRow, currentCol); //Then push it to the stack.
			}
			else if(dmatrix[currentRow][currentCol-1] == ' ') //Look if left is empty.
			{
				dmatrix[currentRow][currentCol-1] = fillingChar;
				currentCol = currentCol - 1;
				stack.push(currentRow, currentCol); //Then push it to the stack.
			}
			else //If no neighbour is empty.
			{
				stack.pop(currentRow,currentCol);
			}

			//If we are finished with starting point, then we continue with the neighbors.
			if (moveLeft && stack.isEmpty()) //Left
			{
				stack.push(startRow, startCol-1);
				currentCol = startCol - 1;
				currentRow = startRow;
				moveLeft = false;
			}
			else if (moveRight && stack.isEmpty()) //Right
			{
				stack.push(startRow, startCol+1);
				currentCol = startCol + 1;
				currentRow = startRow;
				moveRight = false;
			}
			else if (moveTop && stack.isEmpty()) //Top
			{
				stack.push(startRow-1, startCol);
				currentCol = startCol;
				currentRow = startRow - 1;
				moveTop = false;
			}
			else if (moveBelow && stack.isEmpty()) //Below
			{
				stack.push(startRow+1, startCol);
				currentCol = startCol;
				currentRow = startRow + 1;
				moveBelow = false;
			}
		}
		stack.~DynIntStack();
	}

	for(int i=0; i<NumRow && ToShow; i++) //To show the filled matrix.
	{
		for(int j=0; j<NumCol; j++)
		{
			cout << dmatrix[i][j];
		}
		cout << endl;
	}
	
	return 0;
}