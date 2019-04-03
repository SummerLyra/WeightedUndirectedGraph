#ifndef MIN_SPAN_TREE_H
#define MIN_SPAN_TREE_H
#include <cfloat>

struct MSTEdgeNode
{
    int left;
    int right;
    double dist;
    MSTEdgeNode* next;

    MSTEdgeNode(int lt = -1, int rt = -1, double d = DBL_MAX, MSTEdgeNode* n = nullptr);
    bool operator<(MSTEdgeNode& m);
};

struct MinSpanTree
{
    MSTEdgeNode* first;
    MSTEdgeNode* last;

    MinSpanTree();
    void insert(MSTEdgeNode* item); //插入最小生成树
};

#endif
