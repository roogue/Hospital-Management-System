#pragma once

#include "structs/node.h"
#include "structs/iterator.h"

namespace List
{
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
        template <class K>
        void searchNodes(LinkedList<T> &list, bool (*compare)(T &a, K b), K compareValue);
        void searchNodes(LinkedList<T> &list, T compareValue);
        void sortNodes(bool (*compare)(T &a, T &b));
        void sortNodes();
        void deleteNode(int index);
        void deleteNode(T &data);
        bool isEmpty();
        T *getData(int index);
        T *getData(T &data);
        int getSize();

        Iterator<T> iterate();

    protected:
        Node<T> *first;
        int size;

        void divideList(Node<T> *head, Node<T> *&newHead);
        Node<T> *mergeList(Node<T> *head, Node<T> *secondHead, bool (*compare)(T &a, T &b));
        Node<T> *mergeList(Node<T> *head, Node<T> *secondHead);
        void recSortList(Node<T> *&head, bool (*compare)(T &a, T &b));
        void recSortList(Node<T> *&head);
    };
}

#include "structs/linkedList.hpp"