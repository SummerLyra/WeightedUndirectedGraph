#pragma once
#include<string>

using std::string;

struct Edge
{
private:
	string left;
	string right;
	double dist;
public:
	Edge* prev;
	Edge* next;
	Edge* link;
	Edge* partner;
	Edge(string lt = "", string rt = "", double d = DBL_MAX, Edge* p = nullptr, Edge* n = nullptr, Edge* l = nullptr, Edge* pt = nullptr) :left(lt), right(rt), dist(d), prev(p), next(n), link(l), partner(pt) {}
	string getLeft()
	{
		return left;
	}
	string getRight()
	{
		return right;
	}
	void setDist(double d)
	{
		dist = d;
	}
	double getDist()
	{
		return dist;
	}
};
