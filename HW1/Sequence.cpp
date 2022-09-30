#include "Sequence.h"
#include <iostream>
// Create an empty sequence (i.e., one with no items)
Sequence::Sequence()
{
	m_size = 1;
	m_array = new string[m_size];
}

// Return true if the sequence is empty, otherwise false.
bool Sequence::empty()
{
	bool result = true;
	for (int i = 0; i < size(); i++)
	{
		if (m_array[i] != "")
			result = false;
	}
	return result;
}

// Return the number of items in the sequence.
int Sequence::size()
{
	return m_size;
}

bool Sequence::insert(int pos, const std::string& value)
{
	if (pos >= 0 || pos <= size())
	{
		//if the insert is replacing an empty string and is not at the pos size (b/c in that case,would need to 
		if (pos != size() && m_array[pos] == "")
		{
			m_array[pos] = value;
			return true;
		}
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
	return 0;
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

}