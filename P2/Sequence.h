#pragma once
#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <string>
using ItemType = std::string;

class Sequence
{
public:
	Sequence(); //makes an empty doubly linked list
	//~Sequence();
	Sequence(const Sequence& s);
	Sequence operator = (const Sequence& s);
	bool empty() const;
	int size() const;
	bool insert(int pos, const ItemType& value);
	int insert(const ItemType& value);
	bool erase(int pos);
	int remove(const ItemType& value);
	bool get(int pos, ItemType& value) const;
	bool set(int pos, const ItemType& value);
	int find(const ItemType& value) const;
	void swap(Sequence& other);
private:
	struct node
	{
		ItemType data;
		node* next;
		node* prev;
	};
	node * head;
	node * tail;
	int m_size;
	int p;
};
#endif // !SEQUENCE_H
int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);