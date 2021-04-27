#include <iostream>
using namespace std;

class Board
{
	public:
		Board();
		void displayBoard() const;
		char getOwner(int row, int column);
		void setOwner(int row, int column, char owner);
		bool isFull();
		int countOwnedCells(char owner);

	private:
		char theBoard[2][6];

};