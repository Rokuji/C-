#include "player.h"
#include "cookie.h"



void initHumanPlayer(Player& human)
{
	human.numGamesWon = 0;
	cout << "Welcome to Chomp!\n"
			<< "What is your name? "
			<< flush;
	getline (cin, human.name);

	cout << "OK, " << human.name << ", let's play." << endl;
}

void getHumanPlayerMove (Cookie& cookie, int& column, int& row)
{
	cout << "Your turn to take a bite from the cookie.\n";
	cout << "Enter the column number and row number at which\n";
	cout << "  you wish to chomp (separated by a blank space): " << flush;
	cin >> column >> row;
	if (cin.fail()) {
		cin.clear();
		std::string junk;
		getline(cin, junk); // discard rest of this input line
	}
}
