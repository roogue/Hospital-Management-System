#include <stdexcept>
#include "structs/queue.h"

template <class T>
Queue<T>::Queue() : queue(){};

template <class T>
void Queue<T>::enqueue(T &data)
{
    this->queue.addNode(T & data);
};

template <class T>
void Queue<T>::dequeue()
{
    if(this->isEmpty()) {
        throw std::out_of_range("Queue is empty.")
    }

    // Always delete the first node
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
