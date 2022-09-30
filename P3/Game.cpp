#include "Game.h"
#include "Well.h"
#include "Piece.h"
#include "UserInterface.h"
#include <string>
#include <algorithm>

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 0;
const int WELL_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

Game::Game(int width, int height) : m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_time(), m_score(0), m_rowsLeft(5), m_levelDone(false), m_playingLevel(false)
{
	//fill queue
	for (int a = 0; a < 2; a++)
		generatePiece();
}

void Game::play()
{
    m_well.display(m_screen, WELL_X, WELL_Y);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Chetyris!");
    waitForEnter();  // [in UserInterface.h]

    for(;;)
    {
        if ( ! playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
        m_level++;
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

void Game::displayStatus()
{
    // [Replace this with code to display the status.]
	if (m_playingLevel)
	{
		Piece* next = m_pieces.front();
		m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);
		m_screen.printString("Next Piece: ");
		int y = NEXT_PIECE_Y;
		m_screen.gotoXY(NEXT_PIECE_X, y);
		for (int a = 0; a < 4; a++)
		{
			for (int b = 0; b < 4; b++)
			{
				std::cout << next->accessBB()[a][b];
			}
			y++;
			m_screen.gotoXY(NEXT_PIECE_X, y);
		}
	}
	m_screen.gotoXY(SCORE_X, SCORE_Y);
	m_screen.printString("Score:             " + std::to_string(m_score));
	m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
	m_screen.printString("Rows Left:         " + std::to_string(m_rowsLeft));
	m_screen.gotoXY(LEVEL_X, LEVEL_Y);
	m_screen.printString("Level:             " + std::to_string(m_level));

}

void Game::checkRowFilled()
{
	bool isRowFilled = true;
	int numRowsFilled = 0;
	std::vector<int> rowsToDelete;
	std::vector<std::vector<char>>& this_board = m_well.getBoard();
	for (int a = 17; a >= 0; a--)//rows
	{
		for (int b = 1; b < 11; b++)//columns
		{
			if (this_board[b][a] != '$' && this_board[b][a] != '*')
			{
				isRowFilled = false;
				break;
			}
		}
		if (isRowFilled)
		{
			numRowsFilled++;
			rowsToDelete.push_back(a);
		}
		isRowFilled = true;
	}
	for (unsigned int c = 0; c < rowsToDelete.size(); c++)
	{
		deleteRow(rowsToDelete[c]);
		if (c + 1 != rowsToDelete.size())
			rowsToDelete[c + 1] += 1;
	}
	//add to score
	switch (numRowsFilled)
	{
	case 1:
		m_score += 100;
		m_rowsLeft--;
		break;
	case 2:
		m_score += 200;
		m_rowsLeft -= 2;
		break; 
	case 3:
		m_score += 400;
		m_rowsLeft -= 3;
		break;
	case 4:
		m_score += 800;
		m_rowsLeft -= 4;
		break;
	case 5:
		m_score += 1600;
		m_rowsLeft -= 5;
		break;
	default:
		break;
	}
}

void Game::deleteRow(int rowToDelete)
{
	std::vector<std::vector<char>>& this_board = m_well.getBoard();
	for (unsigned int i = 0; i < this_board.size(); i++)
	{
		if (this_board[i].size() > rowToDelete)
		{
			this_board[i].erase(this_board[i].begin() + rowToDelete);
			this_board[i].insert(this_board[i].begin(), ' ');
		}
	}
}

void Game::generatePiece()
{
	PieceType pieceChoice = chooseRandomPieceType();
	switch (pieceChoice)
	{
	case PIECE_I:
		m_pieces.push(new IPiece);
		break;
	case PIECE_L:
		m_pieces.push(new LPiece);
		break;
	case PIECE_J:
		m_pieces.push(new JPiece);
		break;
	case PIECE_T:
		m_pieces.push(new TPiece);
		break;
	case PIECE_O:
		m_pieces.push(new OPiece);
		break;
	case PIECE_S:
		m_pieces.push(new SPiece);
		break;
	case PIECE_Z:
		m_pieces.push(new ZPiece);
		break;
	case PIECE_VAPOR:
		m_pieces.push(new vaporBomb);
		break;
	case PIECE_FOAM:
		m_pieces.push(new foamBomb);
		break;
	case PIECE_CRAZY:
		m_pieces.push(new crazyPiece);
		break;
	default:
		break;
	}
}

bool Game::playOneLevel()
{
	bool howItEnd = true;
	m_rowsLeft = 5 * m_level;
	//true - 
	//lets say give them 10 pieces to clear the number of lines or else its over
	while (!m_levelDone) //while the level is not done
	{
		m_playingLevel = true; //you are playing the level
		Piece* current = m_pieces.front(); //get the current piece that will be dropped
		m_pieces.pop(); //then pop it off
		generatePiece(); //then create another piece and place in the queue
		if (current->initialPosition(m_well)) //if the initial position generated is possible, then can play game
		{
			while (!current->isDone())
			{
				Timer t;
				while (t.elapsed() < std::max(1000 - 100 * (m_level - 1), 100))
				{
					m_well.display(m_screen, WELL_X, WELL_Y);
					displayStatus();
					bool QorNot = current->shift(m_well, m_screen);
					if (QorNot == false)
					{
						howItEnd = false;
						return howItEnd;
					}
				}
 				current->fall(m_well);
			}
			checkRowFilled();
			m_well.display(m_screen, WELL_X, WELL_Y);
			displayStatus();
			if (m_rowsLeft <= 4) {
				m_levelDone = true;
				howItEnd = true;
			}
		}
		else //end the game
		{
			m_levelDone = true;
			howItEnd = false;
		}
	}
	m_well.clear(0,0);
	m_levelDone = false;
	return howItEnd;
}

