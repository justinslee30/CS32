// Dictionary.cpp

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <utility>  // for swap
#include <functional>
using namespace std;
#define MAX_HASH_TABLE_SIZE 50000

void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

  // This class does the real work of the implementation.
//my bucket is an array of pointers
struct Bucket
{
	list<string> m_sub_bucket;
};

class DictionaryImpl
{
  public:
    DictionaryImpl() {}
    ~DictionaryImpl() {}
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
  private:
	  unsigned hashFunc(string& word) const;
	  Bucket m_buckets[MAX_HASH_TABLE_SIZE];
};

void DictionaryImpl::insert(string word)
{
	removeNonLetters(word);
	if (!word.empty())
	{
		unsigned bucket_num = hashFunc(word);
		m_buckets[bucket_num].m_sub_bucket.push_back(word);
	}
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
	if (callback == nullptr)
		return;

	removeNonLetters(letters);
	if (letters.empty())
		return;

	string permutation = letters;
	do
	{
		unsigned wordp_hash = hashFunc(permutation);
		if (m_buckets[wordp_hash].m_sub_bucket.size() == 0)
		{}
		else
		{
			for (list<string>::const_iterator wordp = m_buckets[wordp_hash].m_sub_bucket.begin(); wordp != m_buckets[wordp_hash].m_sub_bucket.end(); wordp++)
			{
				if (permutation == *wordp)
					callback(*wordp);
			}
		}
		generateNextPermutation(permutation);
	} while (permutation != letters);
}

unsigned DictionaryImpl::hashFunc(string& word) const
{
	hash<string> str_hash;
	unsigned hashValue = str_hash(word);
	return hashValue % MAX_HASH_TABLE_SIZE;
}
/*
void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);
    if ( ! word.empty())
        m_words.push_back(word);
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if (callback == nullptr)
        return;

    removeNonLetters(letters);
    if (letters.empty())
        return;

    string permutation = letters;

    do
    {   
        for (list<string>::const_iterator wordp = m_words.begin();
                                               wordp != m_words.end(); wordp++)
        {   
            if (permutation == *wordp)
                callback(*wordp);
        }
        generateNextPermutation(permutation);
    } while (permutation != letters);
}
 */   
void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
} 
  // Each successive call to this function generates the next permutation of the
  // characters in the parameter.  For example,
  //    string s = "eel";
  //    generateNextPermutation(s);  // now s == "ele"
  //    generateNextPermutation(s);  // now s == "lee"
  //    generateNextPermutation(s);  // now s == "eel"
  // You don't have to understand this function's implementation.
void generateNextPermutation(string& permutation)
{
    string::iterator last = permutation.end() - 1;
    string::iterator p;

    for (p = last; p != permutation.begin()  &&  *p <= *(p-1); p--)
        ;
    if (p != permutation.begin())
    {
        string::iterator q;
        for (q = p+1; q <= last  &&  *q > *(p-1); q++)
            ;
        swap(*(p-1), *(q-1));
    }
    for ( ; p < last; p++, last--)
        swap(*p, *last);
}

//******************** Dictionary functions ********************************

// These functions simply delegate to DictionaryImpl's functions.
// You probably don't want to change any of this code

Dictionary::Dictionary()
{
    m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters,callback);
}
