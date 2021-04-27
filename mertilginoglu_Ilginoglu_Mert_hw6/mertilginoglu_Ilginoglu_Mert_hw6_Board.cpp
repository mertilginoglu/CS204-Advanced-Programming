#include "mertilginoglu_Ilginoglu_Mert_hw6_Board.h"

using namespace std;

Board::Board() //Constructor
{
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 6; j++)
			theBoard[i][j] = '-';
	}
}

void Board::displayBoard() const //Show the board state
{
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 6; j++)
		{
			cout << theBoard[i][j] << " ";
		}
		cout << endl;
	}
}

char Board::getOwner(int row, int column) //Return the owner
{
	return theBoard[row][column];
}

void Board::setOwner(int row, int column, char owner) //Change the owner
{
	theBoard[row][column] = owner;
}

bool Board::isFull() //Look if board is full
{
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 6; j++)
		{
			if(theBoard[i][j] == '-')
				return false;
		}
	}
	return true;
}

int Board::countOwnedCells(char owner) //Count the owned cells of a player
{
	int ownedCell = 0;

	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 6; j++)
		{
			if(theBoard[i][j] == owner)
				ownedCell++;
		}
	}
	return ownedCell;
}