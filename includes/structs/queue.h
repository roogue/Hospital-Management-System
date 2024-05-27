#pragma once

#include "structs/linkedList.h"

template <class T>
class Queue {
    public:
        Queue();
        void enqueue(T &data);
        void dequeue();
        int getSize();
        bool isEmpty();

    private:
        LinkedList<T> queue;
};

#include "structs/queue.hpp"