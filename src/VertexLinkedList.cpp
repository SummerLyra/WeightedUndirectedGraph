#include "../inc/VertexLinkedList.h"

VertexLinkedList::VertexLinkedList()
{
    first = new Vertex();
    first->next = first;
    first->prev = first;
    count = 0;
}

int VertexLinkedList::getCount()
{
    return count;
}

void VertexLinkedList::add(Vertex* v)
{
    first->next->prev = v;
    v->next = first->next;
    first->next = v;
    v->prev = first;
    count++;
}

void VertexLinkedList::remove(Vertex* v)
{
    if (v == nullptr)
    {
        return;
    }
    v->next->prev = v->prev;
    v->prev->next = v->next;
    delete v;
    count--;
}
