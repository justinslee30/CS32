//DONE

#include <string>
#include <cassert>
using namespace std;
// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then for this value of a2            the function must return
//    "stan" "kenny" "cartman"                      1
//    "stan" "cartman" "butters"                    2
//    "kenny" "stan" "cartman"                      0
//    "kyle" "cartman" "butters"                    3
int countIncludes(const string a1[], int n1, const string a2[], int n2)
{
	//BASE CASE: the empty sequence appears in a sequence of length n1 in 1 way, even if n1 is 0
	if (n2 == 0)
		return 1;
	//BASE CASE 2: decreasing n1 and n2 each recursive call, until n1 is 1, then check that the first element of a1 and a2 match
	if (n1 == 1)
	{
		if (n2 == n1 && a1[0] == a2[0])
			return 1;
		else
			return 0;
	}
	else
	{
		//recursion part, every time the if statement is true, more recursive calls made to the function
		if (a1[0] == a2[0])
			return countIncludes(a1+1, n1 - 1, a2, n2) + countIncludes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
		else
			return countIncludes(a1 + 1, n1 - 1, a2, n2);
	}
}

// Exchange two strings
void exchange(string& x, string& y)
{
	string t = x;
	x = y;
	y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is < separator come before all the other elements,
// and all the elements whose value is > separator come after all
// the other elements.  Upon return, firstNotLess is set to the
// index of the first element in the rearranged array that is
// >= separator, or n if there is no such element, and firstGreater is
// set to the index of the first element that is > separator, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotLess, a[i] < separator
//   * for firstNotLess <= i < firstGreater, a[i] == separator
//   * for firstGreater <= i < n, a[i] > separator
// All the elements < separator end up in no particular order.
// All the elements > separator end up in no particular order.
void separate(string a[], int n, string separator,
	int& firstNotLess, int& firstGreater)
{
	if (n < 0)
		n = 0;

	// It will always be the case that just before evaluating the loop
	// condition:
	//  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
	//  Every element earlier than position firstNotLess is < separator
	//  Every element from position firstNotLess to firstUnknown-1 is
	//    == separator
	//  Every element from firstUnknown to firstGreater-1 is not known yet
	//  Every element at position firstGreater or later is > separator

	firstNotLess = 0;
	firstGreater = n;
	int firstUnknown = 0;
	while (firstUnknown < firstGreater)
	{
		if (a[firstUnknown] > separator)
		{
			firstGreater--;
			exchange(a[firstUnknown], a[firstGreater]);
		}
		else
		{
			if (a[firstUnknown] < separator)
			{
				exchange(a[firstNotLess], a[firstUnknown]);
				firstNotLess++;
			}
			firstUnknown++;
		}
	}
}

// Rearrange the elements of the array so that
// a[0] <= a[1] <= a[2] <= ... <= a[n-2] <= a[n-1]
// If n <= 1, do nothing.
void order(string a[], int n)
{
	if (n <= 1)
		return;
	int mid = (n+1) / 2;
	int firstNotless = 0;
	int firstGreater = n;
	separate(a, n, a[mid], firstNotless, firstGreater);
	order(a, firstNotless);
	order(a + firstNotless, n- firstGreater);
}

int main()
{
	string i[7] = { "stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters" };
	string j[3] = { "stan","kenny","cartman" };
	string j2[3] = { "stan", "cartman", "butters" };
	string j3[3] = { "kenny", "stan", "cartman" };
	string j4[3] = { "kyle", "cartman", "butters" };
	string k[1] = { "j" };
	string l[2] = { "j","a" };
	assert(countIncludes(i, 7, j, 3) == 1);
	assert(countIncludes(i, 7, j2, 3) == 2);
	assert(countIncludes(i, 7, j3, 3) == 0);
	assert(countIncludes(i, 7, j4, 3) == 3);
	order(i, 7);
	order(j, 3);
	order(k, 1);
	order(l, 2);
	assert(i[0] == "butters");
	assert(i[1] == "cartman");
	assert(i[2] == "cartman");
	assert(i[3] == "kenny");
	assert(i[4] == "kyle");
	assert(i[5] == "kyle");
	assert(i[6] == "stan");
	assert(j[0] == "cartman");
	assert(j[1] == "kenny");
	assert(j[2] == "stan");
	assert(k[0] == "j");
	assert(l[0] == "a");
	assert(l[1] == "j");
}
