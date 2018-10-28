#pragma once
#include"Vertex.h"

const int VMAX = 10000;
const int VMOD = 9973;

int vertexHash(const string& key)
{
	unsigned long h = 0;
	char* ckey = new char[100];
	strcpy(ckey, key.c_str());
	while (*ckey)
	{
		h = (h << 4) + *ckey++;
		unsigned long g = h & 0Xf0000000L;
		if (g) h ^= g >> 24;
		h &= ~g;
	}
	return h % VMOD;
}

int vertexHash(int key)
{
	return key % VMOD;
}

class VertexHashTable
{
private:
	Vertex* ht[VMAX];
	int count;
public:
	VertexHashTable();
	int getCount();
	void add(Vertex* v);
	void addByPos(Vertex* v);
	Vertex* search(const string& key);
	Vertex* search(int key);
	void remove(Vertex* v);
	void removeByPos(Vertex* v);
};

VertexHashTable::VertexHashTable()
{
	for (int i = 0; i < VMAX; i++)
	{
		ht[i] = nullptr;
	}
	count = 0;
}

int VertexHashTable::getCount()
{
	return count;
}

void VertexHashTable::add(Vertex* v)
{
	int addr = vertexHash(v->getData());
	v->link = ht[addr];
	ht[addr] = v;
	count++;
}

void VertexHashTable::addByPos(Vertex* v)
{
	int addr = vertexHash(v->pos);
	v->linkByPos = ht[addr];
	ht[addr] = v;
}

Vertex* VertexHashTable::search(const string& key)
{
	int addr = vertexHash(key);
	Vertex* current = ht[addr];
	while (current != nullptr)
	{
		if (current->getData() == key)
		{
			return current;
		}
		current = current->link;
	}
	return nullptr;
}

Vertex* VertexHashTable::search(int key)
{
	int addr = vertexHash(key);
	Vertex* current = ht[addr];
	while (current != nullptr)
	{
		if (current->pos == key)
		{
			return current;
		}
		current = current->linkByPos;
	}
	return nullptr;
}

void VertexHashTable::remove(Vertex* v)
{
	if (v == nullptr)
	{
		return;
	}
	int addr = vertexHash(v->getData());
	Vertex* front = ht[addr];
	if (v == front)
	{
		ht[addr] = front->link;
	}
	while (front->link != v && v != front)
	{
		front = front->link;
	}
	front->link = v->link;
	count--;
}

void VertexHashTable::removeByPos(Vertex* v)
{
	if (v == nullptr)
	{
		return;
	}
	int addr = vertexHash(v->pos);
	Vertex* front = ht[addr];
	if (v == front)
	{
		ht[addr] = front->linkByPos;
	}
	while (front->linkByPos != v && v != front)
	{
		front = front->linkByPos;
	}
	front->linkByPos = v->linkByPos;
}
