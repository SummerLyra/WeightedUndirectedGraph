#pragma once
#include"Vertex.h"

class VertexLinkList
{
private:
	int count;
public:
	Vertex* first;
	VertexLinkList();
	int getCount();
	void add(Vertex* v);
	void remove(Vertex* v);
};

VertexLinkList::VertexLinkList()
{
	first = new Vertex();
	first->next = first;
	first->prev = first;
	count = 0;
}

int VertexLinkList::getCount()
{
	return count;
}

void VertexLinkList::add(Vertex* v)
{
	first->next->prev = v;
	v->next = first->next;
	first->next = v;
	v->prev = first;
	count++;
}

void VertexLinkList::remove(Vertex* v)
{
	if (v == nullptr)
	{
		return;
	}
	v->next->prev = v->prev;
	v->prev->next = v->next;
	delete v;
	count--;
}
