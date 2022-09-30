#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols) : m_Rows(nRows), m_Cols(nCols)
{
	//initalize grid to 0
	for (int i = 0; i < nRows; i++)
		for (int j = 0; j < nCols; j++)
			grid[i][j] = 0;
}


bool History::record(int r, int c)
{
	//if the row and column are outside the city, then return false
	if (r > m_Rows || c > m_Cols)
		return false;
	else
	{
		//if the row and column are within the city, return true and notifies the history object that a Flatulan at the indicated position was converted upon being preached to
		grid[r-1][c-1] += 1;
		return true;
	}
}

void History::display() const
{
	char newGrid[MAXROWS][MAXCOLS];
	int difference = 'A' - 1;
	for (int r = 0; r < m_Rows; r++)
	{
		for (int c = 0; c < m_Cols; c++)
		{
			if (grid[r][c] == 0)
				newGrid[r][c] = '.';
			else if (grid[r][c] > 0 && grid[r][c] < 26)
				newGrid[r][c] = grid[r][c] + difference;
			else
				newGrid[r][c] = 'Z';
		}
	}
	clearScreen();
	for (int r = 0; r < m_Rows; r++)
	{
		for (int c = 0; c < m_Cols; c++)
			cout << newGrid[r][c];
		cout << endl;
	}
	cout << endl;

}


