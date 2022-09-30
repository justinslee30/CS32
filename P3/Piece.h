#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED

#include "UserInterface.h"
#include <list> //linked list for the orientations
#include <vector> //for the 2D array for the bounding box
class Well;
enum PieceType {
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
    PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES
};
//Normal Piece Subclass
// T L J O S Z I
//Special Piece Subclass
//vaporbomb foam bomb special piece

//Piece Superclass
class Piece
{
public:
	Piece(); //CONSTRUCTOR
	virtual ~Piece() { }; //DESTRUCTOR
	//MUTATORS
	bool initialPosition(Well& well);
	void changeOrientation(Well& well);
	void changeRow(int i);
	void changeCol(int i);
	void changeDone(bool i);
	void changeOri();
	virtual void fall(Well& well);
	void update(Well& well, int action);
	bool OKtoFall(Well& well);
	virtual bool shift(Well& well, Screen& screen);
	//ACCESSORS
	bool isDone();
	int accessRow();
	int accessCol();
	std::vector<std::vector<char>>& accessBB();
	std::list<std::vector<std::vector<char>>>& accessOri();
	int accessmOri();
private:
	std::vector<std::vector<char>> m_BB;
	std::list<std::vector<std::vector<char>>> orientations;
	bool m_done;
	int m_orientation;
	int m_row;
	int m_col;
};

class OPiece : public Piece
{
public:
	OPiece();
	virtual ~OPiece() {};
};

class IPiece : public Piece
{
public:
	IPiece();
	virtual ~IPiece() {};
};

class SPiece : public Piece
{
public:
	SPiece();
	virtual ~SPiece() {};
};

class ZPiece : public Piece
{
public:
	ZPiece();
	virtual ~ZPiece() {};
};

class TPiece : public Piece
{
public:
	TPiece();
	virtual ~TPiece() {};
};

class LPiece : public Piece
{
public:
	LPiece();
	virtual ~LPiece() {};
};

class JPiece : public Piece
{
public:
	JPiece();
	virtual ~JPiece() {};
};

class vaporBomb : public Piece
{
public:
	vaporBomb();
	virtual ~vaporBomb() {};
	virtual void fall(Well& well);
};

class foamBomb : public Piece
{
public:
	foamBomb();
	virtual ~foamBomb() {};
	virtual void fall(Well& well);
	void fill(Well& well, int Bomb_row, int Bomb_col, int row, int col);
};

class crazyPiece : public Piece
{
public:
	crazyPiece();
	virtual ~crazyPiece() {};
	virtual bool shift(Well& well, Screen& screen);
};

PieceType chooseRandomPieceType();

#endif // PIECE_INCLUDED
