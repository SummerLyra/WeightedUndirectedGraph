#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <fstream>
#include "VertexHashTable.h"
#include "VertexLinkedList.h"
#include "EdgeHashTable.h"
#include "UnionFindSet.h"
#include "SortedQueue.h"

using std::cout;
using std::endl;
using std::ios;
using std::ifstream;
using std::ofstream;

class Graph
{
private:
    VertexHashTable* vht;
    VertexHashTable* pht;
    VertexLinkedList* vll;
    EdgeHashTable* eht;
    int nowpos;

public:
    Graph();
    void readFile();
    void writeFile();
    int vertexCount();
    int edgeCount();
    Vertex** getVertices();
    void addVertex(const int d);
    void addVertexWithoutWrite(const int d);
    void removeVertex(const int d);
    Vertex* isVertex(const int d);
    Vertex* findVertexByPos(int p);
    int degree(const int d);
    Vertex* getFirstNeighbor(const int d);
    Vertex* getNextNeighbor(const int d, const int f);
    void addEdge(const int lt, const int rt, double d);
    void addEdgeWithoutWrite(const int lt, const int rt, double d);
    void removeEdge(const int lt, const int rt);
    Edge* isEdge(const int lt, const int rt);
    bool isEdgeInHashTable(const int lt, const int rt);
    double weight(const int lt, const int rt);
    void updateWeight(const int lt, const int rt, double d);
    bool isEmpty();
    bool hasIsolated();
    void kruskal();
    void dijkstra(const int lt, const int rt);
    void dijkstra(const int lt, double dt);
    void kruskal(int* ar, int n);
};

#endif
