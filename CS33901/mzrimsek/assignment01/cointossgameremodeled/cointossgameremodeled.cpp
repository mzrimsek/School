#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Player{
	public:
		int getCoinGuess()
		{
			int guess;
			cout << "\n\nHeads or Tails? (1 or 2)" <<endl;
			cin >> guess;
			return guess;
		}
};

class CoinGame{
	Player *player;

	void handleCorrectGuess(int* streak, int playsLeft)
	{
		*streak = *streak + 1;
		cout << "\n\nYou guessed correct! "<< playsLeft << " plays left, with a streak of " << *streak << "!";
	}

	void handleIncorrectGuess(int* streak, int playsLeft)
	{
		*streak = 0;
		cout << "\n\nUnlucky, you were wrong! " << playsLeft << " plays left!";
	}

	void compareAndHandleGuess(int guess, int coinFace, int* streak, int playsLeft)
	{
		if(guess == coinFace)
		{
			handleCorrectGuess(streak, playsLeft);
		}
		else
		{
			handleIncorrectGuess(streak, playsLeft);
		}
	}

	void checkAndCompareCoinFace(int guess, int coinFace, int* streak, int playsLeft)
	{
		if(coinFace == 1)
		{
			cout << "\nThe coin landed Heads up!";
			compareAndHandleGuess(guess, coinFace, streak, playsLeft);
		}
		else if(coinFace == 2)
		{
			cout << "\nThe coin landed Tails up! ";
			compareAndHandleGuess(guess, coinFace, streak, playsLeft);
		}
	}

	void printInstructions()
	{
		cout <<"\n\n			Welcome to Coin Toss Game!!" <<endl;
		cout <<"\n\nRules:\nGuess 5 coin tosses in a row to win the 1,000,000 dollar Jackpot.";
		cout <<"\nGuess 3 in a row, and cash in for 100 dollars";
	}

	void printGameOver(int streak)
	{
		if(streak == 3)
		{
			cout << "\n\nCONGRATULATIONS!!";
			cout << "\nYou have cashed in for 100 dollars with a streak of 3!"<<endl;
		}
		else if(streak == 5)
		{
			cout << "\n\nCONGRATULATIONS!!";
			cout << "\nYou win the Jackpot of 1,000,000 dollars with a streak of FIVE!!!"<<endl;
		}
		else
		{
			cout << "\n\nYou have run out of plays! Better luck next time!"<<endl;
		}
	}

	int getCoinFace()
	{
		srand(static_cast<unsigned int>(time(0)));
		return rand() % 2+1;
	}

	char getCashIn(int streak, int playsLeft)
	{
		char cashIn;
		if(streak == 3)
		{
			cout << "\n\nYou have reached a streak of three!! Cash in?(y/n)";
			cin >> cashIn;
		}
		if(streak == 5 || playsLeft == 0)
		{
			cashIn = 'y';
		}
		return cashIn;
	}

	char getPlayAgain()
	{
		char playAgain;
		cout << "\n\nDo you wish to play again?(y/n)" ;
		cin >> playAgain;
		return playAgain;
	}

	void playRound(int* streak)
	{
		int playsLeft = 5;
		char cashIn = 'n';

		do
		{
			int coinFace = getCoinFace();
			int guess = player->getCoinGuess();
			playsLeft--;

			checkAndCompareCoinFace(guess, coinFace, streak, playsLeft);
			cashIn = getCashIn(*streak, playsLeft);
		} while(cashIn != 'y');
	}

	public:
		CoinGame(Player* currentPlayer)
		{
			player = currentPlayer;
		}

		void runGame()
		{
			printInstructions();

			char playAgain = 'y';
			while (playAgain =='y')
			{
				int streak = 0;

				playRound(&streak);
				printGameOver(streak);

				playAgain = getPlayAgain();
			}

			cout << "\n\nOk, cya!!"<<endl;
		}
};

int main()
{
	Player *gamePlayer = new Player;
	CoinGame *coinGame = new CoinGame(gamePlayer);
	coinGame->runGame();
	return 0;
}
