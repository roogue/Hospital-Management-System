#include <stdexcept>
#include "structs/queue.h"

template <class T>
Queue<T>::Queue() : queue(){};

template <class T>
void Queue<T>::enqueue(T &data)
{
    this->queue.addNode(data);
};

template <class T>
void Queue<T>::dequeue()
{
    if (this->isEmpty())
    {
        throw std::out_of_range("Queue is empty.");
    }

    // Always delete the first node.
    this->queue.deleteNode(0);
};

template <class T>
int Queue<T>::getSize()
{
    return this->queue.getSize();
};

template <class T>
bool Queue<T>::isEmpty()
{
    return this->queue.isEmpty();
};

template <class T>
void Queue<T>::sortQueue(bool (*compare)(T &a, T &b))
{
    this->queue.sortNodes(compare);
};

template <class T>
void Queue<T>::sortQueue()
{
    this->queue.sortNodes();
};

template <class T>
void Queue<T>::resetQueue()
{
    this->queue.reset();
};

template <class T>
Iterator<T> Queue<T>::iterate()
{
    return this->queue.iterate();
};