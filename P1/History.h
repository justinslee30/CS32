#pragma once
#ifndef History_H
#define History_H
#include "globals.h"

class History
{
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;
private:
	int m_Rows;
	int m_Cols;
	int grid[MAXROWS][MAXCOLS];
};
#endif // !History_H
