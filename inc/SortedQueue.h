#ifndef SORTED_QUEUE_H
#define SORTED_QUEUE_H
#include <list>
#include "MinSpanTree.h"

using std::list;

class SortedQueue
{
private:
    list<MSTEdgeNode> edgeList;

public:
    void insert(MSTEdgeNode x); //插入最小堆
    void sort();
    MSTEdgeNode removeMin(); //保存并删除堆顶上的最小元素
};

#endif
