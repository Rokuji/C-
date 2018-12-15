#include <cstdlib>
#include <sys/types.h>
#include <ctime>
#include <iostream>
#include <string>
#include "cookie.h"
#include "game.h"
#include "player.h"
#include "humanPlayer.h"
#include "computerplayer.h"


using namespace std;


int main (int argc, char** argv)
{
	// Start the random number generator
	int seed = 12371;
	if (argc == 1)
		seed = time(0);
	srand (seed);


	printRules();

	bool playAnotherGame = true;
	while (playAnotherGame)
	{
		Game game;
		initializeGame(game);
		playAGame(game, human, computer);
		printScore(human, computer);
		cout << "Restart??? " << flush;
		string response;
		playAnotherGame = false;
		while (response == "" && cin >> response)
		{
			if (response[0] == 'Y' || response[0] == 'y' ||
					response[0] == 'N' || response[0] == 'n')
				playAnotherGame = response[0] == 'Y' || response[0] == 'y';
			else
				response = "";
		}
		cleanUpGame(game);
	}
	return 0;
}









