#include "mertilginoglu_Ilginoglu_Mert_hw6_Player.h"

using namespace std;

Player::Player(Board & board, char id, int direction) //Constructor
	: identity(id), movementDirection(direction), board(board), currentRow(0), currentCol(0)
{ }


void Player::move(int cellAmount)
{
	for(int i = 0; i < (cellAmount%12); i++)
	{
		if(movementDirection == 1)
		{
			if(currentRow == 0)
			{
				if (currentCol < 5) //Move right
				{
					currentCol++;
				}
				else //currentCol == 5
				{
					currentRow++; //Move down
				}
			}


			else //currentRow == 1
			{
				if (currentCol > 0) //Move left
				{
					currentCol--;
				}
				else //currentCol == 0 //Move above
				{
					currentRow--;
				}
			}


		}



		else //movementDirection = 0
		{
			if(currentRow == 1)
			{
				if (currentCol < 5) //Move right
				{
					currentCol++;
				}
				else //currentCol == 5 //Move above
				{
					currentRow--;
				}
			}


			else //currentRow == 0
			{
				if (currentCol > 0) //Move left
				{
					currentCol--;
				}
				else //currentCol == 0 //Move below
				{
					currentRow++;
				}
			}


		}
	}
}

void Player::claimOwnership() //Change the value of specific coordinate
{
	if(board.getOwner(currentRow, currentCol) == '-') //If empty
		board.setOwner(currentRow, currentCol, identity);
}

bool Player::wins() //Check if already won
{
	if(board.countOwnedCells(identity) == 7)
		return true;
	else
		return false;
}

int Player::getRow() //Get row
{
	return currentRow;
}

int Player::getCol() //Get column
{
	return currentCol;
}