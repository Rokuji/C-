#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "cookie.h"
#include "player.h"
#include <iostream>
#include <string>

struct Game {

	/// The cookie for this game.
	Cookie cookie;
};
void cleanUpGame (Game& g);
bool biteIsLegal (const Game& g, int column, int row);
void display (std::ostream& output, const Cookie& cookie);
void initializeGame(Game& g);
bool gameEnded(const Game& g);
void printRules();
void playAGame(Game& game, Player& human, Player& computer);


#endif // GAME_H_INCLUDED
