#pragma once
#include"Edge.h"

class EdgeLinkList
{
private:
	int degree;
public:
	Edge* first;
	EdgeLinkList();
	int getDegree();
	void add(Edge* e);
	void remove(Edge* e);
};

EdgeLinkList::EdgeLinkList()
{
	first = new Edge();
	first->next = first;
	first->prev = first;
	degree = 0;
}

int EdgeLinkList::getDegree()
{
	return degree;
}

void EdgeLinkList::add(Edge* e)
{
	first->next->prev = e;
	e->next = first->next;
	first->next = e;
	e->prev = first;
	degree++;
}

void EdgeLinkList::remove(Edge* e)
{
	if (e == nullptr)
	{
		return;
	}
	e->next->prev = e->prev;
	e->prev->next = e->next;
	degree--;
}
