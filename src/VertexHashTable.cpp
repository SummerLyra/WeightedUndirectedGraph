#include "../inc/VertexHashTable.h"

int vertexHash(int key)
{
    return key % VMOD;
}

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

Vertex* VertexHashTable::search(int key)
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

Vertex* VertexHashTable::searchByPos(int key)
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
