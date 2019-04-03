#include "../inc/Graph.h"

Graph::Graph()
{
    vht = new VertexHashTable();
    pht = new VertexHashTable();
    vll = new VertexLinkedList();
    eht = new EdgeHashTable();
    nowpos = 0;
}

void Graph::readFile()
{
    ifstream read("source");
    while (true)
    {
        int a, b;
        double e;
        read >> a >> b >> e;
        addEdgeWithoutWrite(a, b, e);
        if (read.eof() != 0)
        {
            break;
        }
    }
    read.close();
    writeFile();
}

void Graph::writeFile()
{
    ofstream write("graph", ios::ate);
    Vertex* current = vll->first->prev;
    while (current != vll->first)
    {
        Edge* e = current->attach->first->prev;
        while (e != current->attach->first)
        {
            if (isEdgeInHashTable(e->getLeft(), e->getRight()) == true)
            {
                write << e->getLeft() << " " << e->getRight() << " " << e->getDist() << endl;
            }
            e = e->prev;
        }
        current = current->prev;
    }
    write << -1;
    write.close();
}

int Graph::vertexCount()
{
    return vht->getCount();
}

int Graph::edgeCount()
{
    return eht->getCount();
}

Vertex** Graph::getVertices()
{
    int vcount = vertexCount();
    Vertex* current = vll->first->prev;
    Vertex** varray = new Vertex * [vcount];
    for (int i = 0; i < vcount; i++)
    {
        varray[i] = current;
        current = current->prev;
    }
    return varray;
}

void Graph::addVertex(const int d)
{
    addVertexWithoutWrite(d);
    writeFile();
}

void Graph::addVertexWithoutWrite(const int d)
{
    if (isVertex(d) != nullptr)
    {
        return;
    }
    Vertex* v = new Vertex(nowpos, d);
    v->attach = new EdgeLinkedList();
    vht->add(v);
    pht->addByPos(v);
    vll->add(v);
    nowpos++;
}

void Graph::removeVertex(const int d)
{
    Vertex* v = isVertex(d);
    if (v == nullptr)
    {
        return;
    }
    while (v->attach->first->next != v->attach->first)
    {
        removeEdge(v->attach->first->next->getLeft(), v->attach->first->next->getRight());
    }
    int p = v->pos;
    vht->remove(v);
    pht->removeByPos(v);
    vll->remove(v);
    Vertex* current = vll->first->next;
    while (current->pos < p)
    {
        current = current->next;
        if (current == vll->first)
        {
            break;
        }
    }
    if (current != vll->first)
    {
        current->pos = p;
    }
    writeFile();
}

Vertex* Graph::isVertex(const int d)
{
    return vht->search(d);
}

Vertex* Graph::findVertexByPos(int p)
{
    return pht->searchByPos(p);
}

int Graph::degree(const int d)
{
    Vertex* v = isVertex(d);
    if (v == nullptr)
    {
        return -1;
    }
    return v->attach->getDegree();
}

Vertex* Graph::getFirstNeighbor(const int d)
{
    Vertex* v = isVertex(d);
    if (v == nullptr)
    {
        return nullptr;
    }
    return isVertex(v->attach->first->next->getRight());
}

Vertex* Graph::getNextNeighbor(const int d, const int f)
{
    Vertex* v = isVertex(d);
    Vertex* front = isVertex(f);
    if (v == nullptr || front == nullptr)
    {
        return nullptr;
    }
    Edge* e = isEdge(d, f);
    if (e == nullptr)
    {
        return nullptr;
    }
    if (e->getRight() == d)
    {
        e = e->partner;
    }
    if (e->next == v->attach->first)
    {
        return nullptr;
    }
    else
    {
        return isVertex(e->next->getRight());
    }
}

void Graph::addEdge(const int lt, const int rt, double d)
{
    addEdgeWithoutWrite(lt, rt, d);
    writeFile();
}

