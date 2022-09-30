#include "Well.h"
#include "Piece.h"
#include "UserInterface.h"
#include <iostream>
using namespace std;
//should work on the implementation of the well first (DONE)
Well::Well()  
{
	m_board.resize(12, std::vector<char>(19, ' '));
}

void Well::display(Screen& screen, int x, int y)
{
	screen.clear();
	int m_width = 12;
	int m_length = 19;
	//DRAW THE WELL
	//define your length and width
	//create a Screen instance
	//loop through to create the well (except the last row)
	for (int a = x; a < m_length - 1; a++)
	{
		for (int b = y; b < m_width; b += m_width - 1)
		{
			accessBoard(b, a, '@');
		}
	}
	//create the last row
	for (int c = x; c < m_width; c++)
	{
		accessBoard(c, m_length - 1, '@');
	}
	//display board
	for (int d = x; d < m_length; d++)
	{
		for (int e = y; e < m_width; e++)
		{
			screen.gotoXY(e, d);
			screen.printChar(m_board[e][d]);
		}
	}
}

std::vector<std::vector<char>>& Well::getBoard()
{
	return m_board;
}

void Well::accessBoard(int x, int y, char ch)
{
	m_board[x][y] = ch;
}

void Well::clear(int x, int y)
{
	int m_width = 12;
	int m_length = 19;
	for (int d = 0; d < m_length; d++)
	{
		for (int e = 0; e < m_width; e++)
		{
			if (m_board[e][d] != '@')
				m_board[e][d] = ' ';
		}
	}
}
