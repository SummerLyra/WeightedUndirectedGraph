#ifndef VERTEX_H
#define VERTEX_H
#include "EdgeLinkedList.h"

struct Vertex
{
private:
    int data;

public:
    int pos;
    Vertex* prev;
    Vertex* next;
    Vertex* link;
    Vertex* linkByPos;
    EdgeLinkedList* attach;

    Vertex(int num = -1, int d = -1, Vertex* p = nullptr, Vertex* n = nullptr, Vertex* l = nullptr, Vertex* lbp = nullptr, EdgeLinkedList* a = nullptr);
    int getData();
    bool isIsolated();
};

#endif
