#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip> 

using namespace std;

struct indexInfo
{
	int x;
	int y;
};

void Print(vector<vector<char>> & mat) //Prints our matrix. Taken from the lab files.
{
    for (int j=0; j < mat.size(); j++)
    {   
		for (int k=0; k < mat[j].size(); k++)
        {   
			cout << setw(4) << mat[j][k];
        }
        cout << endl;
    }
}

bool RowLengthCheck(vector<vector<char>> & mat) //This function checks if the matrix has equal row length.
{
	int FirstRow = mat[0].size();
	for(int i = 1; i < mat.size(); i++)
	{
		if(FirstRow != mat[i].size())
		{
			return false;
		}
	}
	return true;
} 

bool CharacterCheck(vector<vector<char>> & mat) //This checks if the matrix is consisted only of 'x' and 'o' characters.
{
	for(int i = 0; i < mat.size(); i++)
	{
		for(int j = 0; j < mat[i].size(); j++)
		{
			if(mat[i][j] != 'x' && mat[i][j] != 'o')
			{
				return false;
			}
		}
	}
	return true;
}

bool VectorCheck(vector<indexInfo> & CellList, int xCoordinate, int yCoordinate) //Function to check if a certain cell coordinate was in the given vector.
{
	for(int i = CellList.size() - 1; i >= 0; i--)
	{
		if((CellList[i].x == xCoordinate) && (CellList[i].y == yCoordinate))
		{
			return false;
		}
	}
	return true;
}


