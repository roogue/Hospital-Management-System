#pragma once

#include "structs/orderedLinkedList.h"

template <class T>
class PriorityQueue : public Queue<T>
{
private:
    OrderedLinkedList<T> queue;
};

#include "structs/priorityQueue.hpp"