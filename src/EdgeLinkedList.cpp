#include "../inc/EdgeLinkedList.h"

EdgeLinkedList::EdgeLinkedList()
{
    first = new Edge();
    first->next = first;
    first->prev = first;
    degree = 0;
}

int EdgeLinkedList::getDegree()
{
    return degree;
}

void EdgeLinkedList::add(Edge* e)
{
    first->next->prev = e;
    e->next = first->next;
    first->next = e;
    e->prev = first;
    degree++;
}

void EdgeLinkedList::remove(Edge* e)
{
    if (e == nullptr)
    {
        return;
    }
    e->next->prev = e->prev;
    e->prev->next = e->next;
    degree--;
}
