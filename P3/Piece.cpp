#include "Piece.h"
#include "Well.h"
#include "Game.h"
#include <algorithm>
//------------------------------------------------------------------------------------------------------------------------------------------------
//PIECE FUNCTIONS + CONSTRUCTOR
Piece::Piece() : m_row(0), m_col(4), m_done(false),m_orientation(0),m_BB(4,std::vector<char>(4,' '))
{
}
bool Piece::initialPosition(Well& well)
{

	bool goodToGo = true;
	std::vector<std::vector<char>>& this_board = well.getBoard();
	//beginning position for the piece
	for (int a = accessRow(); a < (accessRow()+4); a++) //rows (y)
	{
		for (int b = accessCol(); b < (accessCol()+4); b++) //columns (x)
		{
			if (accessBB()[a][b - accessCol()] == '#')
			{
				if (this_board[b][a] != '$' && this_board[b][a] != '*')
				{
					well.accessBoard(b, a, m_BB[a][b - accessCol()]);
				}
				else
				{
					goodToGo = false;
				}
			}
		}
	}
	return goodToGo;
}

void Piece::changeOrientation(Well& well)
{
	bool canChange = true;
	std::vector<std::vector<char>>& this_board = well.getBoard();
	std::list<std::vector<std::vector<char>>>::iterator it = accessOri().begin();
	it++;
	std::vector<std::vector<char>> goal_BB = *it;
	for (int a = accessRow(); a < (accessRow() + 4) && a < 19; a++)
	{
		for (int b = accessCol(); b < (accessCol() + 4) && b < 12; b++)
		{
			if ((this_board[b][a] == '$' || this_board[b][a] == '@' || this_board[b][a] == '*') && goal_BB[a - accessRow()][b - accessCol()] == '#')
			{
				canChange = false;
			}
		}
	}
	if (canChange)
	{
		changeOri();
		//then changing the orientation is just changing what m_BB is pointing to 
		std::vector<std::vector<char>> toTheBack = accessOri().front();
		accessOri().pop_front();
		accessOri().push_back(toTheBack);
		std::list <std::vector<std::vector<char>>>::iterator it = accessOri().begin();
		accessBB() = *it;
	}
}

bool Piece::OKtoFall(Well& well)
{
	bool OKtoFall = true;
	std::vector<std::vector<char>>& this_board = well.getBoard();
	for (int a = accessRow(); a < (accessRow() + 4) && a < 18; a++)
	{
		for (int b = accessCol(); b < (accessCol() + 4) && b < 11; b++)
		{
			if (accessBB()[a-accessRow()][b-accessCol()] == '#')
			{
				if (this_board[b][a+1] == '$' || this_board[b][a+1] == '@' || this_board[b][a+1] == '*')
				{
					OKtoFall = false;
				}
			}
		}
	}
	return OKtoFall;
}

void Piece::fall(Well& well)
{
	//keep falling until it reaches the bottom or a block
	if (OKtoFall(well))
	{
		update(well, 0);
	}
	else
	{
		for (int a = accessRow(); a < (accessRow() + 4) && a < 18; a++)
		{
			for (int b = accessCol(); b < (accessCol() + 4) && b < 11; b++)
			{
				if (accessBB()[a - accessRow()][b - accessCol()] == '#')
				{
					well.accessBoard(b, a, '$');
				}
			}
		}
		changeDone(true);
	}
}

bool Piece::shift(Well& well, Screen& screen)
{
	std::vector<std::vector<char>>& this_board = well.getBoard();
	//Repeat as long as before the block moves down
	char ch;
	bool canMove = true;
	if (getCharIfAny(ch))
	{
		//there was a character typed, it's now stored in ch
		switch (ch)
		{
		case 'Q':
		case 'q':
			return false;
		case ARROW_LEFT:
		{
			for (int a = accessRow(); a < (accessRow() + 4) && a < 18; a++)
			{
				for (int b = accessCol(); b < (accessCol() + 4) && b < 11; b++)
				{
					if (accessBB()[a - accessRow()][b - accessCol()] == '#')
					{
						if (this_board[b - 1][a] == '$' || this_board[b - 1][a] == '@' || this_board[b][a] == '*')
							canMove = false;
					}
				}

			}
			if (canMove)
				update(well, 2);
			break;
		}
		case ARROW_RIGHT:
		{
			for (int a = accessRow(); a < (accessRow() + 4) && a < 18; a++)
			{
				for (int b = accessCol(); b < (accessCol() + 4) && b < 11; b++)
				{
					if (accessBB()[a - accessRow()][b - accessCol()] == '#')
					{
						if (this_board[b + 1][a] == '$' || this_board[b + 1][a] == '@' || this_board[b][a] == '*')
							canMove = false;
					}
				}

			}
			if (canMove)
				update(well, 1);
			break;
		}
		case ARROW_DOWN:
		{
			fall(well);
			break;
		}
		case ARROW_UP:
		{
			changeOrientation(well);
			break;
		}
		//SPACE BAR
		case ' ':
			while (OKtoFall(well))
				fall(well);
			break;
		default:
			break;
		}
	}
	return true;
}

