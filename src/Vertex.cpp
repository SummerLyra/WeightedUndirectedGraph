#include "../inc/Vertex.h"

Vertex::Vertex(int num, int d, Vertex* p, Vertex* n, Vertex* l, Vertex* lbp, EdgeLinkedList* a) :pos(num), data(d), prev(p), next(n), link(l), linkByPos(lbp), attach(a)
{}

int Vertex::getData()
{
    return data;
}

bool Vertex::isIsolated()
{
    return (attach->first->next == attach->first);
}
