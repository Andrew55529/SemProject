
#include "circle_list.h"


CircleList::CircleList()    //constructor
{
    first = last = nullptr;
    size = 0;
};
CircleList::CircleList(const CircleList& original)
{
    size = original.size;
    first = last = nullptr;

    size_t tmpSize = 0;

    for (Node* tmpNode = original.first; tmpNode; tmpNode = tmpNode->next, tmpSize++)
    {
        Node* newListNode = new Node;
        newListNode->idx = tmpSize;
        newListNode->data = tmpNode->data;
        newListNode->next = nullptr;
        if (first == nullptr)
            first = last = newListNode;
        else
        {
            last->next = newListNode;
            last = newListNode;
        };
    };


}
CircleList::~CircleList()   //destructor
{
    for (Node* tmp = first; tmp; tmp = first)
    {
        first = tmp->next;
        delete tmp;
    };
};
void CircleList::addCircle(Circle val2add)
{
    Node* tmp = new Node;
    tmp->idx = size;
    tmp->data = val2add;
    tmp->next = nullptr;
    if (first == nullptr)
    {
        first = last = tmp;
        size = 1;
    }
    else
    {
        last->next = tmp;
        last = tmp;
        size++;
    }
};
Circle CircleList::getElementByIdx(size_t Num) const
{
    if (Num < size)
    {
        Node* tmp;
        for (tmp = first; tmp->idx != Num; tmp = tmp->next);
        return tmp->data;
    }
    else
        exit(1); //Error
};
size_t CircleList::getSize() const
{
    return size;
};