#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include "UserInterface.h"
#include "Piece.h"
#include <string>
#include <queue>
#include <stack>
#include <iostream>
// [Add other #include directives as necessary.]

class Game
{
  public:
    Game(int width, int height);
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
	void checkRowFilled();
	void deleteRow(int m_row);
	void generatePiece();
    // [Add other members as necessary.]

  private:
    Well    m_well;
    Screen  m_screen;
    int     m_level;
	Timer   m_time;
	int		m_score;
	int		m_rowsLeft;
	bool	m_levelDone;
	bool	m_playingLevel;
	std::queue <Piece*> m_pieces;
	std::stack <Piece*> for_next;
    // [Add other members as necessary.]
};

#endif // GAME_INCLUDED
