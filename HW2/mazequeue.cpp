//DONE

#include <queue>
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

//main function test the pathExist function
int main()
{
	char maze[10][10] = {
	{ 'X','X','X','X','X','X','X','X','X','X' },
	{ 'X','.','.','.','.','.','.','.','.','X' },
	{ 'X','X','X','X','X','.','X','.','X','X' },
	{ 'X','.','.','.','X','.','X','.','.','X' },
	{ 'X','.','X','.','.','.','X','.','.','X' },
	{ 'X','.','X','X','X','.','X','X','X','X' },
	{ 'X','X','X','.','.','.','.','X','.','X' },
	{ 'X','.','X','X','.','X','X','X','.','X' },
	{ 'X','.','.','.','.','X','.','.','.','X' },
	{ 'X','X','X','X','X','X','X','X','X','X' }
	};

	if (pathExists(maze, 6, 5, 8, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}

//function implementation
bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	queue<Coord> coordQueue;
	//Push the starting coordinate (sr,sc) onto the coordinate stack
	Coord start(sr, sc);
	coordQueue.push(start);
	//update maze[sr][sc] to indicate that the algorithm has encountered it(i.e., set maze[sr][sc] to have a value other than '.')
	maze[sr][sc] = '0';
	//While the stack is not empty
	while (!coordQueue.empty())
	{
		Coord current = coordQueue.front();
		//cout << current.r() << " " << current.c() << endl;
		coordQueue.pop();
		if (current.r() == er && current.c() == ec)
			return true;
		// If you can move NORTH and haven't encountered that cell yet, then push the coordinate(r - 1, c) onto the stack and update maze[r - 1][c] to indicate the algorithm has encountered it.
		if (current.r() - 1 >= 0 && maze[current.r() - 1][current.c()] != '0' && maze[current.r() - 1][current.c()] != 'X')
		{
			coordQueue.push(Coord(current.r() - 1, current.c()));
			maze[current.r() - 1][current.c()] = '0';
		}
		//If you can move WEST and haven't encountered that cell yet, then push the coordinate(r, c - 1) onto the stack and update maze[r][c - 1] to indicate the algorithm has encountered it.
		if (current.c() - 1 >= 0 && maze[current.r()][current.c() - 1] != '0' && maze[current.r()][current.c() - 1] != 'X')
		{
			coordQueue.push(Coord(current.r(), current.c() - 1));
			maze[current.r()][current.c() - 1] = '0';
		}
		// If you can move SOUTH and haven't encountered that cell yet, then push the coordinate(r + 1, c) onto the stack and update maze[r + 1][c] to indicate the algorithm has encountered it.
		if (current.r() + 1 >= 0 && maze[current.r() + 1][current.c()] != '0' && maze[current.r() + 1][current.c()] != 'X')
		{
			coordQueue.push(Coord(current.r() + 1, current.c()));
			maze[current.r() + 1][current.c()] = '0';
		}
		//If you can move EAST and haven't encountered that cell yet, then push the coordinate(r, c + 1) onto the stack and update maze[r][c + 1] to indicate the algorithm has encountered it.
		if (current.c() + 1 >= 0 && maze[current.r()][current.c() + 1] != '0'  && maze[current.r()][current.c() + 1] != 'X')
		{
			coordQueue.push(Coord(current.r(), current.c() + 1));
			maze[current.r()][current.c() + 1] = '0';
		}
	}
	//There was no solution, so return false
	return false;
}
