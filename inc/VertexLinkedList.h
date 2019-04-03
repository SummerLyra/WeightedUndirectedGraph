#ifndef VERTEX_LINKED_LIST_H
#define VERTEX_LINKED_LIST_H
#include "Vertex.h"

class VertexLinkedList
{
private:
    int count;

public:
    Vertex* first;

    VertexLinkedList();
    int getCount();
    void add(Vertex* v);
    void remove(Vertex* v);
};

#endif