void Graph::addEdgeWithoutWrite(const int lt, const int rt, double d)
{
    if (isEdge(lt, rt) != nullptr)
    {
        return;
    }
    Vertex* l = isVertex(lt);
    Vertex* r = isVertex(rt);
    if (l == nullptr)
    {
        addVertexWithoutWrite(lt);
        l = isVertex(lt);
    }
    if (r == nullptr)
    {
        addVertexWithoutWrite(rt);
        r = isVertex(rt);
    }
    Edge* e1 = new Edge(lt, rt, d);
    Edge* e2 = new Edge(rt, lt, d);
    e1->partner = e2;
    e2->partner = e1;
    eht->add(e1);
    l->attach->add(e1);
    r->attach->add(e2);
}

void Graph::removeEdge(const int lt, const int rt)
{
    Edge* e = isEdge(lt, rt);
    if (e == nullptr)
    {
        return;
    }
    eht->remove(e);
    Edge* ea = e->partner;
    Vertex* l = isVertex(lt);
    Vertex* r = isVertex(rt);
    if (e->getLeft() == lt)
    {
        l->attach->remove(e);
    }
    if (e->getLeft() == rt)
    {
        r->attach->remove(e);
    }
    if (ea->getLeft() == lt)
    {
        l->attach->remove(ea);
    }
    if (ea->getLeft() == rt)
    {
        r->attach->remove(ea);
    }
    delete e;
    delete ea;
    writeFile();
}

Edge* Graph::isEdge(const int lt, const int rt)
{
    if (eht->search(lt, rt) != nullptr)
    {
        return eht->search(lt, rt);
    }
    else
    {
        return eht->search(rt, lt);
    }
}

