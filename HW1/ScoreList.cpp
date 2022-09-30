#include "ScoreList.h"

ScoreList::ScoreList() : m_array()
{

}

bool ScoreList::add(unsigned long score)
{
	if (score >= 0 || score <= 100)
	{
		m_array.insert(score);
		return true;
	}
	else
	{
		return false;
	}
}

bool ScoreList::remove(unsigned long score)
{
	//find where the score is
	int pos = m_array.find(score);
	//erase the score at the pos
	bool ans = m_array.erase(pos);
	//true if erase was successful
	if (ans)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int ScoreList::size() const
{
	return m_array.size();
}

unsigned long ScoreList::minimum() const
{
	ItemType x;
	if (m_array.size() == 0)
		return NO_SCORE;
	m_array.get(0, x);
	return x;
}

unsigned long ScoreList::maximum() const
{
	ItemType x;
	if (m_array.size() == 0)
		return NO_SCORE;
	m_array.get(size()-1, x);
	return x;
}
