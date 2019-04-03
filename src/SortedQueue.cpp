#include "../inc/SortedQueue.h"

void SortedQueue::insert(MSTEdgeNode x)
{
    edgeList.push_back(x);
}

void SortedQueue::sort()
{
    edgeList.sort();
}

MSTEdgeNode SortedQueue::removeMin()
{
    MSTEdgeNode ed = edgeList.front();
    edgeList.pop_front();
    return ed;
}
