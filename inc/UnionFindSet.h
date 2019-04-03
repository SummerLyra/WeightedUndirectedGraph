#ifndef UNION_FIND_SET_H
#define UNION_FIND_SET_H

class UnionFindSet
{
private:
    int* parent;
    int size;

public:
    UnionFindSet(int sz);
    ~UnionFindSet();
    void setUnion(int root1, int root2);
    int find(int x);
};

#endif
