#pragma once
#ifndef City_H
#define City_H
#include "History.h"
#include "globals.h"
class Player;
class Flatulan;

class City
{
public:
	// Constructor/destructor
	City(int nRows, int nCols);
	~City();

	// Accessors
	int     rows() const;
	int     cols() const;
	Player* player() const;
	int     flatulanCount() const;
	int     nFlatulansAt(int r, int c) const;
	bool    isPlayerAt(int r, int c) const;
	bool    determineNewPosition(int& r, int& c, int dir) const;
	void    display() const;
	History& history();

	// Mutators
	bool  addFlatulan(int r, int c);
	bool  addPlayer(int r, int c);
	void  preachToFlatulansAroundPlayer();
	void  moveFlatulans();


private:
	int       m_rows;
	int       m_cols;
	Player*   m_player;
	Flatulan* m_flatulans[MAXFLATULANS];
	int       m_nFlatulans;
	History   m_history;

	// Helper functions
	bool isInBounds(int r, int c) const;
};
#endif // !City_H

