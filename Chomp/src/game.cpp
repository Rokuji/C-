#include "game.h"
#include "cookie.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

void cleanUpGame (Game& g)
{
	cleanUpCookie(g.cookie);
}

bool biteIsLegal (const Game& g, int column, int row)
{
	return (column >= 0) && (row >= 0) && row < getNumberOfRows(g.cookie)
			&& (column < getNumberOfColumns(g.cookie,row));
}

void display (std::ostream& output, const Cookie& cookie)
{
	// Print top line with numeric index of columns
	output << ' ';
	for (int col = 0; col < cookie.numberOfColumns; ++ col)
		output << (col % 10);
	output << endl;

	// Print each row, preceded by a numeric row index
	for (int row = 0; row < cookie.numberOfRows; ++row)
	{
		output << (row % 10);
		for (int col = 0; col < cookie.crumbs[row]; ++col)
			if (row == 0 && col == 0)
				output << "P"; // (poison)
			else
				output << "Z";
		output << endl;
	}
}

void initializeGame(Game& g)
{
	initCookie (g.cookie);
	cout << "The cookie has " << getNumberOfRows(g.cookie) << " rows of "
			<< getNumberOfColumns(g.cookie) << " columns" << endl;
}

bool gameEnded(const Game& g)
{
	return getNumberOfColumns(g.cookie) <= 0;
}

void printRules()
{
	cout << "Chomp is a game played with a rectangular \"cookie\" made\n"
			<< "up of square \"crumbs\".\n\n";
	cout << "Taking turns, each player takes a bite from the cookie,\n"
			<< "selecting a crumb that is removed from the cookie, together\n"
			<< "with all crumbs below and to the right of the selected one.\n\n";
	cout << "The top-left crumb in this cookie is poisoned. The player\n"
			<< "who eats the poisoned crumb loses the game.\n" << endl;

}

void playAGame(Game& game, Player& human, Player& computer)
{
	while (!gameEnded(game))
	{
		display (cout, game.cookie);

		// First, the human player's move
		int xBite = -1;
		int yBite = -1;
		bool legalMove = false;
		while (!legalMove)
		{
			getHumanPlayerMove (game.cookie, xBite, yBite);
			legalMove = biteIsLegal (game, xBite, yBite);
			if (!legalMove)
			{
				cout << "Sorry, but that is not a legal move." << endl;
			}
		}
		takeABite (game.cookie, xBite, yBite);
		if (gameEnded(game))
		{
			++computer.numGamesWon;
			cout << "You have eaten the poison crumb! You lose." << endl;
		}
		else
		{
			// Computer player's move
			display (cout, game.cookie);
			getComputerPlayerMove (game.cookie, xBite, yBite);
			cout << "I will chomp at column " << xBite
					<< ", row " << yBite << "." << endl;
			takeABite (game.cookie, xBite, yBite);
			if (gameEnded(game))
			{
				++human.numGamesWon;
				cout << "I had to eat the poison crumb. You win!"
						<< endl;
			}
		}

	}
}

