#pragma once
#include<string>
#include"EdgeLinkList.h"

using std::string;

struct Vertex
{
private:
	string data;
public:
	int pos;
	Vertex* prev;
	Vertex* next;
	Vertex* link;
	Vertex* linkByPos;
	EdgeLinkList* attach;
	Vertex(int num = -1, string d = "", Vertex* p = nullptr, Vertex* n = nullptr, Vertex* l = nullptr, Vertex* lbp = nullptr, EdgeLinkList* a = nullptr) :pos(num), data(d), prev(p), next(n), link(l), linkByPos(lbp), attach(a) {}
	string getData()
	{
		return data;
	}
	bool isIsolated()
	{
		if (attach->first->next == attach->first)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
