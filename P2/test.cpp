#include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Sequence s;
	assert(s.insert(0, "lavash"));
	assert(s.insert(0, "tortilla"));
	assert(s.size() == 2);
	ItemType x = "injera";
	assert(s.get(0, x) && x == "tortilla");
	assert(s.get(1, x) && x == "lavash");
}

int main()
{
	test();
	// default constructor
	Sequence s;
	// For an empty sequence:
	assert(s.size() == 0);             // test size
	assert(s.empty());                 // test empty
	assert(s.remove("paratha") == 0);  // nothing to remove

	Sequence sq;
	sq.insert(0, "a");
	sq.insert(1, "b");
	sq.insert(2, "b");
	sq.insert(3, "c");
	sq.insert(4, "e");
	assert(sq.remove("b") == 2);
	assert(sq.size() == 3);
	string x;
	assert(sq.get(0, x) && x == "a");
	assert(sq.get(1, x) && x == "c");
	assert(sq.get(2, x) && x == "e");

	Sequence s1;
	s1.insert(0, "paratha");
	s1.insert(0, "focaccia");
	Sequence s2;
	s2.insert(0, "roti");
	s1.swap(s2);
	assert(s1.size() == 1 && s1.find("roti") == 0 && s2.size() == 2 && s2.find("focaccia") == 0 && s2.find("paratha") == 1);
	Sequence s3(s1);
	assert(s3.size() == 1 && s3.find("roti") == 0);
	Sequence s4 = s3;
	assert(s4.size() == 1 && s4.find("roti") == 0);

	Sequence sp;
	sp.insert(0, "dosa");
	sp.insert(1, "pita");
	sp.insert(2, "");
	sp.insert(3, "matzo");
	assert(sp.find("") == 2);
	sp.remove("dosa");
	assert(sp.size() == 3 && sp.find("pita") == 0 && sp.find("") == 1 && sp.find("matzo") == 2);

	Sequence sz;
	sz.insert(0, "30");
	sz.insert(1, "21");
	sz.insert(2, "63");
	sz.insert(3, "42");
	sz.insert(4, "17");
	sz.insert(5, "63");
	sz.insert(6, "17");
	sz.insert(7, "29");
	Sequence sy;
	sy.insert(0, "63");
	sy.insert(1, "17");
	sy.insert(2, "29");
	Sequence sx;
	sx.insert(0, "17");
	sx.insert(1, "63");
	sx.insert(2, "29");
	assert(subsequence(sz, sy) == 5); 
	assert(subsequence(sz, sx) == -1);

	Sequence szz;
	szz.insert(0, "30");
	szz.insert(1, "21");
	szz.insert(2, "63");
	szz.insert(3, "42");
	szz.insert(4, "17");
	szz.insert(5, "63");
	Sequence syy;
	syy.insert(0, "42");
	syy.insert(1, "63");
	syy.insert(2, "84");
	syy.insert(3, "19");
	Sequence result;
	ItemType p;
	interleave(szz, syy, result);
	assert(result.find("30") == 0);
	assert(result.find("42") == 1);
	assert(result.find("21") == 2);
	assert(result.find("63") == 3);
	//assert(result.find("63") == 4);
	assert(result.find("84") == 5);
	//assert(result.find("42") == 6);
	assert(result.find("19") == 7);
	assert(result.find("17") == 8);
	//assert(result.find("63") == 9);

	Sequence sqq;
	sqq.insert(0, "30");
	sqq.insert(1, "25");
	Sequence sll;
	sll.insert(0, "20");
	sll.insert(1, "15");
	Sequence r1;
	interleave(sqq, sll, r1);
	assert(r1.find("30") == 0);
	assert(r1.find("20") == 1);
	assert(r1.find("25") == 2);
	assert(r1.find("15") == 3);

	Sequence sgg;
	sgg.insert(0, "30");
	sgg.insert(1, "25");
	Sequence stt;
	stt.insert(0, "20");
	stt.insert(1, "15");
	stt.insert(2, "5");
	stt.insert(3, "0");
	Sequence r2;
	interleave(sgg, stt, r2);
	assert(r2.find("30") == 0);
	assert(r2.find("20") == 1);
	assert(r2.find("25") == 2);
	assert(r2.find("15") == 3);
	assert(r2.find("5") == 4);
	assert(r2.find("0") == 5);
	cout << "Passed all tests" << endl;
}