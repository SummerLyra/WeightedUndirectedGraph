#ifndef VERTEX_HASH_TABLE_H
#define VERTEX_HASH_TABLE_H
#include "Vertex.h"

const int VMAX = 10000;
const int VMOD = 9973;

int vertexHash(int key);

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
    Vertex* search(int key);
    Vertex* searchByPos(int key);
    void remove(Vertex* v);
    void removeByPos(Vertex* v);
};

#endif
