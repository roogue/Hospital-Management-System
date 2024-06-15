#pragma once

#include "structs/linkedList.h"
#include "structs/iterator.h"

template <class T>
class Queue
{
public:
    Queue();
    void enqueue(T &data);
    void dequeue();
    int getSize();
    bool isEmpty();
    void sortQueue(bool (*compare)(T &a, T &b));
    void sortQueue();
    void resetQueue();

    Iterator<T> iterate();

private:
    LinkedList<T> queue;
};

#include "structs/queue.hpp"