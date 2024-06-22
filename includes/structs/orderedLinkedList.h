#pragma once

#include "structs/linkedList.h"

namespace List
{
    template <class T>
    class OrderedLinkedList : public LinkedList<T>
    {
    public:
        void addNode(T &data);
        void deleteNode(T &data);
        using LinkedList<T>::getData;
        T *getData(T &data);

    protected:
        using LinkedList<T>::first;
        using LinkedList<T>::size;
        Node<T> *getMiddle(Node<T> *first, Node<T> *last);
    };
}

#include "orderedLinkedList.hpp"