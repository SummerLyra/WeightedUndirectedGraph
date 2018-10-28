#pragma once
#include<functional>
#include"Edge.h"

using std::hash;

const long long EMAX = 70000;
const long long EMOD = 69997;

int edgeHash(Edge* e)
{
	//unsigned long h = 0;
	//char* ckey = new char[100];
	//strcpy(ckey, (e->getLeft() + e->getRight()).c_str());
	//while (*ckey)
	//{
	//	h = (h << 4) + *ckey++;
	//	unsigned long g = h & 0Xf0000000L;
	//	if (g) h ^= g >> 24;
	//	h &= ~g;
	//}
	//return h % EMOD;
	hash<string> edgeHash;
	return edgeHash(e->getLeft() + e->getRight()) % EMOD;
}

int edgeHash(const string& lkey, const string& rkey)
{
	//unsigned long h = 0;
	//char* ckey = new char[100];
	//strcpy(ckey, (lkey + rkey).c_str());
	//while (*ckey)
	//{
	//	h = (h << 4) + *ckey++;
	//	unsigned long g = h & 0Xf0000000L;
	//	if (g) h ^= g >> 24;
	//	h &= ~g;
	//}
	//return h % EMOD;
	hash<string> edgeHash;
	return edgeHash(lkey + rkey) % EMOD;
}


class EdgeHashTable
{
private:
	Edge* ht[EMAX];
	int count;
public:
	EdgeHashTable();
	int getCount();
	void add(Edge* e);
	Edge* search(const string& lkey, const string& rkey);
	void remove(Edge* e);
};

EdgeHashTable::EdgeHashTable()
{
	for (int i = 0; i < EMAX; i++)
	{
		ht[i] = nullptr;
	}
	count = 0;
}

int EdgeHashTable::getCount()
{
	return count;
}

void EdgeHashTable::add(Edge* e)
{
	int addr = edgeHash(e);
	e->link = ht[addr];
	ht[addr] = e;
	count++;
}

Edge* EdgeHashTable::search(const string& lkey, const string& rkey)
{
	int addr = edgeHash(lkey, rkey);
	Edge* current = ht[addr];
	while (current != nullptr)
	{
		if (current->getLeft() == lkey && current->getRight() == rkey)
		{
			return current;
		}
		current = current->link;
	}
	return nullptr;
}

void EdgeHashTable::remove(Edge* e)
{
	if (e == nullptr)
	{
		return;
	}
	int addr = edgeHash(e);
	Edge* front = ht[addr];
	if (e == front)
	{
		ht[addr] = front->link;
	}
	while (front->link != e && e != front)
	{
		front = front->link;
	}
	front->link = e->link;
	count--;
}
