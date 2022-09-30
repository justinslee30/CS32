#include "Sequence.h"

Sequence::Sequence()
{
	m_size = 0;
}

bool Sequence::empty() const
{
	if (m_size == 0)
		return true;
	else
		return false;
}

int Sequence::size() const
{
	return m_size;
}

bool Sequence::insert(int pos, const ItemType& value)
{
	if ((pos >= 0 || pos <= size()) && size() != DEFAULT_MAX_ITEMS)
	{
			for (int i = size(); i > pos; i--)
			{
				m_array[i] = m_array[i - 1];
			}
			m_array[pos] = value;
			m_size++;
			return true;
	}
	else
	{
		return false;
	}

}

int Sequence::insert(const ItemType& value)
{
	//if the array is filled
	if (size() == DEFAULT_MAX_ITEMS)
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
	if (pos >= 0 || p < size())
	{
		for (int i = pos; i < size(); i++)
		{
			m_array[i] = m_array[i + 1];
		}
		m_size--;
		return true;
	}
	else
	{
		return false;
	}
}

int Sequence::remove(const ItemType& value)
{
	int count = 0;
	for (int i = 0; i < size(); i++)
	{
		if (m_array[i] == value)
		{
			erase(i);
			count++;
		}
	}
	return count;
}

bool Sequence::get(int pos, ItemType& value) const
{
	if (pos >= 0 || pos < size())
	{
		value = m_array[pos];
		return true;
	}
	else
	{
		return false;
	}
}

bool Sequence::set(int pos, const ItemType& value)
{
	if (pos >= 0 || pos < size())
	{
		m_array[pos] = value;
		return true;
	}
	else
	{
		return false;
	}
}

int Sequence::find(const ItemType& value) 
{
	p = -1;
	for (int i = 0; i < size(); i++)
	{
		if (m_array[i] == value)
		{
			p = i;
			return p;
		}
	}
	return p;
}

void Sequence::swap(Sequence& other)
{
	//get the larger size
	int size;
	if (m_size > other.m_size)
		size = m_size;
	else
		size = other.m_size;
	//copy the array of this class into a temporary ItemType
	ItemType z;
	for (int i = 0; i < size; i++)
	{
		z = m_array[i];
		m_array[i] = other.m_array[i];
		other.m_array[i] = z;
	}
	int switch_size = m_size;
	m_size = other.m_size;
	other.m_size = switch_size;
}