bool Graph::isEdgeInHashTable(const int lt, const int rt)
{
    if (eht->search(lt, rt) != nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

double Graph::weight(const int lt, const int rt)
{
    Edge* e = isEdge(lt, rt);
    if (e == nullptr)
    {
        return DBL_MAX;
    }
    return e->getDist();
}

void Graph::updateWeight(const int lt, const int rt, double d)
{
    Edge* e = isEdge(lt, rt);
    if (e == nullptr)
    {
        return;
    }
    e->setDist(d);
    e->partner->setDist(d);
}

bool Graph::isEmpty()
{
    return (vertexCount() == 0);
}

bool Graph::hasIsolated()
{
    Vertex* current = vll->first->next;
    while (current != vll->first)
    {
        if (current->attach->getDegree() == 0)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

void Graph::kruskal()
{
    cout << "最小生成树为：" << endl;
    if (isEmpty() == false && hasIsolated() == false)
    {
        MinSpanTree MST;
        MSTEdgeNode ed;
        MSTEdgeNode* p = nullptr;
        int u, v;
        int n = vertexCount();
        int m = edgeCount();
        SortedQueue H;
        UnionFindSet F(n);
        ifstream read("graph");
        while (true)
        {
            int a, b;
            double c;
            read >> a >> b >> c;
            if (a == -1)
            {
                break;
            }
            ed.left = a;
            ed.right = b;
            ed.dist = c;
            H.insert(ed);
            if (read.eof() != 0)
            {
                break;
            }
        }
        read.close();
        H.sort();
        int count = 1;
        while (count < n) //取(n-1)条边
        {
            ed = H.removeMin(); //从最小堆中取出根结点保存在ed中
            u = F.find(isVertex(ed.left)->pos);
            v = F.find(isVertex(ed.right)->pos);
            if (u != v) //若不在同一集合，即u，v不连通
            {
                p = new MSTEdgeNode(ed.left, ed.right, ed.dist);
                //p = new MSTEdgeNode(ed->left, ed->right, ed->dist);
                F.setUnion(u, v); //合并，连通u，v
                MST.insert(p); //插入最小生成树
                count++;
            }
        }
        p = MST.first->next;
        count = 1;
        while (p != nullptr && count < n) //从最小生成树中输出
        {
            cout << p->left << " -- " << p->right << " : " << p->dist << endl;
            p = p->next;
            count++;
        }
    }
    else
    {
        cout << "最小生成树不存在" << endl;
    }
}

void Graph::dijkstra(const int lt, const int rt)
{
    if (isEmpty() == false)
    {
        if (isVertex(lt) == nullptr || isVertex(rt) == nullptr || isVertex(lt)->isIsolated() == true || isVertex(rt)->isIsolated() == true)
        {
            cout << "输入错误" << endl;
            return;
        }
        int n = vertexCount();
        double* dist = new double[n];
        for (int i = 0; i < n; i++)
        {
            dist[i] = DBL_MAX;
        }
        int* path = new int[n];
        bool* s = new bool[n];
        int i, j, k;
        int v = isVertex(lt)->pos;
        int va = isVertex(rt)->pos;
        double w, min;
        ifstream read("graph");
        while (true)
        {
            int a, b;
            double c = 0;
            read >> a;
            if (a == -1)
            {
                break;
            }
            read >> b >> c;
            if (isVertex(a)->pos == v)
            {
                dist[isVertex(b)->pos] = c;
            }
            if (isVertex(b)->pos == v)
            {
                dist[isVertex(a)->pos] = c;
            }
            if (read.eof() != 0)
            {
                break;
            }
        }
        for (i = 0; i < n; i++)
        {
            s[i] = false;
            if (i != v && dist[i] != DBL_MAX)
            {
                path[i] = v;
            }
            else
            {
                path[i] = -1;
            }
        }
        s[v] = true;
        dist[v] = 0;
        for (i = 0; i < n - 1; i++)
        {
            min = DBL_MAX;
            int u = v;
            for (j = 0; j < n; j++)
            {
                if (s[j] == false && dist[j] < min)
                {
                    u = j;
                    min = dist[j];
                }
            }
            s[u] = true;
            w = DBL_MAX;
            for (k = 0; k < n; k++)
            {
                w = weight(findVertexByPos(u)->getData(), findVertexByPos(k)->getData());
                if (s[k] == false && w < DBL_MAX && dist[u] + w < dist[k])
                {
                    dist[k] = dist[u] + w;
                    path[k] = u;
                }
            }
        }
        int* d = new int[n];
        j = va;
        k = 0;
        while (j != v)
        {
            d[k++] = j;
            j = path[j];
        }
        cout << lt << "到" << rt << "间的最短路径为" << endl;
        cout << lt << " -- ";
        while (k > 0)
        {
            if (k != 1)
            {
                cout << findVertexByPos(d[--k])->getData() << " -- ";
            }
            else
            {
                cout << findVertexByPos(d[--k])->getData();
            }
        }
        cout << " : " << dist[va] << endl;
        delete[] d;
        delete[] s;
        delete[] path;
        delete[] dist;
    }
    else
    {
        cout << "输入错误" << endl;
    }
}

void Graph::dijkstra(const int lt, double dt)
{
    if (isEmpty() == false)
    {
        if (isVertex(lt) == nullptr || isVertex(lt)->isIsolated() == true)
        {
            cout << "输入错误" << endl;
            return;
        }
        int n = vertexCount();
        double* dist = new double[n];
        for (int i = 0; i < n; i++)
        {
            dist[i] = DBL_MAX;
        }
        int* path = new int[n];
        bool* s = new bool[n];
        int i, j, k;
        int v = isVertex(lt)->pos;
        double w, min;
        ifstream read("graph");
        while (true)
        {
            int a, b;
            double c = 0;
            read >> a;
            if (a == -1)
            {
                break;
            }
            read >> b >> c;
            if (isVertex(a)->pos == v)
            {
                dist[isVertex(b)->pos] = c;
            }
            if (isVertex(b)->pos == v)
            {
                dist[isVertex(a)->pos] = c;
            }
            if (read.eof() != 0)
            {
                break;
            }
        }
        for (i = 0; i < n; i++)
        {
            s[i] = false;
            if (i != v && dist[i] != DBL_MAX)
            {
                path[i] = v;
            }
            else
            {
                path[i] = -1;
            }
        }
        s[v] = true;
        dist[v] = 0;
        for (i = 0; i < n - 1; i++)
        {
            min = DBL_MAX;
            int u = v;
            for (j = 0; j < n; j++)
            {
                if (s[j] == false && dist[j] < min)
                {
                    u = j;
                    min = dist[j];
                }
            }
            s[u] = true;
            w = DBL_MAX;
            for (k = 0; k < n; k++)
            {
                if (findVertexByPos(u) != nullptr && findVertexByPos(k) != nullptr)
                {
                    w = weight(findVertexByPos(u)->getData(), findVertexByPos(k)->getData());
                    if (s[k] == false && w < DBL_MAX && dist[u] + w < dist[k])
                    {
                        dist[k] = dist[u] + w;
                        path[k] = u;
                    }
                }
            }
        }
        int* d = new int[n];
        cout << "距" << lt << "景点" << dt << "公里内的景点有：" << endl;
        for (i = 0; i < n; i++)
        {
            if (i != v && dist[i] <= dt)
            {
                j = i;
                k = 0;
                while (j != v)
                {
                    d[k++] = j;
                    j = path[j];
                }
                cout << lt << " -- ";
                while (k > 0)
                {
                    if (k != 1)
                    {
                        cout << findVertexByPos(d[--k])->getData() << " -- ";
                    }
                    else
                    {
                        cout << findVertexByPos(d[--k])->getData();
                    }
                }
                cout << " : " << dist[i] << endl;
            }
        }
        delete[] d;
        delete[] s;
        delete[] path;
        delete[] dist;
    }
    else
    {
        cout << "输入错误" << endl;
    }
}

void Graph::kruskal(int* ar, int num)
{
    Graph sub;
    ifstream read("graph");
    while (true)
    {
        int a, b;
        double c;
        read >> a >> b >> c;
        if (a == -1)
        {
            break;
        }
        for (int i = 0; i < num; i++)
        {
            for (int j = i + 1; j < num; j++)
            {
                if ((a == ar[i] && b == ar[j]) || (a == ar[j] && b == ar[i]))
                {
                    sub.addEdgeWithoutWrite(a, b, c);
                }
            }
        }
        if (read.eof() != 0)
        {
            break;
        }
    }
    read.close();
    ofstream write("subgraph", ios::ate);
    Vertex* current = sub.vll->first->prev;
    while (current != sub.vll->first)
    {
        Edge* e = current->attach->first->prev;
        while (e != current->attach->first)
        {
            if (sub.isEdgeInHashTable(e->getLeft(), e->getRight()) == true)
            {
                write << e->getLeft() << " " << e->getRight() << " " << e->getDist() << endl;
            }
            e = e->prev;
        }
        current = current->prev;
    }
    write << -1;
    write.close();
    if (sub.isEmpty() == false && sub.hasIsolated() == false)
    {
        cout << "选出的道路为：" << endl;
        MinSpanTree MST;
        MSTEdgeNode ed;
        MSTEdgeNode* p = nullptr;
        int u, v;
        int n = sub.vertexCount();
        int m = sub.edgeCount();
        SortedQueue H;
        UnionFindSet F(n);
        ifstream read("subgraph");
        while (true)
        {
            int a, b;
            double c;
            read >> a >> b >> c;
            if (a == -1)
            {
                break;
            }
            ed.left = a;
            ed.right = b;
            ed.dist = c;
            H.insert(ed);
            if (read.eof() != 0)
            {
                break;
            }
        }
        read.close();
        H.sort();
        int count = 1;
        while (count < n) //取(n-1)条边
        {
            ed = H.removeMin(); //从最小堆中取出根结点保存在ed中
            u = F.find(sub.isVertex(ed.left)->pos);
            v = F.find(sub.isVertex(ed.right)->pos);
            if (u != v) //若不在同一集合，即u，v不连通
            {
                p = new MSTEdgeNode(ed.left, ed.right, ed.dist);
                F.setUnion(u, v); //合并，连通u，v
                MST.insert(p); //插入最小生成树
                count++;
            }
        }
        p = MST.first->next;
        count = 1;
        while (p != nullptr && count < n) //从最小生成树中输出
        {
            cout << p->left << " -- " << p->right << " : " << p->dist << endl;
            p = p->next;
            count++;
        }
    }
    else
    {
        cout << "所需的道路不存在" << endl;
    }
}
