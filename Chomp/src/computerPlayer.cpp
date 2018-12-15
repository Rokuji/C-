#include <cstdlib>
#include <sys/types.h>
#include <ctime>
#include "Player.h"
#include "cookie.h"


bool isADangerousMove (Cookie& cookie, int column, int row)
{
	// Always dangerous to eat the poison crumb
	if (column == 0 && row == 0)
		return true;

	// Dangerous to leave only one row or one column unless
	// it has only one element (the poison)
	if (column == 0 && row > 1)
		return true;
	if (row == 0 && column > 1)
		return true;

	// Dangerous to take element (1,1) if the #rows and #cols are equal
	if (row == 1 && column == 1 &&
			getNumberOfRows(cookie) == getNumberOfColumns(cookie))
		return true;

	// Dangerous to take element (2,0) if the th remaining two rows
	//   are equal length
	if (row == 2 && column == 0
			&& getNumberOfColumns(cookie,0) == getNumberOfColumns(cookie,1))
		return true;

	// Dangerous to take element (2,0) if the the remaining two cols
	//   are equal length
	if (row == 0 && column == 2
			&& getNumberOfColumns(cookie, getNumberOfRows(cookie)-1) > 1)
		return true;

	return false;
}
bool computerPlayerMustLose
(Cookie& cookie, int& column, int& row,
		int maxColumns, int lastNonEmptyRow)
{
	if (getNumberOfColumns(cookie,0) == 1 && getNumberOfColumns(cookie,1) == 0)
	{
		// We have to bite the poison crumb.
		column = row = 0;
		return true;
	}
	return false;
}
bool computerPlayerCanForceAWin
(Cookie& cookie,
		int& column, int& row,
		int maxColumns, int lastNonEmptyRow)
{
	// We can force a win if there is only one row and that has
	//   more than one column
	if (getNumberOfRows(cookie) == 1 && getNumberOfColumns(cookie,0) > 1)
	{
		column = 1;
		row = 0;
		return true;
	}
	// Or if there is only one column and that has more than one row
	if (getNumberOfColumns(cookie) == 1 && getNumberOfRows(cookie) > 1)
	{
		column = 0;
		row = 1;
		return true;
	}



	// If row 0 is the only row with more than 1 column, and
	// column 0 is the only column with more than 1 row, and the number of
	// elements in each are different, then we can force an eventual win
	// by evening them up.
	if (getNumberOfRows(cookie) != getNumberOfColumns(cookie) &&
			getNumberOfRows(cookie) > 1 &&
			getNumberOfColumns(cookie) > 1 &&
			getNumberOfColumns(cookie,1) == 1)
	{
		if (getNumberOfRows(cookie) > getNumberOfColumns(cookie))
		{
			column = 0;
			row = getNumberOfColumns(cookie);
		}
		else
		{
			row = 0;
			column = getNumberOfRows(cookie);
		}
		return true;
	}





	// More subtly, if we are down to two rows and the number of columns
	//   in each is different, we can force an eventual win by evening them
	//   up.
	if (getNumberOfRows(cookie) == 2 && getNumberOfColumns(cookie,0) != getNumberOfColumns(cookie,1))
	{
		row = 0;
		column = getNumberOfColumns(cookie,1);
		return true;
	}
	// Or, if we are down to two columns and the number of rows
	//   in each is different, we can force an eventual win by evening them
	//   up.
	if (getNumberOfColumns(cookie) == 2 && getNumberOfColumns(cookie,getNumberOfRows(cookie)-1) == 1)
	{
		column = 0;
		row = 1;
		while (getNumberOfColumns(cookie,row) == 2)
			++row;
		return true;
	}


	// If none of those are true, no obvious way to force a win
	return false;
}

void getComputerPlayerMove (Cookie& cookie, int& column, int& row)
{
	// Collect some basic info about the shape of the cookie
	int maxColumns = getNumberOfColumns(cookie,0);
	int lastNonEmptyRow = -1;
	for (int r = 0; r < getNumberOfRows(cookie); ++r)
	{
		if (getNumberOfColumns(cookie,r) > maxColumns)
			maxColumns = getNumberOfColumns(cookie,r);
		if (getNumberOfColumns(cookie,r) <= 0)
			lastNonEmptyRow = r;
	}

	// If we can force a win, do it.
	if (computerPlayerCanForceAWin(cookie, column, row, maxColumns, lastNonEmptyRow))
	{
		cout << "You're not going to like this..." << endl;
		return;
	}

	// If we are forced to lose, so be it.
	if (computerPlayerMustLose(cookie, column, row, maxColumns, lastNonEmptyRow))
	{
		cout << "Alas!" << endl;
		return;
	}

	// Otherwise, choose a random move, but try to find one
	// that is not obviously dangerous;
	cout << "Hmm..." << endl;
	const int LIMIT = 10;
	row = rand() % lastNonEmptyRow;
	column = rand() % getNumberOfColumns(cookie,row);
	for (int attempt = 0; attempt < LIMIT
	&& isADangerousMove(cookie, column, row);
	++attempt)
	{
		row = rand() % lastNonEmptyRow;
		column = rand() % getNumberOfColumns(cookie,row);
	}

}

