#pragma once
#ifndef Game_H
#define Game_H
class City;

class Game
{
public:
	// Constructor/destructor
	Game(int rows, int cols, int nFlatulans);
	~Game();

	// Mutators
	void play();

	//auxiliary functions
	int decodeDirection(char dir);

private:
	City * m_city;
};
#endif // !Game_H
