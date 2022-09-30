//DONE

#include <stack>
#include <iostream>
using namespace std;

//create a class Coord that represents a coordinate pair
class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};
//function declaration
bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	if (sr == er && sc == ec)
		return true;
	else
	{
		maze[sr][sc] = 'O';
		//NORTH
		if (sr != 0 && maze[sr + 1][sc] != 'O' && maze[sr + 1][sc] != 'X')
			if (pathExists(maze, sr + 1, sc, er, ec))
				return true;
		//WEST
		if (sc != 0 && maze[sr][sc - 1] != 'O' && maze[sr][sc - 1] != 'X')
			if (pathExists(maze, sr, sc - 1, er, ec))
				return true;
		//SOUTH
		if (sr != 9 && maze[sr - 1][sc] != 'O' && maze[sr - 1][sc] != 'X')
			if (pathExists(maze, sr - 1, sc, er, ec))
				return true;
		//EAST
		if (sc != 9 && maze[sr][sc + 1] != 'O' && maze[sr][sc + 1] != 'X')
			if (pathExists(maze, sr, sc + 1, er, ec))
				return true;
	}
	return false;
}
