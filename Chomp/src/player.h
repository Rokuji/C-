#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED



#include <iostream>
#include <string>
#include "cookie.h"


using namespace std;

struct Player {
	std::string name;
	int numGamesWon;
};
void initPlayer (Player& player, std::string name);
void printScore(Player& human, Player& computer);
void getComputerPlayerMove (Cookie& cookie, int& column, int& row);
void getHumanPlayerMove (Cookie& cookie, int& column, int& row);


#endif // PLAYER_H_INCLUDED
