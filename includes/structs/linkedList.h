#pragma once

namespace List
{
    template <class T>
    class Node
    {
    public:
        T data;
        Node *next;

        Node(T &data);
    };

    template <class T>
    class LinkedList
    {
    public:
        LinkedList();
        LinkedList(const LinkedList<T> &other);
        LinkedList<T> &operator=(const LinkedList<T> &other);
        virtual ~LinkedList();
        void reset();
        void addNode(T &data);
        void deleteNode(T &data);
        bool isEmpty();
        T *getData(int index);
        T *getData(T &data);
        int getSize();

    protected:
        Node<T> *first;
        int size;
    };
}

#include "structs/linkedList.hpp"