void Piece::update(Well& well, int action)
{
	std::vector<std::vector<char>>& this_board = well.getBoard();
	//delete the previous instance
	for (int a = accessRow(); a < (accessRow() + 4) && a < 18; a++)
	{
		for (int b = accessCol(); b < (accessCol() + 4) && b < 11; b++)
		{
			if (this_board[b][a] != '$' && this_board[b][a] != '@' && this_board[b][a] != '*')
				well.accessBoard(b, a, ' ');
		}
	}
	switch (action)
	{
	case 0:
		changeRow(1);
		break;
	case 1:
		changeCol(1);
		break;
	case 2:
		changeCol(-1);
		break;
	default:
		break;
	}
	std::vector<std::vector<char>>& thisBB = accessBB();
	for (int c = accessRow(); c < (accessRow() + 4) && c < 18; c++) //rows (x)
	{
		for (int d = accessCol(); d < (accessCol() + 4) && d < 11; d++) //columns (y)
		{
			if (this_board[d][c] != '$' && this_board[d][c] != '*')
				well.accessBoard(d, c, thisBB[c - accessRow()][d - accessCol()]);
		}
	}
}

void Piece::changeRow(int i)
{
	m_row += i;
}

void Piece::changeCol(int i)
{
	m_col += i;
}

void Piece::changeDone(bool i)
{
	m_done = i;
}

void Piece::changeOri()
{
	m_orientation++;
	if (m_orientation = 4)
		m_orientation = 0;
}

bool Piece::isDone()
{
	return m_done;
}


int Piece::accessRow()
{
	return m_row;
}


int Piece::accessCol()
{
	return m_col;
}

std::vector<std::vector<char>>& Piece::accessBB()
{
	return m_BB;
}

std::list<std::vector<std::vector<char>>>& Piece::accessOri()
{
	return orientations;
}

