#include <iostream>
#include "mertilginoglu_Ilginoglu_Mert_hw6_Board.h"
using namespace std;

class Player
{
	public:
		// Player();
		Player(Board & board, char id, int direction);
		void move(int cellAmount);
		void claimOwnership();
		bool wins();
		int getRow();
		int getCol();

	private:
		char identity;
		int currentRow, currentCol;
		int movementDirection;
		Board & board;
};