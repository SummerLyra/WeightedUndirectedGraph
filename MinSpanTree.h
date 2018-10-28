#pragma once
#include<string>

using std::string;

struct MSTEdgeNode
{
	string left;
	string right;
	double dist;
	MSTEdgeNode* next;
	MSTEdgeNode(string lt = "", string rt = "", double d = DBL_MAX, MSTEdgeNode* n = nullptr) :left(lt), right(rt), dist(d), next(n) {}
	bool operator<(MSTEdgeNode& m);

};

bool MSTEdgeNode::operator<(MSTEdgeNode& m)
{
	return dist < m.dist;
}

struct MinSpanTree
{
	MSTEdgeNode* first;
	MSTEdgeNode* last;
	MinSpanTree()
	{
		first = new MSTEdgeNode();
		last = first;
	}
	void insert(MSTEdgeNode* item); //插入最小生成树
};

void MinSpanTree::insert(MSTEdgeNode* item)
{
	last->next = item;
	last = item;
}
