#include "../inc/Edge.h"

Edge::Edge(int lt, int rt, double d, Edge* p, Edge* n, Edge* l, Edge* pt) :left(lt), right(rt), dist(d), prev(p), next(n), link(l), partner(pt)
{}

int Edge::getLeft()
{
    return left;
}

int Edge::getRight()
{
    return right;
}

void Edge::setDist(double d)
{
    dist = d;
}

double Edge::getDist()
{
    return dist;
}
