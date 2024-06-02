#pragma once

namespace List
{
    template <class T>
    struct Node
    {
        T data;
        Node *next;
    };

    template <class T>
    class LinkedList
    {
    public:
        LinkedList();
        // virtual ~LinkedList();
        void reset();
        void addNode(T &data);
        void deleteNode(T &data);
        bool isEmpty();
        T* getData(int index);
        T* getData(T &data);
        int getSize();

    protected:
        Node<T> *first;
        int size;
    };
}

#include "structs/linkedList.hpp"