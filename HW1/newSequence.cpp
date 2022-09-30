#include "newSequence.h"
#include <iostream>
// Create an empty sequence that holds DEFAULT_MAX_ITEMS (i.e., one with no items)
Sequence::Sequence()
{
	m_size = 0;
	m_length = DEFAULT_MAX_ITEMS;
	m_array = new string[DEFAULT_MAX_ITEMS];
}
//Create an empty sequence that holds size
Sequence::Sequence(int size)
{
	m_size = 0;
	m_length = size;
	m_array = new string[size];
}

Sequence::~Sequence()
{
	delete[]m_array;
}

Sequence Sequence::operator=(const Sequence& seq)
{
	Sequence copied;
	copied.m_array = seq.m_array;
	copied.m_length = seq.m_length;
	copied.m_size = seq.m_size;
	copied.p = seq.p;
	return copied;
}

// Return true if the sequence is empty, otherwise false.
bool Sequence::empty()
{
	if (m_size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Return the number of items in the sequence.
int Sequence::size()
{
	return m_size;
}

bool Sequence::insert(int pos, const std::string& value)
{
	if ((pos >= 0 || pos <= size()) && pos < m_length)
	{
		//Allocate a new[] array and store it in a temporary pointer.
		m_size = m_size + 1;
		string * temp_array = new string[m_size];
		//Copy over the previous values that you want to keep.
		for (int i = 0; i < pos; i++)
			temp_array[i] = m_array[i];
		temp_array[pos] = value;
		for (int j = pos + 1; j < size(); j++)
			temp_array[j] = m_array[j - 1];
		//Delete[] the old array.
		delete[] m_array;
		//Change the member variables, ptr and size to point to the new array and hold the new size.
		m_array = temp_array;
		return true;
	}
	else
	{
		return false;
	}
}

int Sequence::insert(const std::string& value)
{
	//if the array is filled
	if (size() == m_length)
	{
		p = -1;
		return p;
	}
	//if, it is not, find p
	for (int i = 0; i < size(); i++)
	{
		if (value <= m_array[i])
		{
			p = i;
			insert(p, value);
			return p;
		}
	}
	//if none of the values are greater than or equal to value, make p equal size 
	p = size();
	insert(p, value);
	return p;
}

bool Sequence::erase(int pos)
{
	if (pos >= 0 && pos < size())
	{
		string * temp_Array = new string[m_size];
		for (int i = 0; i < pos; i++)
			temp_Array[i] = m_array[i];
		for (int j = pos + 1; j < size(); j++)
			temp_Array[j - 1] = m_array[j];
		m_size--;
		delete[] m_array;
		m_array = temp_Array;
		return true;
	}
	else
	{
		return false;
	}
}

int Sequence::remove(const std::string& value)
{
	int count = 0;
	for (int i = 0; i < size(); i++)
	{
		if (value == m_array[i])
		{
			count++;
			erase(i);
		}
	}
	return count;
}

bool Sequence::get(int pos, std::string& value)
{
	if (pos >= 0 && pos < size())
	{
		value = m_array[pos];
		return true;
	}
	else
	{
		return false;
	}
}

bool Sequence::set(int pos, const std::string& value)
{
	if (pos >= 0 || p < size()) {
		m_array[pos] = value;
		return true;
	}
	else
		return false;
}

int Sequence::find(const std::string& value)
{
	p = -1;
	for (int i = 0; i < size(); i++)
	{
		if (m_array[i] == value)
		{
			p = i;
			goto outside;
		}
	}
outside:
	return p;
}

void Sequence::swap(Sequence& other)
{
	ItemType* t1 = other.m_array;
	ItemType* t2 = this->m_array;
	other.m_array = this->m_array;
	this->m_array = t1;
}