
// add your #includes here
#include "mertilginoglu_Ilginoglu_Mert_hw6_Player.h"
using namespace std;

int randomGenerator()
{
	return rand() % 6 + 1;
}

int main()
{
	int seed = 0; 
	cout << "Welcome to my cool game :)\nPlease enter an integer for the seed of the random number generator: ";
	cin >> seed;  //99090 A wins in 19 steps, 523743 Tie game in 15 steps, 9231 B wins in 16 steps for VS2012, I do not know for other versions
	srand(seed);
	cout << endl;
	int counter = 0;
	Board myBoard = Board();
	Player playerA = Player(myBoard, 'A', 1); //1 for clockwise
	Player playerB = Player(myBoard, 'B', 0); //0 for counter-clockwise
	char turn = 'A';
	int dice;
	bool gameContinue = true;

	while (gameContinue)
	{
		dice = randomGenerator();

		if (turn == 'A')
		{
			cout << "Player A rolled the dice: "<< dice << endl;
			cout << "Player A" << " moves from " << playerA.getRow()<< " " << playerA.getCol();
			playerA.move(dice);
			cout << " to " << playerA.getRow() << " " << playerA.getCol() << endl;
			playerA.claimOwnership();
		}
		else if (turn == 'B')
		{
			cout << "Player B rolled the dice: "<< dice << endl;
			cout << "Player B" << " moves from " << playerB.getRow() << " " << playerB.getCol();
			playerB.move(dice);
			cout << " to " << playerB.getRow() << " " << playerB.getCol() << endl;
			playerB.claimOwnership();
		}
		
		if (turn == 'A')
			turn = 'B';
		else
			turn = 'A';
	

		myBoard.displayBoard();

		//Check whether one of the players won or the game ended with draw
		if (playerA.wins())
		{
			gameContinue = false;
			cout <<endl << "Player A won the game!" << endl;
		}
		else if (playerB.wins())
		{
			gameContinue = false;
			cout << endl << "Player B won the game!" << endl;
		}
		else if (myBoard.isFull())
		{
			gameContinue = false;
			cout << endl << "It is a tie!" << endl;
		}
		//cin.get();//if you want to try the game step by step, you can uncomment this line; but before submitting do not forget to comment it again
		counter++;
		cout << endl;
	}
	cout << "Total number of turns: "<<counter << endl;;
	return 0;
}