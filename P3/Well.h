#ifndef WELL_INCLUDED
#define WELL_INCLUDED

#include <vector>

class Screen;

class Well
{
  public:
	Well();
    void display(Screen& screen, int x, int y);
	void accessBoard(int x, int y, char ch);
	std::vector<std::vector<char>>& getBoard();
	void clear(int x, int y);
private:
	std::vector<std::vector<char>> m_board;
};

#endif // WELL_INCLUDED
