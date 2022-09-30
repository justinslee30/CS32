#include "Sequence.h"

//makes an empty doubly linked list 
Sequence::Sequence()
{
	head = nullptr;
	tail = nullptr;
	m_size = 0;
}
/*
Sequence::~Sequence() <-- need to work on this since it does not destruct the linked list correctly, need to ask josh if my linked list created is correct
{
	node* temp = head;
	node *temp1 = new node;
	while (temp != nullptr)
	{
		temp1 = temp->next;
		delete temp;
		temp = temp1;
	}
}
*/
Sequence::Sequence(const Sequence& s) //actually this needs work because it has the same addresses which is not correct
{
	if (s.head == nullptr) //for empty list
		head = tail = nullptr;
	else
	{
		m_size = s.m_size;
		head = s.head;
		node * temp1 = s.head->next;
		node * temp2 = head;
		while (temp1 != nullptr)
		{
			temp2->next = temp1;
			temp2 = temp2->next;
			temp1 = temp1->next;
		}
		tail = temp2;
	}

}

Sequence Sequence::operator=(const Sequence & s)
{
	Sequence copied(s);
	return copied;
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

bool Sequence::insert(int pos, const ItemType & value)
{
	//make a temporary node
	node* n = new node;
	//if the pos is less than zero return false
	if (pos < 0 || pos > size())
	{
		return false;
	}
	//insert a new node if empty
	else if (head == nullptr) 
	{
		//set the data values of n
		n->data = value;
		n->prev = nullptr;
		n->next = nullptr;
		head = n;
		tail = n;
		m_size++;
		return true;
	}
	//insert from front if pos = 0
	else if (pos == 0) 
	{
		node* temp = new node;
		temp->data = value;
		temp->next = head;
		temp->prev = nullptr;
		head = temp;
		m_size++;
		return true;

	}
	//insert at position if pos > 0 and pos != size
	else if (pos > 0 && pos < size()) {
		node *temp1 = head;
		node *temp2 = new node;
		for (int i = 1; i < pos; i++)
		{
			temp1 = temp1->next;
		}
		temp2->data = value;
		temp2->next = temp1->next;
		temp1->next = temp2;
		temp2->prev = temp1;
		m_size++;
		return true;
	}
	//insert at back if pos = size
	else
	{
		node* temp1 = head;
		node* temp = new node;
		temp->data = value;
		temp->next = nullptr;
		while (temp1->next != nullptr)
		{
			temp1 = temp1->next;
		}
		temp1->next = temp;
		temp->prev = temp1;
		tail = temp;
		m_size++;
		return true;
	}
}

int Sequence::insert(const ItemType & value)
{
	node * temp = head;
	for (int i = 1; i < size(); i++) {
		if (value <= temp->data)
		{
			p = i;
			goto outside;
		}
		temp = temp->next;
	}
outside:
	insert(p, value);
	return p;
}

bool Sequence::erase(int pos)
{
	//if the pos is negative, then return false
	if (pos < 0 || head == nullptr)
		return false;
	else
	{
		node *temp = new node;
		node *temp1 = new node;
		//delete from front if pos = 0
		if (pos == 0)
		{
			temp = head;
			head = temp->next;
			head->prev = nullptr;
			delete temp;
			m_size--;
		}
		//delete from a position if pos > 0 and p < size()
		else if (pos > 0 && pos < size())
		{
			temp = head;
			temp1 = temp;
			for (int i = 0; i < pos; i++)
			{
				temp1 = temp;
				temp = temp->next;
			}
			temp1->next = temp->next;
			temp->next->prev = temp1;
			delete temp;
			m_size--;
		}
		//delete from the back if the p = size()
		else
		{
			temp = head;
			temp1 = temp;
			while (temp->next != nullptr)
			{
				temp1 = temp;
				temp = temp->next;
			}
			temp1->next = nullptr;
			delete temp;
			m_size--;
		}
		return true;
	}
}

int Sequence::remove(const ItemType & value)
{
	int i = 0;
	int count = 0;
	if (head == nullptr)
	{
		return count;
	}
	node * temp = head;
	node * temp1 = head->next;
	while (temp->next != nullptr) {
		if (temp->data == value)
		{
			erase(i);
			count++;
		}
		else
		{
			i++;
		}
		temp = temp1;
		temp1 = temp1->next;
	}
	return count;
}

bool Sequence::get(int pos, ItemType & value) const
{
	if (pos >= 0 && pos < size())
	{
		node* temp = head;
		for (int i = 0; i < pos; i++)
		{
			temp = temp->next;
		}
		value = temp->data;
		return true;
	}
	else
	{
		return false;
	}
}

bool Sequence::set(int pos, const ItemType & value)
{
	if (pos >= 0 && pos < size())
	{
		node* temp = head;
		for (int i = 0; i < pos; i++)
		{
			temp = temp->next;
		}
		temp->data = value;
		return true;
	}
	else
	{
		return false;
	}
}

int Sequence::find(const ItemType & value) const //problems with one element linked list and the values at the end
{
	node *temp = head;
	int count = 0;
	//take into account if the linked list is just one element
	while (temp != nullptr) {
		if (temp->data == value)
		{
			return count;
		}
		else 
		{
			temp = temp->next;
			count++;
		}
	}
	return -1;
}

void Sequence::swap(Sequence & other)
{
	//can just switch what the head and tail point too, but be sure to account for different cases (empty list, one-node list, same list)
	node * temp = head;
	node * temp1 = tail;
	int temp_size = m_size;
	this->head = other.head;
	other.head = temp;
	this->tail = other.tail;
	other.tail = temp1;
	m_size = other.m_size;
	other.m_size = temp_size;
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
	int count = -1;
	bool matches;
	int s2_move = 0;
	ItemType s1;
	ItemType s2;
	for (int i = 0; i < seq1.size()-(seq2.size()-1); ++i)
	{
		seq1.get(i, s1);
		seq2.get(0, s2);
		if (s1 == s2)
		{
			count = i;
			matches = true;
			for (int j = 1; j < seq2.size(); ++j)
			{
				seq1.get(i + j, s1);
				seq2.get(j, s2);
				if (s1 != s2)
				{
					matches = false;
					count = -1;
					break;
				}
			}
			if (matches)
				return count;
		}
	}
	return count;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) //need to consider aliasing, is probably just if (&seq1 == &seq2) result = seq1;
{
	ItemType s1;
	ItemType s2;
	int i1 = 0;
	int i2 = 0;
	seq1.get(0, s1);
	seq2.get(0, s2);
	if (seq1.size() == seq2.size())
	{
		for (int i = 0; i < 2 * seq1.size(); ++i)
		{
			//if odd, add  from seq2
			if (i % 2 == 1)
			{
				seq2.get(i2, s2);
				result.insert(i, s2);
				i2++;
			}
			//if even, add from seq1
			else
			{
				seq1.get(i1, s1);
				result.insert(i, s1);
				i1++;
			}
		}
	}
	else if (seq1.size() < seq2.size())
	{
		for (int i = 0; i < 2 * seq1.size(); ++i)
		{
			//if odd, add  from seq2
			if (i % 2 == 1)
			{
				seq2.get(i2, s2);
				result.insert(i, s2);
				i2++;
			}
			//if even, add from seq1
			else
			{
				seq1.get(i1, s1);
				result.insert(i, s1);
				i1++;
			}
		}
		for (int j = 0; j < (seq2.size() - seq1.size()); ++j)
		{
			seq2.get(i2, s2);
			result.insert(2*seq1.size()+j, s2);
			i2++;
		}
	}
	else
	{
		for (int i = 0; i < 2 * seq2.size(); ++i)
		{
			//if odd, add  from seq2
			if (i % 2 == 1)
			{
				seq2.get(i2, s2);
				result.insert(i, s2);
				i2++;
			}
			//if even, add from seq1
			else
			{
				seq1.get(i1, s1);
				result.insert(i, s1);
				i1++;
			}
		}
		for (int j = 0; j < (seq1.size() - seq2.size()); ++j)
		{
			seq1.get(i1, s1);
			result.insert(2 * seq2.size() + j, s1);
			i1++;
		}
	}

}
