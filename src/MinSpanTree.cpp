#include "../inc/MinSpanTree.h"

MSTEdgeNode::MSTEdgeNode(int lt, int rt, double d, MSTEdgeNode* n)
{}

bool MSTEdgeNode::operator<(MSTEdgeNode& m)
{
    return dist < m.dist;
}

MinSpanTree::MinSpanTree()
{
    first = new MSTEdgeNode();
    last = first;
}

void MinSpanTree::insert(MSTEdgeNode* item)
{
    last->next = item;
    last = item;
}
