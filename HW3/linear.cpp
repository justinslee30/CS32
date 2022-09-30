//DONE

#include <string>
#include <cassert>
using namespace std;
//predicate used, if the string is empty, return false, else return true
bool somePredicate(string s)
{
	if (s.empty())
	{
		return false;
	}
	else
	{
		return true;
	}
}
// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
	//return false;  // This is not always correct.
	//BASE CASE, if the somePredicate returns true for all
	if (n == 0)
		return true;
	if (somePredicate(a[n-1]) ==  true)
		return allTrue(a,n - 1);
	else
		return false;
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const string a[], int n)
{
	//return -999;  // This is incorrect.
	//the method of a, n- 1 loops the array backward
	//BASE CASE
	if (n == 0)
		return 0;
	//RECURSION
	if (somePredicate(a[n-1]) == false)
	{
		return 1 + countFalse(a, n - 1);
	}
	return countFalse(a, n - 1);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const string a[], int n)
{
	//return -999;  // This is incorrect.
	//the method of a+1, n- 1 loops the array forward
	//BASE CASE
	if (n == 0)
		return -1;
	//RECURSION
	if (somePredicate(a[0]) == false)
	{
		return 0;
	}
	else
	{
		if (firstFalse(a + 1, n - 1) == -1) //this prevents the incrementing if no false is found
			return -1;
		return 1 + firstFalse(a + 1, n - 1);
	}

}

// Return the subscript of the least string in the array (i.e.,
// the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the array has no elements to examine,
// return -1.
int indexOfLeast(const string a[], int n)
{
	//return -999;  // This is incorrect.
	//empty array
	if (n <= 0)
		return -1;
	//recursion part
	int track = 1 + indexOfLeast(a+1,n-1); //how to index through the array recursively
	if (a[0] <= a[track])
	{
		return 0;
	}
	return track;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool includes(const string a1[], int n1, const string a2[], int n2)
{
	//return false;  // This is not always correct.
	//BASE CASE: the empty sequence appears in a sequence of length n1 in 1 way, even if n1 is 0
	if (n2 == 0)
		return true;
	//BASE CASE 2: decreasing n1 and n2 each recursive call, until n1 is 1, then check that the first element of a1 and a2 match
	if (n1 == 1)
	{
		if (n2 == n1 && a1[0] == a2[0])
			return true;
		else
			return false;
	}
	else
	{
		//recursion part
		if (a1[0] == a2[0])
			return includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
		else
			return includes(a1 + 1, n1 - 1, a2, n2);
	}
}

int main()
{
	string c1[3] = { "a","b","c" };
	string c2[3] = { "e", "c", "d" };
	string c3[5] = { "","a","","b","" };
	string c4[10] = { "d","a","b","c","","q","g","p","o","t" };
	string c5[1] = { "a" };
	string c6[1] = { "" };
	assert(allTrue(c1, 3));
	assert(allTrue(c2, 3));
	assert(!allTrue(c3, 5));
	assert(!allTrue(c4, 10));
	assert(allTrue(c5, 1));
	assert(!allTrue(c6, 1));
	assert(countFalse(c1, 3) == 0);
	assert(countFalse(c2, 3) == 0);
	assert(countFalse(c3, 5) == 3);
	assert(countFalse(c4, 10) == 1);
	assert(countFalse(c5, 1) == 0);
	assert(countFalse(c6, 1) == 1);
	assert(firstFalse(c1, 3) == -1);
	assert(firstFalse(c2, 3) == -1);
	assert(firstFalse(c3, 5) == 0);
	assert(firstFalse(c4, 10) == 4);
	assert(firstFalse(c5, 1) == -1);
	assert(firstFalse(c6, 1) == 0);
	assert(indexOfLeast(c1, 3) == 0);
	assert(indexOfLeast(c2, 3) == 1);
	assert(indexOfLeast(c3, 5) == 0);
	assert(indexOfLeast(c4, 10) == 4);
	assert(indexOfLeast(c5, 1) == 0);
	assert(indexOfLeast(c6, 1) == 0);
	string i[7] = { "stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters" };
	string j[3] = { "stan","kenny","cartman" };
	string j2[3] = { "stan", "cartman", "butters" };
	string j3[3] = { "kenny", "stan", "cartman" };
	string j4[3] = { "kyle", "cartman", "butters" };
	assert(includes(i, 7, j, 3));
	assert(includes(i, 7, j2, 3));
	assert(!includes(i, 7, j3, 3));
	assert(includes(i, 7, j4, 3));
}
