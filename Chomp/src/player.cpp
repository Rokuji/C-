#include "player.h"

void initPlayer (Player& player, std::string name)
{
	player.name = name;
	player.numGamesWon = 0;
}

void printScore(Player& human, Player& computer)
{
	cout << "Score\tComputer: " << computer.numGamesWon
			<< "\t" << human.name << ": " << human.numGamesWon
			<< endl;
}

