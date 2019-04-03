#ifndef EDGE_H
#define EDGE_H
#include <cfloat>

struct Edge
{
private:
    int left;
    int right;
    double dist;

public:
    Edge* prev;
    Edge* next;
    Edge* link;
    Edge* partner;

    Edge(int lt = -1, int rt = -1, double d = DBL_MAX, Edge* p = nullptr, Edge* n = nullptr, Edge* l = nullptr, Edge* pt = nullptr);
    int getLeft();
    int getRight();
    void setDist(double d);
    double getDist();
};

#endif
