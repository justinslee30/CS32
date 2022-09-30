#pragma once
#ifndef Flatulan_H
#define Flatulan_H
class City;

class Flatulan
{
public:
	// Constructor
	Flatulan(City* cp, int r, int c);

	// Accessors
	int  row() const;
	int  col() const;

	// Mutators
	void move();
	bool possiblyGetConverted();

private:
	City * m_city;
	int   m_row;
	int   m_col;
};
#endif
