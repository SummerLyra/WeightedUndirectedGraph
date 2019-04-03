#ifndef EDGE_LINKED_LIST_H
#define EDGE_LINKED_LIST_H
#include "Edge.h"

class EdgeLinkedList
{
private:
    int degree;

public:
    Edge* first;

    EdgeLinkedList();
    int getDegree();
    void add(Edge* e);
    void remove(Edge* e);
};

#endif