int Piece::accessmOri()
{
	return m_orientation;
}
//------------------------------------------------------------------------------------------------------------------------------------------------
//OPEICE
OPiece::OPiece() : Piece()
{
	//idea the constructor makes a linked list of the different orientations by using the list class and then adding all the orientations 
	//and then have m_BB point to the first orientation
	std::vector <std::vector<char>> O1 = {
	{'#','#',' ',' '},
	{'#','#',' ',' '},
	{' ',' ',' ',' '},
	{' ',' ',' ',' '}
	};
	std::vector<std::vector<char>> O2 = {
	{ '#','#',' ',' ' },
	{ '#','#',' ',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O3 = {
	{ '#','#',' ',' ' },
	{ '#','#',' ',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O4 = {
	{ '#','#',' ',' ' },
	{ '#','#',' ',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	accessOri().push_back(O1);
	accessOri().push_back(O2);
	accessOri().push_back(O3);
	accessOri().push_back(O4);
	accessBB() = O1;
}

//------------------------------------------------------------------------------------------------------------------------------------------------
//IPiece
IPiece::IPiece() : Piece()
{
	std::vector <std::vector<char>> O1 = {
	{ ' ',' ',' ',' ' },
	{ '#','#','#','#' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O2 = {
	{ ' ','#',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ','#',' ',' ' }
	};
	std::vector<std::vector<char>> O3 = {
	{ ' ',' ',' ',' ' },
	{ '#','#','#','#' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O4 = {
	{ ' ','#',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ','#',' ',' ' }
	};
	accessOri().push_back(O1);
	accessOri().push_back(O2);
	accessOri().push_back(O3);
	accessOri().push_back(O4);
	accessBB() = O1;
}
//------------------------------------------------------------------------------------------------------------------------------------------------
//SPiece
SPiece::SPiece() : Piece()
{
	std::vector <std::vector<char>> O1 = {
	{ ' ',' ',' ',' ' },
	{ ' ','#','#',' ' },
	{ '#','#',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O2 = {
	{ ' ','#',' ',' ' },
	{ ' ','#','#',' ' },
	{ ' ',' ','#',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O3 = {
	{ ' ',' ',' ',' ' },
	{ ' ','#','#',' ' },
	{ '#','#',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O4 = {
	{ ' ','#',' ',' ' },
	{ ' ','#','#',' ' },
	{ ' ',' ','#',' ' },
	{ ' ',' ',' ',' ' }
	};
	accessOri().push_back(O1);
	accessOri().push_back(O2);
	accessOri().push_back(O3);
	accessOri().push_back(O4);
	accessBB() = O1;
}
//------------------------------------------------------------------------------------------------------------------------------------------------
//ZPiece
ZPiece::ZPiece() : Piece()
{
	std::vector <std::vector<char>> O1 = {
	{ ' ',' ',' ',' ' },
	{ '#','#',' ',' ' },
	{ ' ','#','#',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O2 = {
	{ ' ',' ','#',' ' },
	{ ' ','#','#',' ' },
	{ ' ','#',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O3 = {
	{ ' ',' ',' ',' ' },
	{ '#','#',' ',' ' },
	{ ' ','#','#',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O4 = {
	{ ' ',' ','#',' ' },
	{ ' ','#','#',' ' },
	{ ' ','#',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	accessOri().push_back(O1);
	accessOri().push_back(O2);
	accessOri().push_back(O3);
	accessOri().push_back(O4);
	accessBB() = O1;
}
//------------------------------------------------------------------------------------------------------------------------------------------------
//TPiece
TPiece::TPiece() : Piece()
{
	std::vector <std::vector<char>> O1 = {
	{ ' ','#',' ',' ' },
	{ '#','#','#',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O2 = {
	{ ' ','#',' ',' ' },
	{ ' ','#','#',' ' },
	{ ' ','#',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O3 = {
	{ ' ',' ',' ',' ' },
	{ '#','#','#',' ' },
	{ ' ','#',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O4 = {
	{ ' ','#',' ',' ' },
	{ '#','#',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	accessOri().push_back(O1);
	accessOri().push_back(O2);
	accessOri().push_back(O3);
	accessOri().push_back(O4);
	accessBB() = O1;
}
//------------------------------------------------------------------------------------------------------------------------------------------------
//LPiece
LPiece::LPiece() : Piece()
{
	std::vector <std::vector<char>> O1 = {
	{ ' ',' ',' ',' ' },
	{ '#','#','#',' ' },
	{ '#',' ',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O2 = {
	{ '#','#',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O3 = {
	{ ' ',' ',' ',' ' },
	{ ' ',' ','#',' ' },
	{ '#','#','#',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O4 = {
	{ ' ',' ',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ','#','#',' ' }
	};
	accessOri().push_back(O1);
	accessOri().push_back(O2);
	accessOri().push_back(O3);
	accessOri().push_back(O4);
	accessBB() = O1;
}
//------------------------------------------------------------------------------------------------------------------------------------------------
//JPiece
JPiece::JPiece() : Piece()
{
	std::vector <std::vector<char>> O1 = {
	{ ' ',' ',' ',' ' },
	{ ' ','#','#','#' },
	{ ' ',' ',' ','#' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O2 = {
	{ ' ',' ',' ',' ' },
	{ ' ',' ','#',' ' },
	{ ' ',' ','#',' ' },
	{ ' ','#','#',' ' }
	};
	std::vector<std::vector<char>> O3 = {
	{ ' ',' ',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ','#','#','#' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O4 = {
	{ ' ','#','#',' ' },
	{ ' ','#',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	accessOri().push_back(O1);
	accessOri().push_back(O2);
	accessOri().push_back(O3);
	accessOri().push_back(O4);
	accessBB() = O1;
}
//------------------------------------------------------------------------------------------------------------------------------------------------
//vaporBomb
vaporBomb::vaporBomb()
{
	std::vector <std::vector<char>> O1 = {
	{ ' ','#','#',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O2 = {
	{ ' ','#','#',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O3 = {
	{ ' ','#','#',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O4 = {
	{ ' ','#','#',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	accessOri().push_back(O1);
	accessOri().push_back(O2);
	accessOri().push_back(O3);
	accessOri().push_back(O4);
	accessBB() = O1;
}

void vaporBomb::fall(Well & well)
{
	//keep falling until it reaches the bottom or a block
	if (OKtoFall(well))
	{
		update(well, 0);
	}
	else //BLOW UP
	{
		std::vector<std::vector<char>>& this_board = well.getBoard();
		for (int b = accessCol() + 1; b < (accessCol() + 3); b++)
		{
			for (int a = accessRow() - 2; a <= (accessRow() + 2); a++)
			{
				if (a >= 0 && a < 18)
				{
					this_board[b].erase(this_board[b].begin() + a);
					this_board[b].insert(this_board[b].begin(), ' ');
				}
			}
		}
		changeDone(true);
	}
}
//------------------------------------------------------------------------------------------------------------------------------------------------
//foamBomb
foamBomb::foamBomb()
{
	std::vector <std::vector<char>> O1 = {
	{ ' ',' ',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O2 = {
	{ ' ',' ',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O3 = {
	{ ' ',' ',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O4 = {
	{ ' ',' ',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	accessOri().push_back(O1);
	accessOri().push_back(O2);
	accessOri().push_back(O3);
	accessOri().push_back(O4);
	accessBB() = O1;
}

void foamBomb::fall(Well & well)
{
	//keep falling until it reaches the bottom or a block
	if (OKtoFall(well))
	{
		update(well, 0);
	}
	else //BLOW UP AND FOAM
	{
		fill(well, accessRow()+1, accessCol()+1, accessRow()+1, accessCol()+1);
		changeDone(true);
	}
	
}

void foamBomb::fill(Well& well, int bomb_row, int bomb_col, int row, int col)
{
	std::vector<std::vector<char>>& this_board = well.getBoard();
	//base cases
	bool cond1 = (col > 0 && col < 11 && row >= 0 && row < 18);
	bool cond2 = (this_board[col][row] != '$' && this_board[col][row] != '*' && this_board[col][row] != '@');
	bool cond3 = (col > (bomb_col - 3) && col < (bomb_col + 3) && row >(bomb_row - 3) && row < (bomb_row + 3));
	if (cond1 && cond2 && cond3)
		this_board[col][row] = '*';
	else
		return;
	fill(well, bomb_row, bomb_col, row - 1, col);
	fill(well, bomb_row, bomb_col, row + 1, col);
	fill(well, bomb_row, bomb_col, row, col - 1 );
	fill(well, bomb_row, bomb_col, row, col + 1);
}

//------------------------------------------------------------------------------------------------------------------------------------------------
//CrazyPiece
crazyPiece::crazyPiece()
{
	std::vector <std::vector<char>> O1 = {
	{ '#',' ',' ','#' },
	{ ' ','#','#',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' }
	};
	std::vector<std::vector<char>> O2 = {
	{ ' ',' ','#',' ' },
	{ ' ','#',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ',' ','#',' ' }
	};
	std::vector<std::vector<char>> O3 = {
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ','#','#',' ' },
	{ '#',' ',' ','#' }
	};
	std::vector<std::vector<char>> O4 = {
	{ '#',' ',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ','#',' ',' ' },
	{ '#',' ',' ',' ' }
	};
	accessOri().push_back(O1);
	accessOri().push_back(O2);
	accessOri().push_back(O3);
	accessOri().push_back(O4);
	accessBB() = O1;
}
bool crazyPiece::shift(Well & well, Screen & screen)
{
	std::vector<std::vector<char>>& this_board = well.getBoard();
	//Repeat as long as before the block moves down
	char ch;
	bool canMove = true;
	if (getCharIfAny(ch))
	{
		//there was a character typed, it's now stored in ch
		switch (ch)
		{
		case 'Q':
		case 'q':
			return false;
		case ARROW_RIGHT:
		{
			int startColumn;
			if (accessCol() == 0)
				startColumn = 1;
			else
				startColumn = accessCol();
			for (int a = accessRow(); a < (accessRow() + 4) && a < 18; a++)
			{
				for (int b = startColumn; b < (accessCol() + 4) && b < 11; b++)
				{
					if (accessBB()[a - accessRow()][b - accessCol()] == '#')
					{
						if (this_board[b - 1][a] == '$' || this_board[b - 1][a] == '@')
							canMove = false;
					}
				}
			}
			if (canMove)
				update(well, 2);
			break;
		}
		case ARROW_LEFT:
		{
			for (int a = accessRow(); a < (accessRow() + 4) && a < 18; a++)
			{
				for (int b = accessCol(); b < (accessCol() + 4) && b < 11; b++)
				{
					if (accessBB()[a - accessRow()][b - accessCol()] == '#')
					{
						if (this_board[b + 1][a] == '$' || this_board[b + 1][a] == '@')
							canMove = false;
					}
				}
			}
			if (canMove)
				update(well, 1);
			break;
		}
		case ARROW_DOWN:
		{
			fall(well);
			break;
		}
		case ARROW_UP:
		{
			changeOrientation(well);
			break;
		}
		//SPACE BAR
		case ' ':
			while (OKtoFall(well))
				fall(well);
			break;
		default:
			break;
		}
	}
	return true;
}