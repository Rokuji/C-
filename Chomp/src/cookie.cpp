
#include "cookie.h"
#include <cstdlib>
#include <ctime>

int getNumberOfColumns(const Cookie& cookie, int rowNum)
{
	return cookie.crumbs[rowNum];
}

/**
 * Number of non-empty columns currently remaining in the cookie
 * @param cookie the cookie
 * @return number of non-empty columns
 */
int getNumberOfColumns(const Cookie& cookie)
{
	return cookie.numberOfColumns;
}

/**
 * Number of non-empty rows currently remaining in the cookie
 *    (value decreases as we continue to take bites)
 *
 * @param cookie the cookie
 * @return number of non-empty rows in the cookie
 */
int getNumberOfRows(const Cookie& cookie)
{
	return cookie.numberOfRows;
}


/**
 * The number of rows remaining in a specific column
 * @param cookie   the cookie
 * @param colNum   a column number in the cookie
 * @return   number of non-empty rows remaining in that column
 */
int getNumberOfRows(const Cookie& cookie, int colNum)
{
	int k = 0;
	while (k < cookie.numberOfRows && cookie.crumbs[k] > colNum)
		++k;
	return k;
}
/**
 * Remove the crumb at the indicated position and
 *   all crumbs below and to the right of that position.
 * @param cookie   cookie from which we want to take a bite
 * @param column   column of desired bite
 * @param row      row of desired biete
 */
void takeABite (Cookie& cookie, int column, int row)
{
	for (int r = row; r < cookie.numberOfRows; ++r)
	{
		int c = cookie.crumbs[r];
		if (c > column)
			cookie.crumbs[r] = column;
	}
	cookie.numberOfRows = 0;
	for (int r = 0; r < cookie.initialNumberOfRows && cookie.crumbs[r] > 0; ++r)
	{
		cookie.numberOfRows = r + 1;
	}
	cookie.numberOfColumns = (cookie.numberOfRows > 0) ? cookie.crumbs[0] : 0;
}

/**
 * Set up a new cookie of random size
 * @param cookie output - the cookie
 */
void initCookie(Cookie& cookie)
{
	const int MAXROWS = 10;

	// Randomply select size of the cookie, between 4 and MAXROWS
	cookie.initialNumberOfRows = cookie.numberOfRows = 4 + rand() % (MAXROWS - 4);
	cookie.crumbs = new int[cookie.initialNumberOfRows];
	cookie.numberOfColumns = cookie.numberOfRows;
	while (cookie.numberOfColumns == cookie.numberOfRows)
		cookie.numberOfColumns = 4 + rand() % (MAXROWS - 4);
	for (int row = 0; row < cookie.numberOfRows; ++row)
		cookie.crumbs[row] = cookie.numberOfColumns;
}

void cleanUpCookie(Cookie& cookie)
{
	delete [] cookie.crumbs;
}
