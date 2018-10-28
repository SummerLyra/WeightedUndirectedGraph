#pragma once
#include<list>
#include"MinSpanTree.h"

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
