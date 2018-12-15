#ifndef COMPUTERPLAYER_H_INCLUDED
#define COMPUTERPLAYER_H_INCLUDED
#include "player.h"
#include "cookie.h"


Player computer = {"computerASDAF", 0};

bool isADangerousMove (Cookie& cookie, int column, int row);
bool computerPlayerMustLose
(Cookie& cookie, int& column, int& row,
		int maxColumns, int lastNonEmptyRow);
bool computerPlayerCanForceAWin
(Cookie& cookie,
		int& column, int& row,
		int maxColumns, int lastNonEmptyRow);





#endif // COMPUTERPLAYER_H_INCLUDED
