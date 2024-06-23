#pragma once

#include "structs/linkedList.h"
#include "structs/iterator.h"

/**
 * @brief A template class for a queue implemented using a linked list.
 * @tparam T The type of data stored in the queue.
 */
template <class T>
class Queue
{
public:
    Queue();
    /**
     * @brief Adds an element to the end of the queue.
     * @param data The data to be added to the queue.
     */
    void enqueue(T &data);

    /**
     * @brief Removes the element from the front of the queue.
     */
    void dequeue();

    /**
     * @brief Gets the number of elements in the queue.
     * @return The size of the queue.
     */
    int getSize();

    /**
     * @return true if the queue is empty, false otherwise.
     */
    bool isEmpty();

    /**
     * @brief Sorts the queue using the given comparison function.
     * @param compare A function pointer to a comparison function.
     */
    void sortQueue(bool (*compare)(T &a, T &b));

    /**
     * @brief Sorts the queue using the default comparison.
     */
    void sortQueue();

    /**
     * @brief Resets the queue to an empty state.
     */
    void resetQueue();

    /**
     * @return An iterator for the queue.
     */
    Iterator<T> iterate();

private:
    /**
     * @brief The linked list used to implement the queue.
     */
    LinkedList<T> queue;
};

#include "structs/queue.hpp"