#ifndef EDGE_HASH_TABLE_H
#define EDGE_HASH_TABLE_H
#include "Edge.h"

const int EMAX = 70000;
const int EMOD = 69997;

int edgeHash(Edge* e);

int edgeHash(const int lkey, const int rkey);

class EdgeHashTable
{
private:
    Edge* ht[EMAX];
    int count;

public:
    EdgeHashTable();
    int getCount();
    void add(Edge* e);
    Edge* search(const int lkey, const int rkey);
    void remove(Edge* e);
};

#endif
