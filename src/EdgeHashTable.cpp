#include "../inc/EdgeHashTable.h"

int edgeHash(Edge* e)
{
    return (e->getLeft() * e->getRight()) % EMOD;
}

int edgeHash(const int lkey, const int rkey)
{
    return (lkey * rkey) % EMOD;
}

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

Edge* EdgeHashTable::search(const int lv, const int rv)
{
    int addr = edgeHash(lv, rv);
    Edge* current = ht[addr];
    while (current != nullptr)
    {
        if (current->getLeft() == lv && current->getRight() == rv)
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