int main()
{
	string MatText, line;
	ifstream InputMat;
	vector <vector<char>> Matrix1;

	cout << "Please enter file name: "; 
	cin >> MatText;
	InputMat.open(MatText.c_str()); //Try to open the file.
	while (InputMat.fail()) //If file can't be opened, ask again.
	{
		cout << "Cannot find a file named " << MatText << endl;
		cout << "Please enter file name: "; 
		cin >> MatText;
		InputMat.open(MatText.c_str());
	}

	while(!InputMat.eof()) //Get lines until the end of the file and store them in a vector of vector of char.
	{
		getline(InputMat, line);
		stringstream s(line);
		char element;
		vector <char> TempRow;

		while(s >> element)
		{
			TempRow.push_back(element);
		}
		Matrix1.push_back(TempRow);
	}


	if(RowLengthCheck(Matrix1) && CharacterCheck(Matrix1)) //If our matrix is proper. With same length in every row and only 'x', 'o' characters.
	{
		Print(Matrix1);
		string xCoor, yCoor; //We'll get coordinates as string first, to not further complicate the input checks. With this, we will not also have to use cin clear.
		cout << "Please enter starting coordinates, first row X then column Y:";
		cin >> xCoor >> yCoor;
		while(true)
		{
			bool xCorrect = true, yCorrect = true; //We first assume everything is correct.
			for(int i = 0; i < xCoor.length() &&  xCorrect; i++) //We check for given x coordinate value. If it contains any character other than numbers, we will make xCorrect value false.
			{
				if(xCoor.at(i) < '0' || xCoor.at(i) > '9')
					xCorrect = false;
			}
			for(int i = 0; i < yCoor.length() && xCorrect && yCorrect; i++) //This repeats the process we have done above, but for y coordinate.
			{
				if(yCoor.at(i) < '0' || yCoor.at(i) > '9')
					yCorrect = false;
			}

			if((xCoor == "-1") && (yCoor == "-1")) //Finish directly if both inputs were -1.
			{
				cout << "Terminating...";
				break;
			}
	
			else if(!yCorrect || !xCorrect) //If inputs were not both -1 and contained some characters other than numbers.
			{
				cout << "Invalid coordinates" << endl;
			}
			else if(stoi(yCoor) > Matrix1[0].size()-1 || stoi(yCoor) < 0 || stoi(xCoor) > Matrix1.size()-1 || stoi(xCoor) < 0) //If inputs are numbers, but either much higher (or lower) than column or row size.
			{
				cout << "Invalid coordinates" << endl;
			}
			else //At this point we make sure everything is going correct.
			{
				vector<indexInfo> visitedCells;														//To store visited cells.//
				indexInfo CurrentCell;																//We'll use this struct to push_back our current cell.//
				bool pathEnd = false, cellOccupied = true, topEdge, bottomEdge, rightEdge, leftEdge;
				int currentX = stoi(xCoor), currentY = stoi(yCoor), moveCount = 0;					//We change our string values to integers.//
				if(Matrix1[currentX][currentY] == 'o')//Checks if the initial cell is occupied.
				{
					cout << "This cell is not occupied!" << endl;
					cellOccupied = false;
				}
				while(!pathEnd && cellOccupied) //If our path didn't end yet or our starting cell is not 'o', this while loop will continue.
				{
					bool moved = false; //We will use this to move only once, for every single loop.
					topEdge = false, bottomEdge = false, rightEdge = false, leftEdge = false; //We will use these variable to check if current cell is in edges of the matrix.
					CurrentCell.x = currentX;
					CurrentCell.y = currentY;
					visitedCells.push_back(CurrentCell);
					if (currentX == 0)
						topEdge = true;
					if (currentY == 0)
						leftEdge = true;
					if (currentX == (Matrix1.size()-1))
						bottomEdge = true;
					if (currentY == (Matrix1[0].size()-1))
						rightEdge = true;
					while(!moved)
					{
						if (!rightEdge) //If current cell is in right edge, we won't try to move to right.
						{
							if(Matrix1[currentX][currentY+1] == 'x' && VectorCheck(visitedCells, currentX, currentY+1)) //If we didn't visit the cell on the right and it contains 'x',
							{                                                                                           //this part will run.
								currentY++;
								moved = true; //If we are in this part, we have already moved to the right cell. So we change our moved variable value.
								moveCount++;
							}
						}
						if(!bottomEdge && !moved) //If we didn't move in the first part and we are not in the bottom edge. With adding "!moved" to condition list, we are kind of creating and elif structure.
						{
							if(Matrix1[currentX+1][currentY] == 'x' && VectorCheck(visitedCells, currentX+1, currentY))
							{
								currentX++;
								moved = true;
								moveCount++;
							}
						}
						if(!leftEdge && !moved) //Repetition of the same things above.
						{
							if(Matrix1[currentX][currentY-1] == 'x' && VectorCheck(visitedCells, currentX, currentY-1))
							{
								currentY--;
								moved = true;
								moveCount++;
							}
						}
						if(!topEdge && !moved) ////Repetition of the same things above.
						{
							if(Matrix1[currentX-1][currentY] == 'x' && VectorCheck(visitedCells, currentX-1, currentY))
							{
								currentX--;
								moved = true;
								moveCount++;
							}
						}
						if(!moved) //After checking right, left, up, down and still couldn't make a move. This means that path is over.
						{
							if(((currentX == stoi(xCoor)-1 && currentY == stoi(yCoor)) ||                         /*  This part checks if our last       */
								(currentX == stoi(xCoor) && currentY == stoi(yCoor)-1) ||                         /*  cell is below, up, right or left   */
								(currentX == stoi(xCoor)+1 && currentY == stoi(yCoor)) ||                         /*  of our starting cell.              */
								(currentX == stoi(xCoor) && currentY == stoi(yCoor)+1)) && moveCount >= 3)       /*  We also check the move count, to know if the path is enclosed or not. */ 
																												  /*  We need atleast 3 moves for path to be closed */  
							{
								moved = true;
								pathEnd = true;
								cout << "Found an enclosed area. The coordinates of the followed path:" << endl; //Output for the enclosed path situation.
								for(int i = 0; i < visitedCells.size(); i++)
								{
									cout << visitedCells[i].x << " " << visitedCells[i].y << endl;
								}
							}
							else 
							{
								moved = true;
								pathEnd = true;
								cout << "Cannot found an enclosed area starting with given coordinate. The coordinates of the followed path:" << endl; //Output for not finding an enclosed area.
								for(int i = 0; i < visitedCells.size(); i++)
								{
									cout << visitedCells[i].x << " " << visitedCells[i].y << endl;
								}
							}
						}
					}
				
				}
			}
			cout << "Please enter starting coordinates, first row X then column Y:"; //We return back by asking coordinates again and do every check once again.
			cin >> xCoor >> yCoor;
		}
	}
	else if(!CharacterCheck(Matrix1)) //If contains invalid chars.
	{
		cout << MatText << " includes invalid char(s)";
	}
	else  //If row length differs.
	{
		cout << MatText << " is invalid matrix, does not contain same amount of char each row!";
	}
	
	return 0;
}